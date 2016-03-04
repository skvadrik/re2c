Reuse
-----

Reuse mode is controlled by ``-r --reusable`` option.
Allows reuse of scanner definitions with ``/*!use:re2c */`` after ``/*!rules:re2c */``.
In this mode no ``/*!re2c */`` block and exactly one ``/*!rules:re2c */`` must be present.
The rules are being saved and used by every ``/*!use:re2c */`` block that follows.
These blocks can contain inplace configurations, especially ``re2c:flags:e``,
``re2c:flags:w``, ``re2c:flags:x``, ``re2c:flags:u`` and ``re2c:flags:8``.
That way it is possible to create the same scanner multiple times for
different character types, different input mechanisms or different output mechanisms.
The ``/*!use:re2c */`` blocks can also contain additional rules that will be appended
to the set of rules in ``/*!rules:re2c */``.

