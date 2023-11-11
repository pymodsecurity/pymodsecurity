#include <pybind11/pybind11.h>
#include <modsecurity/rules.h>
#include <modsecurity/rules_set.h>

namespace py = pybind11;
using modsecurity::Rule;
using modsecurity::Rules;
using modsecurity::RulesSet;

void init_rules_set(py::module &m)
{
    py::class_<RulesSet>(m, "RulesSet")
        .def(py::init<>())
        .def("loadFromUri", &RulesSet::loadFromUri)
        .def("loadRemote", &RulesSet::loadRemote)
        .def("load", (int (RulesSet::*) (const char *)) &RulesSet::load)
        .def("load", (int (RulesSet::*) (const char *, const std::string &)) &RulesSet::load)
        .def("dump", &RulesSet::dump)
        .def("merge", (int (RulesSet::*) (RulesSet*)) &RulesSet::merge)
        .def("evaluate", &RulesSet::evaluate)
        .def("getParserError", &RulesSet::getParserError)
        .def("debug", &RulesSet::debug);
}
