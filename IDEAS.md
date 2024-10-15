If you run out of ideas of how to make re2c better...

## Multibyte switch

Reading multiple characters at a time is problematic due to the absence of
alignment guarantees: even if unaligned reads are supported by the CPU, they are
still likely to be slow.

But it should be possible to read a few characters, combine them into one using
shifts and bitwise operations, and then switch on the combined character. It can
be done with existing API; no new primitives are needed.

Of course it will only help in cases when the underlying DFA has long "chains"
of transitions without branches that can be collapsed into one transition. But
the optimization can be local (applied to some parts of the DFA).

## User-defined language support

The idea originated in a linux.org.ru thread (in Russian):
    https://www.linux.org.ru/news/development/16759268?cid=16762746

The original idea was to provide an API to render the generated AST into code
and let the user implement it in the form of a plugin/library. This is
problematic because 1) there is no stable AST, and 2) there are some language-
agnostic optimizations and decisions that re2c takes way before the final
rendering phase (so it is not as simple as providing a bunch or functions to
generate code for different AST nodes).

There may be another way to provide any-language support: let the user define a
set of primitives/configurations that re2c will use for language-agnostic
decisions and for code generation (some of them exist already, but not enough to
fully redefine the target language). This is akin to the idea of Midnight
Commander's skins or syntax files. re2c can provide default syntax files for
some languages (it already provides "standard" Unicode categories).

## Negation and complement

It would be good to support these operations on regular expressions, but it
requires some research. Does TDFA present any special difficulties?

## Location support

It would be good to have something like Bison locations (automatic tracking of
line/column/filename information). This is primarily useful for tokenizers and
large lexers.

