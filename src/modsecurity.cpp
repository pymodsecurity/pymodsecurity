#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <modsecurity/modsecurity.h>

namespace py = pybind11;
using modsecurity::ModSecurity;

// py::cpp_function logcb()
// {
//     return py::cpp_function([](int i) { return i + 1; },
//                             py::arg("number"));
// }


void init_modsecurity(py::module& m)
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
}