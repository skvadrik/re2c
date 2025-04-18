// re2swift $INPUT -o $OUTPUT -i --header lexer/state.swift

/*!header:re2c:on*/
struct LexerState {
  var yyinput: UnsafePointer<UInt8>
  var yycursor: Int
  /*!stags:re2c format = "var @@ = -1"; */

  init(str: UnsafePointer<UInt8>, cur: Int = 0) {
    self.yyinput = str
    self.yycursor = cur
  }
}
/*!header:re2c:off*/

extension LexerState {
  mutating func lex() -> Int {
  let t: Int
  /*!re2c
    re2c:header        = "lexer/state.swift";
    re2c:api           = record;
    re2c:tags          = 1;
    re2c:yyfill:enable = 0;
    re2c:yyrecord      = "self";

    [a]* @t [b]* { return t }
  */
  }
}

@main struct Program {
  static func main() {
    let str: StaticString = "ab"
    var state = LexerState(str: str.utf8Start)
    assert(state.lex() == 1)
  }
}
