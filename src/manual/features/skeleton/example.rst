Example
~~~~~~~

:download:`[hex2.re] <hex2.re.txt>`

.. literalinclude:: hex2.re.txt
    :language: c

Here is a very simple program (it tries to match two-digit hexadecimal numbers).
We can see the generated DFA using ```re2c -D hex2.re | dot -Gratio=0.5 -Tpng -o example.png```:

.. image:: example.png
    :width: 50%

Given this program, ```re2c -S -o example.c hex2.re``` generates three files:
``example.c`` (main program), ``example.c.line4.input`` (input data) and ``example.c.line4.keys`` (expected match results).
First, let's look at the generated strings:

:download:`[example.c.line4.input] <example.c.line4.input>`

.. code-block:: none

    $ hexdump -v -e '"%08_ax " 24/1 "%02x "' -e '" |" 24/1 "%_p" "|\n"' example.c.line4.input
    00000000 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 |........................|
    00000018 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f |........ !"#$%&'()*+,-./|
    00000030 3a 3b 3c 3d 3e 3f 40 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52 53 54 55 56 57 |:;<=>?@GHIJKLMNOPQRSTUVW|
    00000048 58 59 5a 5b 5c 5d 5e 5f 60 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 |XYZ[\]^_`ghijklmnopqrstu|
    00000060 76 77 78 79 7a 7b 7c 7d 7e 7f 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d |vwxyz{|}~...............|
    00000078 8e 8f 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f a0 a1 a2 a3 a4 a5 |........................|
    00000090 a6 a7 a8 a9 aa ab ac ad ae af b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd |........................|
    000000a8 be bf c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf d0 d1 d2 d3 d4 d5 |........................|
    000000c0 d6 d7 d8 d9 da db dc dd de df e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed |........................|
    000000d8 ee ef f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff 30 30 31 31 32 32 |..................001122|
    000000f0 33 33 34 34 35 35 36 36 37 37 38 38 39 39 41 41 42 42 43 43 44 44 45 45 |33445566778899AABBCCDDEE|
    00000108 46 46 61 61 62 62 63 63 64 64 65 65 66 66 30 00 31 01 32 02 33 03 34 04 |FFaabbccddeeff0.1.2.3.4.|
    00000120 35 05 36 06 37 07 38 08 39 09 41 0a 42 0b 43 0c 44 0d 45 0e 46 0f 61 10 |5.6.7.8.9.A.B.C.D.E.F.a.|
    00000138 62 11 63 12 64 13 65 14 66 15 30 16 31 17 32 18 33 19 34 1a 35 1b 36 1c |b.c.d.e.f.0.1.2.3.4.5.6.|
    00000150 37 1d 38 1e 39 1f 41 20 42 21 43 22 44 23 45 24 46 25 61 26 62 27 63 28 |7.8.9.A B!C"D#E$F%a&b'c(|
    00000168 64 29 65 2a 66 2b 30 2c 31 2d 32 2e 33 2f 34 3a 35 3b 36 3c 37 3d 38 3e |d)e*f+0,1-2.3/4:5;6<7=8>|
    00000180 39 3f 41 40 42 47 43 48 44 49 45 4a 46 4b 61 4c 62 4d 63 4e 64 4f 65 50 |9?A@BGCHDIEJFKaLbMcNdOeP|
    00000198 66 51 30 52 31 53 32 54 33 55 34 56 35 57 36 58 37 59 38 5a 39 5b 41 5c |fQ0R1S2T3U4V5W6X7Y8Z9[A\|
    000001b0 42 5d 43 5e 44 5f 45 60 46 67 61 68 62 69 63 6a 64 6b 65 6c 66 6d 30 6e |B]C^D_E`Fgahbicjdkelfm0n|
    000001c8 31 6f 32 70 33 71 34 72 35 73 36 74 37 75 38 76 39 77 41 78 42 79 43 7a |1o2p3q4r5s6t7u8v9wAxByCz|
    000001e0 44 7b 45 7c 46 7d 61 7e 62 7f 63 80 64 81 65 82 66 83 30 84 31 85 32 86 |D{E|F}a~b.c.d.e.f.0.1.2.|
    000001f8 33 87 34 88 35 89 36 8a 37 8b 38 8c 39 8d 41 8e 42 8f 43 90 44 91 45 92 |3.4.5.6.7.8.9.A.B.C.D.E.|
    00000210 46 93 61 94 62 95 63 96 64 97 65 98 66 99 30 9a 31 9b 32 9c 33 9d 34 9e |F.a.b.c.d.e.f.0.1.2.3.4.|
    00000228 35 9f 36 a0 37 a1 38 a2 39 a3 41 a4 42 a5 43 a6 44 a7 45 a8 46 a9 61 aa |5.6.7.8.9.A.B.C.D.E.F.a.|
    00000240 62 ab 63 ac 64 ad 65 ae 66 af 30 b0 31 b1 32 b2 33 b3 34 b4 35 b5 36 b6 |b.c.d.e.f.0.1.2.3.4.5.6.|
    00000258 37 b7 38 b8 39 b9 41 ba 42 bb 43 bc 44 bd 45 be 46 bf 61 c0 62 c1 63 c2 |7.8.9.A.B.C.D.E.F.a.b.c.|
    00000270 64 c3 65 c4 66 c5 30 c6 31 c7 32 c8 33 c9 34 ca 35 cb 36 cc 37 cd 38 ce |d.e.f.0.1.2.3.4.5.6.7.8.|
    00000288 39 cf 41 d0 42 d1 43 d2 44 d3 45 d4 46 d5 61 d6 62 d7 63 d8 64 d9 65 da |9.A.B.C.D.E.F.a.b.c.d.e.|
    000002a0 66 db 30 dc 31 dd 32 de 33 df 34 e0 35 e1 36 e2 37 e3 38 e4 39 e5 41 e6 |f.0.1.2.3.4.5.6.7.8.9.A.|
    000002b8 42 e7 43 e8 44 e9 45 ea 46 eb 61 ec 62 ed 63 ee 64 ef 65 f0 66 f1 30 f2 |B.C.D.E.F.a.b.c.d.e.f.0.|
    000002d0 31 f3 32 f4 33 f5 34 f6 35 f7 36 f8 37 f9 38 fa 39 fb 41 fc 42 fd 43 fe |1.2.3.4.5.6.7.8.9.A.B.C.|
    000002e8 44 ff                                                                   |D.|

Byte sequences correspond to the paths in DFA.
All strings are glued together, so it's hard to tell where is the end of one string and the beginning of another.
For that re2c generates keys:

:download:`[example.c.line4.keys] <example.c.line4.keys>`

.. code-block:: none

    $hexdump -v -e '"%08_ax " 36/1 "%02x " "\n"' example.c.line4.keys
    00000000 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000024 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000048 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    0000006c 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000090 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000000b4 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000000d8 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000000fc 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000120 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000144 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000168 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    0000018c 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000001b0 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000001d4 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000001f8 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    0000021c 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000240 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000264 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    00000288 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe
    000002ac 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 01 01 fe 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00
    000002d0 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00 02 02 00
    000002f4 02 02 00 02 02 00 02 02 00 02 02 00 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000318 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    0000033c 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000360 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000384 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000003a8 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000003cc 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000003f0 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000414 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000438 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    0000045c 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000480 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000004a4 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000004c8 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000004ec 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000510 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000534 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    00000558 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    0000057c 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe
    000005a0 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe 02 01 fe                  


A key is a triplet: string length, the length of matching prefix and the number of matching rule.
All three components occupy equal amount of memory (re2c uses unsigned integer type of minimal sufficient width).
Keys are packed into array of length ``3 * n`` (where ``n`` is the number of keys).
In our case each triplet occupies three bytes.

And finally, the program itself:

:download:`[example.c] <example.c.txt>`

.. literalinclude:: example.c.txt
    :language: c
    :linenos:

re2c generated two auxilary functions: ``read_file`` and ``action_line4``.
``read_file`` is used to map ``.input`` and ``.keys`` files into memory (this function is shared between all lexers).
``action_line4`` is a replacement for actions: it compares actual lexing results with the expected results.
This function is specific to each lexer.
Lexing is done by ``lex_line4``: this function contains the generated DFA.
``main`` simply calls the lexer.

Compile and run:

.. code-block:: none

    $ gcc -o example example.c
    $ ./example
    $ echo $?
    0

When everything is fine, the program outputs nothing and exits with zero.


