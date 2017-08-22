Options & arguments
-------------------

This example shows how to parse command-line options
with possible arguments, where each individual option may need its own argument format.
Our parser handles errors and typos:
for known options it reports ill-formed arguments;
for unrecognized options it collects them and reports at the end of parsing.
Our imaginary options are summarized below:

* ``-v``, ``--verbose``

* ``-l LIMIT``, ``--limit=LIMIT``, where ``LIMIT`` is a decimal number followed by one of the suffixes ``B``, ``K``, ``M`` or ``G``

* ``-d DATE``, ``--date=DATE``, where ``DATE`` has the form ``DD/MM/YYYY``

* ``-p PATH``, ``--path=PATH``, where ``PATH`` is a ``/``-separated file path

* ``-f FORMAT``, ``--format=FORMAT``, where ``FORMAT`` is a double-quoted format string

:download:`[options.re] <14_options.i--tags.re>`

.. literalinclude:: 14_options.i--tags.re
    :language: cpp
    :linenos:

Compile:

.. code-block:: bash

    $ re2c --tags -o options.cc options.re
    $ g++ -o options options.cc

Run:

.. code-block:: bash

    $ ./options '-v --limit=8K -d08/08/1985 -p/usr/src/linux --format="%s" --limit -f=3 --verbos --d"19th May"'
    bad argument '' to option --limit
    bad argument '=3' to option -f
    
    options:
      date:    08/08/1985
      path:    /usr/src/linux
      format:  "%s"
      limit:   8K
      verbose: yes
    
    unknown:
      verbos: ''
      d: '"19th May"'

