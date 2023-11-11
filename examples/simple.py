from ModSecurity import ModSecurity
from ModSecurity import RulesSet
from ModSecurity import Transaction

modsec = ModSecurity()
print(modsec.whoAmI())

rules = RulesSet()

rules.loadFromUri("basic_rules.conf")
print(rules.getParserError())

transaction = Transaction(modsec, rules)
print(transaction.processURI("http://www.modsecurity.org/test?key1=value1&key2=value2&key3=value3&test=args&test=test", "GET", "2.0"))
