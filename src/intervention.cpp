#include <pybind11/pybind11.h>
#include <modsecurity/intervention.h>

namespace py = pybind11;
using modsecurity::ModSecurityIntervention;

const auto& intervention_reset = modsecurity::intervention::reset;
const auto& intervention_clean = modsecurity::intervention::clean;
const auto& intervention_freeUrl = modsecurity::intervention::freeUrl;
const auto& intervention_freeLog = modsecurity::intervention::freeLog;
const auto& intervention_free = modsecurity::intervention::free;

void init_intervention(py::module &m)
{
    py::module intervention_module = m.def_submodule("intervention");

    py::class_<ModSecurityIntervention>(m, "ModSecurityIntervention")
        .def(pybind11::init<>())
        .def_readwrite("status", &ModSecurityIntervention::status)
        .def_readwrite("pause", &ModSecurityIntervention::pause)
        .def_readwrite("url", &ModSecurityIntervention::url)
        .def_readwrite("log", &ModSecurityIntervention::log)
        .def_readwrite("disruptive", &ModSecurityIntervention::disruptive)
        ;

    intervention_module.def("reset", &intervention_reset)
        .def("clean", &intervention_clean)
        .def("freeUrl", &intervention_freeUrl)
        .def("freeLog", &intervention_freeLog)
        .def("free", &intervention_free);
}