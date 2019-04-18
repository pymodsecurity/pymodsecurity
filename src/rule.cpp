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
        .def("organizeActions", &Rule::organizeActions)
        .def("cleanUpActions", &Rule::cleanUpActions)
        .def("executeAction", &Rule::executeAction)
        // .def("executeTransformation", &Rule::executeTransformation)
        // .def("getVariablesExceptions", &Rule::getVariablesExceptions)
        // .def("getFinalVars", &Rule::getFinalVars)
        .def("executeActionsAfterFullMatch", &Rule::executeActionsAfterFullMatch)
        .def("executeDefaultTransformations", &Rule::executeDefaultTransformations)
        .def("executeOperatorAt", &Rule::executeOperatorAt)
        .def("executeActionsIndependentOfChainedRuleResult", &Rule::executeActionsIndependentOfChainedRuleResult)
        // .def("updateMatchedVars", &Rule::updateMatchedVars)
        // .def("cleanMatchedVars", &Rule::cleanMatchedVars)
        .def("getActionsByName", &Rule::getActionsByName)
        .def("containsTag", &Rule::containsTag)
        .def("containsMsg", &Rule::containsMsg)
        .def("refCountDecreaseAndCheck", &Rule::refCountDecreaseAndCheck)
        // .def("refCountIncrease", &Rule::refCountIncrease)
        // .def("executeTransformations", &Rule::executeTransformations)
        .def_readwrite("m_theDisruptiveAction", &Rule::m_theDisruptiveAction)
        // .def_readwrite("m_logData", &Rule::m_logData)
        // .def_readwrite("m_msg", &Rule::m_msg)
        // .def_readwrite("m_severity", &Rule::m_severity)
        .def_readwrite("m_chained", &Rule::m_chained)
        .def_readwrite("m_containsCaptureAction", &Rule::m_containsCaptureAction)
        .def_readwrite("m_containsMultiMatchAction", &Rule::m_containsMultiMatchAction)
        .def_readwrite("m_containsStaticBlockAction", &Rule::m_containsStaticBlockAction)
        .def_readwrite("m_secMarker", &Rule::m_secMarker)
        .def_readwrite("m_ruleId", &Rule::m_ruleId)
        .def_readwrite("m_accuracy", &Rule::m_accuracy)
        .def_readwrite("m_lineNumber", &Rule::m_lineNumber)
        .def_readwrite("m_maturity", &Rule::m_maturity)
        .def_readwrite("m_phase", &Rule::m_phase)
        // .def_readwrite("m_variables", &Rule::m_variables)
        // .def_readwrite("m_op", &Rule::m_op)
        .def_readwrite("m_chainedRuleChild", &Rule::m_chainedRuleChild)
        .def_readwrite("m_chainedRuleParent", &Rule::m_chainedRuleParent)
        .def_readwrite("m_fileName", &Rule::m_fileName)
        .def_readwrite("m_marker", &Rule::m_marker)
        .def_readwrite("m_rev", &Rule::m_rev)
        .def_readwrite("m_ver", &Rule::m_ver)
        .def_readwrite("m_actionsRuntimePos", &Rule::m_actionsRuntimePos)
        .def_readwrite("m_actionsRuntimePre", &Rule::m_actionsRuntimePre)
        .def_readwrite("m_actionsSetVar", &Rule::m_actionsSetVar)
        .def_readwrite("m_actionsTag", &Rule::m_actionsTag);
}