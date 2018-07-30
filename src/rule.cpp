#include <pybind11/pybind11.h>
#include <modsecurity/rule_message.h>
#include <modsecurity/rule.h>
#include <modsecurity/variable_value.h>
#include <modsecurity/actions/action.h>

namespace py = pybind11;
using modsecurity::Rule;
using modsecurity::operators::Operator;
using modsecurity::VariableValue;
using namespace modsecurity;

void init_rule(py::module &m)
{
    py::class_<Rule>(m, "Rule")
        .def(py::init<std::string>())
        // .def(py::init<Operator *, std::vector<VariableValue *> *, std::vector<actions::Action *> *, std::string, int>())
        .def("evaluate", &Rule::evaluate)
        .def("evaluateActions", &Rule::evaluateActions)
        .def("getFinalVars", &Rule::getFinalVars)
        .def("executeActionsAfterFullMatch", &Rule::executeActionsAfterFullMatch)
        .def("executeDefaultTransformations", &Rule::executeDefaultTransformations)
        .def("executeOperatorAt", &Rule::executeOperatorAt)
        .def("executeActionsIndependentOfChainedRuleResult", &Rule::executeActionsIndependentOfChainedRuleResult)
        .def("updateMatchedVars", &Rule::updateMatchedVars)
        .def("cleanMatchedVars", &Rule::cleanMatchedVars)
        .def("updateRulesVariable", &Rule::updateRulesVariable)
        .def("getActionNames", &Rule::getActionNames)
        .def("getActionsByName", &Rule::getActionsByName)
        .def("containsTag", &Rule::containsTag)
        .def("containsMsg", &Rule::containsMsg)
        .def("containsDisruptiveAction", &Rule::containsDisruptiveAction)
        .def("refCountDecreaseAndCheck", &Rule::refCountDecreaseAndCheck)
        .def("refCountIncrease", &Rule::refCountIncrease)
        .def_readwrite("m_accuracy", &Rule::m_accuracy)
        .def_readwrite("m_actionsConf", &Rule::m_actionsConf)
        .def_readwrite("m_actionsRuntimePos", &Rule::m_actionsRuntimePos)
        .def_readwrite("m_actionsRuntimePre", &Rule::m_actionsRuntimePre)
        .def_readwrite("m_chained", &Rule::m_chained)
        .def_readwrite("m_chainedRule", &Rule::m_chainedRule)
        .def_readwrite("m_fileName", &Rule::m_fileName)
        .def_readwrite("m_lineNumber", &Rule::m_lineNumber)
        .def_readwrite("m_logData", &Rule::m_logData)
        .def_readwrite("m_marker", &Rule::m_marker)
        .def_readwrite("m_maturity", &Rule::m_maturity)
        // .def_readwrite("m_op", &Rule::m_op)
        .def_readwrite("m_phase", &Rule::m_phase)
        .def_readwrite("m_rev", &Rule::m_rev)
        .def_readwrite("m_ruleId", &Rule::m_ruleId)
        .def_readwrite("m_secMarker", &Rule::m_secMarker)
        .def_readwrite("m_variables", &Rule::m_variables)
        .def_readwrite("m_ver", &Rule::m_ver);
}