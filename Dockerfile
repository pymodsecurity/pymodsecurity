FROM nginx:1
MAINTAINER Chaim Sanders chaim.sanders@gmail.com

ENV LD_LIBRARY_PATH /usr/local/modsecurity/lib:/usr/local/lib:${LD_LIBRARY_PATH} 
ENV CPLUS_INCLUDE_PATH /usr/local/modsecurity/include:${CPLUS_INCLUDE_PATH} 

RUN apt-get update && apt-get install -y git cmake libtool automake g++ libxml2-dev libcurl4-gnutls-dev doxygen liblua5.3-dev libpcre++-dev wget libgeoip-dev make python3 python3-pip
RUN wget https://github.com/LMDB/lmdb/archive/LMDB_0.9.23.tar.gz
RUN tar -xvzf LMDB_0.9.23.tar.gz
RUN cd lmdb-LMDB_0.9.23/libraries/liblmdb && \
    make && \
    make install
RUN wget https://github.com/lloyd/yajl/archive/2.1.0.tar.gz
RUN tar -xvzf 2.1.0.tar.gz
RUN cd yajl-2.1.0/ && \
    ./configure && \
    make && \
    make install

RUN wget https://github.com/ssdeep-project/ssdeep/releases/download/release-2.14.1/ssdeep-2.14.1.tar.gz
RUN tar -xvzf ssdeep-2.14.1.tar.gz
RUN cd ssdeep-2.14.1 && \
       ./configure && \
       make && \
       make install

RUN wget https://github.com/SpiderLabs/ModSecurity/releases/download/v3.0.3/modsecurity-v3.0.3.tar.gz
RUN tar -xvzf modsecurity-v3.0.3.tar.gz
RUN mv modsecurity-v3.0.3 ModSecurity


RUN cd ModSecurity && \
    ./configure && \
    make -j 10 && \
    make install

RUN ln -s /usr/local/modsecurity/lib/libmodsecurity.so /usr/lib/libmodsecurity.so
RUN git clone --recurse-submodules https://github.com/actions-security/pymodsecurity.git
RUN pip3 install setuptools pybind11
RUN cd pymodsecurity && \
    python3 setup.py install
EXPOSE 80
EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
