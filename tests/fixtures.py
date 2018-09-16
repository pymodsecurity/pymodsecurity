import pytest
import os

from ModSecurity import ModSecurity
from ModSecurity import Rules
from ModSecurity import Transaction
from ModSecurity import ModSecurityIntervention


@pytest.fixture
def modsec():
    modsec = ModSecurity()
    return modsec


@pytest.fixture
def rules(tmpdir):
    rules = Rules()
    rules.loadFromUri('tests/config-logs.conf')
    rules.load('SecTmpDir %s' % str(tmpdir))
    rules.load('SecDataDir %s' % str(tmpdir))
    rules.load('SecDebugLog %s/modsec_debug.log' % str(tmpdir))
    return rules


@pytest.fixture
def basic_rules(rules, tmpdir):
    log_filename = tmpdir.join('modsec_audit.log')
    rules.loadFromUri('tests/basic_rules.conf')
    rules.load('SecAuditLog %s' % str(log_filename))
    return rules


@pytest.fixture
def transaction(modsec, rules):
    transaction = Transaction(modsec, rules)
    return transaction

@pytest.fixture
def intervention():
    return ModSecurityIntervention()