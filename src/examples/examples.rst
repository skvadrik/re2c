========
Examples
========

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
    Strings in binaries                         <example_15>
    Fake sentinel                               <example_16>
    std::ifstream                               <example_17>

Examples have been written with two goals in mind.
First, they are practical: each example solves a distinct real-world problem,
ranging from simple recognizers to complex parsers conforming to real-world standards and specifications.
Second, examples show various aspects of using re2c API:

  Checking for the end of input: this can be done in a number of different ways.
  The simplest and the most efficient way is the sentinel method demonstrated by `lexing numbers <example_01.html>`_ example:
  it should be used when there is a *sentinel character* that never appears in the middle of well-formed input,
  such as the ``NULL`` character in null-terminated strings.
  If the input is buffered, sentinel should be `appended at the end of buffer <example_09.html>`_.
  If appending is not possible, one can `emulate fake sentinel <example_16.html>`_ using generic API.
  Another, more general (but also less efficient) method is based on comparison of current input position and the end position:
  that is, comparison of ``YYCURSOR`` and ``YYLIMIT`` as explained in `parsing strings <example_02.html>`_ example,
  or using ``YYLESSTHAN`` in case of generic API.
  By default, this method requires padding input with ``YYMAXFILL`` fake characters;
  if padding is undesirable or impossible, one can override the checking mechanism using generic API
  and `perform checks on each input character <example_15.html>`_
  (also used in `std::ifstream <example_17.html>`_ example).

  Handling `large input <example_03.html>`_: how to organize buffering and how to refill buffer with ``YYFILL``.
  Some additional details of handling *tags* in ``YYFILL`` are illustrated
  in parsing `URI <example_10.html>`_ and parsing `HTTP messages <example_11.html>`_.

  `Submatch extraction <../manual/features/submatch/submatch.html>`_:
  using *s-tags* to store input positions corresponding to various parts of the regular expression in variables
  (outlined by parsing `IPv4 address <example_08.html>`_ and also used in
  parsing `floating-point <example_12.html>`_ numbers,
  parsing `/etc/passwd <example_09.html>`_ file format,
  parsing command-line `options and arguments <example_14.html>`_
  and parsing `URI <example_10.html>`_);
  using *m-tags* to handle repeated submatch and store repeated values efficiently in the form of a prefix tree
  (outlined by parsing non-recursive `records and structures <example_13.html>`_ and also used in parsing `HTTP messages <example_11.html>`_).

  Using `generic API </manual/features/generic_api/generic_api.html>`_,
  either to override the input mechanism (outlined by `std::ifstream <example_17.html>`_ example),
  or to tweak it (as explained in
  `fake sentinel <example_16.html>`_ and
  `strings in binaries <example_15.html>`_
  examples).

  Switching between different lexing *modes* using multiple interrelated sub-lexers:
  either in semi-automated manner with re2c `conditions <../manual/features/conditions/conditions.html>`_ feature
  (outlined by a simple example of `parsing integers <example_05.html>`_ and also used in parsing `Braille patterns <example_06.html>`_),
  or manually with the use of multiple blocks
  (outlined by `another example <example_04.html>`_ of parsing integers and a more complex example of `C++98 lexer <example_07.html>`_).

  Reusing `the same set of rules <example_06.html>`_ to generate multiple lexers with different options.

  Using various `encodings <example_06.html>`_.

All examples are written in C-90 and in C++98, so they should be quite portable.
However, many examples use new re2c features and options,
and they have been tested on the latest re2c version.
Please `report <re2c-general@lists.sourceforge.net>`_ any errors and contribute new examples!

