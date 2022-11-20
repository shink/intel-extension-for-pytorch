import intel_extension_for_pytorch._C


# utils function to define trapper base object
def _trap_module(name: str) -> type:
    def init_err(self):
        class_name = self.__class__.__name__
        raise RuntimeError(
            "Tried to instantiate trap base class {}".format(class_name))
    return type(name, (object,), {"__init__": init_err})


def _register_trap(module: str):
    if not hasattr(intel_extension_for_pytorch._C, module):
        intel_extension_for_pytorch._C.__dict__[module] = _trap_module(module)


_register_trap('ShortStorageBase')
_register_trap('CharStorageBase')
_register_trap('IntStorageBase')
_register_trap('LongStorageBase')
_register_trap('BoolStorageBase')
_register_trap('HalfStorageBase')
_register_trap('DoubleStorageBase')
_register_trap('FloatStorageBase')
_register_trap('BFloat16StorageBase')
_register_trap('QUInt8StorageBase')
_register_trap('QInt8StorageBase')


_register_trap('_XPUStreamBase')
_register_trap('_XPUEventBase')
