[![Build Status](https://travis-ci.org/actions-security/pymodsecurity.svg?branch=master)](https://travis-ci.org/actions-security/pymodsecurity)
[![PyPI version](https://img.shields.io/pypi/v/pymodsecurity.svg)](https://pypi.org/project/pymodsecurity)

# ModSecurity Python

Python binding for ModSecurity

## Developer Guide

### Dependencies

`libmodsecurity`, `python-dev` or `python3-dev` as well as `cmake` 


### Compiling with CMake

The module's shared library can be built through CMake:

1 - Clone this repo
2 - Update the pybind11 submodule

```bash
$ git submodule init && git submodule update
```

3 - Create a build directory

```bash
$ mkdir build && cd build
```

4 - Run cmake and make

```bash
$ cmake .. && make
```
5 - Add the shared library to python's path

### Building and installing with conda

If you're using conda, you can build the package locally using conda-build:

1 - Clone this repo
2 - Update the pybind11 submodule

```bash
$ git submodule init && git submodule update
```

3 - Run conda-build

```
$ conda-build recipe
```

4 - Install

```
$ conda install --use-local pymodsecurity
```

### Examples

Some examples are provided in the `examples/` directory
