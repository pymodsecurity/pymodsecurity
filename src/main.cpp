#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(ModSecurity, m)
{
    init_modsecurity(m);
    // init_intervension(m);
    init_rule(m);
    init_rules(m);
    // init_transaction(m);
}