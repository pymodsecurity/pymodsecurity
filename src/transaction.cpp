#include <pybind11/pybind11.h>
#include <modsecurity/transaction.h>

namespace py = pybind11;
using modsecurity::Transaction;

// void init_transaction(py::module &m)
// {
    //     py::class_<Transaction>(m, "Transaction")
    //         .def(py::init<>())

    //         ;
    // }