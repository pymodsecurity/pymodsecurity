cmake_minimum_required(VERSION 3.1)
project(modsecurity)

set(PYBIND11_CPP_STANDARD -std=c++11)


# cmake .. -DMODSEC_PATH="/path/to/modsec/install/directory"
# set(MODSEC_PATH /opt/ModSecurity/)

if (EXISTS "${MODSEC_PATH}")
    set(LIB_DIR "${MODSEC_PATH}/lib")
    set(INC_DIR "${MODSEC_PATH}/include")

    FIND_LIBRARY(MODSEC_LIBRARY modsecurity ${LIB_DIR})
else()
    set(LIB_DIR "")
    set(INC_DIR "")

    set(MODSEC_LIBRARY modsecurity)
endif()


# Conda support
set(INCLUDES ${INCLUDES} $ENV{CONDA_PREFIX}/include)
link_directories($ENV{CONDA_PREFIX}/lib)

add_subdirectory(pybind11)
pybind11_add_module(ModSecurity src/main.cpp src/action.cpp src/anchored_set_variable.cpp src/anchored_variable.cpp src/audit_log.cpp src/collection.cpp src/collections.cpp src/debug_log.cpp src/intervention.cpp src/transaction.cpp src/modsecurity.cpp src/rule_message.cpp src/rule.cpp src/rules_exceptions.cpp src/rules_properties.cpp src/rules.cpp src/variable_origin.cpp src/variable_value.cpp)
include_directories(${INCLUDES} ${INC_DIR})
target_link_libraries(ModSecurity PRIVATE ${MODSEC_LIBRARY})