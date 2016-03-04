Real-world examples
~~~~~~~~~~~~~~~~~~~

In general, it is a common mistake to use ``*`` instead of ``+`` in repetitions.
That is, to accept zero or more repetitions instead of one or more.

Typos in definitions
....................

Here is the skeleton of REXX lexer (the very lexer which motivated Peter to write re2c ``:)``).

.. code-block:: cpp
    :linenos:

    /*!re2c
        all    = [\000-\377];
        eof    = [\000];
        any    = all\eof;
        letter = [a-z]|[A-Z];
        digit  = [0-9];
        symchr = letter|digit|[.!?_];
        const  = (digit|[.])symchr*([eE][+-]?digit+)?;
        simple = (symchr\(digit|[.]))(symchr\[.])*;
        stem   = simple [.];
        symbol = symchr*;
        sqstr  = ['] ((any\['\n])|(['][']))* ['];
        dqstr  = ["] ((any\["\n])|(["]["]))* ["];
        str    = sqstr|dqstr;
        ob     = [ \t]*;
        not    = [\\~];
        A      = [aA];
        B      = [bB];
        C      = [cC];
        D      = [dD];
        E      = [eE];
        F      = [fF];
        G      = [gG];
        H      = [hH];
        I      = [iI];
        J      = [jJ];
        K      = [kK];
        L      = [lL];
        M      = [mM];
        N      = [nN];
        O      = [oO];
        P      = [pP];
        Q      = [qQ];
        R      = [rR];
        S      = [sS];
        T      = [tT];
        U      = [uU];
        V      = [vV];
        W      = [wW];
        X      = [xX];
        Y      = [yY];
        Z      = [zZ];
    
        "\n"                                  {}
        "|" ob "|"                            {}
        "+"                                   {}
        "-"                                   {}
        "*"                                   {}
        "/"                                   {}
        "%"                                   {}
        "/" ob "/"                            {}
        "*" ob "*"                            {}
        "="                                   {}
        not ob "=" | "<" ob ">" | ">" ob "<"  {}
        ">"                                   {}
        "<"                                   {}
        ">" ob "=" | not ob "<"               {}
        "<" ob "=" | not ob ">"               {}
        "=" ob "="                            {}
        not ob "=" ob "="                     {}
        ">" ob ">"                            {}
        "<" ob "<"                            {}
        ">" ob ">" ob "=" | not ob "<" ob "<" {}
        "<" ob "<" ob "=" | not ob ">" ob ">" {}
        "&"                                   {}
        "|"                                   {}
        "&" ob "&"                            {}
        not                                   {}
        ":"                                   {}
        ","                                   {}
        "("                                   {}
        ")"                                   {}
        ";"                                   {}
        A D D R E S S                         {}
        A R G                                 {}
        C A L L                               {}
        D O                                   {}
        D R O P                               {}
        E L S E                               {}
        E N D                                 {}
        E X I T                               {}
        I F                                   {}
        I N T E R P R E T                     {}
        I T E R A T E                         {}
        L E A V E                             {}
        N O P                                 {}
        N U M E R I C                         {}
        O P T I O N S                         {}
        O T H E R W I S E                     {}
        P A R S E                             {}
        P R O C E D U R E                     {}
        P U L L                               {}
        P U S H                               {}
        Q U E U E                             {}
        R E T U R N                           {}
        S A Y                                 {}
        S E L E C T                           {}
        S I G N A L                           {}
        T H E N                               {}
        T R A C E                             {}
        W H E N                               {}
        O F F                                 {}
        O N                                   {}
        B Y                                   {}
        D I G I T S                           {}
        E N G I N E E R I N G                 {}
        E R R O R                             {}
        E X P O S E                           {}
        F A I L U R E                         {}
        F O R                                 {}
        F O R E V E R                         {}
        F O R M                               {}
        F U Z Z                               {}
        H A L T                               {}
        L I N E I N                           {}
        N A M E                               {}
        N O T R E A D Y                       {}
        N O V A L U E                         {}
        S C I E N T I F I C                   {}
        S O U R C E                           {}
        S Y N T A X                           {}
        T O                                   {}
        U N T I L                             {}
        U P P E R                             {}
        V A L U E                             {}
        V A R                                 {}
        V E R S I O N                         {}
        W H I L E                             {}
        W I T H                               {}
        const                                 {}
        simple                                {}
        stem                                  {}
        symbol                                {}
        str                                   {}
        str [bB] / (all\symchr)               {}
        str [xX] / (all\symchr)               {}
        eof                                   {}
        any                                   {}
    */

```re2c -Wmatch-empty-string``` warns:

.. code-block:: none

    re2c: warning: line 133: rule matches empty string [-Wmatch-empty-string]

The faulty rule is ``symbol``.
It is defined as ``symchr*`` and clearly is nullable.
In this particular example (assuming ASCII encoding) empty match is shadowed by other rules:
together ``eof`` and ``any`` cover all possible code units.
So in this case there is no chance of hitting eternal loop.

However, by no means ``symbol`` should be nullable: it makes no sense.
Sure, it's just a typo and the author meant ``symchr+``.


Skipping uninteresting stuff
............................

One often needs to skip variable number of, say, spaces:

.. code-block:: cpp

    /*!re2c
        TABS_AND_SPACES = [ \t]*;
    */

This definition is ok when used inside of another (non-nullable) rule:

.. code-block:: cpp

    /*!re2c
        TABS_AND_SPACES = [ \t]*;
        "(" TABS_AND_SPACES ("int" | "integer") TABS_AND_SPACES ")" {}
    */

However, as a standalone rule it may cause eternal loop on ill-formed input.
And it's very common to reuse one rule for multiple purposes.



