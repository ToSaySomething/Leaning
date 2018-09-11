from distutils.core import setup, Extension
setup(name = "foo", version = "1.0", ext_modules = [Extension("_foo",["foo_wrap.cxx", "foo.cpp"],extra_compile_args = ['-g'])])
