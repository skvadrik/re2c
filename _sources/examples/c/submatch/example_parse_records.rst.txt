Parsing records
---------------

This example shows how to parse simple non-recursive structures and records.
It uses both s-tags (for simple fields) and m-tags (for fields that contain multiple elements).
Our imaginary records describe IRC users.
Each record consists of a nickname followed by an opening curly brace, a list of attributes (one per line), and a closing curly brace.
Attributes are name, country and a list of IRC channels.

:download:`[records.re] <parse_records.re>`

.. literalinclude:: parse_records.re
    :language: cpp

Compile as ``re2c -o records.c records.re``.
