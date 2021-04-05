[-Wsentinel-in-midrule]
-----------------------

When using sentinel method of checking for the end of input, it is easy to
forget that the sentinel symbol must not be allowed in the middle of the rule.
For example, the following code tries to match single-quoted strings. It allows
any character except the single quote to occur in the string, including
terminating ``NULL``. As a result, the generated lexer works as expected on
well-formed input like ``'aaa'\0``, but things go wrong on ill-formed input like
``'aaa\0`` (where the closing single quote is missing). Lexer reaches the
terminating ``NULL`` and assumes it is a part of the single-quoted string, so
it continues reading bytes from memory. Eventually the lexer terminates due to
memory access violation, or worse --- it accidentally hits a single quote and
assumes this to be the end of the string.

.. code-block:: cpp

    #include <assert.h>
    
    int lex(const char *YYCURSOR)
    {
        /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        ['] [^']* ['] { return 0; }
        *             { return 1; }
        */
    }
    
    int main()
    {
        assert(lex("'good'") == 0);
        assert(lex("'bad") == 1);
        return 0;
    }

On this code re2c reports a warning. It cannot be certain that ``NULL`` is the sentinel
symbol, but this is by far the most common case.

.. code-block:: none

    $ re2c -Wsentinel-in-midrule example.re -oexample.c
    example.re:9:18: warning: sentinel symbol 0 occurs in the middle of the rule
        (note: if a different sentinel symbol is used, specify it with 're2c:sentinel' configuration) [-Wsentinel-in-midrule]

However, re2c suggests us to define the sentinel symbol using ``re2c:sentinel``
configuration. Let's do it.

.. code-block:: cpp

    #include <assert.h>
    
    int lex(const char *YYCURSOR)
    {
        /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:sentinel = 0;
        ['] [^']* ['] { return 0; }
        *             { return 1; }
        */
    }
    
    int main()
    {
        assert(lex("'good'") == 0);
        assert(lex("'bad") == 1);
        return 0;
    }

The warning has turned into an error, as re2c is now certain that the code
contains an error.

.. code-block:: none

    $ re2c -Wsentinel-in-midrule example.re -oexample.c
    example.re:10:18: error: sentinel symbol 0 occurs in the middle of the rule [-Werror-sentinel-in-midrule]

The code can be fixed by excluding ``NULL`` from the set of symbols allowed in
the middle of the string: ``['] [^'\x00]* [']``. If it is necessary to allow
all symbols, a more powerful EOF handling method should be used.

