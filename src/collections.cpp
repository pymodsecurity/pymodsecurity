#include <pybind11/pybind11.h>
#include <modsecurity/collection/collections.h>
#include <modsecurity/collection/collection.h>

namespace py = pybind11;

using modsecurity::collection::Collections;
using modsecurity::collection::Collection;

void init_collections(py::module& m)
{
    py::module collection_module = m.def_submodule("collection");

    py::class_<Collections>(collection_module, "Collections")
        .def(py::init<Collection *, Collection *, Collection *, Collection *, Collection *>())
        .def_readwrite("m_global_collection_key", &Collections::m_global_collection_key)
        .def_readwrite("m_ip_collection_key", &Collections::m_ip_collection_key)
        .def_readwrite("m_session_collection_key", &Collections::m_session_collection_key)
        .def_readwrite("m_user_collection_key", &Collections::m_user_collection_key)
        .def_readwrite("m_resource_collection_key", &Collections::m_resource_collection_key)
        .def_readwrite("m_global_collection", &Collections::m_global_collection)
        .def_readwrite("m_ip_collection", &Collections::m_ip_collection)
        .def_readwrite("m_session_collection", &Collections::m_session_collection)
        .def_readwrite("m_user_collection", &Collections::m_user_collection)
        .def_readwrite("m_resource_collection", &Collections::m_resource_collection)
        .def_readwrite("m_tx_collection", &Collections::m_tx_collection)
        ;
}