#include <pybind11/pybind11.h>
#include <modsecurity/variable_value.h>
#include <modsecurity/variable_origin.h>
#include <memory>

namespace py = pybind11;

using modsecurity::VariableValue;
using modsecurity::VariableOrigin;

void init_variable_value(py::module &m)
{
    py::class_<VariableValue>(m, "VariableValue")
        .def(py::init<>())
        .def(py::init<const std::string *>())
        .def(py::init<const std::string *, const std::string *>())
        .def(py::init<const std::string *, const std::string *, const std::string *>())
        .def(py::init<const VariableValue *>())
        .def_readwrite("m_key", &VariableValue::m_key)
        .def_readwrite("m_value", &VariableValue::m_value)
        .def_readwrite("m_col", &VariableValue::m_col)
        .def_property("m_keyWithCollection", [](const VariableValue& v) {
            return *v.m_keyWithCollection.get();
        }, [](VariableValue& v, const std::string m_keyWithCollection) {
            v.m_keyWithCollection = std::make_shared<std::string>(m_keyWithCollection);
        }, py::return_value_policy::copy)
        // .def_readwrite("m_orign", &VariableValue::m_orign)
        ;
}