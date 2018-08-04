import pytest
import os

from ModSecurity import ModSecurity
from ModSecurity import Rules
from ModSecurity import Transaction


@pytest.fixture
def modsec():
    modsec = ModSecurity()
    return modsec


@pytest.fixture
def rules():
    rules = Rules()
    return rules


@pytest.fixture
def basic_rules(rules, tmpdir):
    log_filename = tmpdir.join('modsec_audit.log')

    with open('tests/basic_rules.conf.template') as f:
        content = f.read()
        content = content.replace('{{ audit_log_filename }}',
                                  str(log_filename))
        log_filename.write(content)

    rules.loadFromUri(str(log_filename))
    return rules


@pytest.fixture
def transaction(modsec, basic_rules):
    transaction = Transaction(modsec, basic_rules)
    return transaction
