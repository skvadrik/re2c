HTTP (RFC-7230)
---------------

This example was used as a benchmark in
`"Tagged Deterministic Finite Automata with Lookahead" <../../../../2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_ paper;
it is an RFC-7230 compliant HTTP message parser.
It uses both s-tags and m-tags.

:download:`[http_rfc7230.re] <http_rfc7230.re>`

.. literalinclude:: http_rfc7230.re
    :language: cpp

Compile as ``re2c -o http_rfc7230.c http_rfc7230.re``.
