#include <pybind11/pybind11.h>
#include <modsecurity/rules.h>

namespace py = pybind11;
using modsecurity::Rule;
using modsecurity::Rules;
using modsecurity::debug_log::DebugLog;

void init_rules(py::module &m)
{
    py::class_<Rules>(m, "Rules")
        .def("dump", &Rules::dump);
}
