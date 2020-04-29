#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <modsecurity/variable_value.h>
#include <modsecurity/variable_origin.h>
#include <memory>

namespace py = pybind11;

using modsecurity::VariableValue;
using modsecurity::VariableOrigin;

void init_variable_value(py::module &m)
{
    py::class_<VariableValue>(m, "VariableValue")
        .def(py::init<const std::string *, const std::string *>(), py::arg("value") = nullptr)
        .def(py::init<const std::string *, const std::string *, const std::string *>())
        .def(py::init<const VariableValue *>())
        .def("getKey", &VariableValue::getKey)
        .def("getKeyWithCollection", &VariableValue::getKeyWithCollection)
        .def("getCollection", &VariableValue::getCollection)
        .def("getValue", &VariableValue::getValue)
        .def("setValue", &VariableValue::setValue)
        // .def("addOrigin", &Variable::addOrigin)
        .def("getOrigin", &VariableValue::getOrigin)
        ;
}