Real-world examples
~~~~~~~~~~~~~~~~~~~

I found many useless escapes in real-world programs:

* A very strange escape ``\*`` in a regular expression like ``"*\*"``:
  either someone wanted to write ``"*\\*"`` (with backslash in the middle),
  or I have no explanation at all (considering that the first ``*`` is not escaped).
  As far as I know re2c always treated ``"*\*"`` as ``"**"``.

* ``\h`` in character classes (e.g. ``[ \h\t\v\f\r]``):
  perhaps someone confused ``\h`` with horisontal tab
  (or even hostname ``:)``).

* ``\[`` in charater classes; this one is very common.

* ``\/`` in character classes (e.g. ``[^\/\000]``) and strings (e.g. ``"\/*"``).
  However, there is one interesting case: ``"/**** State @@ ***\/"``:
  here unescaped slash would end multiline comment.
  Perhaps ``[-Wuseless-escape]`` should be fixed to recognize such cases.

* ``\.`` in character classes (e.g ``[\.]``).


