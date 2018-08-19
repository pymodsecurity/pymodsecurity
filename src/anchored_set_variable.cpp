#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <modsecurity/transaction.h>
#include <modsecurity/variable_value.h>
#include <modsecurity/anchored_set_variable.h>

namespace py = pybind11;

using modsecurity::AnchoredSetVariable;
using modsecurity::VariableValue;
using modsecurity::Transaction;

void init_anchored_set_variable(py::module &m)
{
    py::class_<AnchoredSetVariable>(m, "AnchoredSetVariable")
        .def(py::init<Transaction *, std::string>())
        .def("unset", &AnchoredSetVariable::unset)
        .def("set", (void (AnchoredSetVariable::*) (const std::string &, const std::string &, size_t)) &AnchoredSetVariable::set)
        .def("set", (void (AnchoredSetVariable::*) (const std::string &, const std::string &, size_t, size_t)) &AnchoredSetVariable::set)
        // .def("setCopy", &AnchoredSetVariable::setCopy)
        // .def("resolve", py::overload_cast<std::vector<const VariableValue *> *>(&AnchoredSetVariable::resolve))
        // .def("resolve", py::overload_cast<const std::string &, std::vector<const VariableValue *> *>(&AnchoredSetVariable::resolve))
        // .def("resolveRegularExpression", &AnchoredSetVariable::resolveRegularExpression)
        // .def("resolveFirst", &AnchoredSetVariable::resolveFirst)
        .def_readwrite("m_transaction", &AnchoredSetVariable::m_transaction)
        .def_readwrite("m_name", &AnchoredSetVariable::m_name);
}