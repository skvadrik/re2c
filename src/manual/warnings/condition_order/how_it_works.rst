How it works
~~~~~~~~~~~~

The warning is triggered if at the same time:

* Conditions are enabled with with ``-c``.
* Neither ``/*!types:re2c*/`` nor ``-t, --type-header`` is used.
* The initial condition dispatch is sensitive to condition order:
  it is either an ``if`` statement or a jump table.
  Note that the number of conditions must be greater than one,
  otherwise the dispatch shrinks to a simple unconditional jump.

