Failures
~~~~~~~~

Skeleton's main purpose was to find and prevent errors in re2c code generation (which it did).
I don't have a ready example of failure (otherwise I would have fixed re2c),
but we can trigger various errors by alternating the generated program, input and keys.

Artificial examples
...................

Let's take the first key in ``example.c.line4.keys``  (bytes ``0x01``, ``0x01`` and ``0xFE``) and mangle it in various ways.
For example, let's change the first byte (length of current input string) to ``0xFF``:

.. code-block:: bash

    $ re2c -S -o example.c hex2.re
    $ sed -i -e 's/\x01\x01\xfe/\xff\x01\xfe/' example.c.line4.keys
    $ ./example
    error: lex_line4: unused input strings left at position 255
    error: lex_line4: unused keys left after 1 iterations

Lexer complains about unused keys and input strings.
The alternated parameter controls offset of the next string:
lexer was forced to jump past the end of input.
Now let's alter the second byte (length of the matching prefix):

.. code-block:: bash

    $ re2c -S -o example.c hex2.re
    $ sed -i -e 's/\x01\x01\xfe/\x01\x03\xfe/' example.c.line4.keys
    $ ./example
    error: lex_line4: at position 0 (iteration 0):
            expected: match length 3, rule 254
            actual:   match length 1, rule 254

Third byte stands for rule number:

.. code-block:: bash

    $ re2c -S -o example.c hex2.re
    $ sed -i -e 's/\x01\x01\xfe/\x01\x01\xfd/' example.c.line4.keys
    $ ./example
    error: lex_line4: at position 0 (iteration 0):
            expected: match length 1, rule 253
            actual:   match length 1, rule 254

Now let's change the input string:

.. code-block:: bash

    $ re2c -S -o example.c hex2.re
    $ sed -i -e 's/@/00/' example.c.line4.input
    $ ./example
    error: lex_line4: at position 3 (iteration 3):
            expected: match length 1, rule 254
            actual:   match length 2, rule 0

And so on.
Of course, some errors won't be captured by skeleton program: it's not feasible to cover all possible inputs.
For example, of all the hex digits ``[0-9a-fA-F]`` re2c uses only ``[09afAF]``:
we can mangle the lexer to not to recognize ``[1-8b-eB-E]`` as hex digits and the program won't notice.
However, the chosen values are *edge* values they are tested *extensively*
(see the section about data generation for details).


Undefined control flow
......................

One special case of failure is caused by undefined control flow in the generated lexer.
Suppose, for example, that we forgot to handle default case in the example above:

.. code-block:: cpp
    :number-lines:

    /*!re2c
        [0-9a-fA-F]{2} {}
    */

In this case re2c generates code that is perfectly correct,
but because of the undefined control flow skeleton program fails:

.. code-block:: bash

    $ re2c -S -o example.c hex2.re
    $ gcc -o example example.c
    $ ./example
    warning: lex_line3: control flow is undefined for input at position 72, rerun re2c with '-W'
    error: lex_line3: at position 72 (iteration 36):
            expected: match length 0, rule 255
            actual:   match length 3, rule 0

In this case we are lucky: lexer erroneously hit an action and was terminated.
We got a nice error and a warning that suggests that we should rerun re2c with ``-W``:

.. code-block:: bash

    $ re2c -W -S -o example.c hex2.re
    re2c: warning: line 3: control flow is undefined for strings that match 
            '[\x0-\x2F\x3A-\x40\x47-\x60\x67-\xFF]'
            '[\x30-\x39\x41-\x46\x61-\x66] [\x0-\x2F\x3A-\x40\x47-\x60\x67-\xFF]'
    , use default rule '*' [-Wundefined-control-flow]

However, it could be much worse: segfault or eternal loop.
One thing is for sure: the generated input would have triggered undefined control flow anyway.


