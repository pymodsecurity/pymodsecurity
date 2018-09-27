#!/bin/bash

CFLAGS="-I$PREFIX/include -L$PREFIX/lib" ${PYTHON} setup.py install;