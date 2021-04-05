[-Wundefined-control-flow]
--------------------------

.. toctree::
    :hidden:

With ``-Wundefined-control-flow`` warning re2c checks that every path in the
generated DFA contains at least one accepting state. When the input matches
such a path, lexer will eventually stop and execute the corresponding semantic
action. However, if some path has no accepting state, then lexer behavior is
undefined: it may loop forever, or read past the end of buffer, or jump to some
other semantic action by accident. For example, consider this simple piece of
code (a.re) that is supposed to match letter ``a``:

.. code-block:: cpp

    /*!re2c
        "a" { return 'a'; }
    */

The generated code looks like this:

.. code-block:: cpp

    {
            YYCTYPE yych;
            if (YYLIMIT <= YYCURSOR) YYFILL(1);
            yych = *YYCURSOR;
            switch (yych) {
            case 'a':       goto yy3;
            default:        goto yy2;
            }
    yy2:
    yy3:
            ++YYCURSOR;
            { return 'a'; }
    }

Clearly this is not what we want: this code matches any letter, not just ``a``!
This happens because we did not specify any handler for the remaining input symbols.
If we run re2c with ``-Wundefined-control-flow``, we will see that it complains about undefined control flow and recommends using default rule ``*``:

.. code-block:: none

    a.re:3:2: warning: control flow is undefined for strings that match '[\x0-\x60\x62-\xFF]', use the default '*' rule  [-Wundefined-control-flow]

Let's follow the advice and change the code:

.. code-block:: cpp

    /*!re2c
        *   { return '*'; }
        "a" { return 'a'; }
    */

Now the generated code looks much better:

.. code-block:: cpp

    {
            YYCTYPE yych;
            if (YYLIMIT <= YYCURSOR) YYFILL(1);
            yych = *YYCURSOR;
            switch (yych) {
            case 'a':       goto yy4;
            default:        goto yy2;
            }
    yy2:
            ++YYCURSOR;
            { return '*'; }
    yy4:
            ++YYCURSOR;
            { return 'a'; }
    }

Note that the default rule brings no overhead: it simply binds code to the
default label. It should always be used, unless you are absolutely sure that
your grammar covers all possible cases.

.. include:: /manual/warnings/undefined_control_flow/default_vs_any.rst

