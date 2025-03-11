// re2swift $INPUT -o $OUTPUT

// Expects a null-terminated string.
func lex(_ yyinput: UnsafePointer<UInt8>, _ length: Int) -> Int? {
  var yycursor = 0, yylimit = length, yymarker = 0
  var count = 0

  loop: while true {
    /*!re2c
      re2c:eof = 0;
      re2c:yyfill:enable = 0;

      str = ['] ([^'\\] | [\\][^])* ['];

      str {
        count += 1
        continue loop
      }
      [ ]+ { continue loop }
      *    { return nil }
      $    { return count }
    */
  }
}

func test(_ str: StaticString, _ expect: Int?) {
  assert(lex(str.utf8Start, str.utf8CodeUnitCount) == expect)
}

test("", 0);
test("'qu\0tes' 'are' 'fine: \\'' ", 3);
test("'unterminated\\'", nil);
