Real-world examples
~~~~~~~~~~~~~~~~~~~

Many real-world examples deal with preprocessed input,
so they make strong assumptions about the input form or character set.
These assumptions may or may not be valid under certain circumstances;
however, double-check won't hurt.
Even it you are absolutely sure that default case is impossible, do handle it.
**It adds no overhead.**
No additional checks and transitions.
It simply binds code to default label.

I found ``[-Wundefined-control-flow]`` warnings in many real-world programs (including re2c own lexer).
Mostly these are minor issues like forgetting to handle newlines or zeroes in already preprocessed input,
but it's curious how they creeped into the code.
I bet they were just forgotten and not omitted for a good reason. ``:)``


