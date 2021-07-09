import sys
import argparse
import copy
from copy import deepcopy
import os
import yaml
import re
import scripts.gpu.common_with_cwrap as common_with_cwrap
import ast
import types
from scripts.gpu.model import *
import scripts.gpu.local as local
from scripts.gpu.api import legacy_dispatcher
from scripts.gpu.api.types import TensorOptionsArguments
import itertools
from scripts.gpu.code_template import CodeTemplate
from collections import defaultdict
from typing import Any, Dict, List, Optional, Set, Tuple, NamedTuple


try:
    # use faster C loader if available
    from yaml import CLoader as YamlLoader
except ImportError:
    from yaml import Loader as YamlLoader


class FileManager(object):
    def __init__(self, install_dir=None):
        self.install_dir = install_dir
        self.filenames = set()
        self.outputs_written = False
        self.undeclared_files = []

    def will_write(self, filename):
        filename = '{}/{}'.format(self.install_dir, filename)
        if self.outputs_written:
            raise Exception("'will_write' can only be called before " +
                            "the call to write_outputs, refactor so outputs are registered " +
                            "before running the generators")
        self.filenames.add(filename)

    def _write_if_changed(self, filename, contents):
        try:
            with open(filename, 'r') as f:
                old_contents = f.read()
        except IOError:
            old_contents = None
        if contents != old_contents:
            with open(filename, 'w') as f:
                f.write(contents)

    def write_outputs(self, filename):
        """Write a file containing the list of all outputs which are
        generated by this script."""
        self._write_if_changed(
            filename,
            ''.join(name + ";" for name in sorted(self.filenames)))
        self.outputs_written = True

    def write(self, filename, s, env=None):
        filename = '{}/{}'.format(self.install_dir, filename)
        if isinstance(s, CodeTemplate):
            assert env is not None
            comment = "@" + "generated by aten/src/ATen/gen.py"
            if s.filename:
                comment += " from {}".format(os.path.basename(s.filename))
            env['generated_comment'] = comment
            s = s.substitute(env)
        self._write_if_changed(filename, s)
        if filename not in self.filenames:
            self.undeclared_files.append(filename)
        else:
            self.filenames.remove(filename)

    def check_all_files_written(self):
        if len(self.undeclared_files) > 0:
            raise Exception(
                "trying to write files {} which are not ".format(self.undeclared_files) +
                "in the list of outputs this script produces. " +
                "use will_write to add them.")
        if len(self.filenames) > 0:
            raise Exception("Outputs declared with 'will_write' were " +
                            "never written: {}".format(self.filenames))

TYPE_FORMAL_GENERIC = {
    'THTensor*': 'Tensor &',
    'THByteTensor*': 'Tensor &',
    'THIndexTensor*': 'Tensor &',
    'THBoolTensor*': 'Tensor &',
    'IntArrayRefSize': 'IntArrayRef',
    'accreal': 'Scalar',
    'real': 'Scalar',
    'long': 'int64_t',
}


def format_return_type(returns):
    if len(returns) == 0:
        return 'void'
    elif len(returns) == 1:
        return returns[0]['type']
    else:
        return_types = [r['type'] for r in returns]
        return 'std::tuple<{}>'.format(','.join(return_types))


def get_simple_type(arg):
    simple_type = arg['type']
    simple_type = simple_type.replace(' &', '').replace('const ', '')
    simple_type = simple_type.replace('Generator *', 'Generator')

    opt_match = re.match(r'c10::optional<(.+)>', simple_type)
    if opt_match:
        simple_type = '{}?'.format(opt_match.group(1))
    return simple_type


def has_tensoroptions_argument(declaration):
    for argument in declaration['arguments']:
        if 'TensorOptions' == argument['dynamic_type']:
            return True
    return False


def process_schema_order_arg(schema_order_arg):
    if schema_order_arg == 'dtype':
        return 'optTypeMetaToScalarType(options.dtype_opt())'
    elif schema_order_arg == 'layout':
        return 'options.layout_opt()'
    elif schema_order_arg == 'device':
        return 'options.device_opt()'
    elif schema_order_arg == 'pin_memory':
        return 'options.pinned_memory_opt()'
    elif schema_order_arg == 'memory_format':
        return 'c10::impl::check_tensor_options_and_extract_memory_format(options, memory_format)'
    else:
        return schema_order_arg


def load_aten_declarations(path):
    with open(path, 'r') as f:
        declarations = yaml.load(f, Loader=YamlLoader)

    # enrich declarations with additional information
    selected_declarations = []
    for declaration in declarations:
        if declaration.get('deprecated'):
            continue

        for arg in declaration['arguments']:
            arg['simple_type'] = get_simple_type(arg)
        for ret in declaration['returns']:
            ret['simple_type'] = get_simple_type(ret)

        declaration['formals'] = [arg['type'] + ' ' + arg['name']
                                  for arg in declaration['arguments']]
        declaration['schema_order_formals'] = [arg['type'] + ' ' + arg['name']
                                               for arg in declaration['schema_order_arguments']]
        declaration['args'] = [arg['name'] for arg in declaration['arguments']]
        declaration['schema_order_args'] = [arg['name'] for arg in declaration['schema_order_arguments']]
        if has_tensoroptions_argument(declaration):
            declaration['schema_order_args'] = [process_schema_order_arg(arg) for arg in declaration['schema_order_args']]
        declaration['api_name'] = declaration['name']
        # NB: keep this in sync with common_with_cwrap.py
        if declaration.get('overload_name'):
            declaration['type_wrapper_name'] = "{}_{}".format(
                declaration['name'], declaration['overload_name'])
        else:
            declaration['type_wrapper_name'] = declaration['name']
        declaration['operator_name_with_overload'] = declaration['schema_string'].split('(')[0]
        declaration['unqual_operator_name_with_overload'] = declaration['operator_name_with_overload'].split('::')[1]
        declaration['return_type'] = format_return_type(declaration['returns'])

        declaration['base_name'] = declaration['name']
        declaration['type_method_definition_dispatch'] = {}
        selected_declarations.append(declaration)

    return selected_declarations


type_map = {
    'floating_point': [
        'Float',
        'Double',
        'Half',
        'BFloat16',
    ],
    'integral': [
        'Byte',
        'Char',
        'Short',
        'Int',
        'Long',
        'Bool',
    ],
    'quantized': [
        'QInt8',
        'QUInt8',
        'QInt32',
    ]
}

all_types = type_map['floating_point'] + type_map['integral'] + type_map['quantized']
type_map['all'] = all_types


all_backends = ['XPU', 'SparseXPU', 'QuantizedXPU']
default_backends = ['XPU']


def process_types_and_backends(option):
    # if specific pairs were not listed, then enumerate them
    # based on the backend and type attributes
    # if backend or type is not defined, it is assumed to be all of them
    if 'backend_types' not in option:
        backends = option.get('backends', default_backends)
        if isinstance(option.get('type_method_definition_dispatch'), dict):
            backends = option.get('type_method_definition_dispatch').keys()
        backends = set(backends)

        backend_types = {}
        for backend in backends:
            if backend in ('QuantizedXPU',):
                backend_types[backend] = type_map['quantized']
            else:
                backend_types[backend] = option.get('types', all_types)
    else:
        backend_types = option['backend_types']

    # expand type alias (integral, floating_point, all)
    def expand(types):
        ret = []
        for t in types:
            if t in type_map:
                ret.extend(type_map[t])
            else:
                assert(t in all_types)
                ret.append(t)
        return ret

    for backend in backend_types.keys():
        assert backend in all_backends, "{} {}".format(backend, option['name'])
        backend_types[backend] = set(expand(backend_types[backend]))

    # sort the result for easy reading
    for backend in backend_types.keys():
        backend_types[backend] = sorted(backend_types[backend])
    option['backend_types'] = backend_types


def handle_outputs_taken_as_arguments(options):
    new_options = []

    def is_nullable(arg):
        return (arg['type'] in {'THIntegerTensor*', 'THTensor*'} and
                arg.get('default', '') in {None, 'NULL', 'nullptr'})

    for option in options:
        for arg in option['arguments']:
            # mark arguments which can be null
            if is_nullable(arg):
                arg['is_nullable'] = True

        if any('output' in arg for arg in option['arguments']):
            allocate_option = deepcopy(option)
            # the allocating option needs to be marked
            for arg in allocate_option['arguments']:
                if 'output' in arg:
                    arg['allocate'] = True

            new_options.append(allocate_option)
        else:
            new_options.append(option)
    return new_options


def parse_dispatch(name, dispatch):
    """
    Parse a dictionary like {"CPU, XPU": "blah"}
    into {"CPU": "blah", "XPU": "blah"}
    """
    if not isinstance(dispatch, dict):
        return dispatch
    r = {}
    for old_k, v in dispatch.items():
        ks = old_k.split(',')
        for k in ks:
            k = k.strip()
            assert k not in r, "{}, {}".format(name, k)
            r[k] = v
    return r


class nested_dict(object):
    def __init__(self, base, parent):
        self.base, self.parent = base, parent

    def __getitem__(self, x):
        r = self.base.get(x)
        if r is not None:
            return r
        return self.parent[x]


# Native functions are generated and registered on the dispatcher. We register the
# function on Backend::Undefined if it does not have backend dependent dispatch.
# In this case, it will be called for all backends, but can be overwritten on a
# per backend basis.
NATIVE_DISPATCH_DECLARATION = CodeTemplate("""\
${return_type} ${native_type_method_decl}(${native_formals});
""")

OPERATOR_NAME = CodeTemplate("aten::${operator_name}")

FunctionCode = NamedTuple('FunctionCode', [
    ('definition', str),
    ('declaration', str),
])

OpRegistration = NamedTuple('OpRegistration', [
    ('operator_name', str),
    ('registration_code', str),
])

NATIVE_DISPATCH_DEFENITION_HACKY_WRAPPER = CodeTemplate("""\
${return_type} ${native_type_method_dispatch}(${declaration_formals}) {
  ${xpu_guard}
  ${lazy_reorder}
  ${return_call} decltype(c10::impl::hacky_wrapper_for_legacy_signatures<${schema_order_cpp_signature}>(
  ::c10::CompileTimeFunctionPointer<${native_order_cpp_signature}, ${Type}::${native_type_method_decl}>()))::func_ptr()(${actuals});
}
""")

NATIVE_DISPATCH_DEFINITION_GENERIC_BACKEND = CodeTemplate("""\
${return_type} ${native_type_method_dispatch}(${declaration_formals}) {
  ${xpu_guard}
  ${lazy_reorder}
  ${return_call} ${Type}::${native_type_method_decl}(${actuals});
}
""")

BACKEND_FUNCTION_REGISTRATION = CodeTemplate("""\
  m.impl("${unqual_operator_name_with_overload}",
  TORCH_FN(${Type}_impl::${native_type_method_dispatch})
  );
""")

BACKEND_UNBOXEDONLY_FUNCTION_REGISTRATION = CodeTemplate("""\
  m.impl("${unqual_operator_name_with_overload}",
  torch::dispatch(c10::DispatchKey::${Backend},
  torch::CppFunction::makeUnboxedOnly(&${Type}_impl::${native_type_method_dispatch}))
  );
""")

LAZY_REORDER_TENSORLIST = CodeTemplate("""\
auto ${name}_vec = AtenIpexTypeXPU::to_plain_if_needed(${name});
auto ${temp_name} = at::TensorList(${name}_vec);
""")

LAZY_REORDER_TENSOR = CodeTemplate("""\
${name} = AtenIpexTypeXPU::to_plain_if_needed_(${name});
""")

LAZY_REORDER_CONST_TENSOR = CodeTemplate("""\
auto ${temp_name} = AtenIpexTypeXPU::to_plain_if_needed(${name});
""")

LAZY_REORDER_OPTIONAL_TENSOR = CodeTemplate("""\
c10::optional<Tensor> ${temp_name};
if (${name}.has_value())
    ${temp_name} = c10::optional<Tensor>(AtenIpexTypeXPU::to_plain_if_needed(${name}.value()));
""")

# A schema registration specifies alias analysis for an operator, but doesn't
# actually provide an implementation.  Although our registration API allows you
# to specify all of this information at a function registration site, it's
# better to do it once at a schema registration so that we don't have to
# repeat ourselves everywhere else.
SCHEMA_REGISTRATION = CodeTemplate("""\
m.def("${unqual_schema_string}");
""")


lazy_reorder_block_list = set([
    'convolution_overrideable',
    'convolution_backward_overrideable',
    'relu',
    'relu_',
    'threshold_backward',
    'native_batch_norm',
    'native_batch_norm_backward',
    'native_layer_norm',
    'native_layer_norm_backward',
    'add_',
    'add',
    'add_out',
    'addmm',
    'addmm_',
    'mm',
    'mm_out',
    'avg_pool2d',
    'avg_pool2d_out',
    'avg_pool2d_backward',
    'avg_pool2d_backward_out',
    'adaptive_avg_pool2d',
    '_adaptive_avg_pool2d',
    'adaptive_avg_pool2d',
    '_adaptive_avg_pool2d_backward',
    'max_pool2d_with_indices',
    'max_pool2d_with_indices_out',
    'max_pool2d_with_indices_backward',
    'max_pool2d_with_indices_backward_out',
    'adaptive_max_pool2d',
    'adaptive_max_pool2d_out',
    'adaptive_max_pool2d_backward',
    'adaptive_max_pool2d_backward_out',
    'quantize_per_tensor',
    'quantize_per_channel',
    'dequantize',
    '_softmax',
    '_softmax_backward_data',
    'upsample_trilinear3d_out',
    'upsample_trilinear3d',
    'upsample_trilinear3d_backward_out',
    'upsample_trilinear3d_backward',
    'upsample_bilinear2d_out',
    'upsample_bilinear2d',
    'upsample_bilinear2d_backward_out',
    'upsample_bilinear2d_backward',
    'upsample_linear1d_out',
    'upsample_linear1d',
    'upsample_linear1d_backward_out',
    'upsample_linear1d_backward',
    'upsample_nearest3d_out',
    'upsample_nearest3d',
    'upsample_nearest3d_backward_out',
    'upsample_nearest3d_backward',
    'upsample_nearest2d_out',
    'upsample_nearest2d',
    'upsample_nearest2d_backward_out',
    'upsample_nearest2d_backward',
    'upsample_nearest1d_out',
    'upsample_nearest1d',
    'upsample_nearest1d_backward_out',
    'upsample_nearest1d_backward',
])


def format_formal(f):
    # type: (AtFormal) -> str
    return '{} {}'.format(f['type'], f['name'])


def native_get_formals(option, schema_order, use_optional_tensor):
    # type: (FunctionOption, bool, bool, bool) -> List[AtFormal]

    # TODO The use_optional_tensor argument is only needed because our at::native::xxx functions
    # still take "Tensor" instead of "optional<Tensor>", so we need CPUType, TypeDefault, ...
    # to do the same. Once at::native::xxx are converted, we can remove use_optional_tensor
    # and use the use_optional_tensor=True behavior always.

    if schema_order:
        arguments = option['schema_order_arguments']
    else:
        arguments = option['arguments']

    def native_translate_formals(argument, option):
        # if argument.get('is_nullable') and argument['type'] not in translate_map(False).keys():
        #     argument['type'] = "c10::optional<{}>".format(argument['type'])
        # elif use_optional_tensor and argument.get('is_nullable') and argument['type'] == 'Tensor':
        #     argument['type'] = "const c10::optional<Tensor>&"
        if use_optional_tensor and argument.get('is_nullable') and argument['type'] == 'const c10::optional<Tensor>&':
            argument['type'] = "Tensor"

        def translate_map(const):
            # type: (bool) -> Dict[str, str]
            return {
                'Tensor': 'const Tensor &' if const else 'Tensor &',
                'Type': 'const Type &' if const else 'Type &',
                'TensorOptions': 'const TensorOptions &' if const else 'TensorOptions &',
                'TensorList': 'TensorList',
                'Stream': 'Stream',
            }

        # Note: the 'self' trap is here only to preserve the const arg 0 for set_data.
        # I.e., the signature of the cpp implementation currently fits the code
        # generated from a misread schema, but the alias annotation is the truth.
        # TODO fix the signature of set_data's cpp impl to match correct codegen from
        # the current schema.
        # then remove this
        if argument['name'] == 'self':
            is_mutable = option['inplace']
        else:
            is_mutable = '!' in (argument['annotation'] or '')

        if is_mutable:
            argument['type'] = translate_map(False).get(argument['type'], argument['type'])
        else:
            argument['type'] = translate_map(True).get(argument['type'], argument['type'])

        return argument

    result = [native_translate_formals(argument, option) for argument in arguments]
    return result

def create_derived(backend_type_env, declarations):
    # type: (Environment, List[FunctionOption]) -> Tuple[List[str], List[str], List[OpRegistration], List[str], List[str]]
    type_object_declarations = []  # type: List[str]
    type_object_definitions = []  # type: List[str]
    op_registrations = []  # type: List[OpRegistration]

    def process_native(option):
        # type: (FunctionOption) -> None
        dispatch = option['type_method_definition_dispatch']

        # create native signature as legacy
        env = nested_dict(option, backend_type_env)

        if isinstance(dispatch, dict):
            backend = backend_type_env['Backend']
            if backend in option['backend_types']:

                native_dispatch = dispatch.get(backend)
                option['native_type_method_decl'] = native_dispatch
                if option['overload_name']:
                    option['native_type_method_dispatch'] = native_dispatch + '_' + option['overload_name']
                else:
                    option['native_type_method_dispatch'] = native_dispatch
                # option['device_init'] = gen_device_init(option, backend_type_env)
                type_object_declarations.append(
                    NATIVE_DISPATCH_DECLARATION.substitute(env))

                func = FunctionSchema.parse(option['schema_string'])
                self_args = (a for a in func.arguments if a.name == "self")

                # There is precedence for which argument we use to do
                # device guard.  This describes the precedence order.
                candidate_args = itertools.chain(self_args, func.out_arguments, func.arguments)

                # Only tensor like arguments are eligible
                device_of = next((f'{a.name}' for a in candidate_args if a.type.is_tensor_like()), None)

                if option['use_c10_dispatcher'] == 'full':
                    # Omit the device guard entirely in these cases
                    def_backend = NATIVE_DISPATCH_DEFINITION_GENERIC_BACKEND

                    with local.parametrize(use_c10_dispatcher=UseC10Dispatcher.full):
                        args = legacy_dispatcher.arguments(func)
                elif option['use_c10_dispatcher'] == 'with_codegenerated_unboxing_wrapper':
                    def_backend = NATIVE_DISPATCH_DEFINITION_GENERIC_BACKEND

                    with local.parametrize(use_c10_dispatcher=UseC10Dispatcher.with_codegenerated_unboxing_wrapper):
                        args = legacy_dispatcher.arguments(func)
                    device_guard = """const DeviceGuard device_guard(options.device());"""
                else:
                    assert option['use_c10_dispatcher'] == 'hacky_wrapper_for_legacy_signatures'
                    def_backend = NATIVE_DISPATCH_DEFENITION_HACKY_WRAPPER

                    with local.parametrize(use_c10_dispatcher=UseC10Dispatcher.full):
                        args = legacy_dispatcher.arguments(func)
                    device_guard = """const DeviceGuard device_guard(device_or_default(device));"""

                has_tensor_options = any(isinstance(a.argument, TensorOptionsArguments) for a in args)

                # works just as well.
                if option['device_guard'] and has_tensor_options:
                    option['xpu_guard'] = device_guard
                elif option['device_guard'] and device_of is not None:
                    option['xpu_guard'] = f"""const OptionalDeviceGuard device_guard(device_of({device_of}));"""
                else:
                    option['xpu_guard'] = """// DeviceGuard omitted"""

                type_object_definitions.append(def_backend.substitute(env))

                if native_dispatch:
                    # See NOTE[UnboxedOnly]
                    if option['use_c10_dispatcher'] == 'full':
                        op_registrations.append(OpRegistration(
                            operator_name=OPERATOR_NAME.substitute(option),
                            registration_code=BACKEND_FUNCTION_REGISTRATION.substitute(env)))
                    elif option['use_c10_dispatcher'] == 'with_codegenerated_unboxing_wrapper':
                        op_registrations.append(OpRegistration(
                            operator_name=OPERATOR_NAME.substitute(option),
                            registration_code=BACKEND_UNBOXEDONLY_FUNCTION_REGISTRATION.substitute(env)))
                    else:
                        assert option['use_c10_dispatcher'] == 'hacky_wrapper_for_legacy_signatures'
                        op_registrations.append(OpRegistration(
                            operator_name=OPERATOR_NAME.substitute(option),
                            registration_code=BACKEND_FUNCTION_REGISTRATION.substitute(env)))

    for declaration in declarations:
        for option in declaration['options']:
            if not option.get('skip', False):
                if option['mode'] == 'NN' and option.get('cimpls') is None:
                    continue
                if option['mode'] != 'native':
                    # process_legacy_th_option(option)
                    pass
                else:
                    process_native(option)
    return (type_object_declarations, type_object_definitions, op_registrations)


def backend_to_devicetype(backend):
    if backend == 'QuantizedCPU':
        return 'CPU'
    elif backend == 'QuantizedXPU':
        return 'XPU'
    elif backend == 'SparseXPU':
        return 'XPU'
    return backend


def extract_schema(path):
    schemas_string = []
    errors = []
    for line in open(path, 'r'):
        line = line.strip()
        m = re.match(r'\s*([^\s].*);\s*//\s*([^\s].*)', line)
        if not m:
            continue
        if m:
            schema = m.group(2)
            if schema.startswith('{'):
                signature = ast.literal_eval(schema)
                schemas_string.append(signature['schema'])
            else:
                schemas_string.append(schema)
        else:
            print("Please add schema for the Op >>> \"", line, "\"")

    return schemas_string, errors


def get_lazy_reorder(schema_name, argument):
    cptype = argument['dynamic_type']
    change_dict = {'name': argument['name'], 'temp_name': '_' + argument['name']}
    if schema_name not in lazy_reorder_block_list:
        if cptype == 'TensorList':
            return LAZY_REORDER_TENSORLIST.substitute(change_dict), change_dict['temp_name']
        elif cptype == 'Tensor':
            if argument['type'] == 'const c10::optional<Tensor>&':
                return LAZY_REORDER_OPTIONAL_TENSOR.substitute(change_dict), change_dict['temp_name']
                option['actuals'][i] = change_dict['temp_name']
            elif not argument['type'].startswith('const'):
                return LAZY_REORDER_TENSOR.substitute(change_dict), change_dict['name']
            else:
                return LAZY_REORDER_CONST_TENSOR.substitute(change_dict), change_dict['temp_name']
    return '', change_dict['name']


def preprocess_decl(declarations):
    for declaration in declarations:
        common_with_cwrap.set_declaration_defaults(declaration)
        declaration['options'] = [deepcopy(o) for o in declaration['options']]
        declaration['options'] = common_with_cwrap.filter_unique_options(
            declaration['options'],
            allow_kwarg=False,
            type_to_signature=TYPE_FORMAL_GENERIC,
            remove_self=True)

        common_with_cwrap.sort_by_number_of_args(declaration)

        for option in declaration['options']:
            process_types_and_backends(option)

            option['return_call'] = 'return ' if option['return_type'] != 'void' else ''

            if declaration['use_c10_dispatcher'] == 'full':
                option['declaration_formals'] = declaration['schema_order_formals']
                lazy_reorder = [get_lazy_reorder(option['name'], argument) for argument in option['arguments']]
                option['lazy_reorder'] = [elem[0] for elem in lazy_reorder]
                option['actuals'] = [elem[1] for elem in lazy_reorder]
                native_formals = native_get_formals(option, False, True)
                option['native_formals'] = [format_formal(f) for f in native_formals]
                native_order_cpp_signature = '{} ( {} )' .format(option['return_type'], ', '.join([ f['type'] for f in native_formals ]))
                option['native_order_cpp_signature'] = native_order_cpp_signature
            elif declaration['use_c10_dispatcher'] == 'with_codegenerated_unboxing_wrapper':
                option['declaration_formals'] = declaration['formals']
                lazy_reorder = [get_lazy_reorder(option['name'], argument) for argument in option['arguments']]
                option['lazy_reorder'] = [elem[0] for elem in lazy_reorder]
                option['actuals'] = [elem[1] for elem in lazy_reorder]
                native_formals = native_get_formals(option, False, True)
                option['native_formals'] = [format_formal(f) for f in native_formals]
                native_order_cpp_signature = '{} ( {} )' .format(option['return_type'], ', '.join([ f['type'] for f in native_formals ]))
                option['native_order_cpp_signature'] = native_order_cpp_signature
            else:
                assert declaration['use_c10_dispatcher'] == 'hacky_wrapper_for_legacy_signatures'
                option['declaration_formals'] = declaration['schema_order_formals']
                lazy_reorder = [get_lazy_reorder(option['name'], argument) for argument in option['schema_order_arguments']]
                option['lazy_reorder'] = [elem[0] for elem in lazy_reorder]
                option['actuals'] = [elem[1] for elem in lazy_reorder]
                native_formals = native_get_formals(option, False, True)
                option['native_formals'] = [format_formal(f) for f in native_formals]
                native_order_cpp_signature = '{} ( {} )' .format(option['return_type'], ', '.join([ f['type'] for f in native_formals ]))
                option['native_order_cpp_signature'] = native_order_cpp_signature

        declaration['options'] = handle_outputs_taken_as_arguments(
            declaration['options'])
    return declarations


def process_dpcpp_declarations(declarations, script_path):
    dpcpp_decls = []
    schemas, errors = extract_schema(script_path + '/gpu/DPCPPGPUType.h')
    assert len(errors) == 0, 'parse error'
    for declaration in declarations:
        if declaration['schema_string'] in schemas:
            declaration['type_method_definition_dispatch']['XPU'] = declaration['name']
            schemas.remove(declaration['schema_string'])

    if len(schemas) != 0:
        raise RuntimeError("Those schemas are not found in pytorch. {}".format(schemas))

    schemas, errors = extract_schema(script_path + '/gpu/QUANTIZEDDPCPPGPUType.h')
    assert len(errors) == 0, 'parse error'
    for declaration in declarations:
        if declaration['schema_string'] in schemas:
            declaration['type_method_definition_dispatch']['QuantizedXPU'] = declaration['name']
            schemas.remove(declaration['schema_string'])

    if len(schemas) != 0:
        raise RuntimeError("Those schemas are not found in pytorch. {}".format(schemas))

    schemas, errors = extract_schema(script_path + '/gpu/SPARSEDPCPPGPUType.h')
    assert len(errors) == 0, 'parse error'
    for declaration in declarations:
        if declaration['schema_string'] in schemas:
            declaration['type_method_definition_dispatch']['SparseXPU'] = declaration['name']
            schemas.remove(declaration['schema_string'])

    if len(schemas) != 0:
        raise RuntimeError("Those schemas are not found in pytorch. {}".format(schemas))

    for declaration in declarations:
        if len(declaration['type_method_definition_dispatch']) != 0:
            dpcpp_decls.append(declaration)

    return preprocess_decl(dpcpp_decls)


def add_op_registrations(per_type_registrations, op_registrations):
    for op_registration in op_registrations:
        registration = op_registration.registration_code

        per_type_registrations.append(registration)



def gen_code(aten_path, out, script_path, selected_op_list=None):
    full_aten_decls = load_aten_declarations(aten_path)
    dpcpp_decls = process_dpcpp_declarations(full_aten_decls, script_path)

    TEMPLATE_PATH = script_path + "/templates"
    TYPE_DERIVED_CPP = CodeTemplate.from_file(TEMPLATE_PATH + "/TypeDerived.cpp")
    TYPE_DERIVED_H = CodeTemplate.from_file(TEMPLATE_PATH + "/TypeDerived.h")

    backends = ['XPU', 'QuantizedXPU', 'SparseXPU']
    for backend in backends:
        env = {}
        env['Type'] = "AtenIpexType{}".format(backend)
        env['DeviceType'] = backend_to_devicetype(backend)
        env['Backend'] = backend

        env['command'] = 'gen_code.py ' + ' '.join(sys.argv)

        declarations, definitions, op_registrations = create_derived(env, dpcpp_decls)

        env['type_derived_method_definitions'] = definitions
        env['type_derived_method_declarations'] = declarations
        env['wrapper_registrations'] = []
        add_op_registrations(env['wrapper_registrations'], op_registrations)
        output = TYPE_DERIVED_CPP.substitute(env)
        file_manager = FileManager(out)
        file_manager.write('{}.cpp'.format(env['Type']), output)
        file_manager.write('{}.h'.format(env['Type']), TYPE_DERIVED_H, env)


def main():
    parser = argparse.ArgumentParser(
        description='Generate aten code dispatch register script')
    parser.add_argument('--declarations-path',
                        help='path to Declarations.yaml')
    parser.add_argument('--out',
                        help='path to output directory')
    parser.add_argument('--source-path',
                        help='path to source directory for ATen',
                        default='.')
    args = parser.parse_args()
    gen_code(args.declarations_path, args.out, args.source_path + '/scripts')


if __name__ == '__main__':
    main()
