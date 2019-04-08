from setuptools import setup
from distutils.core import Extension

opepy_module = Extension('_opepy',
                         sources=['opepy_wrap.cxx'],
                         runtime_library_dirs=['/home/zx/CLionProjects/ope_core/lib'],
                         include_dirs=['../cpython/inc'],
                         library_dirs=['../lib'],
                         libraries=['cpython_ope_core']
                         )

setup(name='opepy',
      version='0.1',
      author="zengxin",
      description="""轨道追逃""",
      ext_modules=[opepy_module],
      py_modules=["opepy"]
      )
