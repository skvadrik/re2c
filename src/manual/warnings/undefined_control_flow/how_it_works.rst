How it works
~~~~~~~~~~~~

Every path in the generated DFA must contain at least one accepting state,
otherwise it causes undefined behaviour and should be reported.
re2c walks DFA in deep-first search and checks all paths.
Each branch of search aborts as soon as it meets accepting state.
Most of the real-world programs only forget to handle a few cases,
so almost all branches abort soon and search takes very little time even for a large DFA.
In pathological cases re2c avoids exponential time and space
consumption by placing an upper bound on the number of faulty patterns.
The shortest patterns are reported first.

Note that the analyses is done anyway.
The option ``-Wundefined-control-flow`` only controls if the warning is reported or not.

