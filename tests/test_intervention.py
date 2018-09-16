import pytest
import ModSecurity

def test_intervention_processConnection(mocker, modsec, rules):
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

def test_intervention_processURI(mocker, modsec, rules):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REQUEST_URI "@streq /attack.php" "id:1,phase:1,t:lowercase,deny"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    transaction = ModSecurity.Transaction(modsec, rules)
    intervention = ModSecurity.ModSecurityIntervention()
    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.processURI('/attack.php', 'GET', '1.1')
    transaction.processRequestHeaders()
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_addRequestHeader(mocker, modsec, rules):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REQUEST_HEADERS:Host "^[\d\.]+$" "deny,id:47,log,status:400,msg:\'Host header is a numeric IP address\'"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    transaction = ModSecurity.Transaction(modsec, rules)
    intervention = ModSecurity.ModSecurityIntervention()
    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.addRequestHeader('Host', '127.0.0.1')
    transaction.processRequestHeaders()
    assert transaction.intervention(intervention)
    assert intervention.disruptive