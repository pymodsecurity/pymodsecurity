#include <pybind11/pybind11.h>
#include <modsecurity/actions/action.h>
#include <modsecurity/rule_message.h>


namespace py = pybind11;
using modsecurity::actions::Action;
using modsecurity::Rule;
using modsecurity::RuleWithActions;
using modsecurity::Transaction;
using modsecurity::RuleMessage;

class pyAction : public Action {
    public:
    using Action::Action;

    std::string evaluate(const std::string &exp, Transaction *transaction) override {
        PYBIND11_OVERLOAD(std::string, Action, evaluate, exp, transaction);
    }
    bool evaluate(RuleWithActions *rule, Transaction *transaction) override {
        PYBIND11_OVERLOAD(bool, Action, evaluate, rule, transaction);
    }
    bool evaluate(RuleWithActions *rule, Transaction *transaction, std::shared_ptr<RuleMessage> ruleMessage) override {
        PYBIND11_OVERLOAD(bool, Action, evaluate, rule, transaction, ruleMessage);
    }
    bool init(std::string *error) override {
        PYBIND11_OVERLOAD(bool, Action, init, error);
    }
    bool isDisruptive() override {
        PYBIND11_OVERLOAD(bool, Action, isDisruptive);
    }
};

void init_action(py::module &m)
{
    py::module actions_module = m.def_submodule("actions");

    py::class_<Action, pyAction> action(actions_module, "Action");
    action.def(py::init<const std::string&>())
        .def(py::init<const std::string&, int>())
        .def("evaluate", (bool (Action::*) (RuleWithActions*, Transaction*)) &Action::evaluate)
        .def("evaluate", (bool (Action::*) (RuleWithActions*, Transaction*, std::shared_ptr<RuleMessage>)) &Action::evaluate)
        .def("init", &Action::init)
        .def("isDisruptive", &Action::isDisruptive)
        .def("set_name_and_payload", &Action::set_name_and_payload)
        /* Removed in v3.0.10
        .def("refCountDecreaseAndCheck", &Action::refCountDecreaseAndCheck)
        .def("refCountIncrease", &Action::refCountIncrease)
        */
        .def_readwrite("m_isNone", &Action::m_isNone)
        .def_readwrite("temporaryAction", &Action::temporaryAction)
        .def_readwrite("action_kind", &Action::action_kind)
        // FIXME broken by migration to std::shared_ptr<std::string>
        // .def_readwrite("m_name", &Action::m_name)
        .def_readwrite("m_parser_payload", &Action::m_parser_payload)
        ;
    
    py::enum_<Action::Kind>(action, "Kind")
        .value("ConfigurationKind", Action::Kind::ConfigurationKind)
        .value("RunTimeBeforeMatchAttemptKind", Action::Kind::RunTimeBeforeMatchAttemptKind)
        .value("RunTimeOnlyIfMatchKind", Action::Kind::RunTimeOnlyIfMatchKind)
        .export_values();
}
