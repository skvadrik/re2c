// re2swift $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
  re2c:yyfill:enable = 0;

  "∀x ∃y" { return true }
  *       { return false }
*/

func lexUTF8(_ yyinput: [UInt8]) -> Bool {
  var yycursor = 0, yymarker = 0
  /*!use:re2c
    re2c:YYCTYPE = UInt8;
    re2c:encoding:utf8 = 1;
  */
}

func lexUTF32(_ yyinput: [UInt32]) -> Bool {
  var yycursor = 0, yymarker = 0
  /*!use:re2c
    re2c:YYCTYPE = UInt32;
    re2c:encoding:utf32 = 1;
  */
}

assert(lexUTF8([ 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79 ]))  // UTF-8
assert(lexUTF32([ 0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079 ]))  // UTF-32
