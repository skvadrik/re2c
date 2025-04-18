// re2swift $INPUT -o $OUTPUT -8 -i

/*!include:re2c "unicode_categories.re" */

func lex(_ yyinput: UnsafePointer<UInt8>) -> Bool {
  var yycursor = 0, yymarker = 0
  /*!re2c
    re2c:yyfill:enable = 0;

    // Simplified "Unicode Identifier and Pattern Syntax"
    // (see https://unicode.org/reports/tr31)
    id_start    = L | Nl | [$_];
    id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
    identifier  = id_start id_continue*;

    identifier { return true }
    *          { return false }
  */
}

assert(lex("_Ыдентификатор"))
assert(lex("識別子"))
assert(!lex("+"))
