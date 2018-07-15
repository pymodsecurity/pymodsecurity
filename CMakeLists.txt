cmake_minimum_required(VERSION 2.8.12)
project(modsecurity)

set(LIBRARIES modsecurity)
set(INCLUDES /usr/local/modsecurity/include/)

add_subdirectory(pybind11)
pybind11_add_module(ModSecurity src/main.cpp src/action.cpp src/anchored_set_variable.cpp src/anchored_variable.cpp src/audit_log.cpp src/collection.cpp src/collections.cpp src/debug_log.cpp src/intervention.cpp src/modsecurity.cpp src/rule_message.cpp src/rule.cpp src/rules_exceptions.cpp src/rules_properties.cpp src/rules.cpp src/transaction.cpp src/variable_origin.cpp src/variable_value.cpp)
include_directories(${INCLUDES})
target_link_libraries(ModSecurity PRIVATE ${LIBRARIES})