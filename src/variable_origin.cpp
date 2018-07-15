#include <pybind11/pybind11.h>
#include <modsecurity/variable_origin.h>

namespace py = pybind11;

using modsecurity::VariableOrigin;

void init_variable_origin(py::module &m)
{
    py::class_<VariableOrigin>(m, "VariableOrigin")
        .def(py::init<>())
        .def("toText", &VariableOrigin::toText)
        .def_readwrite("m_length", &VariableOrigin::m_length)
        .def_readwrite("m_offset", &VariableOrigin::m_offset)
        ;
}