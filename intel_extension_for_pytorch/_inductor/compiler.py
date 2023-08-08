import torch
from torch._subclasses import FakeTensor
from torch.utils._mode_utils import no_dispatch
import builtins
import warnings
from typing import Callable, Dict, Optional, Union, List


_compiler_backend = "torchscript"


def _get_compiler_backend():
    return _compiler_backend


def _set_compiler_backend(backend="torchscript"):
    global _compiler_backend
    _compiler_backend = backend


def compile(
    model: torch.fx.GraphModule,
    example_inputs: List[torch.Tensor],
    mode: Union[str, None] = None,
    options: Optional[Dict[str, Union[str, builtins.int, builtins.bool]]] = None,
) -> Callable:
    def defake(x):
        if not isinstance(x, FakeTensor):
            return x
        if x._has_symbolic_sizes_strides:
            size = [
                s.node.shape_env.size_hint(s.node.expr)
                if isinstance(s, torch.SymInt)
                else s
                for s in x.size()
            ]
            stride = [
                s.node.shape_env.size_hint(s.node.expr)
                if isinstance(s, torch.SymInt)
                else s
                for s in x.stride()
            ]
        else:
            size = x.size()
            stride = x.stride()
        y = torch.empty_strided(
            size,
            stride,
            dtype=x.dtype,
            device=x.device,
            requires_grad=x.requires_grad,
        )
        y.zero_()
        return y

    if _get_compiler_backend() == "inductor":
        from .compile_fx import compile_fx

        return compile_fx(model, example_inputs, mode, options)

    try:
        with no_dispatch():
            real_inputs = list(map(defake, example_inputs))
            with torch.no_grad():
                traced_model = torch.jit.trace(model.eval(), real_inputs)
                traced_model = torch.jit.freeze(traced_model)
            return traced_model
    except Exception:
        warnings.warn("JIT trace failed during the IPEX compile process.")
        return model