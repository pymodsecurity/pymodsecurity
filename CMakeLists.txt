cmake_minimum_required(VERSION 2.8.12)
project(modsecurity)

set(LIBRARIES modsecurity)
set(INCLUDES /usr/local/modsecurity/include/)

add_subdirectory(pybind11)
pybind11_add_module(ModSecurity src/modsecurity.cpp src/transaction.cpp src/rule.cpp src/rules.cpp src/intervention.cpp)
include_directories(${INCLUDES})
target_link_libraries(ModSecurity PRIVATE ${LIBRARIES})