// re2swift $INPUT -o $OUTPUT -c

/*!conditions:re2c*/

func parseUInt32(_ yyinput: UnsafePointer<UInt8>) -> UInt32? {
  var yycursor = 0, yymarker = 0, yycond = yycinit

  var accum: UInt64 = 0

  loop: while true {
    /*!re2c
      re2c:yyfill:enable = 0;

      <init> '0b' / [01]        :=> bin
      <init> "0"                :=> oct
      <init> "" / [1-9]         :=> dec
      <init> '0x' / [0-9a-fA-F] :=> hex

      <bin> [01]  { add("0", 2);      continue loop }
      <oct> [0-7] { add("0", 8);      continue loop }
      <dec> [0-9] { add("0", 10);     continue loop }
      <hex> [0-9] { add("0", 16);     continue loop }
      <hex> [a-f] { add("a", 16, 10); continue loop }
      <hex> [A-F] { add("A", 16, 10); continue loop }

      <bin, oct, dec, hex> "\x00" { return UInt32(exactly: accum) }

      <*> * { return nil }
    */
  }

  func add(_ charOrigin: UnicodeScalar, _ base: UInt64, _ offset: UInt64 = 0) {
    let digit = yyinput[yycursor - 1] - UInt8(ascii: charOrigin)
    accum = min(accum * base + UInt64(digit) + offset, UInt64(UInt32.max) + 1)
  }
}

assert(parseUInt32("") == nil)
assert(parseUInt32("1234567890") == 1234567890)
assert(parseUInt32("0b1101") == 13)
assert(parseUInt32("0x7Fe") == 2046)
assert(parseUInt32("0644") == 420)
assert(parseUInt32("9999999999") == nil)
