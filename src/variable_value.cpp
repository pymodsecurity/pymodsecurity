#include <pybind11/pybind11.h>
#include <modsecurity/collection/variable.h>

namespace py = pybind11;

using modsecurity::collection::Variable;

void init_variable_value(py::module &m)
{
    // py::class_<Variable>(m, "VariableValue")
        // .def(py::init<>())
        // .def(py::init<const std::string*>())
        // .def(py::init<const std::string*, const std::string*>())
        // .def(py::init<const std::string*, const std::string*, const std::string*>())
        // .def(py::init<std::shared_ptr<std::string>>())
        // .def(py::init<std::shared_ptr<std::string>, const std::string*>())
        // .def(py::init<const Variable>())
        // .def_readwrite("m_key", &Variable::m_key)
        // .def_readwrite("m_value", &Variable::m_value)
        // .def_readwrite("m_col", &Variable::m_col)
        // .def_readwrite("m_keyWithCollection", &Variable::m_keyWithCollection)
        // .def_readwrite("m_orign", &Variable::m_orign)
        // ;
}