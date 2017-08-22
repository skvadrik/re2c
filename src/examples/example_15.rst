Strings in binaries
-------------------

The program below searches all strings starting with double underscore in the given binary file.
The same method can be used to search for arbitrary signatures or keywords.
Since we are dealing with a *binary* file, we cannot use the sentinel method to check for the end of input:
binary files can contain all kinds of characters, so no sentinel can be chosen.
The usual way in such cases is to use ``YYLIMIT``-based checking: it requires padding input with ``YYMAXFILL`` fake characters,
but it's not a problem since the input is buffered anyway.

However, this exampe takes another approach:
it uses generic API to override the default checking mechanism.
First, it disables the usual mechanism: suppresses the generation of ``YYLESSTHAN`` and ``YYFILL`` with ``re2c:yyfill:enable = 0;`` configuration.
Second, it redefines ``YYSKIP`` to perform checking before advancing to the next input character.
In principle, this approach is less efficient:
checking happens more frequently, as ``YYSKIP`` is invoked on each input character,
while ``YYLESSTHAN`` happens only once per each strongly connected component of automaton.
However, it allows to avoid padding.

:download:`[binsyms.re] <15_binsyms.i--input(custom).re>`

.. literalinclude:: 15_binsyms.i--input(custom).re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --input custom -o binsyms.cc binsyms.re
    $ g++ -o binsyms binsyms.cc

Run:

.. code-block:: bash

    $ ./binsyms binsyms
    __gmon_start__
    __libc_start_main
    __off_t
    __cxx11
    __gnu_cxx3divExx
    __off64_t
    __pad1
    __pad2
    __pad3
    __pad4
    __pad5
    __compar_fn_t
    __gnu_cxx
    __init_array_start
    __libc_csu_fini
    __libc_csu_init
    __init_array_end
    __GNU_EH_FRAME_HDR
    __init_array_end
    __init_array_start
    __libc_csu_fini
    __gmon_start__
    __libc_start_main
    __data_start
    __TMC_END__
    __dso_handle
    __libc_csu_init
    __bss_start


