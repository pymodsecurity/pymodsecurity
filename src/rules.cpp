#include <pybind11/pybind11.h>
#include <modsecurity/rules.h>

namespace py = pybind11;
using modsecurity::Rules;
using namespace modsecurity::Parser;

void init_rules(py::module &m)
{
    py::class_<Rules>(m, "Rules")
        .def(py::init<>())
        .def("incrementReferenceCount", &Rules::incrementReferenceCount)
        .def("decrementReferenceCount", &Rules::decrementReferenceCount)
        .def("loadFromUri", &Rules::loadFromUri)
        .def("loadRemote", &Rules::loadRemote)
        .def("load", (int (Rules::*) (const char *)) &Rules::load)
        .def("load", (int (Rules::*) (const char *, const std::string &)) &Rules::load)
        .def("dump", &Rules::dump)
        // .def("merge", py::overload_cast<Parser::Driver *>(&Rules::merge))
        .def("merge", (int (Rules::*) (Rules *)) &Rules::merge)
        .def("evaluate", &Rules::evaluate)
        .def("getParserError", &Rules::getParserError)
        .def("debug", &Rules::debug)
        .def_readwrite("unicode_codepage", &Rules::unicode_codepage);
}