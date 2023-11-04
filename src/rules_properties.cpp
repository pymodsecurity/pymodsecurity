#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <modsecurity/rules_properties.h>
#include <modsecurity/rule.h>
#include <modsecurity/transaction.h>
#include <modsecurity/debug_log.h>

/*
namespace py = pybind11;

using modsecurity::ConfigInt;
using modsecurity::Rule;
using modsecurity::RulesProperties;
using modsecurity::Transaction;
using modsecurity::debug_log::DebugLog;
using modsecurity::ConfigInt;
using modsecurity::ConfigDouble;
using modsecurity::ConfigString;
using modsecurity::ConfigSet;
using modsecurity::UnicodeMapHolder;
using modsecurity::ConfigUnicodeMap;

void init_rules_properties(py::module &m)
{
    py::class_<ConfigInt>(m, "ConfigInt")
        .def(py::init<>())
        .def_readwrite("m_set", &ConfigInt::m_set)
        .def_readwrite("m_value", &ConfigInt::m_value)
        .def("merge", &ConfigInt::merge);

    py::class_<ConfigDouble>(m, "ConfigDouble")
        .def(py::init<>())
        .def_readwrite("m_set", &ConfigDouble::m_set)
        .def_readwrite("m_value", &ConfigDouble::m_value)
        .def("merge", &ConfigDouble::merge);

    py::class_<ConfigString>(m, "ConfigString")
        .def(py::init<>())
        .def_readwrite("m_set", &ConfigString::m_set)
        .def_readwrite("m_value", &ConfigString::m_value)
        .def("merge", &ConfigString::merge);

    py::class_<ConfigSet>(m, "ConfigSet")
        .def(py::init<>())
        .def_readwrite("m_set", &ConfigSet::m_set)
        .def_readwrite("m_clear", &ConfigSet::m_clear)
        .def_readwrite("m_value", &ConfigSet::m_value);
    
    py::class_<UnicodeMapHolder>(m, "UnicodeMapHolder")
        .def(py::init<>())
        .def("at", &UnicodeMapHolder::at)
        .def("change", &UnicodeMapHolder::change)
        // .def_readwrite("m_data", &UnicodeMapHolder::m_data);
        ;

    py::class_<ConfigUnicodeMap>(m, "ConfigUnicodeMap")
        .def(py::init<>())
        .def_readwrite("m_set", &ConfigUnicodeMap::m_set)
        .def_readwrite("m_unicode_map_table", &ConfigUnicodeMap::m_unicodeMapTable)
        .def_readwrite("m_unicodeMapTable", &ConfigUnicodeMap::m_unicodeMapTable)
        .def("loadConfig", &ConfigUnicodeMap::loadConfig)
        .def("merge", &ConfigUnicodeMap::merge);

    py::class_<RulesProperties> rulesProperties(m, "RulesProperties");

    rulesProperties.def(py::init<>())
        .def(py::init<DebugLog *>())
        .def_static("ruleEngineStateString", &RulesProperties::ruleEngineStateString)
        .def_static("configBooleanString", &RulesProperties::configBooleanString)
        .def_static("mergeProperties", &RulesProperties::mergeProperties)
        .def_static("appendRules", &RulesProperties::appendRules)
        .def("getRulesForPhase", &RulesProperties::getRulesForPhase)
        .def_readwrite("m_auditLog", &RulesProperties::m_auditLog)
        .def_readwrite("m_requestBodyLimitAction", &RulesProperties::m_requestBodyLimitAction)
        .def_readwrite("m_responseBodyLimitAction", &RulesProperties::m_responseBodyLimitAction)
        .def_readwrite("m_secRequestBodyAccess", &RulesProperties::m_secRequestBodyAccess)
        .def_readwrite("m_secResponseBodyAccess", &RulesProperties::m_secResponseBodyAccess)
        .def_readwrite("m_secXMLExternalEntity", &RulesProperties::m_secXMLExternalEntity)
        .def_readwrite("m_tmpSaveUploadedFiles", &RulesProperties::m_tmpSaveUploadedFiles)
        .def_readwrite("m_uploadKeepFiles", &RulesProperties::m_uploadKeepFiles)
        .def_readwrite("m_requestBodyLimit", &RulesProperties::m_requestBodyLimit)
        .def_readwrite("m_requestBodyNoFilesLimit", &RulesProperties::m_requestBodyNoFilesLimit)
        .def_readwrite("m_responseBodyLimit", &RulesProperties::m_responseBodyLimit)
        .def_readwrite("m_uploadFileLimit", &RulesProperties::m_uploadFileLimit)
        .def_readwrite("m_uploadFileMode", &RulesProperties::m_uploadFileMode)
        .def_readwrite("m_debugLog", &RulesProperties::m_debugLog)
        .def_readwrite("m_remoteRulesActionOnFailed", &RulesProperties::m_remoteRulesActionOnFailed)
        .def_readwrite("m_secRuleEngine", &RulesProperties::m_secRuleEngine)
        // .def_readwrite("m_exceptions", &RulesProperties::m_exceptions)
        .def_readwrite("m_components", &RulesProperties::m_components)
        // .def_readwrite("m_parserError", &RulesProperties::m_parserError)
        .def_readwrite("m_responseBodyTypeToBeInspected", &RulesProperties::m_responseBodyTypeToBeInspected)
        .def_readwrite("m_httpblKey", &RulesProperties::m_httpblKey)
        .def_readwrite("m_uploadDirectory", &RulesProperties::m_uploadDirectory)
        .def_readwrite("m_uploadTmpDirectory", &RulesProperties::m_uploadTmpDirectory)
        .def_readwrite("m_secArgumentSeparator", &RulesProperties::m_secArgumentSeparator)
        .def_readwrite("m_secWebAppId", &RulesProperties::m_secWebAppId)
        // .def_readwrite("m_defaultActions", &RulesProperties::m_defaultActions)
        // .def_readwrite("m_rules", &RulesProperties::m_rules)
        .def_readwrite("m_unicodeMapTable", &RulesProperties::m_unicodeMapTable);

    py::enum_<RulesProperties::ConfigBoolean>(rulesProperties, "ConfigBoolean")
        .value("TrueConfigBoolean", RulesProperties::ConfigBoolean::TrueConfigBoolean)
        .value("FalseConfigBoolean", RulesProperties::ConfigBoolean::FalseConfigBoolean)
        .value("PropertyNotSetConfigBoolean", RulesProperties::ConfigBoolean::PropertyNotSetConfigBoolean)
        .export_values();

    py::enum_<RulesProperties::RuleEngine>(rulesProperties, "RuleEngine")
        .value("DisabledRuleEngine", RulesProperties::RuleEngine::DisabledRuleEngine)
        .value("EnabledRuleEngine", RulesProperties::RuleEngine::EnabledRuleEngine)
        .value("DetectionOnlyRuleEngine", RulesProperties::RuleEngine::DetectionOnlyRuleEngine)
        .value("PropertyNotSetRuleEngine", RulesProperties::RuleEngine::PropertyNotSetRuleEngine)
        .export_values();

    py::enum_<RulesProperties::BodyLimitAction>(rulesProperties, "BodyLimitAction")
        .value("ProcessPartialBodyLimitAction", RulesProperties::BodyLimitAction::ProcessPartialBodyLimitAction)
        .value("RejectBodyLimitAction", RulesProperties::BodyLimitAction::RejectBodyLimitAction)
        .value("PropertyNotSetBodyLimitAction", RulesProperties::BodyLimitAction::PropertyNotSetBodyLimitAction)
        .export_values();

    py::enum_<RulesProperties::OnFailedRemoteRulesAction>(rulesProperties, "OnFailedRemoteRulesAction")
        .value("AbortOnFailedRemoteRulesAction", RulesProperties::OnFailedRemoteRulesAction::AbortOnFailedRemoteRulesAction)
        .value("WarnOnFailedRemoteRulesAction", RulesProperties::OnFailedRemoteRulesAction::WarnOnFailedRemoteRulesAction)
        .value("PropertyNotSetRemoteRulesAction", RulesProperties::OnFailedRemoteRulesAction::PropertyNotSetRemoteRulesAction)
        .export_values();
}
*/
