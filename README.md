[![Build Status](https://travis-ci.com/pymodsecurity/pymodsecurity.svg?branch=master)](https://travis-ci.com/pymodsecurity/pymodsecurity)
[![PyPI version](https://img.shields.io/pypi/v/pymodsecurity.svg)](https://pypi.org/project/pymodsecurity)
[![conda-forge version](https://img.shields.io/conda/vn/conda-forge/pymodsecurity.svg)](https://anaconda.org/conda-forge/pymodsecurity)
[![PyPI - Python Version](https://img.shields.io/pypi/pyversions/pymodsecurity.svg)](https://pypi.org/project/pymodsecurity)
[![modsecurity version](https://img.shields.io/badge/modsecurity-3.0.10-blue.svg)](https://github.com/SpiderLabs/ModSecurity/releases)

# ModSecurity Python

Python binding for ModSecurity

* Note: This is an alpha version. Crashes are expected. Comments and suggestions are welcome

## Developer Guide

### Dependencies

`libmodsecurity`, `python-dev` or `python3-dev` as well as `cmake`

#### Bindings and ModSecurity Version Reference

| pymodsecurity 	| ModSecurity 	|
|---------------	|-------------	|
| v0.0.1 	| v3.0.2 	|
| v0.0.2 	| v3.0.2 	|
| v0.0.3 	| v3.0.2 	|
| v0.0.4 	| v3.0.3 	|
| v0.0.5 	| v3.0.3 	|
| v0.1.0 	| v3.0.10 	|

Please refer to [ModSecurity Releases](https://github.com/SpiderLabs/ModSecurity/releases) and [ModSecurity Installation Guide](https://github.com/SpiderLabs/ModSecurity/wiki)

### Packages

Pymodsecurity is available as an python package, to install it simply run:
```
$ pip install pymodsecurity
```

### Building from source

There are multiple ways to build pymodsecurity from source, you can either compile the module manually with CMake, install using setup.py or build a conda package using the recipe. Below are steps for each way.

#### Installing via setup.py

1 - Clone this repo and update the pybind11 submodule:
```bash
$ git clone --recurse-submodules https://github.com/pymodsecurity/pymodsecurity.git
```

2 - Compile and install the module:
```
$ python setup.py install
```

#### Compiling with CMake

1 - Clone this repo and update the pybind11 submodule:
```bash
$ git clone --recurse-submodules https://github.com/pymodsecurity/pymodsecurity.git
```

2 - Create a build directory:
```bash
$ mkdir build && cd build
```

3 - Run CMake and make:
```bash
$ cmake .. && make
```
4 - Add the shared library to python's path

#### Building and installing with conda

If you're using conda, you can build the package locally using conda-build (you will need to install `conda-build`).

1 - Clone this repo and update the pybind11 submodule:
```bash
$ git clone --recurse-submodules https://github.com/pymodsecurity/pymodsecurity.git
```

2 - Run conda-build:
```
$ conda-build recipe
```

3 - Install the package:
```
$ conda install --use-local pymodsecurity
```

### Examples

Some examples are provided in the `examples/` directory. More are coming soon.

#### Real world examples

[django middleware](https://github.com/pymodsecurity/django-pymodsecurity)
