False alarms
~~~~~~~~~~~~

In many cases, matching an empty string makes perfect sense:

* It might be used as a non-consuming default rule.

* It might be used to lex an optional lexeme: if lexeme rules didn't match,
  the lexer must jump to another block and resume lexing at the same input position.

Or any other useful examples you can invent.
All these cases are perfectly sane.
If ``[-Wmatch-empty-string]`` becomes annoying, use ``[-Wno-match-empty-string]``.
Maybe re2c should move this warning to some paranoid level.


