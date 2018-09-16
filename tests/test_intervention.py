import pytest
import ModSecurity

def test_intervention_processConnection(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REMOTE_ADDR "@ipMatch 127.0.0.1" "phase:0,deny,id:161"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.processConnection('127.0.0.1', 33333, '127.0.0.1',
                                  8080)
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_processURI(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REQUEST_URI "@streq /attack.php" "id:1,phase:1,t:lowercase,deny"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.processURI('/attack.php', 'GET', '1.1')
    transaction.processRequestHeaders()
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_addRequestHeader(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REQUEST_HEADERS:Host "^[\d\.]+$" "deny,id:47,log,status:400,msg:\'Host header is a numeric IP address\'"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.addRequestHeader('Host', '127.0.0.1')
    transaction.processRequestHeaders()
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_appendRequestBody(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRequestBodyAccess On\n'
    rule += 'SecRule REQUEST_BODY "@contains attack" "id:43,phase:2,deny"'
    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.appendRequestBody('here comes an attack')
    transaction.processRequestBody()
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_processReponseHeaders(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule RESPONSE_STATUS "@streq 503" "phase:3,id:58,deny"'
    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.processResponseHeaders(503, 'HTTP/1.1')
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_addResponseHeader(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule RESPONSE_HEADERS:X-Cache "MISS" "phase:3,id:55,deny"'
    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.addResponseHeader('X-Cache', 'MISS')
    transaction.processResponseHeaders(200, 'HTTP/1.1')
    assert transaction.intervention(intervention)
    assert intervention.disruptive

def test_intervention_appendResponseBody(modsec, rules, transaction, intervention):
    rule = 'SecRuleEngine On\n'
    rule += 'SecResponseBodyAccess On\n'
    rule += 'SecRule RESPONSE_BODY "Leaked data" "deny,phase:4,id:54"'
    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

    assert not transaction.intervention(intervention)
    assert not intervention.disruptive

    transaction.appendResponseBody('my Leaked data')
    transaction.processResponseBody()
    assert transaction.intervention(intervention)
    assert intervention.disruptive