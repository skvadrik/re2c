========
re2c
========

.. toctree::
    :hidden:

    User manual    </manual/manual>
    How to build   </build/build>
    Benchmarks     </benchmarks/benchmarks>
    Release notes  </releases/release_notes>
    Changelog      </releases/changelog/changelog>

re2c is a free and open-source lexer generator for C/C++, Go and Rust with a
focus on generating fast code. It compiles regular expression specifications to
deterministic finite automata and encodes them in the form of conditional jumps
in the target language. This approach is generally faster than table-based
lexers, and the generated code is easier to debug and understand. A flexible
user interface allows one to adapt the generated lexer to a particular
environment and input model, avoiding the overhead on unnecessary checks and
buffers. re2c is based on the
`lookahead TDFA <2022_borsotti_trofimovich_a_closer_look_at_tdfa.pdf>`_
algorithm that allows it to perform fast and lightweight submatch extraction.
It is used in other open-source projects such as
`php <http://php.net/>`_,
`ninja <https://ninja-build.org/>`_,
`yasm <http://yasm.tortall.net/>`_,
`spamassassin <https://spamassassin.apache.org/>`_,
`BRL-CAD <http://brlcad.org/>`_,
`wake <https://github.com/sifive/wake>`_,
etc.

.. |feed| image:: feed/feed/feed.png
    :target: feed/atom.xml
    :class:  feed
    :width:  2em

|feed| `Subscribe <feed/atom.xml>`_ to receive the latest news and updates.
See the user manuals (
`C/C++ <manual/manual_re2c.html>`_,
`D <manual/manual_re2d.html>`_,
`Go <manual/manual_re2go.html>`_,
`Haskell <manual/manual_re2hs.html>`_,
`Java <manual/manual_re2java.html>`_,
`JS <manual/manual_re2js.html>`_,
`OCaml <manual/manual_re2ocaml.html>`_,
`Python <manual/manual_re2py.html>`_,
`Rust <manual/manual_re2rust.html>`_
`V <manual/manual_re2v.html>`_,
`Zig <manual/manual_re2zig.html>`_,
) for a
complete overview with examples.

Download
--------

You can get the
`latest release <https://github.com/skvadrik/re2c/releases/latest>`_ on GitHub,
as well as the `older releases <https://github.com/skvadrik/re2c/releases>`_.
Many Linux distributions and other systems provide their own packages. The
source code is hosted on both GitHub (`<https://github.com/skvadrik/re2c>`_) and
SourceForge (`<https://sourceforge.net/p/re2c>`_). GitHub serves as the main
repository, bugtracker and tarball hosting. SourceForge is used as a backup
repository and email hosting.

Bugs & patches
--------------

Please send bugs reports, patches and other feedback to `GitHub issue tracker
<https://github.com/skvadrik/re2c>`_ or email them to
`re2c-devel@lists.sourceforge.net <re2c-devel@lists.sourceforge.net>`_ and
`re2c-general@lists.sourceforge.net <re2c-general@lists.sourceforge.net>`_
mailing lists. There is an IRC channel ``#re2c`` on
`irc.libera.chat <https://libera.chat>`_ and
`irc.oftc.net <https://www.oftc.net/>`_. Questions and contributions are
welcome!

Papers
------

- 2022
  `A closer look at TDFA <https://arxiv.org/abs/2206.01398>`_
  by Angelo Borsotti and Ulya Trofimovich.
  arXiv:2206.01398
  `[pdf 2022] <2022_borsotti_trofimovich_a_closer_look_at_tdfa.pdf>`_

- 2020
  `RE2C: A lexer generator based on lookahead-TDFA
  <https://doi.org/10.1016/j.simpa.2020.100027>`_
  by Ulya Trofimovich.
  Software Impacts 6 (2020) 100027,
  `[pdf 2021] <2020_trofimovich_re2c_a_lexer_generator_based_on_lookahead_tdfa.pdf>`_

- 2019
  `Efficient POSIX submatch extraction on NFA <https://doi.org/10.1002/spe.2881>`_
  by Angelo Borsotti and Ulya Trofimovich.
  Software: Practice and Experience 51, 2, pp. 159–192
  `[pdf 2019] <2019_borsotti_trofimovich_efficient_posix_submatch_extraction_on_nfa.pdf>`_

- 2017
  `Tagged Deterministic Finite Automata with Lookahead <https://arxiv.org/abs/1907.08837>`_
  by Ulya Trofimovich.
  arXiv:1907.08837,
  `[pdf 2017] <2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_

- 1994
  `RE2C: a more versatile scanner generator <https://dl.acm.org/doi/abs/10.1145/176454.176487>`_
  by Peter Bumbulis and  Donald D. Cowan.
  ACM Letters on Programming Languages and Systems (LOPLAS)
  `[ps 1994] <1994_bumbulis_cowan_re2c_a_more_versatile_scanner_generator.ps>`_

Authors
-------

re2c was originally written by Peter Bumbulis (peter@csg.uwaterloo.ca) in 1993.
Marcus Boerger and Dan Nuffer spent several years to turn the original idea into
a production ready code generator. Since then it has been maintained and
developed by multiple volunteers, most notably,
Brian Young (bayoung@acm.org),
`Marcus Boerger <https://github.com/helly25>`_,
Dan Nuffer (nuffer@users.sourceforge.net),
`Ulya Trofimovich <https://github.com/skvadrik>`_ (skvadrik@gmail.com),
`Serghei Iakovlev <https://github.com/sergeyklay>`_,
`Sergei Trofimovich <https://github.com/trofi>`_,
`Petr Skocik <https://github.com/pskocik>`_,
`ligfx <https://github.com/ligfx>`_
and `raekye <https://github.com/raekye>`_.
Many thanks to all other contributors!

License
-------

.. include:: LICENSE

Version
-------

This website describes re2c version |version|.

