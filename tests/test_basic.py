from ModSecurity import ModSecurity
from ModSecurity import Rules
from ModSecurity import Transaction


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
