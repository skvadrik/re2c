std::ifstream
-------------

This example shows how to override re2c input mechanism:
instead of reading input characters from a buffer in memory, read them directly from file using STL ``std::ifstream`` class.
Note that we use ``tellg`` / ``seekg`` and rely on the ability to move backward and forward in the input stream:
this might not be possible, for example with ``stdin`` stream.
The program below converts Windows-style line endings ``CR LF`` to Unix-style line endings ``LF``.

This program uses a non-standard way of checking for the end of input:
it disables the usual cheching mechnism with ``re2c:yyfill:enable = 0;``
(this suppresses the generation of ``YYLESSTHAN`` and ``YYFILL``)
and puts the responsibility for checking on ``YYSKIP``.
This results in more frequent checks: ``YYSKIP`` is happens on each input character,
while ``YYLESSTHAN`` happens only once per each strongly connected component of automaton.
However, this method allows to avoid padding, which would require buffering input and nullify all advantages of direct-file input.


:download:`[ifstream.re] <ifstream.re>`

.. literalinclude:: ifstream.re
    :language: cpp

Compile as ``re2c -o ifstream.cc ifstream.re``.
