IPv4 address
------------

This example demonstrates how to use tags to parse simple things like IPv4 address.

:download:`[ipv4.re] <08_ipv4.i--tags.re>`

.. literalinclude:: 08_ipv4.i--tags.re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --tags -o ipv4.cc ipv4.re
    $ g++ -o ipv4 ipv4.cc

Run:

.. code-block:: bash

    $ ./ipv4 127.0.0.1 192.168.1.255
    parsed: 127, 0, 0, 1!
    parsed: 192, 168, 1, 255!


