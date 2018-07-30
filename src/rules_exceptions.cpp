#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <modsecurity/rules_exceptions.h>
#include <modsecurity/rule.h>
#include <modsecurity/transaction.h>
#include <modsecurity/variable_value.h>

namespace py = pybind11;

using modsecurity::Rule;
using modsecurity::RulesExceptions;
using modsecurity::Transaction;
using modsecurity::VariableValue;

void init_rules_exceptions(py::module &m)
{
    py::class_<RulesExceptions>(m, "RulesExceptions")
        .def(py::init<>())
        .def("load", &RulesExceptions::load)
        .def("addRange", &RulesExceptions::addRange)
        .def("addNumber", &RulesExceptions::addNumber)
        .def("contains", &RulesExceptions::contains)
        .def("merge", &RulesExceptions::merge)
        .def("loadRemoveRuleByMsg", &RulesExceptions::loadRemoveRuleByMsg)
        .def("loadRemoveRuleByTag", &RulesExceptions::loadRemoveRuleByTag)
        // .def("loadUpdateTargetByMsg", &RulesExceptions::loadUpdateTargetByMsg)
        // .def("loadUpdateTargetByTag", &RulesExceptions::loadUpdateTargetByTag)
        // .def("loadUpdateTargetById", &RulesExceptions::loadUpdateTargetById)
        // .def_readwrite("m_variable_update_target_by_tag", &RulesExceptions::m_variable_update_target_by_tag)
        // .def_readwrite("m_variable_update_target_by_msg", &RulesExceptions::m_variable_update_target_by_msg)
        // .def_readwrite("m_variable_update_target_by_id", &RulesExceptions::m_variable_update_target_by_id)
        // .def_readwrite("m_remove_rule_by_msg", &RulesExceptions::m_remove_rule_by_msg)
        // .def_readwrite("m_remove_rule_by_tag", &RulesExceptions::m_remove_rule_by_tag)
        ;
}