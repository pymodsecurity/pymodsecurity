def test_chunk_response_body(transaction):
    body = [
        # First chunk
        '' \
        '<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\r' \
        '<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ' \
        'xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"',

        # Second chunk
        '' \
        'xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">\n\r' \
        '  <soap:Body>\n\r' \
        '  <EnlightenResponse xmlns=\"http://clearforest.com/\">\n\r' \
        '  <EnlightenResult>string</EnlightenResult>\n\r',

        # Third chunk
        '' \
        '  </EnlightenResponse>\n\r' \
        '  </soap:Body>\n\r' \
        '</soap:Envelope>\n\r'
    ]

    for chunk in body:
        assert transaction.appendResponseBody(chunk)

    assert transaction.processResponseBody()