#include <pybind11/pybind11.h>
#include <modsecurity/audit_log.h>
#include <modsecurity/transaction.h>

namespace py = pybind11;
using modsecurity::audit_log::AuditLog;
using modsecurity::Transaction;

void init_audit_log(py::module& m)
{
    py::module audit_log_module = m.def_submodule("audit_log");

    py::class_<AuditLog> auditLog(audit_log_module, "AuditLog");
    auditLog.def(py::init<>())
    .def("setStorageDirMode", &AuditLog::setStorageDirMode)
    .def("setFileMode", &AuditLog::setFileMode)
    .def("setStatus", &AuditLog::setStatus)
    .def("setRelevantStatus", &AuditLog::setRelevantStatus)
    .def("setFilePath1", &AuditLog::setFilePath1)
    .def("setFilePath2", &AuditLog::setFilePath2)
    .def("setStorageDir", &AuditLog::setStorageDir)
    .def("setFormat", &AuditLog::setFormat)
    .def("getDirectoryPermission", &AuditLog::getDirectoryPermission)
    .def("getFilePermission", &AuditLog::getFilePermission)
    .def("getParts", &AuditLog::getParts)
    .def("setParts", &AuditLog::setParts)
    .def("setType", &AuditLog::setType)
    .def("init", &AuditLog::init)
    .def("close", &AuditLog::close)
    .def("saveIfRelevant", (bool (AuditLog::*) (Transaction*)) &AuditLog::saveIfRelevant)
    .def("saveIfRelevant", (bool (AuditLog::*) (Transaction*, int)) &AuditLog::saveIfRelevant)
    .def("isRelevant", &AuditLog::isRelevant)
    .def("addParts", &AuditLog::addParts)
    .def("removeParts", &AuditLog::removeParts)
    .def("merge", &AuditLog::merge)
    /* Removed in 3.0.10
    .def("refCountIncrease", &AuditLog::refCountIncrease)
    .def("refCountDecreaseAndCheck", &AuditLog::refCountDecreaseAndCheck)
    */
    .def_readwrite("m_path1", &AuditLog::m_path1)
    .def_readwrite("m_path2", &AuditLog::m_path2)
    .def_readwrite("m_storage_dir", &AuditLog::m_storage_dir)
    .def_readwrite("m_format", &AuditLog::m_format)
    ;

    py::enum_<AuditLog::AuditLogType>(auditLog, "AuditLogType")
    .value("NotSetAuditLogType", AuditLog::AuditLogType::NotSetAuditLogType)
    .value("SerialAuditLogType", AuditLog::AuditLogType::SerialAuditLogType)
    .value("ParallelAuditLogType", AuditLog::AuditLogType::ParallelAuditLogType)
    .value("HttpsAuditLogType", AuditLog::AuditLogType::HttpsAuditLogType)
    .export_values();

    py::enum_<AuditLog::AuditLogStatus>(auditLog, "AuditLogStatus")
    .value("NotSetLogStatus", AuditLog::AuditLogStatus::NotSetLogStatus)
    .value("OnAuditLogStatus", AuditLog::AuditLogStatus::OnAuditLogStatus)
    .value("OffAuditLogStatus", AuditLog::AuditLogStatus::OffAuditLogStatus)
    .value("RelevantOnlyAuditLogStatus", AuditLog::AuditLogStatus::RelevantOnlyAuditLogStatus)
    .export_values();

    py::enum_<AuditLog::AuditLogFormat>(auditLog, "AuditLogFormat")
    .value("NotSetAuditLogFormat", AuditLog::AuditLogFormat::NotSetAuditLogFormat)
    .value("JSONAuditLogFormat", AuditLog::AuditLogFormat::JSONAuditLogFormat)
    .value("NativeAuditLogFormat", AuditLog::AuditLogFormat::NativeAuditLogFormat)
    .export_values();

    py::enum_<AuditLog::AuditLogParts>(auditLog, "AuditLogParts")
    .value("AAuditLogPart", AuditLog::AuditLogParts::AAuditLogPart)
    .value("BAuditLogPart", AuditLog::AuditLogParts::BAuditLogPart)
    .value("CAuditLogPart", AuditLog::AuditLogParts::CAuditLogPart)
    .value("DAuditLogPart", AuditLog::AuditLogParts::DAuditLogPart)
    .value("EAuditLogPart", AuditLog::AuditLogParts::EAuditLogPart)
    .value("FAuditLogPart", AuditLog::AuditLogParts::FAuditLogPart)
    .value("GAuditLogPart", AuditLog::AuditLogParts::GAuditLogPart)
    .value("HAuditLogPart", AuditLog::AuditLogParts::HAuditLogPart)
    .value("IAuditLogPart", AuditLog::AuditLogParts::IAuditLogPart)
    .value("JAuditLogPart", AuditLog::AuditLogParts::JAuditLogPart)
    .value("KAuditLogPart", AuditLog::AuditLogParts::KAuditLogPart)
    .value("ZAuditLogPart", AuditLog::AuditLogParts::ZAuditLogPart)
    .export_values();
}
