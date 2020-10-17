[re2c][re2c] was written in 1993 by Peter Bumbulis. Since then it has been
maintained and developed by multiple volunteers. Contributions are welcome,
please have a look at the guidelines below.

## Contributions

The preferred form of a contribution is a pull request on GitHub. Patches sent
by email are also fine (but less convenient). Discussion in
[GitHub issues][issues] is welcome. Email threads are also fine (but less
convenient).

## Language guidelines

re2c is written in C++. The project uses a conservative language subset (for
portability reasons the currently used standard is C++98). The code should stay
simple and avoid complex object hierarchies and excessive use of template
metaprogramming. It should allow the reader to concentrate on the underlying
algorithms, without the language getting in the way.

The line length limit is 90 characters, indentation is 4 spaces, and the
indentation style is more or less K&R (egyptian braces).

## Updating bootstrap files

For changes that affect lexers (`.re` files), it is necessary to regenerate the
corresponding bootstrap files. This can be done by reconfiguring and
rebuilding re2c with options `--enable-lexers` (Autotools) or
`-DRE2C_REBUILD_LEXERS=ON` (CMake). `RE2C_FOR_BUILD` should be defined as a
path to an already existing re2c executable that will be used to regenerate
the lexers.

For changes that affect parser (`.ypp` files), it is necessary to regenerate
bootstrap parser files. This happens automatically if bison is installed.

For changes that update documentation, it is necessary to rebuild the
bootstrap manpages by reconfiguring and rebuilding re2c with options
`--enable-docs` (Autotools) or `-DRE2C_REBUILD_DOCS=ON` (CMake).

Please do not commit trivial updates to the bootstrap files, such as changes of
the generator version or generation date.

## Commit messages

The headline should use present tense and start with a capital letter. Commit
messages should be as descriptive as possible and avoid uncertain terms like
"fix", "refactoring", "code cleanup" and so on. Long commit messages with
explanations, examples and test instructions are welcome.

Unrelated changes should be split into multiple commits.

[re2c]: http://re2c.org/
[issues]: https://github.com/skvadrik/re2c/issues
