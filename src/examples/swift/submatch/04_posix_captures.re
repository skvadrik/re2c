// re2swift $INPUT -o $OUTPUT

// Maximum number of capturing groups among all rules.
/*!maxnmatch:re2c*/

struct SemVer: Equatable { var major: Int, minor: Int, patch: Int }

func lex(_ yyinput: UnsafePointer<UInt8>) -> SemVer? {
  let tagNone = -1

  var yycursor = 0, yymarker = 0

  // Allocate memory for capturing parentheses (twice the number of groups).
  var yypmatch = [Int](repeating: 0, count: yymaxnmatch * 2)
  let yynmatch: Int

  // Intermediate tag variables used by the lexer (must be autogenerated).
  /*!stags:re2c format = "  var @@: Int = tagNone\n"; */

  /*!re2c
    re2c:yyfill:enable  = 0;
    re2c:posix-captures = 1;

    num = [0-9]+;

    (num) "." (num) ("." num)? [\x00] {
      // `yynmatch` is the number of capturing groups.
      assert(yynmatch == 4)
      // Even `yypmatch` values are for opening parentheses, odd values
      // are for closing parentheses, the first group is the whole match.
      return SemVer(
        major: s2n(yypmatch[2]..<yypmatch[3]),
        minor: s2n(yypmatch[4]..<yypmatch[5]),
        patch: yypmatch[6] != tagNone ? s2n((yypmatch[6] + 1)..<yypmatch[7]) : 0)
    }
    * { return nil }
  */

  func s2n(_ range: Range<Int>) -> Int {
    range.reduce(0) { accum, idx in
      accum * 10 + Int(yyinput[idx] - UInt8(ascii: "0"))
    }
  }
}

assert(lex("23.34") == SemVer(major: 23, minor: 34, patch: 0))
assert(lex("1.2.999") == SemVer(major: 1, minor: 2, patch: 999))
assert(lex("1.a") == nil)
