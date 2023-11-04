#include <pybind11/pybind11.h>
#include <modsecurity/rule_message.h>
#include <modsecurity/rule.h>
#include <modsecurity/variable_value.h>
#include <modsecurity/actions/action.h>

/*
namespace py = pybind11;
using modsecurity::Rule;
using modsecurity::RuleMessage;
using modsecurity::operators::Operator;
using modsecurity::VariableValue;
using namespace modsecurity;


// FIXME add PYBIND11_OVERRIDE_PURE
void init_rule(py::module &m)
{
    py::class_<Rule> rule(m, "Rule");
    rule.def(py::init<std::unique_ptr<std::string>, int>());

    rule
        .def("evaluate", (bool (Rule::*) (Transaction*)) &Rule::evaluate)
        .def("evaluate", (bool (Rule::*) (Transaction*, std::shared_ptr<RuleMessage>)) &Rule::evaluate)
        // .def("getFileName", (std::shared_ptr<std::string> (Rule::*) ()) &Rule::getFileName)
        .def("getLineNumber", (int (Rule::*) ()) &Rule::getLineNumber)
        .def("getPhase", (int (Rule::*) ()) &Rule::getPhase)
        .def("setPhase", (int (Rule::*) (int)) &Rule::setPhase)
        .def("getReference", (std::string (Rule::*) ()) &Rule::getReference)
        .def("isMarker", (bool (Rule::*) ()) &Rule::isMarker);
    // TODO add private members if needed
}
*/
