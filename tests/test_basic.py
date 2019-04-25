import pytest

def test_create(modsec):
    assert modsec is not None


def test_whoAmI(modsec):
    result = modsec.whoAmI()
    print(result)
    assert result is not None


def test_load_rules(basic_rules):
    error_msg = basic_rules.getParserError()
    assert error_msg == '', error_msg


def test_transaction(transaction):
    assert transaction.processConnection("127.0.0.1", 12345, "127.0.0.1", 80)
    assert transaction.processURI(
        "http://www.modsecurity.org/test?key1=value1&key2=value2&key3=value3",
        "GET", "1.1")

    # Request
    assert transaction.processRequestHeaders()
    assert transaction.processRequestBody()

    # Response
    assert transaction.processResponseHeaders(200, 'HTTP 1.2')
    assert transaction.processResponseBody()

    assert transaction.processLogging()

def test_intervention_create():
    from ModSecurity import ModSecurityIntervention
    it = ModSecurityIntervention()
    assert it is not None

@pytest.fixture
def callback_test_rules(rules):
    rule = 'SecRuleEngine On\n'
    rule += 'SecRule REMOTE_ADDR "@ipMatch 127.0.0.1" "phase:0,allow,id:161,msg:\'test\'"'

    assert rules.load(rule) > 0, rules.getParserError() or 'Failed to load rule'

def test_log_callback1(modsec, callback_test_rules, transaction, mocker):
    stub = mocker.stub('ModSecurity callback')
    modsec.setServerLogCb(stub)

    transaction.processConnection('127.0.0.1', 33333, '127.0.0.1', 8080)

    assert stub.call_count == 1

    _, rule_msg = stub.call_args_list[0][0]

    assert '[id "161"]' in rule_msg
    assert '[msg "test"]' in rule_msg

@pytest.mark.skipif(True, reason='TODO: Waiting for modsecurity 3.0.3')
def test_log_callback2(modsec, callback_test_rules, transaction, mocker):
    stub = mocker.stub('ModSecurity callback')
    import ModSecurity
    modsec.setServerLogCb2(stub, ModSecurity.LogProperty.RuleMessageLogProperty)

    transaction.processConnection('127.0.0.1', 33333, '127.0.0.1', 8080)

    assert stub.call_count == 1

    _, rule_msg = stub.call_args_list[0][0]

    assert isinstance(rule_msg, ModSecurity.RuleMessage)
    assert rule_msg.m_ruleId == 161
    # assert rule_msg.m_phase == 0
    assert rule_msg.m_message == 'test'
    assert rule_msg.m_isDisruptive