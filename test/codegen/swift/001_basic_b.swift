/* Generated by re2swift */
#sourceLocation(file: "codegen/swift/001_basic_b.re", line: 1)
// re2swift $INPUT -o $OUTPUT --api generic -b

func lex(_ s: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0
  
#sourceLocation(file: "codegen/swift/001_basic_b.swift", line: 9)
  var yych: UInt8 = 0
  var yystate: UInt = 0
  let yybm: [UInt8] = [
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
    128, 128, 128, 128, 128, 128, 128, 128,
    128, 128,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
  ]
  yyl: while true {
    switch yystate {
      case 0:
        yych = s[cursor]
        cursor += 1
        if yych <= 0x30 {
          yystate = 1
          continue yyl
        }
        if yych <= 0x39 {
          yystate = 2
          continue yyl
        }
        yystate = 1
        continue yyl
      case 1:
#sourceLocation(file: "codegen/swift/001_basic_b.re", line: 13)
        return false
#sourceLocation(file: "codegen/swift/001_basic_b.swift", line: 64)
      case 2:
        yych = s[cursor]
        if (yybm[0 + Int(yych)] & 128) != 0 {
          cursor += 1
          yystate = 2
          continue yyl
        }
#sourceLocation(file: "codegen/swift/001_basic_b.re", line: 12)
        return true
#sourceLocation(file: "codegen/swift/001_basic_b.swift", line: 74)
      default: fatalError("internal lexer error")
    }
  }
#sourceLocation(file: "codegen/swift/001_basic_b.re", line: 14)

}

@main struct Program {
  static func main() {
    let s: StaticString = "1234\0"
    s.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
