/etc/passwd
-----------

This example shows how to parse simple file formats such as the ``/etc/passwd`` file.
This file consists of multiple lines of the form ``user`` ``:`` ``password`` ``:`` ``UID`` ``:`` ``GID`` ``:`` ``info`` ``:`` ``home`` ``:`` ``command``.
Our example file is the following :download:`[/etc/passwd] <09_etc_passwd.txt>`:

.. literalinclude:: 09_etc_passwd.txt

:download:`[etc_passwd.re] <09_etc_passwd.i--tags.re>`

.. literalinclude:: 09_etc_passwd.i--tags.re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --tags -o etc_passwd.cc etc_passwd.re
    $ g++ -o etc_passwd etc_passwd.cc

Run:

.. code-block:: bash

    $ ./etc_passwd /etc/passwd
    user:     root
    password: x
    UID:      0
    GID:      0
    info:     root
    home:     /root
    command:  /bin/bash
    
    user:     bin
    password: x
    UID:      1
    GID:      1
    info:     bin
    home:     /bin
    command:  /bin/false
    
    user:     portage
    password: x
    UID:      250
    GID:      250
    info:     portage
    home:     /var/tmp/portage
    command:  /bin/false
    


