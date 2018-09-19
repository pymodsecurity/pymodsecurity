[![Build Status](https://travis-ci.org/actions-security/pymodsecurity.svg?branch=master)](https://travis-ci.org/actions-security/pymodsecurity)
[![PyPI version](https://img.shields.io/pypi/v/pymodsecurity.svg)](https://pypi.org/project/pymodsecurity)

# ModSecurity Python

Python binding for ModSecurity

## Developer Guide

### Dependencies

`libmodsecurity`, `python-dev` or `python3-dev` as well as `cmake` 

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
$ git clone --recurse-submodules https://github.com/actions-security/pymodsecurity.git
```

2 - Compile and install the module:
```
$ python setup.py install
```

#### Compiling with CMake

1 - Clone this repo and update the pybind11 submodule:
```bash
$ git clone --recurse-submodules https://github.com/actions-security/pymodsecurity.git
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
$ git clone --recurse-submodules https://github.com/actions-security/pymodsecurity.git
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
