#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <modsecurity/rule_message.h>
#include <modsecurity/modsecurity.h>

namespace py = pybind11;
using modsecurity::ModSecurity;
using modsecurity::Phases;
using modsecurity::LogProperty;

    void
    init_modsecurity(py::module &m)
{
    py::class_<ModSecurity>(m, "ModSecurity")
        .def(py::init<>())
        .def("whoAmI", &ModSecurity::whoAmI)
        .def("setConnectorInformation", &ModSecurity::setConnectorInformation)
        .def("getConnectorInformation", &ModSecurity::getConnectorInformation)
        // .def("setServerLogCb", &ModSecurity::setServerLogCb)
        // .def("setServerLogCb", &ModSecurity::setServerLogCb)
        // .def("serverLog", &ModSecurity::serverLog)
        // .def("processContentOffset", &ModSecurity::processContentOffset)
        .def_readwrite("m_global_collection", &ModSecurity::m_global_collection)
        .def_readwrite("m_resource_collection", &ModSecurity::m_resource_collection)
        .def_readwrite("m_ip_collection", &ModSecurity::m_ip_collection)
        .def_readwrite("m_session_collection", &ModSecurity::m_session_collection)
        .def_readwrite("m_user_collection", &ModSecurity::m_user_collection)
        ;

    py::enum_<Phases>(m, "Phases")
        .value("ConnectionPhase", Phases::ConnectionPhase)
        .value("UriPhase", Phases::UriPhase)
        .value("RequestHeadersPhase", Phases::RequestHeadersPhase)
        .value("RequestBodyPhase", Phases::RequestBodyPhase)
        .value("ResponseHeadersPhase", Phases::ResponseHeadersPhase)
        .value("ResponseBodyPhase", Phases::ResponseBodyPhase)
        .value("LoggingPhase", Phases::LoggingPhase)
        .value("NUMBER_OF_PHASES", Phases::NUMBER_OF_PHASES)
        .export_values();

    py::enum_<LogProperty>(m, "LogProperty")
        .value("TextLogProperty", LogProperty::TextLogProperty)
        .value("RuleMessageLogProperty", LogProperty::RuleMessageLogProperty)
        .value("IncludeFullHighlightLogProperty", LogProperty::IncludeFullHighlightLogProperty)
        .export_values();
}