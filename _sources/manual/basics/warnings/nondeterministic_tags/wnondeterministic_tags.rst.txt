-Wnondeterministic-tags
-----------------------

Consider the following example, in which symbol ``a`` is repeated a few times,
followed by a tag ``t``, followed by three or more repetitions of ``a``:

.. literalinclude:: /manual/basics/warnings/nondeterministic_tags/example.re
    :language: cpp

Because the repetition is greedy, it should consume as many symbols ``a``
before the tag as possible, leaving only the last three ``a`` after the tag.
With ``-Wnondeterministic-tags`` re2c gives a warning:

.. code-block:: none

    $ re2c --tags -Wnondeterministic-tags example.re -o/dev/null
    example.re:2:24: warning: tag 't' has 4th degree of nondeterminism [-Wnondeterministic-tags]

Nondeterminism degree means the maximum number of different versions of a tag
that must be tracked simultaneously during matching. Higher degrees require
more tag variables and operations on DFA transitions. Generally it is fine if
some tags have degrees 2 or 3, but higher degrees may be a point of concern, as
the transitions get cluttered with operations and the execution gets slower.

To explain nondeterminism degrees in depth, let's have a look at the generated
NFA, its determinization process and the resulting DFA.
NFA can be visualized with
``re2c --dump-nfa --tags example.re 2>&1 1>/dev/null | dot -Tsvg -o nfa.svg``
(note that debug options ``--dump-<xxx>`` only work if re2c was built in debug
mode). Some of the NFA transitions are labeled with ``97`` (ASCII code for
``a``); other are epsilon-transitions (they do not consume any symbols).
Epsilon-transition from state 5 to state 4 is tagged.

.. image:: /manual/basics/warnings/nondeterministic_tags/nfa.svg
    :width: 50%

Determinization process can be visualized with
``re2c --dump-dfa-raw --tags example.re 2>&1 1>/dev/null | dot -Tsvg -o determinization.svg``.
It shows all possible paths through the NFA when matching a string of ``a``
symbols. Transitions are labeled with ``1``, which means the first character
class (in this case  just the symbol ``a`` --- there would be more classes if
the regular expression contained other symbols). Some transitions have tag
operations: for example, ``3↑`` on transition from state 4 to state 3 means that
the version of tag ``t`` changes from 1 to 3 (upper arrow means that version 3
is set to the current input position). Boxes in-between transitions show subsets
of NFA states at each step of determinization (after consuming one more ``a``).
Each NFA state is paired with a tag version. Exploring state sets at each step,
we can see that the maximum number of different tag versions is 4 (``t1``,
``t5``, ``t4``, ``t3``). Therefore tag ``t`` has 4th degree of nondeterminism.

.. image:: /manual/basics/warnings/nondeterministic_tags/determinization.svg
    :width: 70%

The resulting DFA (before optimizations) can be visualized with
``re2c --dump-dfa-det --tags example.re 2>&1 1>/dev/null | dot -Tsvg -o dfa.svg``.
4Th degree of nondeterminism causes the relatively high number of copy
operations on the looping transition in state 3.

.. image:: /manual/basics/warnings/nondeterministic_tags/dfa.svg
    :width: 40%

In this case it is sufficient to move tag ``t`` past the counted repetition
(as in ``[a]*[a]{3} @t [a]*`` or introduce another tag ``u`` on which ``t``
can be fixed (as in ``[a]* @t [a]{3} @u [a]*``) in order to decrease
nondeterminism degree to 1 (in the latter case ``t`` will not require any
tag operations at all, because it will be computed from ``u`` by subtracting a
fixed offset).
