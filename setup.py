# Based on https://raw.githubusercontent.com/pybind/python_example/master/setup.py

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import glob

__version__ = '0.0.4'


class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)

ext_modules = [
    Extension(
        'ModSecurity',
        glob.glob('src/*.cpp'),
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
        libraries=[
            'modsecurity',
        ],
        language='c++'
    ),
]

# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.

    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')

class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': [],
        'unix': [
            '-lmodsecurity',
        ],
    }

    link_opts = {
        'unix': [
            '-lmodsecurity',
        ],
    }

    if not sys.platform == 'linux' and not sys.platform == 'unix':
        raise RuntimeError('Platform is {} not supported'.format(sys.platform))

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
        opts.append(cpp_flag(self.compiler))
        if has_flag(self.compiler, '-fvisibility=hidden'):
            opts.append('-fvisibility=hidden')
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)

setup(
    name='pymodsecurity',
    version=__version__,
    author='Davysson0, GustavoKatel',
    author_email='davysson0@gmail.com, gbritosampaio@gmail.com',
    url='https://github.com/actions-security/pymodsecurity',
    description='Python bindings for ModSecurity',
    long_description='',
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.2'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Operating System :: POSIX :: Linux",
    ],
)
