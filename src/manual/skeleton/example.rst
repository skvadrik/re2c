
Here is an example of a very simple program
:download:`[example.re] </manual/skeleton/example.re.txt>`
that tries to match two-digit hexadecimal numbers:

.. literalinclude:: /manual/skeleton/example.re.txt
    :language: c

We can see the generated DFA using ```re2c -D example.re | dot -Grankdir=LR -Tpng -o example.png```:

.. image:: /manual/skeleton/example.png
    :width: 60%

Given this program, ```re2c -S -o example.c example.re``` generates three files:
``example.c`` (main program), ``example.c.line4.input`` (input data) and ``example.c.line4.keys`` (expected match results).
First, let's look at the generated strings
:download:`[example.c.line4.input] </manual/skeleton/example.c.line4.input>`:

.. code-block:: none

    $ hexdump -v -e '"%08_ax " 24/1 "%02x "' -e '" |" 24/1 "%_p" "|\n"' example.c.line4.input
    00000000 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 |........................|
    00000018 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f |........ !"#$%&'()*+,-./|
    00000030 3a 3b 3c 3d 3e 3f 40 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52 53 54 55 56 57 |:;<=>?@GHIJKLMNOPQRSTUVW|
    [ ... ]

Byte sequences correspond to the paths in DFA.
All strings are glued together, so it's hard to tell where is the end of one string and the beginning of another.
For that re2c generates keys :download:`[example.c.line4.keys] </manual/skeleton/example.c.line4.keys>`:

.. code-block:: none

    $hexdump -v -e '"%08_ax " 36/1 "%02x " "\n"' example.c.line4.keys
    00000000 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000024 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000048 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    [ ... ]

A key is a triplet: string length, the length of matching prefix and the number of matching rule.
(If tags are used, there is an additional key per each tag variable).
Keys are packed into an array.
In our case each key fits into 1 byte, but in case of a larger DFA they might take 2 or 4 bytes.
The generated program :download:`[example.c] </manual/skeleton/example.c.txt>`
contains two auxilary functions: ``read_file`` and ``action_line4``.
``read_file`` is used to map ``.input`` and ``.keys`` files into memory (this function is shared between all lexers).
``action_line4`` is a replacement for actions: it compares actual lexing results with the expected results.
This function is specific to each lexer.
Lexing is done by ``lex_line4``: this function contains the generated DFA.
The skeleton program is self-contained, so we can compile and run it:

.. code-block:: none

    $ cc -o example example.c
    $ ./example
    $ echo $?
    0

When everything is fine (there are no errors) the program outputs nothing and
exits with zero. For the sake of example, let's pretend that re2c has an error
that results in a missing ``case`` statement:

.. code-block:: bash

    $ re2c -S -o example.c example.re
    $ sed -i -e "s/case '7'://" example.c
    $ cc -o example example.c
    $ ./example
    error: lex_line4: at position 248 (iteration 241):
            expected: match length 2, rule 0
            actual:   match length 1, rule 254

Viola! Now the lexer complains about discrepancy between expected and actual
match results.

One special case of failure detected by skeleton programs is undefined control
flow in the lexer. Use ``-Wundefined-control-flow`` warning to catch all such
cases in in your code (more details `here </manual/manual.html#wundefined-control-flow>`_).
