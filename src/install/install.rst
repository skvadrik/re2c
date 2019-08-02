==================
Build instructions
==================

.. toctree::
    :hidden:

Dependencies
============

Re2c users need only a C++ compiler to build re2c from a release tarball, and
optionally Bash if they want to run the tests.

Re2c developers also need Autotools, Bison (if they change parser code), rst2man
(if they change documentation), Sphinx (if they change this website), Mingw and
Wine (if they test builds for Windows) and Libtool (if they change the
experimental libre2c library). A few occasional helper scripts are written in
Haskell (but they are not necessary for re2c development).
Re2c is a bootstrapping project with all the consequences.

Building
========

If you are building re2c from repository, *not* from a release tarball, first of
all you should run Autotools:

.. code-block:: bash

    $ autoreconf -i -W all

The simplest possible build is an in-tree build (will install re2c to
``$RE2C_PATH`` location):

.. code-block:: bash

    $ ./configure --prefix=$RE2C_PATH
    $ make
    $ make install

Out-of-tree build (puts build artifacts in a separate directory):

.. code-block:: bash

    $ mkdir $BUILD_DIR
    $ cd $BUILD_DIR
    $ ../configure --prefix=$RE2C_PATH
    $ make
    $ make install

Bootstrapping build (rebuilds re2c with the freshly built re2c and updates
precompiled bootstrap files):

.. code-block:: bash

    $ make bootstrap

Building on Windows is more tricky. The best option is to use
`Cygwin <https://cygwin.com/>`_, or build re2c with `Mingw <http://mingw.org/>`_
(Mingw builds are supported and tested regularly).
For some Mingw versions you might have to use ``-std=gnu++11`` compiler option
to avoid spurious build errors (re2c uses ``-std=c++98`` by default).

.. code-block:: bash

    $ ./configure --host i686-w64-ming 32 CXXFLAGS="-std=gnu++11"

To build documentation:

.. code-block:: bash

    $ ./configure --enable-docs

To enable debug:

.. code-block:: bash

    $ ./configure --enable-debug

To build the experimental libre2c library:

.. code-block:: bash

    $ ./configure --enable-libs

Re2c provides a bunch of build scripts ``__build_*.sh`` that can be used
for specialized builds with ``GLIBCXX_DEBUG``, AddressSanitizer, etc.

Testing
=======

Re2c has a main test suite and a couple of small unit tests. Run them all:

.. code-block:: bash

    $ make check

Run only the main test suite and watch the progress dumped on ``stdout``:

.. code-block:: bash

    $ ./run_tests.sh -j<N>

Run the main test suite with ``--skeleton`` re2c option:

.. code-block:: bash

    $ ./run_tests.sh --skeleton

Run the test suite under Valgrind (takes some time and memory):

.. code-block:: bash

    $ make vtests

Test mingw builds with Wine:

.. code-block:: bash

    $ make wtests

Check the distribution:

.. code-block:: bash

    $ make distcheck

Re2c provides a helper script ``__alltest.sh`` that builds and tests various
re2c build flavours with ``GLIBCXX_DEBUG``, AddressSanitizer, etc.
There is a couple of fuzz-testing Haskell scripts in the ``fuzz`` subdirectory;
they are based on the QuickCheck library and can be easily modified to fuzz-test
various aspects of re2c by comparing current re2c version against older versions
or against other regular expression libraries.

