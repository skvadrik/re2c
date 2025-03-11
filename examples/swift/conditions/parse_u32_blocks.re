// re2swift $INPUT -o $OUTPUT

func parseUInt32(_ yyinput: UnsafePointer<UInt8>) -> UInt32? {
  var yycursor = 0, yymarker = 0

  /*!re2c
    re2c:yyfill:enable = 0;

    "0b" / [01]        { return parseBin() }
    "0"                { return parseOct() }
    "" / [1-9]         { return parseDec() }
    "0x" / [0-9a-fA-F] { return parseHex() }
    *                  { return nil }
  */

  func add(_ accum: inout UInt64, _ charOrigin: UnicodeScalar, _ base: UInt64, _ offset: UInt64 = 0) {
    let digit = yyinput[yycursor - 1] - UInt8(ascii: charOrigin)
    accum = min(accum * base + UInt64(digit) + offset, UInt64(UInt32.max) + 1)
  }

  func parseBin() -> UInt32? {
    var accum: UInt64 = 0
    parse: while true {
      /*!re2c
        [01] { add(&accum, "0", 2); continue parse }
        *    { return UInt32(exactly: accum) }
      */
    }
  }
  func parseOct() -> UInt32? {
    var accum: UInt64 = 0
    parse: while true {
      /*!re2c
        [0-7] { add(&accum, "0", 8); continue parse }
        *     { return UInt32(exactly: accum) }
      */
    }
  }
  func parseDec() -> UInt32? {
    var accum: UInt64 = 0
    parse: while true {
      /*!re2c
        [0-9] { add(&accum, "0", 10); continue parse }
        *     { return UInt32(exactly: accum) }
      */
    }
  }
  func parseHex() -> UInt32? {
    var accum: UInt64 = 0
    parse: while true {
      /*!re2c
        [0-9] { add(&accum, "0", 16);     continue parse }
        [a-f] { add(&accum, "a", 16, 10); continue parse }
        [A-F] { add(&accum, "A", 16, 10); continue parse }
        *     { return UInt32(exactly: accum) }
      */
    }
  }
}

assert(parseUInt32("") == nil)
assert(parseUInt32("1234567890") == 1234567890)
assert(parseUInt32("0b1101") == 13)
assert(parseUInt32("0x7Fe") == 2046)
assert(parseUInt32("0644") == 420)
assert(parseUInt32("9999999999") == nil)
