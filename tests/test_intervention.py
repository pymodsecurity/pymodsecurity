import pytest
import ModSecurity

def test_intervention_processConnection(modsec, rules):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REMOTE_ADDR "@ipMatch 127.0.0.1" "phase:0,deny,id:161"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    transaction = ModSecurity.Transaction(modsec, rules)
    intervention = ModSecurity.ModSecurityIntervention()
    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.processConnection('127.0.0.1', 33333, '127.0.0.1',
                                  8080)
    assert transaction.intervention(intervention)
    assert intervention.disruptive