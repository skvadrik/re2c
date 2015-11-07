How it works
~~~~~~~~~~~~

For each state of the generated DFA re2c calculates the set of all rules reachable from this state
(including default rule and no rule at all).
The algorithm starts with initial state and recurses to child states.
Recursion stops if either current state is final (then its set is trivial)
or the set for current state has already been calculated.
Thus each state is processed only once and the algorithm has ``O(n)`` complexity
(where ``n`` is the number of states in DFA).
When all the sets have been calculated, re2c checks that the set of rules
reachable from each accepting state includes either accepted rule or no rule at all.

Analyses is done regardless of the ``-Wunreachable-rules`` option,
the option only controls if the warning is reported or not.

