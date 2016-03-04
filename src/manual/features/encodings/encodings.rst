Encodings
---------

.. toctree::
    :hidden:

``re2c`` supports the following encodings: ASCII (default), EBCDIC (``-e``),
UCS-2 (``-w``), UTF-16 (``-x``), UTF-32 (``-u``) and UTF-8 (``-8``).
See also inplace configuration ``re2c:flags``.

The following concepts should be clarified when talking about encoding.
*Code point* is an abstract number, which represents single encoding
symbol. *Code unit* is the smallest unit of memory, which is used in the
encoded text (it corresponds to one character in the input stream). One
or more code units can be needed to represent a single code point,
depending on the encoding. In *fixed-length* encoding, each code point
is represented with equal number of code units. In *variable-length*
encoding, different code points can be represented with different number
of code units.

* ASCII is a fixed-length encoding. Its code space includes 0x100
  code points, from 0 to 0xFF. One code point is represented with exactly one
  1-byte code unit, which has the same value as the code point. Size of
  ``YYCTYPE`` must be 1 byte.

* EBCDIC is a fixed-length encoding. Its code space includes 0x100
  code points, from 0 to 0xFF. One code point is represented with exactly
  one 1-byte code unit, which has the same value as the code point. Size
  of ``YYCTYPE`` must be 1 byte.

* UCS-2 is a fixed-length encoding. Its code space includes 0x10000
  code points, from 0 to 0xFFFF. One code point is represented with
  exactly one 2-byte code unit, which has the same value as the code
  point. Size of ``YYCTYPE`` must be 2 bytes.

* UTF-16 is a variable-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with one or two 2-byte code units. Size of
  ``YYCTYPE`` must be 2 bytes.

* UTF-32 is a fixed-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with exactly one 4-byte code unit. Size of
  ``YYCTYPE`` must be 4 bytes.

* UTF-8 is a variable-length encoding. Its code space includes all
  Unicode code points, from 0 to 0xD7FF and from 0xE000 to 0x10FFFF. One
  code point is represented with sequence of one, two, three or four
  1-byte code units. Size of ``YYCTYPE`` must be 1 byte.

In Unicode, values from range 0xD800 to 0xDFFF (surrogates) are not
valid Unicode code points, any encoded sequence of code units, that
would map to Unicode code points in the range 0xD800-0xDFFF, is
ill-formed. The user can control how ``re2c`` treats such ill-formed
sequences with ``--encoding-policy <policy>`` flag.

For some encodings, there are code units, that never occur in valid
encoded stream (e.g. 0xFF byte in UTF-8). If the generated scanner must
check for invalid input, the only true way to do so is to use default
rule ``*``. Note, that full range rule ``[^]`` won't catch invalid code units when variable-length encoding is used
(``[^]`` means "all valid code points", while default rule ``*`` means "all possible code units").

