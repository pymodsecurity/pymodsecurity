#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <modsecurity/transaction.h>
#include <modsecurity/anchored_variable.h>

namespace py = pybind11;

using modsecurity::AnchoredVariable;
using modsecurity::Transaction;

void init_anchored_variable(py::module &m)
{
    py::class_<AnchoredVariable>(m, "AnchoredVariable")
        .def(py::init<Transaction *, std::string>())
        .def("unset", &AnchoredVariable::unset)
        .def("set", (void (AnchoredVariable::*) (const std::string &, size_t)) &AnchoredVariable::set)
        .def("set", (void (AnchoredVariable::*) (const std::string &, size_t, size_t)) &AnchoredVariable::set)
        .def("append", (void (AnchoredVariable::*) (const std::string &, size_t, bool)) &AnchoredVariable::append)
        .def("append", (void (AnchoredVariable::*) (const std::string &, size_t, bool, int)) &AnchoredVariable::append)
        // .def("evaluate", py::overload_cast<std::vector<const VariableValue *> *>(&AnchoredVariable::evaluate))
        .def("evaluate", (std::string * (AnchoredVariable::*) ()) &AnchoredVariable::evaluate)
        // .def("resolveFirst", &AnchoredVariable::resolveFirst)
        .def_readwrite("m_transaction", &AnchoredVariable::m_transaction)
        .def_readwrite("m_offset", &AnchoredVariable::m_offset)
        .def_readwrite("m_name", &AnchoredVariable::m_name)
        .def_readwrite("m_value", &AnchoredVariable::m_value);
}