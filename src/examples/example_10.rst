URI (RFC-3986)
--------------

This example was used as a benchmark in
`"Tagged Deterministic Finite Automata with Lookahead" <../../2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_ paper;
it is an RFC-3986 compliant URI parser.
It uses s-tags.

:download:`[uri_rfc3986.re] <10_uri_rfc3986.i--tags.re>`

.. literalinclude:: 10_uri_rfc3986.i--tags.re
    :language: cpp
    :linenos:

:download:`[uri.dat] <10_uri.dat.txt>`

.. literalinclude:: 10_uri.dat.txt

Compile:

.. code-block:: bash

    $ re2c --tags -o uri_rfc3986.cc uri_rfc3986.re
    $ g++ -o uri_rfc3986 uri_rfc3986.cc

Run:

.. code-block:: bash

    $ ./uri_rfc3986 uri.dat
    URI 1:
      scheme:   http
      userinfo: user:pass
      host:     127.0.0.1 (IPv4)
      port:     8000
      path:     /path/data
      query:    key=val&key2=val2
      fragment: frag1
    
    URI 2:
      scheme:   rsync
      host:     rsync.kernel.org (name)
      path:     /pub/
    
    URI 3:
      scheme:   http
      host:     re2c.org (name)
      path:     /manual/syntax/syntax.html
      fragment: rules
    
    URI 4:
      scheme:   ssh
      host:     [2001:db8:85a3::8a2e:370:7334] (IP literal)
      path:     /
    
    ok, parsed 4 URIs


