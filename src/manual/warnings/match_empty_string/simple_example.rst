A simple example
~~~~~~~~~~~~~~~~

``[-Wmatch-empty-string]`` warns when a rule is nullable (matches an empty string).
It was intended to prevent infinite looping in cases such as this:

:download:`[wmatch_empty_string.re] <wmatch_empty_string.re.txt>`

.. literalinclude:: wmatch_empty_string.re.txt
    :language: cpp
    :linenos:

The program loops over its arguments (the outer ``for`` loop)
and tries to lex each argument (the inner ``for`` loop).
Lexer stops when all input has been consumed and it sees the terminating ``NULL``.
Arguments must consist of lowercase letters only.
Generate, compile and run:

.. code-block:: none

    $ re2c -o example.c -Wmatch-empty-string wmatch_empty_string.re
    re2c: warning: line 11: rule matches empty string [-Wmatch-empty-string]
    $ g++ -o example example.c
    $
    $ ./example only lowercase letters are allowed
    argv[1]: only
    argv[2]: lowercase
    argv[3]: letters
    argv[4]: are
    argv[5]: allowed
    $
    $ ./example oh really?
    argv[1]: oh
    ^C

The program hangs forever if one of the arguments is ill-formed.

Note that `[-Wundefined-control-flow] <../undefined_control_flow/wundefined_control_flow.html>`_
has no complaints about this particular case: all input patterns are covered by the rules.
Yet if we add the default rule (``*``), the lexer won't hang anymore: it will match the default rule
instead of the nullable rule.

The fix is easy: make the rule non-nullable (say, ``[a-z]+``) and add the default rule (``*``).


