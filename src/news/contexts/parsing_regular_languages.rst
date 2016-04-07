=========================
Parsing regular languages
=========================

.. toctree::
    :hidden:

It is a truth universally acknowledged,
that *parsing* regular languages is not the same as just *recognizing* them.
Parsing is way more difficult: it introduces the notion of ambiguity,
which immediately poses ambiguity decision problem
and gives rise to a bunch of disambiguation techniques.
Even if we put aside ambiguity, still there is a problem of efficient extraction of parse results:
non-determinism of the underlying automata is a clear advantage in this respect,
but NFA are not as fast as DFA.

The question is, given a regular expression recognizer, what is the best way of turning it into a parser?
Well, the real question is, how do we add submatch extraction to re2c,
while retaining the extreme speed of direct executable DFA?
As usual, there's no solution to the problem in general:

    *No servant can serve two masters:
    for either he will hate the one, and love the other;
    or else he will hold to the one, and despise the other.*

All existing techniques for parsing regular grammars (those I'm aware of)
are a kind of compromise: they trade off recognition speed for parsing ability.
In many cases this is quite acceptable:
interpreting engines are inherently slower than compiled regular expressions.
They are usually NFA-based and don't aim at extreme speed (they are *fast enough*).
Captures? Eh. Such engines don't even hesitate to allow backreferences,
which throw them far beyond regular languages and imply exponential recognition complexity.
Captures are simply not an issue.
Well, they have a clear practical goal: regular expressions should be *easy to use*.

On the other side, there are compiling engines that are mad about generating fast code.
They are willing to increase compilation time and complexity
in order to gain even a little run-time speed.
Their definition of *practical* is somewhat less popular: regular expressions should be a *zero-cost abstraction*;
in fact, compiled code should be better than hand-crafted (faster, smaller).
One such engine is re2c, and in the battle of speed against generality re2c will surely hold to speed.

Then there is the third camp: engines that try to take best of both worlds,
kind of JIT-compilers for regular expressions.
Such engines usually incorporate a bunch of techniques ranging from fast substring search to backtracking,
including NFA, DFA and mixed approaches like cached NFA, also known as lazy DFA.
The choice of technique is based on the given regular expression:
it must be the fastest technique still capable of handling the given expression.
In case of backreferences the engine will fallback to exponential backtracking;
in case of captures it will probably use NFA.

And than there are experiments: various research efforts
that yield interesting tools (usually tailored for a particular domain-specific problem).
Some of them look very promising, and we'll definitely have an overview of them.
Yet it becomes clear that even DFA-based approaches are not suitable for re2c:
they incur too much overhead.

So in the end, it seems logical that re2c should have *partial* parsing capabilities.
It should allow captures in unambiguous cases
that can be technically implemented with a simple DFA.
The rest of the article tries to formalize these requirements
and define effective procedure to find out if a given regular expression conforms to them.

The analyses is based on the work of many people:
some ideas are taken from papers,
others are inspired by fellow regular expression engines like flex and quex.
The discussion is rather informal; a thoughtful reader might notice
a couple of references at the bottom of the page.


Ambiguity
=========

In short, *ambiguity* in grammar is the possibility of parsing the same sentence in two different ways.

One should clearly see the difference between *recognition* and *parsing*.
To recognize a sentence means to tell if it belongs to the language.
To parse a sentence means to recognize it and find out its meaning in the given language.
The notion of ambiguity applies to parsing, not to recognition:
if a sentence has two different meanings, then it is ambiguous.

Ambiguity in regular grammars can take two forms: horizontal or vertical. [2]
Roughly speaking, vertical ambiguity is concerned with intersection of alternative grammar rules,
while horizontal ambiguity deals with overlap in rule concatenation.
Both kinds can be defined in terms of operations on finite-state automata.
Ambiguity problem for regular languages is decidable and has ... complexity.

Formal definition
-----------------

Ambiguity in regular expressions is defined in terms of corresponding parse trees,
so we first need to define regular expressions, 

    A *regular expression* over finite alphabet :math:`\Sigma` is:
        - :math:`\emptyset` (empty set)
        - :math:`\epsilon` (set that contains empty string)
        - :math:`a \in \Sigma` (set that contains one-symbol string :math:`a`)
        - :math:`R_1 R_2`, where :math:`R_1, R_2` are regular expressions (concatenation)
        - :math:`R_1 | R_2`, where :math:`R_1, R_2` are regular expressions (alternative)
        - :math:`R^*`, where :math:`R` is a regular expression (iteration, or Kleene star)

    Regular expression :math:`R` is *ambiguous* iff :math:`\exists \thickspace T, T' \in AST_R`
    such that :math:`T \neq T'` and :math:`\| T \| = \| T' \|`.



    Let grammar :math:`G` be a 4-tuple :math:`(N, \Sigma, P, S)`, where:
        - :math:`N` is the set of non-terminal symbols
        - :math:`\Sigma` is the set of terminal symbols
        - :math:`P` is the set of rules of the form :math:`xAy \longrightarrow z`,
          where :math:`x,y,z \in (\Sigma \cup N)^*` (the set of all strings over :math:`\Sigma \cup N`),
          :math:`A \in N`
        - :math:`S \in N` is the start symbol

    Derivation in one step:
    :math:`x \Rightarrow_{G} y`
    :math:`\iff`
    :math:`\exists u,v \in (\Sigma \cup N)^*`
    :math:`| x=upv, y=uqv, p \longrightarrow q \in P`

    Derivation:
    :math:`x \Rightarrow_{G}^* y`
    :math:`\iff`
    :math:`\exists n \in \mathbb{Z} : \thickspace x=z_0 \Rightarrow_{G} ... \Rightarrow_{G} z_n=y`

    Sentential form :math:`u` is a string in :math:`(\Sigma \cup N)^*`
    that is derived from the start symbol: :math:`S \Rightarrow_{G}^* u`

    Sentence :math:`v` is a sentential form that is free of non-terminals: :math:`v \in \Sigma^*`

    Language :math:`L(G)` is the set of all sentences generated by grammar :math:`G`.

    Grammar :math:`G` is ambiguous iff a sentence in :math:`L(G)`
    has two different derivations: :math:`\exists v \in L(G)`

    Given a grammar :math:`G = (N, \Sigma, P, S)` that generates language :math:`L(G)`, we say that
    :math:`G` is ambiguous iff there is a sentence :math:`w \in L(G)` that
    has two different parse derivations: :math:`D_{G}(w)` and :math:`D'_{G}(w)`

.. math::

    G \in AMB \iff \exists w \in L(G) | T_{G}(w)

G is ambigous <==> exists W | :math:`W^{3\beta}_{\delta_1 \rho_1 \sigma_2} \approx U^{3\beta}_{\delta_1 \rho_1}` aaaa


.. math::

  W^{3\beta}_{\delta_1 \rho_1 \sigma_2} \approx U^{3\beta}_{\delta_1 \rho_1}

Horizontal ambiguity
--------------------

Vertical ambiguity
------------------


Submatch extraction
===================

NFA
---

TDFA
----

Two DFA
-------


