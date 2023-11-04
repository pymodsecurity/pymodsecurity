#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_action(py::module &m);
void init_anchored_set_variable(py::module &m);
void init_anchored_variable(py::module &m);
void init_audit_log(py::module& m);
// void init_collection(py::module &m);
// void init_collections(py::module &m);
void init_debug_log(py::module &m);
void init_intervention(py::module &m);
void init_modsecurity(py::module &m);
void init_rule_message(py::module &m);
// void init_rule(py::module &m);
void init_rules_exceptions(py::module &m);
// void init_rules_properties(py::module &m);
void init_rules(py::module &m);
void init_rules_set(py::module &m);
void init_transaction(py::module &m);
void init_variable_origin(py::module &m);
void init_variable_value(py::module &m);

PYBIND11_MODULE(ModSecurity, m)
{
    init_action(m);
    init_anchored_set_variable(m);
    init_anchored_variable(m);
    init_audit_log(m);
    // init_collection(m);
    // init_collections(m);
    init_debug_log(m);
    init_intervention(m);
    init_modsecurity(m);
    init_rule_message(m);
    // FIXME this is an abstract class now, it needs PYBIND11_OVERRIDE_PURE
    // init_rule(m);
    init_rules_exceptions(m);
    // init_rules_properties(m);
    init_rules(m);
    init_rules_set(m);
    init_transaction(m);
    init_variable_origin(m);
    init_variable_value(m);
}
