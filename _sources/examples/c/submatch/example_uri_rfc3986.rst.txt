URI (RFC-3986)
--------------

This example was used as a benchmark in
`"Tagged Deterministic Finite Automata with Lookahead" <../../../../2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_ paper;
it is an RFC-3986 compliant URI parser.
It uses s-tags.

:download:`[uri_rfc3986.re] <uri_rfc3986.re>`

.. literalinclude:: uri_rfc3986.re
    :language: cpp

Compile as ``re2c -o uri_rfc3986.c uri_rfc3986.re``.
