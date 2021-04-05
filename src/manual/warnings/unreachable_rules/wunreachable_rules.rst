[-Wunreachable-rules]
--------------------------

Sometimes the input grammar contains rules that will never match. This can
happen for two reasons. First, some rules may be shadowed by other rules that
match the same input, but have higher priority. Second, the rule itself may be
infinitely greedy: it may consume as many input characters as it can get and
never stop, and as a result never match. Both cases indicate a problem with
the grammar, and ``-Wunreachable-rules`` detects and reports such rules.

Let's see an example of the first kind: shadowed rules (shadowed.re).

.. code-block:: cpp

    /*!re2c
        ""          { return ""; }
        *           { return "*"; }
        "a" | "b"   { return "a | b"; }
        "a"         { return "a"; }
        [\x00-\xFF] { return "[0 - 0xFF]"; }
        [^]         { return "[^]"; }
    */

In this example the empty rule ``""`` never matches, because any single code
unit is matched by other rules, which take precedence due to the longerst match.
Rule ``"a"`` is shadowed by rule ``"a" | "b"``, which also matches ``a``, but
takes precedence because it comes first. Similarly, rule ``[^]`` is shadowed by
rule ``[\x00-\xFF]``. Default rule ``*`` is also shadowed, but it's an exception
that is not reported (default case should always be handled). Shadowed rules
normally do not appear in the generated code: re2c removes them during its dead
code elimination pass.

.. code-block:: none

    $ re2c -Wunreachable-rules shadowed.re -o shadowed.c
    shadowed.re:2:16: warning: unreachable rule (shadowed by rules at lines 4, 6) [-Wunreachable-rules]
    shadowed.re:5:16: warning: unreachable rule (shadowed by rule at line 4) [-Wunreachable-rules]
    shadowed.re:7:16: warning: unreachable rule (shadowed by rules at lines 4, 6) [-Wunreachable-rules]

Now let's see an example of second kind: infinitely greedy rule (greedy.re).

.. code-block:: cpp

    /*!re2c
        [^]* { return "greeedy"; }
    */

This rule will continue eating input characters until ``YYFILL`` fails, or until
it reads past the end of buffer and causes memory access violation.

.. code-block:: none

    $ re2c -Wunreachable-rules greedy.re -o greedy.c
    greedy.re:2:9: warning: unreachable rule  [-Wunreachable-rules]

