#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <modsecurity/rule_message.h>
#include <modsecurity/modsecurity.h>
#include <modsecurity/transaction.h>

namespace py = pybind11;
using modsecurity::ModSecurity;
using modsecurity::Phases;
using modsecurity::RuleMessage;
using modsecurity::LogProperty;

static std::function<void(char *, const char *)> modSecLogCb;
static std::function<void(char *, const RuleMessage *)> modSecLogCb2;

void init_modsecurity(py::module &m)
{
    py::class_<ModSecurity>(m, "ModSecurity")
        .def(py::init<>())
        .def("whoAmI", &ModSecurity::whoAmI)
        .def("setConnectorInformation", &ModSecurity::setConnectorInformation)
        .def("getConnectorInformation", &ModSecurity::getConnectorInformation)
        .def("setServerLogCb", [](ModSecurity &ms, std::function<void(char *, const char *)> cb) {
            modSecLogCb = cb;
            ms.setServerLogCb(+[](void * arg1, const void * arg2) {
                /* Acquire GIL before calling Python code */
                py::gil_scoped_acquire acquire;
                modSecLogCb((char *)arg1, (const char *)arg2);
            });
        })
        .def("setServerLogCb2", [](ModSecurity &ms, std::function<void(char *, const RuleMessage *)> cb) {
            modSecLogCb2 = cb;
            ms.setServerLogCb(+[](void *arg1, const void *arg2) {
                /* Acquire GIL before calling Python code */
                py::gil_scoped_acquire acquire;
                modSecLogCb2((char *)arg1, (const RuleMessage *)arg2);
            });
        })
        .def("setServerLogCb", [](ModSecurity &ms, std::function<void(char *, const char *)> cb, int properties) {
            modSecLogCb = cb;
            ms.setServerLogCb(+[](void *arg1, const void *arg2) {
                /* Acquire GIL before calling Python code */
                py::gil_scoped_acquire acquire;
                modSecLogCb((char *)arg1, (const char *)arg2);
            }, properties);
        })
        .def("setServerLogCb2", [](ModSecurity &ms, std::function<void(char *, const RuleMessage *)> cb, int properties) {
            modSecLogCb2 = cb;
            ms.setServerLogCb(+[](void *arg1, const void *arg2) {
                /* Acquire GIL before calling Python code */
                py::gil_scoped_acquire acquire;
                modSecLogCb2((char *)arg1, (const RuleMessage *)arg2);
            }, properties);
        })
        .def("serverLog", [](ModSecurity &ms, char *data, RuleMessage rm) {
            ms.serverLog((void *) data, std::make_shared<RuleMessage>(rm));
        })
        // .def("processContentOffset", &ModSecurity::processContentOffset)
        .def_readwrite("m_global_collection", &ModSecurity::m_global_collection)
        .def_readwrite("m_resource_collection", &ModSecurity::m_resource_collection)
        .def_readwrite("m_ip_collection", &ModSecurity::m_ip_collection)
        .def_readwrite("m_session_collection", &ModSecurity::m_session_collection)
        .def_readwrite("m_user_collection", &ModSecurity::m_user_collection);

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


    // helper function, just to test if the callback is working properly
    m.def("testLogCb", [](char *d1, char *d2) {
        /* Acquire GIL before calling Python code */
        py::gil_scoped_acquire acquire;
        modSecLogCb(d1, d2);
    });

    m.add_object("_cleanup", py::capsule([]() {
        // We need to clean up modSecLogCb and modSecLogCb2, otherwise GIL will end up in a deadlock with pending references
        std::function<void(char *, const char *)> cb;
        std::function<void(char *, const RuleMessage *)> cb2;

        modSecLogCb = cb;
        modSecLogCb2 = cb2;
    }));
}
