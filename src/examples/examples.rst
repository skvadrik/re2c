========
Examples
========

Examples have two purposes.
First, they show various aspects of using re2c API:

* the `sentinel method <example_01.html>`_ of checking for the end of input
* the ``YYLIMIT`` `method <example_02.html>`_ of checking for the end of input and purpose of ``YYMAXFILL`` padding
* how to `refill buffer <example_02.html>`_ with ``YYFILL`` in case of large input
* how to use `conditions <example_05.html>`_ to switch between different lexer modes
* how to switch lexer modes using `multiple interrelated blocks <example_04.html>`_
* how to `reuse the same set of rules <example_06.html>`_ for multiple lexers
* the support for various `encodings <example_06.html>`_
* how to use `basic <example_08.html>`_ `submatch <example_12.html>`_ `extraction <example_09.html>`_ (and also `here <example_14.html>`_)
* submatch extraction in case of `repeated submatch <example_13.html>`_


Second, examples are practical: each of them solves a distinct real-world problem.
Some problems are deliberately simple, such as lexing `numbers <example_01.html>`_ and `strings <example_02.html>`_,
or parsing `IPv4 address <example_08.html>`_ and `floating-point numbers <example_12.html>`_.
Others problems are moderately complex, such as parsing `/etc/passwd file format <example_09.html>`_,
parsing command-line `options and arguments <example_14.html>`_
or parsing non-recursive `records and structures <example_13.html>`_.
Finally, some examples are quite complex and conforming to real-world standards and specifications:
`C++98 <example_07.html>`_ lexer,
RFC-3986 compliant `URI parser <example_10.html>`_,
RFC-7230 compliant `HTTP parser <example_11.html>`_
and the parser of `Braille patterns <example_06.html>`_.


All examples are written in C-90 and in C++98, so they should be quite portable.
However, many examples use new re2c features and options,
and they have been tested on the latest re2c version.
Please `report <re2c-general@lists.sourceforge.net>`_ any errors and contribute new examples!

.. toctree::
    :maxdepth: 1

    Numbers                                     <example_01>
    Strings                                     <example_02>
    Large input                                 <example_03>
    Multiple blocks                             <example_04>
    Conditions                                  <example_05>
    Floating-point                              <example_12>
    IPv4 address                                <example_08>
    /etc/passwd                                 <example_09>
    Options & arguments                         <example_14>
    Records & structs                           <example_13>
    C++98                                       <example_07>
    URI (RFC-3986)                              <example_10>
    HTTP (RFC-7230)                             <example_11>
    Braille patterns                            <example_06>

