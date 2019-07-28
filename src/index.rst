====
re2c
====

.. toctree::
    :hidden:

    User manual <manual/manual>
    Download & build <install/install>
    Releases <news/news>

Re2c is a free and open-source lexer generator for C and C++. 
Its most distinctive features are the following:

    **Very fast lexers.**
    The main goal of re2c is to generate lexers that match or exceed the
    speed of carefully optimized hand-written code. Instead of using traditional
    table-driven approach, re2c encodes the underlying finite state
    automaton directly in the form of conditional jumps. The resulting programs
    are faster and often smaller than their table-driven counterparts, and they
    are much easier to debug, understand and optimize. Re2c applies quite a few
    optimizations in order to further speed up and compress the generated code.

    **Flexible user interface.**
    Instead of assuming a fixed program template, re2c leaves the definition of
    the interface code to the user. It exposes a number of primitives which
    should be defined in the form of C/C++ functions, variables and macros. In
    addition, re2c allows to configure almost every aspect of the generated
    code. All this gives the users a lot of freedom in the way they bind the
    generated lexer to their particular environment and allows them to avoid
    unnecessary overhead and decide on the optimal input model, buffering,
    end-of-input checking mechanism and other aspects.

    **Fast lightweight submatch extraction.**
    Re2c uses a
    `novel algorithm <2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_
    that allows it to perform submatch extraction without the overhead on full
    parsing. The overhead is proportional to submatch detalization: for only a
    few submatch positions it is barely noticeable, and for a moderate number of
    submatch positions the overhead is still small. This corresponds to the main
    re2c idea --- the users should only pay for what they really use.

.. |feed| image:: feed/feed/feed.png
    :target: feed/atom.xml
    :class:  feed
    :width:  2em

Re2c aims at being fully backward compatible and never breaking existing code.
It is used by many other projects, most notably
`PHP <http://php.net/>`_,
`ninja <https://ninja-build.org/>`_,
`yasm <http://yasm.tortall.net/>`_,
`spamassassin <https://spamassassin.apache.org/>`_,
`BRL-CAD <http://brlcad.org/>`_
and re2c itself.
At the same time, re2c is a research project: the core of it is old and stable,
but some of the more recent features are a playground for experiments and
development of new algorithms in the field of formal grammars and automata
theory.

|feed| `Subscribe <feed/atom.xml>`_ to receive the latest news and updates.
See the `user manual <manual/manual.html>`_ for a complete overview with
examples.

Bugs & patches
--------------

The best place to report a bug is `on github <https://github.com/skvadrik/re2c>`_
or in `re2c-devel <re2c-devel@lists.sourceforge.net>`_ and `re2c-general <re2c-general@lists.sourceforge.net>`_ mailing lists.
Note that re2c is hosted on both `github <https://github.com/skvadrik/re2c>`_
and `sourceforge <https://sourceforge.net/p/re2c>`_:
github serves as the main repository, bugtracker, and tarball hosting;
sourceforge is used as a backup repository and for mail.
All contributions are welcome!

Papers
------

Re2c is a research project. It is described in the following papers:

- `"RE2C: a more versatile scanner generator"
  <../1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.ps>`_
  by Peter Bumbulis and  Donald D. Cowan,
  ACM Letters on Programming Languages and Systems (LOPLAS),
  1994

- `"Tagged Deterministic Finite Automata with Lookahead"
  <../2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_
  by Ulya Trofimovich,
  arXiv:1907.08837,
  2017

- `"Efficient POSIX submatch extraction on NFA"
  <../2019_borsotti_trofimovich_efficient_posix_submatch_extraction_on_nfa.pdf>`_
  by Angelo Borsotti and Ulya Trofimovich,
  2017

Authors
-------

Re2c was originally written by Peter Bumbulis (peter@csg.uwaterloo.ca)
and described in research article `"RE2C: a more versatile scanner generator"
<../1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.ps>`_
by Peter Bumbulis and Donald Cowan, 1994.
Since then re2c has been maintained and developed by multiple volunteers,
most notably,
Brian Young (bayoung@acm.org),
Markus Boerger (helly@users.sourceforge.net),
Dan Nuffer (nuffer@users.sourceforge.net)
and Ulya Trofimovich (skvadrik@gmail.com).
Here is a list of re2c contributors (sorry if anyone is missing):
Brian Young,
Dan Nuffer,
Derick Rethans,
Emmanuel Mogenet,
Hartmut Kaiser,
jcfp,
joscherl,
Markus Boerger,
Mike Gilbert,
Nerd,
nuno-lopes,
Oleksii Taran,
Peter Bumbulis,
Petr Skocik,
Paulo Custodio,
Ross Burton,
Ryan Mast,
Serghei Iakovlev,
Sergei Trofimovich,
Tim Kelly,
Ulya Trofimovich.

License
-------

Re2c is in the public domain. The data structures and algorithms used
in re2c are all either taken from documents available to the general
public or are inventions of the author. Programs generated by re2c may
be distributed freely. Re2c itself may be distributed freely, in source
or binary, unchanged or modified. Distributors may charge whatever fees
they can obtain for re2c. If you do make use of re2c, or incorporate it into a larger project an
acknowledgement somewhere (documentation, research report, etc.) would
be appreciated.
Re2c is distributed with no warranty whatsoever.
The code is certain to contain errors.
Neither the author nor any contributor takes responsibility for any consequences of its use.

Version
-------

This website describes re2c version |version|.

