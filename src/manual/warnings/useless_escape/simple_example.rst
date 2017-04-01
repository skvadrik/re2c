A simple example
~~~~~~~~~~~~~~~~

.. code-block:: cpp
    :linenos:

    /*!re2c
        *                        {}
        "\a\A\"\'\[\]\-\x5d\377" {}
        '\a\A\"\'\[\]\-\x5d\377' {}
        [\a\A\"\'\[\]\-\x5d\377] {}
    */

Given this code, ```re2c -Wuseless-escape``` reports a bunch of warnings:

.. code-block:: none

    re2c: warning: line 3: column 11: escape has no effect: '\A' [-Wuseless-escape]
    re2c: warning: line 3: column 15: escape has no effect: '\'' [-Wuseless-escape]
    re2c: warning: line 3: column 17: escape has no effect: '\[' [-Wuseless-escape]
    re2c: warning: line 3: column 19: escape has no effect: '\]' [-Wuseless-escape]
    re2c: warning: line 3: column 21: escape has no effect: '\-' [-Wuseless-escape]
    re2c: warning: line 4: column 11: escape has no effect: '\A' [-Wuseless-escape]
    re2c: warning: line 4: column 13: escape has no effect: '\"' [-Wuseless-escape]
    re2c: warning: line 4: column 17: escape has no effect: '\[' [-Wuseless-escape]
    re2c: warning: line 4: column 19: escape has no effect: '\]' [-Wuseless-escape]
    re2c: warning: line 4: column 21: escape has no effect: '\-' [-Wuseless-escape]
    re2c: warning: line 5: column 11: escape has no effect: '\A' [-Wuseless-escape]
    re2c: warning: line 5: column 13: escape has no effect: '\"' [-Wuseless-escape]
    re2c: warning: line 5: column 15: escape has no effect: '\'' [-Wuseless-escape]
    re2c: warning: line 5: column 17: escape has no effect: '\[' [-Wuseless-escape]

This is because the ``\A`` and ``\[`` escapes are meaningless in all rules,
``\-`` makes sense only in a character class, 
and each type of closing quotes (``"``, ``'`` and ``]``) should only be escaped inside of a string delimited with the same quotes.
Useless escapes are ignored: the escaped symbol is treated as not escaped (``\A`` becomes ``A``, etc.).
The above example should be fixed as follows:

.. code-block:: cpp
    :linenos:

    /*!re2c
        *                    {}
        "\aA\"'[]-\x5d\377"  {}
        '\aA"\'[]-\x5d\377'  {}
        [\aA"'[\]\-\x5d\377] {}
    */


