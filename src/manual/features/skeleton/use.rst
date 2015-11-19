Use
~~~

Code verification
.................

When re2c transforms regular expressions to code, it uses several internal representations:

1. Regular expressions are parsed and transformed into abstract syntax tree (AST).
2. AST is compiled to bytecode.
3. Bytecode is used to construct deterministic finite automaton (DFA).
4. DFA undergoes some transformations.
5. Transformed DFA is compiled to C/C++ code.

Skeleton is constructed right after stage 3, before any additional changes have been made to DFA.
Skeleton is in fact a simplified copy of DFA (better suited for deriving data and freed of all irrelevant information).
It is used only to generate ``.input`` and ``.keys`` files.
The rest of skeleton program is the usual re2c-generated code:
``-S, --skeleton`` option only resets environment bindings, but does not affect any code generation decisions.

Skeleton programs are therefore capable of catching various errors in code generation.
In other words, it is much safer to rebalance nested ``if`` statements,
add some novel dispatch mechanism, apply various code deduplication or inlining optimizations
and otherwise reorganize and tweak the generated code.


Benchmarks
..........

Another direct application of skeleton is benchmarking.
There is no need to construct benchmarks by hand: re2c automatically converts any real-world program
to a ready benchmark and provides input data.
One only needs to measure execution time of the generated program
(and perhaps adjust it by running the main loop multiple times).


Executable specs
................

Because of the fact that skeleton ignores all non-re2c code (including actions),
skeleton programs don't need any additional code.
One can just sketch a regular expression specification
and immediately get an executable program.



