FROM owasp/modsecurity:3.0.4

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y python3 python3-pip
ENV DEBIAN_FRONTEND=dialog

ENV LD_LIBRARY_PATH /usr/local/modsecurity/lib:/usr/local/lib:${LD_LIBRARY_PATH}
ENV CPLUS_INCLUDE_PATH /usr/local/modsecurity/include:${CPLUS_INCLUDE_PATH}

RUN ln -s /usr/local/modsecurity/lib/libmodsecurity.so /usr/lib/libmodsecurity.so
RUN pip3 install setuptools pybind11 pytest pytest-mock
# RUN cd pymodsecurity && python3 setup.py install