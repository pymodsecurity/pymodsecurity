#include <pybind11/pybind11.h>
#include <modsecurity/variable_value.h>

namespace py = pybind11;

using modsecurity::VariableValue;

void init_variable_value(py::module &m)
{
    py::class_<VariableValue>(m, "VariableValue")
        .def(py::init<>())
        .def(py::init<const std::string*>())
        .def(py::init<const std::string*, const std::string*>())
        .def(py::init<const std::string*, const std::string*, const std::string*>())
        // .def(py::init<std::shared_ptr<std::string>>())
        // .def(py::init<std::shared_ptr<std::string>, const std::string*>())
        .def(py::init<const VariableValue*>())
        .def_readwrite("m_key", &VariableValue::m_key)
        .def_readwrite("m_value", &VariableValue::m_value)
        .def_readwrite("m_col", &VariableValue::m_col)
        // .def_readwrite("m_keyWithCollection", &VariableValue::m_keyWithCollection)
        // .def_readwrite("m_orign", &VariableValue::m_orign)
        ;
}