Parsing /etc/passwd
-------------------

This example shows how to parse simple file formats such as the ``/etc/passwd`` file.
This file consists of multiple lines of the form ``user`` ``:`` ``password`` ``:`` ``UID`` ``:`` ``GID`` ``:`` ``info`` ``:`` ``home`` ``:`` ``command``.

:download:`[etc_passwd.re] <parse_etc_passwd.re>`

.. literalinclude:: parse_etc_passwd.re
    :language: cpp

Compile as: ``re2c -o etc_passwd.c etc_passwd.re``.
