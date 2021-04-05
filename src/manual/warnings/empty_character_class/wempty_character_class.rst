[-Wempty-character-class]
--------------------------

This warning is complementary to the
``--empty-class <match-empty | match-none | error>`` option.
For bakward compatibility reasons the default is ``match-empty``: empty
character class ``[]`` matches empty string (that is, it always matches without
consuming any input). This behaviour doesn't make much sense, therefore re2c
provides a warning ``-Wempty-character-class``.
Note that empty character class can be constructed in many ways, for example as
a result of range negation or the difference operator. The code below (empty.re)
demonstrates some of the possibilities:

.. code-block:: cpp

    /*!re2c
        []                        { return 0; }
        [^\x00-\xFF]              { return 1; }
        [^] \ [^]                 { return 2; }
        [abc] \ ("a" | "b" | "c") { return 3; }
        "a" \ [a-z]               { return 4; }
    */

Re2c gives the following warnings:

.. code-block:: none

    $ re2c -Wempty-character-class empty.re -o empty.c
    empty.re:2:4: warning: empty character class [-Wempty-character-class]
    empty.re:3:4: warning: empty character class [-Wempty-character-class]
    empty.re:4:4: warning: empty character class [-Wempty-character-class]
    empty.re:5:4: warning: empty character class [-Wempty-character-class]
    empty.re:6:4: warning: empty character class [-Wempty-character-class]

