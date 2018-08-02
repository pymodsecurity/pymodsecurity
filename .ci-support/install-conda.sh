#!/bin/bash

wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O $HOME/miniconda.sh

bash ~/miniconda.sh -b -p $HOME/miniconda

export PATH="$HOME/miniconda/bin:$PATH"

echo "source $HOME/miniconda/etc/profile.d/conda.sh" >> $HOME/.bashrc

conda config --add channels conda-forge 

conda install conda-devenv