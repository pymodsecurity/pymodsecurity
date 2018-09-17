#!/bin/bash

sudo apt-get update

sudo apt-get install -y g++ flex bison curl doxygen libyajl-dev libgeoip-dev libtool dh-autoreconf libcurl4-gnutls-dev libxml2 libpcre++-dev libxml2-dev git cmake libtool automake autoconf m4 pkg-config || exit 1

wget -O modsecurity.tar.gz https://github.com/SpiderLabs/ModSecurity/releases/download/v$MODSECURITY_VERSION/modsecurity-v$MODSECURITY_VERSION.tar.gz || exit 1

tar xvf modsecurity.tar.gz || exit 1

pushd modsecurity-v$MODSECURITY_VERSION || exit 1

./build.sh || exit 1

./configure --prefix=/usr && make -j 2 && sudo make install && sudo ldconfig || exit 1

popd || exit 1