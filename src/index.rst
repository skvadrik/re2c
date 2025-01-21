.. |nbsp| unicode:: 0xA0

==================================================
re2c |nbsp| --- |nbsp| Regular Expressions to Code
==================================================

.. toctree::
    :hidden:

    User manual     </manual/manual>
    Build & install </build/build>
    Benchmarks      </benchmarks/benchmarks>
    Release notes   </releases/release_notes>
    Changelog       </releases/changelog/changelog>

*re2c* stands for *Regular Expressions to Code*.
It is a free and open-source lexer generator that supports C/C++, D, Go,
Haskell, Java, JavaScript, OCaml, Python, Rust, V, Zig, and can be extended to
other languages by implementing a single :ref:`syntax file <manual/manual_c:syntax files>`.
The primary focus of re2c is on generating *fast* code: it compiles regular
expressions to deterministic finite automata and translates them into
direct-coded lexers in the target language (such lexers are generally faster
and easier to debug than their table-driven analogues).
Secondary re2c focus is on *flexibility*: it does not assume a fixed program
template; instead, it allows the user to embed lexers anywhere in the source
code and configure them to avoid unnecessary buffering and bounds checks.
Internal algorithm used by re2c is based on a special kind of deterministic
finite automata: `lookahead TDFA <2022_borsotti_trofimovich_a_closer_look_at_tdfa.pdf>`_.
These automata are as fast as ordinary DFA, but they are also capable of
performing submatch extraction with minimal overhead.
re2c is used in other open-source projects, such as
`php <http://php.net/>`_,
`ninja <https://ninja-build.org/>`_,
`yasm <http://yasm.tortall.net/>`_,
`spamassassin <https://spamassassin.apache.org/>`_,
`BRL-CAD <http://brlcad.org/>`_,
`wake <https://github.com/sifive/wake>`_,
etc.

.. |man| image:: _static/manual.png
    :target: manual/manual.html
    :class:  feed
    :width:  2em

|man| |nbsp| Read the manual for
`C/C++ <manual/manual_c.html>`_,
`D <manual/manual_d.html>`_,
`Go <manual/manual_go.html>`_,
`Haskell <manual/manual_hs.html>`_,
`Java <manual/manual_java.html>`_,
`JS <manual/manual_js.html>`_,
`OCaml <manual/manual_ocaml.html>`_,
`Python <manual/manual_py.html>`_,
`Rust <manual/manual_rust.html>`_,
`V <manual/manual_v.html>`_,
`Zig <manual/manual_zig.html>`_.

.. |play| image:: _static/play.png
    :target: ../playground
    :class:  feed
    :width:  2em

|play| |nbsp| Run examples in the `playground <../playground>`_.

.. |feed| image:: feed/feed/feed.png
    :target: feed/atom.xml
    :class:  feed
    :width:  2em

|feed| |nbsp| `Subscribe <feed/atom.xml>`_ to receive release notes.

Download
--------

- **Packages**.
  Many systems provide their own packages that can be installed via package
  managers. See the full list `on Repology <https://repology.org/project/re2c/versions>`_.

- **Release tarballs**.
  You can get the `latest release <https://github.com/skvadrik/re2c/releases/latest>`_
  on GitHub, as well as the `older releases <https://github.com/skvadrik/re2c/releases>`_.

- **Source code**.
  The main repository is on GitHub: `<https://github.com/skvadrik/re2c>`_.
  There is a mirror on SourceForge: `<https://sourceforge.net/p/re2c>`_, but it
  may be out of date.

Bugs & patches
--------------

Please send bugs reports, patches and other feedback to
`GitHub issue tracker <https://github.com/skvadrik/re2c>`_ or
`GitHub discussions <https://github.com/skvadrik/re2c/discussions>`_,
or else send an email to `skvadrik@gmail.com <skvadrik@gmail.com>`_,
`re2c-devel@lists.sourceforge.net <re2c-devel@lists.sourceforge.net>`_ or
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

