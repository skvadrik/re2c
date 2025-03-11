// re2swift $INPUT -o $OUTPUT -i

/*!re2c
  re2c:yyfill:enable = 0;
*/

/*!rules:re2c:generic
  re2c:api = generic;
  re2c:YYPEEK      = "str[cursor]";
  re2c:YYSKIP      = "cursor += 1";
  re2c:YYBACKUP    = "marker = cursor";
  re2c:YYRESTORE   = "cursor = marker";
  re2c:YYSTAGP     = "@@ = cursor";
  re2c:YYSTAGN     = "@@ = -1";
  re2c:YYSHIFTSTAG = "@@{tag} += @@{shift}";
*/

/*!rules:re2c:simple
  re2c:YYINPUT = str;
*/

/*!rules:re2c:r1
  re2c:tags = 1;
  ([b] @x [a] @y)? { return (x == -1) ? -1 : (y - x) }
*/

/*!rules:re2c:r2
  re2c:posix-captures = 1;
  (([a]))? {
    assert(yynmatch == 3)
    return yypmatch[4]
  }
*/

func lexTagsGeneric(_ str: UnsafeBufferPointer<UInt8>) -> Int {
  /*!stags:re2c:b1 format = "var @@ = -1\n  "; */
  var cursor = 0, marker = 0
  var x: Int, y: Int
  /*!local:re2c:b1
    !use:generic;
    !use:r1;
  */
  return -2
}

func lexTagsSimple(_ str: UnsafeBufferPointer<UInt8>) -> Int {
  /*!stags:re2c:b2 format = "var @@ = -1\n  "; */
  var yycursor = 0, yymarker = 0
  var x: Int, y: Int
  /*!local:re2c:b2
    !use:simple;
    !use:r1;
  */
}

func lexCapturesGeneric(_ str: UnsafeBufferPointer<UInt8>) -> Int {
  /*!maxnmatch:re2c*/
  /*!stags:re2c:b3 format = "var @@ = -1\n  "; */
  var cursor = 0, yynmatch: Int
  var yypmatch = [Int](repeating: 0, count: 2 * yymaxnmatch)
  /*!local:re2c:b3
    !use:generic;
    !use:r2;
  */
}

func lexCapturesSimple(_ str: UnsafeBufferPointer<UInt8>) -> Int {
  /*!maxnmatch:re2c*/
  /*!stags:re2c:b3 format = "var @@ = -1\n  "; */
  var yycursor = 0, yynmatch: Int
  var yypmatch = [Int](repeating: 0, count: 2 * yymaxnmatch)
  /*!local:re2c:b4
    !use:simple;
    !use:r2;
  */
}

@main struct Program {
  static func test(call: (UnsafeBufferPointer<UInt8>) -> Int, string: StaticString, expect: Int) {
    string.withUTF8Buffer {
      assert(call($0) == expect)
    }
  }

  static func main() {
    test(call: lexTagsGeneric, string: "\0",   expect: -1)
    test(call: lexTagsGeneric, string: "ba\0", expect:  1)
    test(call: lexTagsSimple,  string: "\0",   expect: -1)
    test(call: lexTagsSimple,  string: "ba\0", expect:  1)
    test(call: lexCapturesGeneric, string: "\0",  expect: -1)
    test(call: lexCapturesGeneric, string: "a\0", expect:  0)
    test(call: lexCapturesSimple,  string: "\0",  expect: -1)
    test(call: lexCapturesSimple,  string: "a\0", expect:  0)
  }
}
