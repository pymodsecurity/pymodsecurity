#!/bin/bash

wget -O miniconda.sh https://repo.continuum.io/miniconda/Miniconda3-$CONDA_VERSION.sh

bash miniconda.sh -b -p $HOME/miniconda

export PATH="$HOME/miniconda/bin:$PATH"

conda config --set always_yes yes --set changeps1 no

conda config --add channels conda-forge

conda update -q conda

conda install -q conda-build conda-devenv