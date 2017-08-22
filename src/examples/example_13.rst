Records & structs
-----------------

This example shows how to parse simple non-recursive structures and records.
It uses both s-tags (for simple fields) and m-tags (for fields that contain multiple elements).
Our imaginary records describe IRC users.
Each record consists of a nickname followed by an opening curly brace, a list of attributes (one per line), and a closing curly brace.
Attributes are name, country and a list of IRC channels.
Below is an example:

:download:`[records.dat] <13_records.dat.txt>`

.. literalinclude:: 13_records.dat.txt

:download:`[records.re] <13_records.i--tags.re>`

.. literalinclude:: 13_records.i--tags.re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --tags -o records.cc records.re
    $ g++ -o records records.cc

Run:

.. code-block:: bash

    $ ./records records.dat

    h4cker1970
      name:     Jon Smith
      country:  UK
      channels:
        freenode/#gentoo-dev
        freenode/#gentoo-arch
        freenode/#alpha
    
    mitek
      name:     Mitrofan Rygoravich
      country:  Belarus
      channels:
        bynets/#haskell
        freenode/#unix

