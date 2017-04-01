Real-world examples
~~~~~~~~~~~~~~~~~~~

Many real-world examples deal with preprocessed input,
so they make strong assumptions about the input form or character set.
These assumptions may or may not be valid under certain circumstances;
however, double-checking won't hurt.
Even it you are absolutely sure that the default case is impossible, do handle it.
**It adds no overhead.**
No additional checks and transitions are added.
It simply binds code to the default label.

I found ``[-Wundefined-control-flow]`` warnings useful in many real-world programs (including re2c's own lexer).
Mostly these are minor issues like forgetting to handle newlines or zeros in already preprocessed input,
but it's curious how they crept into the code.
I bet they were just forgotten and not omitted for a good reason. ``:)``


