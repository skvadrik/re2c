HTTP (RFC-7230)
---------------

This example was used as a benchmark in
`"Tagged Deterministic Finite Automata with Lookahead" <../../2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_ paper;
it is an RFC-7230 compliant HTTP message parser.
It uses both s-tags and m-tags.

:download:`[http_rfc7230.re] <11_http_rfc7230.i--tags.re>`

.. literalinclude:: 11_http_rfc7230.i--tags.re
    :language: cpp
    :linenos:

:download:`[http.dat] <11_http.dat.txt>`

.. literalinclude:: 11_http.dat.txt

Compile:

.. code-block:: bash

    $ re2c --tags -o http_rfc7230.cc http_rfc7230.re
    $ g++ -o http_rfc7230 http_rfc7230.cc

Run:

.. code-block:: bash

    $ ./http_rfc7230 http.dat
    GET /index.html HTTP/1.1
    Host: www.example.com
    User-Agent: Mozilla/5.0
    Accept: text/xml,application/xml,application/xhtml+xml,text/html*/*
    Accept-Language: en-us
    Accept-Charset: ISO-8859-1,utf-8
    Connection: keep-alive
    
    HTTP/1.1 200 OK
    Date: Thu, 24 Jul 2008 17:36:27 GMT
    Server: Apache-Coyote/1.1
    Content-Type: text/html;charset=UTF-8
    Content-Length: 1846
    
    ok, parsed 2 HTTPs


