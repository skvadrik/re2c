=======
Install
=======

.. toctree::
    :hidden:

Download
========

Tarballs
--------

* `re2c-0.16.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.16/re2c-0.16.tar.gz>`_
* `re2c-0.15.3.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.15.3/re2c-0.15.3.tar.gz>`_
* `re2c-0.14.3.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.14.3/re2c-0.14.3.tar.gz>`_
* `re2c-0.13.7.5.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.13.7.5/re2c-0.13.7.5.tar.gz>`_
* `re2c-0.13.6.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.13.6/re2c-0.13.6.tar.gz>`_
* `re2c-0.13.5.tar.gz <http://sourceforge.net/projects/re2c/files/re2c/0.13.5/re2c-0.13.5.tar.gz/download>`_

You can find other releases `here <https://sourceforge.net/projects/re2c/files/old/>`_
(but be aware that they are hidden for a good reason:
most of them contain bugs that have been fixed in the next minor release).

Sources
-------

re2c is hosted on `github <https://github.com/skvadrik/re2c>`_:

.. code-block:: bash

    $ git clone git@github.com:skvadrik/re2c.git re2c

There's also a mirror on `sourceforge <https://sourceforge.net/p/re2c/code-git/ci/master/tree/>`_
(should be in sync with github):

.. code-block:: bash

    $ git clone ssh://git.code.sf.net/p/re2c/code-git re2c

Distributions
-------------

Linux
~~~~~

* `Alt <http://www.sisyphus.ru/ru/srpm/Sisyphus/re2c>`_
* `Arch <https://www.archlinux.org/packages/extra/x86_64/re2c>`_
* `Debian <https://packages.debian.org/search?keywords=re2c>`_
* `Gentoo <https://packages.gentoo.org/packages/dev-util/re2c>`_
* `Fedora <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=fedora>`_
* `Mageia <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=mageia>`_
* `Mandriva <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=mandriva>`_
* `OpenSuSE <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=opensuse>`_
* `RedHat <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=dag>`_
* `Slackware <http://slackbuilds.org/repository/14.1/development/re2c/?search=re2c>`_
* `Ubuntu <http://packages.ubuntu.com/search?keywords=re2c>`_

Summary of available re2c versions in many (but not all) Linux distributions
can be found on `pkgs.org <http://pkgs.org/download/re2c>`_.

BSD
~~~

* `Apple Mac OS X <http://macappstore.org/re2c/>`_
* `FreeBSD <http://www.freebsd.org/cgi/ports.cgi?query=re2c>`_
* `NetBSD <ftp://ftp.netbsd.org/pub/pkgsrc/current/pkgsrc/devel/re2c/README.html>`_
* `OpenBSD <http://www.openbsd.org/4.5_packages/sh/re2c-0.13.5.tgz-long.html>`_

Build
=====

You only need C++98 compier to build re2c from tarball.
If you have bison, re2c will use it (otherwise it will use precompiled files).

If you are building re2c from source (not from tarball), you will also need autotools:

.. code-block:: bash

    $ ./autogen.sh

Simple
------

This will install re2c (binary and manpage) to ``prefix`` (``/usr/local`` by default):

.. code-block:: bash

    $ ./configure [--prefix=<prefix>]
    $ make
    $ make install

Bootstrap
---------

Some parts of re2c (lexers and parser of command-line options) are written in re2c.
These files are precompiled and packaged into re2c distribution (so that re2c can be built without re2c).
However, one can fully bootstrap re2c:

.. code-block:: bash

    $ make bootstrap

Out-of-source
-------------

re2c supports out-of-source builds:

.. code-block:: bash

    $ mkdir builddir && cd builddir
    $ ../configure [--prefix=<prefix>]
    $ make
    $ make install

Windows
-------

If you intend to use re2c on Windows, you can either
use `cygwin <https://cygwin.com/>`_
or build re2c with `mingw <http://mingw.org/>`_:

.. code-block:: bash

    $ ./configure --host i686-w64-mingw32  [--prefix=<prefix>]
    $ make
    $ make install

(mingw builds are supported and tested regularly).

Test
====

re2c has a main test suite and a couple of small tests. Run them all:

.. code-block:: bash

    $ make check

Or run only the main test suite (and watch progress dumped to ``stdout``):

.. code-block:: bash

    $ make tests

Run test suite under `valgrind <http://valgrind.org/>`_ (takes a long time):

.. code-block:: bash

    $ make vtests

Test mingw builds with `wine <https://www.winehq.org/>`_:

.. code-block:: bash

    $ make wtests

Check the distribution:

.. code-block:: bash

    $ make distcheck


