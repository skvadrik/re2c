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


re2c is a lexer generator for C/C++.
Its key features are:

*   Very fast lexers: the generated code is as good as a carefully tuned hand-crafted C/C++ lexer.
    It's because re2c generates minimalistic hard-coded state machine
    (as opposed to full-featured table-based lexers).

*   Flexible API: the generated code can be wired into virtually any environment.
    Instead of exposing traditional ``yylex()`` style API, re2c exposes its internals.
    This gives you several opportunities.
    First, you can avoid unnecessary overhead: drop useless runtime checks, do inplace lexing, etc.
    Second, you can adjust lexer to your particular input model.
    Third, you can make all sorts of strange hacks.
    Of course, this means that you have to be careful:
    with great power comes great responsibility.
    Be sure to take a look at `examples <examples/examples.html>`_,
    they cover a lot of real-world cases and shed some light on dark corners of re2c API.

*   `Warnings <manual/warnings/warnings.html>`_ (static analyses):
    re2c warns you when your code is bad and suggests a fix.

*   `Autognerated tests <manual/features/skeleton/skeleton.html>`_ (dynamic analyses):
    re2c generates test program together with the input data.
    The generated input has very good coverage.

*   `License <about/about.html>`_ (public domain).



Bugs & feedback
---------------

Please send feedback to `re2c-devel <re2c-devel@lists.sourceforge.net>`_ and
`re2c-general <re2c-general@lists.sourceforge.net>`_ mailing lists
(search `mail archieves <https://sourceforge.net/p/re2c/mailman/>`_ for old threads)
or `report a bug <https://github.com/skvadrik/re2c/issues>`_.

Note that re2c is hosted both on `github <https://github.com/skvadrik/re2c>`_
and on `sourceforge <https://sourceforge.net/p/re2c>`_ for redundancy.
Currently github serves as main repository, bugtracker and binary hosting.
Sourceforge is used as backup repository and to host mail
(so please don't send bugs or feedback to sourceforge).


News & updates
--------------

.. |feed| image:: feed/feed/feed.png
    :target: feed/atom.xml
    :class:  feed
    :width:  2em

Subscribe to receive latest news and updates: |feed|



Projects that use re2c
----------------------

* `PHP <http://php.net/>`_ (general-purpose scripting language)
* `ninja <https://ninja-build.org/>`_ (a small build system with a focus on speed)
* `yasm <http://yasm.tortall.net/>`_ (assembler)
* `spamasassin <https://spamassassin.apache.org/>`_ (anti-spam platform)
* `BRL-CAD <http://brlcad.org/>`_ (cross-platform solid modeling system)
* ... last but not least, `re2c <http://re2c.org>`_

This list is by no means complete;
these are only the most well-known and open source projects.



Contribute
----------

Contributions come in various forms:

* Tests: a very easy and valuable contribution is to add your lexer to re2c test suite.
  Real-world tests are the best.
  Feel free to strip out all non-re2c code if you must keep it secret.
  In return re2c will not break your code (re2c developers strive to never break existing tests).

* Ideas: new features and new ways to use re2c.

* Development: bugfixes, features, ports to other languages.

Everyone is welcome!


