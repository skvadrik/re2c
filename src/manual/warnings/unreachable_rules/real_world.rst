Real-world examples
~~~~~~~~~~~~~~~~~~~

In many real-world examples re2c reports unreachable ``[^]`` rule,
which is quite understandable: ``[^]`` served as default rule long before
the true default rule ``*`` was added to re2c.
However, in some cases the warning is quite interesting.
Here is an example of a real-world lexer (all the non-re2c code has beed removed):

.. code-block:: cpp
    :number-lines:

    /*!re2c
        re2c:yyfill:check = 0;
    
        LNUM                [0-9]+
        DNUM                ([0-9]*[\.][0-9]+)|([0-9]+[\.][0-9]*)
        NUMBER              [-]?{LNUM}|{DNUM}
        ANY_CHAR            (.|[\n\t])
        NEWLINE             ("\r"|"\n"|"\r\n")
        TABS_AND_SPACES     [ \t]
        WHITESPACE          [ \t]+
        CONSTANT            [a-zA-Z_][a-zA-Z0-9_]*
        LABEL               [^=\n\r\t;&|^$~(){}!"\[]+
        TOKENS              [:,.\[\]"'()&|^+-/*=%$!~<>?@{}]
        OPERATORS           [&|^~()!]
        DOLLAR_CURLY        "${"
        SECTION_RAW_CHARS   [^\]\n\r]
        SINGLE_QUOTED_CHARS [^']
        RAW_VALUE_CHARS     [^\n\r;\000]
        LITERAL_DOLLAR      ("$"([^{\000]|("\\"{ANY_CHAR})))
        VALUE_CHARS         ([^$= \t\n\r;&|^~()!"'\000]|{LITERAL_DOLLAR})
        SECTION_VALUE_CHARS ([^$\n\r;"'\]\\]|("\\"{ANY_CHAR})|{LITERAL_DOLLAR})

        <INITIAL>"[" {}
        <ST_VALUE,ST_SECTION_VALUE,ST_OFFSET>"'"{SINGLE_QUOTED_CHARS}+"'" {}
        <ST_SECTION_RAW,ST_SECTION_VALUE>"]"{TABS_AND_SPACES}*{NEWLINE}? {}
        <INITIAL>{LABEL}"["{TABS_AND_SPACES}* {}
        <ST_OFFSET>{TABS_AND_SPACES}*"]" {}
        <ST_DOUBLE_QUOTES,ST_SECTION_VALUE,ST_VALUE,ST_OFFSET>{DOLLAR_CURLY} {}
        <ST_VARNAME>{LABEL} {}
        <ST_VARNAME>"}" {}
        <INITIAL,ST_VALUE>("true"|"on"|"yes"){TABS_AND_SPACES}* {}
        <INITIAL,ST_VALUE>("false"|"off"|"no"|"none"){TABS_AND_SPACES}* {}
        <INITIAL,ST_VALUE>("null"){TABS_AND_SPACES}* {}
        <INITIAL>{LABEL} {}
        <INITIAL>{TABS_AND_SPACES}*[=]{TABS_AND_SPACES}* {}
        <ST_RAW>{RAW_VALUE_CHARS} {}
        <ST_SECTION_RAW>{SECTION_RAW_CHARS}+ {}
        <ST_VALUE,ST_RAW>{TABS_AND_SPACES}*{NEWLINE} {}
        <ST_SECTION_VALUE,ST_VALUE,ST_OFFSET>{CONSTANT} {}
        <ST_SECTION_VALUE,ST_VALUE,ST_OFFSET>{NUMBER} {}
        <INITIAL>{TOKENS} {}
        <ST_VALUE>{OPERATORS}{TABS_AND_SPACES}* {}
        <ST_VALUE>[=] {}
        <ST_VALUE>{VALUE_CHARS}+ {}
        <ST_SECTION_VALUE,ST_OFFSET>{SECTION_VALUE_CHARS}+ {}
        <ST_SECTION_VALUE,ST_VALUE,ST_OFFSET>{TABS_AND_SPACES}*["] {}
        <ST_DOUBLE_QUOTES>["]{TABS_AND_SPACES}* {}
        <ST_DOUBLE_QUOTES>[^] {}
        <ST_SECTION_VALUE,ST_VALUE,ST_OFFSET>{WHITESPACE} {}
        <INITIAL,ST_RAW>{TABS_AND_SPACES}+ {}
        <INITIAL>{TABS_AND_SPACES}*{NEWLINE} {}
        <INITIAL,ST_VALUE,ST_RAW>{TABS_AND_SPACES}*[;][^\r\n]*{NEWLINE} {}
        <ST_VALUE,ST_RAW>[^] {}
        <*>[^] {}
    */

```re2c -cF -Wunreachable-rules``` says:

.. code-block::

    re2c: warning: line 54: unreachable rule in condition 'ST_DOUBLE_QUOTES' (shadowed by rules at lines 47, 48) [-Wunreachable-rules]
    re2c: warning: line 49: unreachable rule in condition 'ST_OFFSET' (shadowed by rule at line 45) [-Wunreachable-rules]
    re2c: warning: line 54: unreachable rule in condition 'ST_RAW' (shadowed by rules at lines 36, 38, 53) [-Wunreachable-rules]
    re2c: warning: line 49: unreachable rule in condition 'ST_SECTION_VALUE' (shadowed by rule at line 45) [-Wunreachable-rules]
    re2c: warning: line 54: unreachable rule in condition 'ST_VALUE' (shadowed by rules at lines 38, 39, 40, 42, 43, 44, 46, 49, 53) [-Wunreachable-rules]

The interesting part is the unreachable rule on line 49 in conditions ``ST_OFFSET`` and ``ST_SECTION_VALUE``.
The rule is ``{WHITESPACE}``:

.. code-block::

    WHITESPACE [ \t]+

re2c claims that it is shadowed by the rule on line 45, which is ``{SECTION_VALUE_CHARS}+``:

.. code-block::

    ANY_CHAR            (.|[\n\t])
    LITERAL_DOLLAR      ("$"([^{\000]|("\\"{ANY_CHAR})))
    SECTION_VALUE_CHARS ([^$\n\r;"'\]\\]|("\\"{ANY_CHAR})|{LITERAL_DOLLAR})

Indeed, ``{SECTION_VALUE_CHARS}+`` allows all the patterns accepted by ``{WHITESPACE}``.
In the original program these rules return different types of tokens:
perhaps this is not critical, but clearly unintended.

