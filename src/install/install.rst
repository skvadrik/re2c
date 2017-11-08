=======
Install
=======

.. toctree::
    :hidden:

Download
========

Below is the list of the latest (stable) tarballs for each branch.
You can find other releases `here <https://sourceforge.net/projects/re2c/files/old/>`_
(but be aware that they are hidden for a good reason:
most of them contain bugs that have been fixed in the next minor release).

* `re2c-1.0.3.tar.gz <https://github.com/skvadrik/re2c/releases/download/1.0.3/re2c-1.0.3.tar.gz>`_
* `re2c-0.16.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.16/re2c-0.16.tar.gz>`_
* `re2c-0.15.3.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.15.3/re2c-0.15.3.tar.gz>`_
* `re2c-0.14.3.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.14.3/re2c-0.14.3.tar.gz>`_
* `re2c-0.13.7.5.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.13.7.5/re2c-0.13.7.5.tar.gz>`_
* `re2c-0.13.6.tar.gz <https://github.com/skvadrik/re2c/releases/download/0.13.6/re2c-0.13.6.tar.gz>`_
* `re2c-0.13.5.tar.gz <http://sourceforge.net/projects/re2c/files/re2c/0.13.5/re2c-0.13.5.tar.gz/download>`_

Source files are `on github <https://github.com/skvadrik/re2c>`_:

.. code-block:: bash

    $ git clone https://github.com/skvadrik/re2c.git re2c

There's also a mirror on `sourceforge <https://sourceforge.net/p/re2c/code-git/ci/master/tree/>`_
(should be in sync with github):

.. code-block:: bash

    $ git clone https://git.code.sf.net/p/re2c/code-git re2c

Many distributions and systems provide their own packages:
`Alt <http://www.sisyphus.ru/ru/srpm/Sisyphus/re2c>`_,
`Apple Mac OS X <http://macappstore.org/re2c/>`_,
`Arch <https://www.archlinux.org/packages/extra/x86_64/re2c>`_,
`Debian <https://packages.debian.org/search?keywords=re2c>`_,
`Gentoo <https://packages.gentoo.org/packages/dev-util/re2c>`_,
`Fedora <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=fedora>`_,
`FreeBSD <http://www.freebsd.org/cgi/ports.cgi?query=re2c>`_,
`Mageia <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=mageia>`_,
`Mandriva <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=mandriva>`_,
`NetBSD <ftp://ftp.netbsd.org/pub/pkgsrc/current/pkgsrc/devel/re2c/README.html>`_,
`OpenSuSE <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=opensuse>`_,
`RedHat <http://rpmfind.net/linux/rpm2html/search.php?query=re2c&system=dag>`_,
`Slackware <http://slackbuilds.org/repository/14.1/development/re2c/?search=re2c>`_,
`Ubuntu <http://packages.ubuntu.com/search?keywords=re2c>`_.

Build
=====

The only required build-time dependency for re2c is a C++98 compiler.
Optional build-time dependencies are the following:
autotools (to build re2c from source, not from distribution tarball),
bison (to rebuild re2c parser)
and rst2man (to rebuild documentation).

If you are building re2c from source, first of all you should run autoconf and automake:

.. code-block:: bash

    $ ./autogen.sh

The simplest possible build is an in-tree build.
The following instructions will install re2c (binary and manpage) to ``_p_r_e_f_i_x_`` (by default ``/usr/local``):

.. code-block:: bash

    $ ./configure --prefix=_p_r_e_f_i_x_
    $ make
    $ make install

Since re2c is a self-hosting lexer generator (some parts of re2c are written in re2c), it needs to be bootstrapped.
Bootstrapping files are packaged into the re2c distribution, so that re2c can be built on a system without re2c.
The following instructions bootstrap re2c from scratch and update precompiled files:

.. code-block:: bash

    $ make bootstrap

re2c supports out-of-tree builds:

.. code-block:: bash

    $ mkdir builddir && cd builddir
    $ ../configure
    $ make
    $ make install

If you intend to use re2c on Windows, you can either
use `cygwin <https://cygwin.com/>`_
or build re2c with `mingw <http://mingw.org/>`_
(mingw builds are supported and tested regularly).

.. code-block:: bash

    $ ./configure --host i686-w64-mingw32
    $ make
    $ make install

To rebuild re2c documentation:

.. code-block:: bash

    $ ./configure --enable-docs
    $ make docs


Test
====

re2c has a main test suite and a couple of small tests. Run them all:

.. code-block:: bash

    $ make check

Or run only the main test suite (and watch progress dumped to ``stdout``):

.. code-block:: bash

    $ make tests

Run the test suite under `valgrind <http://valgrind.org/>`_ (takes a long time):

.. code-block:: bash

    $ make vtests

Test mingw builds with `wine <https://www.winehq.org/>`_:

.. code-block:: bash

    $ make wtests

Check the distribution:

.. code-block:: bash

    $ make distcheck


