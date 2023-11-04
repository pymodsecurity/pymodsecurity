#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory.h>
#include <modsecurity/rule_message.h>
#include <modsecurity/rule.h>
#include <modsecurity/rules.h>
#include <modsecurity/rules_set.h>
#include <modsecurity/modsecurity.h>
#include <modsecurity/transaction.h>

namespace py = pybind11;
using modsecurity::Transaction;
using modsecurity::ModSecurity;
using modsecurity::Rules;
using modsecurity::RulesSet;

void init_transaction(py::module &m)
{
    py::class_<Transaction>(m, "Transaction")
        .def(py::init([](ModSecurity *ms, RulesSet *rules) {
            return std::unique_ptr<Transaction>(new Transaction(ms, rules, nullptr));
        }))
        .def(py::init([](ModSecurity *ms, RulesSet *rules, char *logCbData) {
            return std::unique_ptr<Transaction>(new Transaction(ms, rules, (void *) logCbData));
        }))
        .def("processConnection", &Transaction::processConnection)
        .def("processURI", &Transaction::processURI)
        .def("processRequestHeaders", &Transaction::processRequestHeaders)
        .def("addRequestHeader", (int (Transaction::*)(const std::string &, const std::string &)) & Transaction::addRequestHeader)
        .def("addRequestHeader", (int (Transaction::*)(const unsigned char *, const unsigned char *)) & Transaction::addRequestHeader)
        .def("addRequestHeader", (int (Transaction::*)(const unsigned char *, size_t, const unsigned char *, size_t)) & Transaction::addRequestHeader)
        .def("processRequestBody", &Transaction::processRequestBody)
        .def("appendRequestBody", [](Transaction &tr, std::string &str) {
            return tr.appendRequestBody((const unsigned char*) str.c_str(), str.length());
        })
        .def("requestBodyFromFile", &Transaction::requestBodyFromFile)
        .def("processResponseHeaders", &Transaction::processResponseHeaders)
        .def("addResponseHeader", (int (Transaction::*)(const std::string &, const std::string &)) & Transaction::addResponseHeader)
        .def("addResponseHeader", (int (Transaction::*)(const unsigned char *, const unsigned char *)) & Transaction::addResponseHeader)
        .def("addResponseHeader", (int (Transaction::*)(const unsigned char *, size_t, const unsigned char *, size_t)) & Transaction::addResponseHeader)
        .def("processResponseBody", &Transaction::processResponseBody)
        .def("appendResponseBody", [](Transaction &tr, std::string &str) {
            return tr.appendResponseBody((const unsigned char*) str.c_str(), str.length());
        })
        .def("processLogging", &Transaction::processLogging)
        .def("updateStatusCode", &Transaction::updateStatusCode)
        .def("intervention", &Transaction::intervention)
        .def("addArgument", &Transaction::addArgument)
        .def("extractArguments", &Transaction::extractArguments)
        .def("getResponseBody", &Transaction::getResponseBody)
        .def("getResponseBodyLength", &Transaction::getResponseBodyLength)
        .def("getRequestBodyLength", &Transaction::getRequestBodyLength)
        .def("serverLog", &Transaction::serverLog)
        .def("getRuleEngineState", &Transaction::getRuleEngineState)
        .def("toJSON", &Transaction::toJSON)
        .def("toOldAuditLogFormat", &Transaction::toOldAuditLogFormat)
        .def("toOldAuditLogFormatIndex", &Transaction::toOldAuditLogFormatIndex)
        .def_readwrite("m_creationTimeStamp", &Transaction::m_creationTimeStamp)
        // .def_readwrite("m_clientIpAddress", &Transaction::m_clientIpAddress)
        .def_readwrite("m_httpVersion", &Transaction::m_httpVersion)
        // .def_readwrite("m_serverIpAddress", &Transaction::m_serverIpAddress)
        .def_readwrite("m_uri", &Transaction::m_uri)
        // .def_readwrite("m_uri_no_query_string_decoded", &Transaction::m_uri_no_query_string_decoded)
        .def_readwrite("m_ARGScombinedSizeDouble", &Transaction::m_ARGScombinedSizeDouble)
        .def_readwrite("m_clientPort", &Transaction::m_clientPort)
        .def_readwrite("m_highestSeverityAction", &Transaction::m_highestSeverityAction)
        .def_readwrite("m_httpCodeReturned", &Transaction::m_httpCodeReturned)
        .def_readwrite("m_serverPort", &Transaction::m_serverPort)
        .def_readwrite("m_ms", &Transaction::m_ms)
        .def_readwrite("m_requestBodyType", &Transaction::m_requestBodyType)
        .def_readwrite("m_requestBodyProcessor", &Transaction::m_requestBodyProcessor)
        .def_readwrite("m_rules", &Transaction::m_rules)
        .def_readwrite("m_ruleRemoveById", &Transaction::m_ruleRemoveById)
        .def_readwrite("m_ruleRemoveByIdRange", &Transaction::m_ruleRemoveByIdRange)
        .def_readwrite("m_ruleRemoveByTag", &Transaction::m_ruleRemoveByTag)
        .def_readwrite("m_ruleRemoveTargetByTag", &Transaction::m_ruleRemoveTargetByTag)
        .def_readwrite("m_ruleRemoveTargetById", &Transaction::m_ruleRemoveTargetById)
        .def_readwrite("m_requestBodyAccess", &Transaction::m_requestBodyAccess)
        .def_readwrite("m_auditLogModifier", &Transaction::m_auditLogModifier)
        .def_readwrite("m_rulesMessages", &Transaction::m_rulesMessages)
        // .def_readwrite("m_requestBody", &Transaction::m_requestBody)
        // .def_readwrite("m_responseBody", &Transaction::m_responseBody)
        // .def_readwrite("m_id", &Transaction::m_id)
        // .def_readwrite("m_marker", &Transaction::m_marker)
        .def_readwrite("m_skip_next", &Transaction::m_skip_next)
        .def_readwrite("m_allowType", &Transaction::m_allowType)
        .def_readwrite("m_uri_decoded", &Transaction::m_uri_decoded)
        .def_readwrite("m_actions", &Transaction::m_actions)
        .def_readwrite("m_it", &Transaction::m_it)
        .def_readwrite("m_timeStamp", &Transaction::m_timeStamp)
        // .def_readwrite("m_collections", &Transaction::m_collections)
        .def_readwrite("m_matched", &Transaction::m_matched)
        // .def_readwrite("m_xml", &Transaction::m_xml)
        // .def_readwrite("m_json", &Transaction::m_json)
        .def_readwrite("m_secRuleEngine", &Transaction::m_secRuleEngine)
        .def_readwrite("m_variableDuration", &Transaction::m_variableDuration)
        .def_readwrite("m_variableEnvs", &Transaction::m_variableEnvs)
        .def_readwrite("m_variableHighestSeverityAction", &Transaction::m_variableHighestSeverityAction)
        .def_readwrite("m_variableRemoteUser", &Transaction::m_variableRemoteUser)
        .def_readwrite("m_variableTime", &Transaction::m_variableTime)
        .def_readwrite("m_variableTimeDay", &Transaction::m_variableTimeDay)
        .def_readwrite("m_variableTimeEpoch", &Transaction::m_variableTimeEpoch)
        .def_readwrite("m_variableTimeHour", &Transaction::m_variableTimeHour)
        .def_readwrite("m_variableTimeMin", &Transaction::m_variableTimeMin)
        .def_readwrite("m_variableTimeSec", &Transaction::m_variableTimeSec)
        .def_readwrite("m_variableTimeWDay", &Transaction::m_variableTimeWDay)
        .def_readwrite("m_variableTimeYear", &Transaction::m_variableTimeYear);
}
