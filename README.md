DESCRIPTION
-----------

re2c is a free and open-source lexer generator for C/C++, Go and Rust.

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

CONTRIBUTING
------------

re2c is an Open Source, community-driven project. See
[CONTRIBUTING.md](https://github.com/skvadrik/re2c/blob/master/CONTRIBUTING.md)
for details about contributions to this repository.


BUILD
-----

See BUILD.md or the [online docs](https://re2c.org/build/build.html) for
instructions how to build re2c.


FEEDBACK
--------

Bugtracker:

- https://github.com/skvadrik/re2c/issues

Mailing lists:

- re2c-general@lists.sourceforge.net
- re2c-devel@lists.sourceforge.net

IRC channels:

- irc.oftc.net/#re2c
- irc.libera.chat/#re2c

You are welcome to ask for help or share your thoughts and ideas.


AUTHORS
-------

re2c was originally written by Peter Bumbulis <peter@csg.uwaterloo.ca>. Since
then many volunteers have contributed to the project. The current maintainer is
Ulya Trofimovich <skvadrik@gmail.com>.
