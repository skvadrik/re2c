Real-world examples
~~~~~~~~~~~~~~~~~~~

The  best real-world example is a story of how ``[-Wcondition-order]`` was added to re2c.

One day I decided to change condition numbering scheme.
It was only natural: re2c assigns numbers to conditions in the order they appear in code.
This is not very convenient, because elsewhere in the code condition names (not numbers) are used as unique identifiers.
Names are sorted lexicographically, so the original condition order is not preserved.
It takes extra care to remember the mapping of names to numbers.
So why not just drop numbers and sort conditions by their names?
No one cares for condition order anyway: since re2c-generated code uses condition names,
they must be defined, and why would anyone define them by hand if they can do it automatically.

Or wait.
Almost occasionally I found a real-world program that does use fixed condition numbers.
Here is the carcass of this program:

.. code-block:: cpp
    :linenos:

    #define NORMAL 0
    #define PRE_RAW 1
    #define RAW 2
    #define INITIAL 3
    
    /*!re2c
        re2c:yyfill:check = 0;

        T_TRUE      'true'
        T_YES       'yes'
        T_ON        'on'
        T_ENABLED   'enabled'
        T_FALSE     'false'
        T_NO        'no'
        T_OFF       'off'
        T_DISABLED  'disabled'
        T_EVAL      'ev'
        T_SHELL     'sh'
        T_IF        'if'
        T_RUN       'run'
        T_RUN_SHORT "r"
        WS          [ \r\n\t]+
        DIGITS      [-]?[0-9\.]+
        ID          [^ \r\n\t:#\000]+
        ADDR        [0][x][a-fA-F0-9]+
        OPCODE      (ZEND_|zend_)([A-Za-z])+
        INPUT       [^\n\000]+

        <!*> {}
        <*>{WS}?[\n\000] {}
        <PRE_RAW, NORMAL>[-][r]{WS}?{DIGITS} {}
        <NORMAL>{T_IF}{WS} {}
        <NORMAL>{ID}[:]{1}[//]{2} {}
        <NORMAL>[#]{1} {}
        <NORMAL>[:]{2} {}
        <NORMAL>[:]{1} {}
        <NORMAL>({T_YES}|{T_ON}|{T_ENABLED}|{T_TRUE}){WS} {}
        <NORMAL>({T_NO}|{T_OFF}|{T_DISABLED}|{T_FALSE}){WS} {}
        <NORMAL>{DIGITS} {}
        <NORMAL>{ADDR} {}
        <NORMAL>{OPCODE} {}
        <NORMAL>{ID} {}
        <RAW>{INPUT} {}
        <*>{WS} {}
        <INITIAL>{T_EVAL}{WS} {}
        <INITIAL>{T_SHELL}{WS} {}
        <INITIAL>({T_RUN}|{T_RUN_SHORT}){WS} {}
        <PRE_RAW>. {}
        <INITIAL>. {}
    */

Curiously, the program somehow avoids using re2c-generated condition names:
even ``YYSETCONDITION`` is called manually instead of using ``=>`` in rules.
The program uses ``-g`` option, so the initial dispatch does depend on condition order:

.. code-block:: cpp

    static void *yyctable[4] = {
        &&yyc_NORMAL,
        &&yyc_PRE_RAW,
        &&yyc_RAW,
        &&yyc_INITIAL,
    };
    goto *yyctable[YYGETCONDITION()];

Of course, re2c will keep to the old condition numbering scheme (at least in the nearest future).
Who wants to break the old code? ``:)``

