DESCRIPTION
-----------

re2c is a free and open-source lexer generator for C, C++ and Go.

Its main goal is generating fast lexers: at least as fast as their reasonably
optimized hand-coded counterparts. Instead of using traditional table-driven
approach, re2c encodes the generated finite state automata directly in the form
of conditional jumps and comparisons. The resulting programs are faster and
often smaller than their table-driven analogues, and they are much easier to
debug and understand. re2c applies quite a few optimizations in order to speed
up and compress the generated code.

Another distinctive feature is its flexible interface: instead of assuming a
fixed program template, re2c lets the programmer write most of the interface
code and adapt the generated lexer to any particular environment.


DOCUMENTATION
-------------

Official re2c website is [re2c.org](http://re2c.org). It has a lot of examples.


DOWNLOAD
--------

Release tarballs: https://github.com/skvadrik/re2c/releases

Source code:

```
$ git clone https://github.com/skvadrik/re2c.git
$ git clone https://git.code.sf.net/p/re2c/code-git
```

Github is the main repo, sourceforge is a mirror and can be slightly outdated.


BUILD
-----

re2c has two build systems: Autotools and CMake. Both are maintained and tested
on Travis CI. See [the documentation](http://re2c.org/install/install.html) for
instructions how to build re2c.


FEEDBACK
--------

Bugtracker:

- https://github.com/skvadrik/re2c/issues

Mailing lists:

- re2c-general@lists.sourceforge.net
- re2c-devel@lists.sourceforge.net

IRC channel:

- freenode/#re2c

You are welcome to ask for help or share your thoughts and ideas.


AUTHORS
-------
Re2c was originally written by Peter Bumbulis <peter@csg.uwaterloo.ca>.
Since then many people contributed to the project. The current maintainer is
Ulya Trofimovich <skvadrik@gmail.com>.
