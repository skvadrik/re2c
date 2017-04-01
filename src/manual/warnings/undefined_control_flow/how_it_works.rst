How it works
~~~~~~~~~~~~

Every path in the generated DFA must contain at least one accepting state,
otherwise the behavior is undefined, which should be reported.
re2c walks the DFA using a depth-first search and it checks all paths.
Each branch of the search finishes as soon as it reaches an accepting state.
Most real-world programs only forget to handle a few cases,
so almost all branches finish soon and the search takes very little time even for a large DFA.
In pathological cases, re2c avoids exponential time and space
consumption by placing an upper bound on the number of faulty patterns.
The shortest patterns are reported first.

Note that the analysis is done anyway.
The ``-Wundefined-control-flow`` option only controls if the warning is reported or not.

