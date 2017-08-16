====
re2c
====

.. toctree::
    :hidden:

    About <about/about>
    Install <install/install>
    Manual <manual/manual>
    Examples <examples/examples>
    News <news/news>


re2c is a free and open-source lexer generator for C and C++.
Its main goal is generating *fast* lexers: at least as fast as their reasonably optimized hand-coded counterparts.
Instead of using traditional table-driven approach, re2c encodes the generated finite state automata directly in the form of conditional jumps and comparisons.
The resulting programs are faster and often smaller than their table-driven analogues,
and they are much easier to debug and understand.
re2c applies quite a few optimizations in order to speed up and compress the generated code.
Another distinctive feature is its flexible interface: instead of assuming a fixed program template,
re2c lets the programmer write most of the interface code and adapt the generated lexer to any particular environment.

For a step-by-step introduction, see `examples <examples/examples.html>`_.
For complete overview, see the `manual <manual/manual.html>`_.



Features
--------

*   `submatch extraction and parsing <manual/features/submatch/submatch.html>`_
    based on the efficient `novel algorithm <2017_trofimovich_tagged_deterministic_finite_automata_with_lookahead.pdf>`_

*   `encoding support <manual/features/encodings/encodings.html>`_ for ASCII, UTF-8, UTF-16, UTF-32, UCS-2, EBCDIC

*   highly `configurable <manual/syntax/syntax.html#configurations>`_ interface
    and `generic input API <manual/features/generic_api/generic_api.html>`_

*   `self-validation <manual/features/skeleton/skeleton.html>`_
    and static analysis in the form of `warnings <manual/warnings/warnings.html>`_

*   ... and other `useful features <manual/features/features.html>`_




News & updates
--------------

* `Release 1.0.1 <news/release_notes/1_0_1.html>`_
* `Release 1.0 <news/release_notes/1_0.html>`_
* ... and `older news <news/news.html>`_


.. |feed| image:: feed/feed/feed.png
    :target: feed/atom.xml
    :class:  feed
    :width:  2em

`Subscribe <feed/atom.xml>`_ to receive the latest news and updates: |feed|



Bugs & feedback
---------------

The best place to report a bug is `on github <https://github.com/skvadrik/re2c>`_
or in `re2c-devel <re2c-devel@lists.sourceforge.net>`_ and `re2c-general <re2c-general@lists.sourceforge.net>`_ mailing lists.
Note that re2c is hosted on both `github <https://github.com/skvadrik/re2c>`_
and `sourceforge <https://sourceforge.net/p/re2c>`_:
github serves as the main repository, bugtracker, and tarball hosting;
sourceforge is used as a backup repository and for mail.



Contribute
----------

Contributions can come in various forms: bug reports, patches, pull requests, discussion.
A very easy and valuable contribution is adding your lexer to the main re2c test suite
(this is also a good way to make sure that re2c updated will not break your code).
All contributions are welcome!



Projects that use re2c
----------------------

* `PHP <http://php.net/>`_ (general-purpose scripting language)
* `ninja <https://ninja-build.org/>`_ (small build system with a focus on speed)
* `yasm <http://yasm.tortall.net/>`_ (assembler)
* `spamasassin <https://spamassassin.apache.org/>`_ (anti-spam platform)
* `BRL-CAD <http://brlcad.org/>`_ (cross-platform solid modeling system)
* ... last but not least, `re2c <http://re2c.org>`_

This list is by no means complete.
These are only the best-known and open source projects.


