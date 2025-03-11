// re2swift $INPUT -o $OUTPUT -i

func lex(_ yyinput: UnsafePointer<UInt8>) -> Bool {
  var yycursor = 0
  /*!re2c
    re2c:yyfill:enable = 0;

    [1-9][0-9]* { return true }
    *           { return false }
  */
}

assert(lex("1234"))
