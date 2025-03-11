// re2swift $INPUT -o $OUTPUT -f
import Foundation

func log(_ items: Any..., separator: String = " ", terminator: String = "\n") {
#if DEBUG
  var stderr = FileHandle.standardError
  print(items, separator: separator, terminator: terminator, to: &stderr)
#endif
}

extension FileHandle: @retroactive TextOutputStream {
  public func write(_ string: String) {
    self.write(Data(string.utf8))
  }
}

func lex(state: inout State, recv: inout Int) -> Status {
  var yych: UInt8 = 0
  lex: while true {
    state.token = state.yycursor
    /*!re2c
      re2c:api = record;
      re2c:eof = 0;
      re2c:variable:yyrecord = "state";
      re2c:YYCTYPE = UInt8;
      re2c:YYFILL = "return .waiting";

      packet = [a-z]+[;];

      *      { return .badPacket }
      $      { return .end }
      packet {
        recv += 1
        continue lex
      }
    */
  }
}

func fill(state: inout State) -> Status {
  // Error: lexeme too long. In the real world we can reallocate a larger buffer.
  if state.token < 1 {
    return .bigPacket
  }

  // Shift buffer contents (discard everything up to the current lexeme).
  state.yyinput.replaceSubrange(..<(state.yylimit - state.token), with: state.yyinput[state.token..<state.yylimit])
  state.yylimit -= state.token
  state.yycursor -= state.token
  state.yymarker -= state.token
  state.token = 0

  // Fill free space at the end of buffer with new data.
  do {
    if let data = try state.file.read(upToCount: State.bufferSize - 1 - state.yylimit) { // -1 for sentinel
      state.yyinput.replaceSubrange(state.yylimit..<(state.yylimit + data.count), with: data)
      state.yylimit += data.count
    }
  } catch {
    fatalError("cannot read from file: \(error.localizedDescription)")
  }
  state.yyinput[state.yylimit] = 0  // append sentinel

  return .ready
}

func test(_ packets: [StaticString]) -> Status {
  // Create a "socket" (open the same file for reading and writing).
  let fname: String = "pipe"
  guard FileManager.default.createFile(atPath: fname, contents: nil),
      let fw = FileHandle(forWritingAtPath: fname) else {
    fatalError("cannot open '\(fname)'")
  }
  guard let fr = FileHandle(forReadingAtPath: fname) else {
    fatalError("cannot read file '\(fname)'")
  }

  defer {
    // Cleanup: remove input file.
    do {
      try fw.close()
      try fr.close()
      try FileManager.default.removeItem(atPath: fname)
    } catch {
      fatalError("error on file cleanup: \(error.localizedDescription)")
    }
  }

  var state = State(file: fr)

  // Main loop. The buffer contains incomplete data which appears packet by
  // packet. When the lexer needs more input it saves its internal state and
  // returns to the caller which should provide more input and resume lexing.
  var send = 0, recv = 0
  while true {
    switch lex(state: &state, recv: &recv) {
      case .end:
        log("done: got \(recv)")
        assert(recv == send)
        return .end
      case .waiting:
        log("waiting...")
        if send < packets.count {
          log("sent packet \(send)")
          packets[send].withUTF8Buffer {
            do {
              try fw.write(contentsOf: $0)
            } catch {
              fatalError("cannot write to \(fname): \(error.localizedDescription)")
            }
          }
          send += 1
        }
        let status = fill(state: &state)
        state.yyinput.withUnsafeBytes {
          let buf = $0.bindMemory(to: CChar.self)
          log("queue: '\(String(utf8String: buf.baseAddress!) ?? "")'")
        }
        if status == .bigPacket {
          log("error: packet too big")
          return .bigPacket
        }
        assert(status == .ready)
      case .badPacket:
        log("error: ill-formed packet")
        return .badPacket
      default:
        fatalError("shouldn't happen")
    }
  }
}

struct State {
  // Use a small buffer to cover the case when a lexeme doesn't fit,
  // in a real world use case use a larger buffer.
  static let bufferSize = 10

  let file: FileHandle

  var yyinput = ContiguousArray<UInt8>(repeating: 0, count: Self.bufferSize)
  var yylimit: Int = Self.bufferSize - 1
  var yycursor: Int = Self.bufferSize - 1
  var yymarker: Int = Self.bufferSize - 1
  var token: Int = Self.bufferSize - 1
  var yystate: Int = -1
}

enum Status {
  case end, ready, waiting, badPacket, bigPacket
}

@main struct Program {
  static func main() {
    assert(test([]) == .end)
    assert(test([ "zero;", "one;", "two;", "three;", "four;" ]) == .end)
    assert(test([ "zer0;" ]) == .badPacket)
    assert(test([ "looooooooooong;" ]) == .bigPacket)
    log("all tests completed successfully")
  }
}
