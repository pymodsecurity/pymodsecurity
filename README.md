# ModSecurity Python

Python binding for ModSecurity

## Developer Guide

### Dependencies

`libmodsecurity`, `python-dev` or `python3-dev` as well as `cmake` 


### Compilation

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

### Examples

Some examples are provided in the `examples/` directory
