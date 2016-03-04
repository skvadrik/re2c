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
It has two key features:

* Very fast lexers. The generated code is like a carefully tuned hand-crafted C/C++ lexer.
  It's because re2c generates minimalistic hard-coded DFA
  (as opposed to full-featured table based lexers).

* Very flexible lexers. The generated code can be wired into virtually any environment.
  Instead of exposing a traditional API, re2c gives you access to its internals,
  so that you can mess with the guts of your lexer as much as you need.
  Of course, this can lead to all sorts of bad things.
  With great flexibility comes great responsibility. ;)
  Be sure to take a look at `examples <examples/examples.html>`_,
  they cover a lot of real-world cases and
  shed some light on dark corners of re2c API.



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
* `BLR-CAD <http://brlcad.org/>`_ (cross-platform solid modeling system)
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


