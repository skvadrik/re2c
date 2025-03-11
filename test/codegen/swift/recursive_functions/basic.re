// re2swift $INPUT -o $OUTPUT --api generic --recursive-functions -i

class State {
  let string: UnsafeBufferPointer<UInt8>
  var cursor: Int = 0

  init(string: UnsafeBufferPointer<UInt8>) {
    self.string = string
  }
}

/*!re2c
  re2c:yyfill:enable = 0;
  re2c:YYFN   = [ "lex;Bool", "s;State" ];
  re2c:YYPEEK = "s.string[s.cursor]";
  re2c:YYSKIP = "s.cursor += 1";

  alpha = [a-zA-Z];
  ident = alpha (alpha | [0-9])*;

  ident { return true }
  *     { return false }
*/

@main struct Program {
  static func main() {
    let test1: StaticString = "qwerty42\0"
    let test2: StaticString = "??\0"
    test1.withUTF8Buffer {
      assert(lex(State(string: $0)))
    }
    test2.withUTF8Buffer {
      assert(!lex(State(string: $0)))
    }
  }
}
