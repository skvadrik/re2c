Parsing options
---------------

This example shows how to parse command-line options
with possible arguments, where each individual option may need its own argument format.
Our parser handles errors and typos:
for known options it reports ill-formed arguments;
for unrecognized options it collects them and reports at the end of parsing.
Our imaginary options are summarized below:

* ``-v``, ``--verbose``

* ``-l LIMIT``, ``--limit=LIMIT``, where ``LIMIT`` is a decimal number followed by one of the suffixes ``B``, ``K``, ``M`` or ``G``

* ``-d DATE``, ``--date=DATE``, where ``DATE`` has the form ``DD/MM/YYYY``

* ``-p PATH``, ``--path=PATH``, where ``PATH`` is a ``/``-separated file path

* ``-f FORMAT``, ``--format=FORMAT``, where ``FORMAT`` is a double-quoted format string

:download:`[options.re] <parse_options.re>`

.. literalinclude:: parse_options.re
    :language: cpp

Compile as ``re2c -o options.c options.re``.
