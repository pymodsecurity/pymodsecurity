#include <pybind11/pybind11.h>
#include <modsecurity/debug_log.h>

namespace py = pybind11;
using modsecurity::debug_log::DebugLog;

void init_debug_log(py::module &m)
{
    py::module debug_log_module = m.def_submodule("debug_log");

    py::class_<DebugLog>(debug_log_module, "DebugLog")
            .def(py::init<>())
            .def("write", (void (DebugLog::*) (int, const std::string &)) &DebugLog::write)
            .def("write", (void (DebugLog::*) (int level, const std::string &, const std::string &, const std::string &)) &DebugLog::write)
            .def("isLogFileSet", &DebugLog::isLogFileSet)
            .def("isLogLevelSet", &DebugLog::isLogLevelSet)
            .def("setDebugLogLevel", &DebugLog::setDebugLogLevel)
            .def("setDebugLogFile", &DebugLog::setDebugLogFile)
            .def("getDebugLogFile", &DebugLog::getDebugLogFile)
            .def("getDebugLogLevel", &DebugLog::getDebugLogLevel)
            ;
}
