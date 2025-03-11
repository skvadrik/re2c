// re2swift $INPUT -o $OUTPUT --api generic -fc
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

struct State {
  // Use a small buffer to cover the case when a lexeme doesn't fit.
  // In a real world scenario, use a larger buffer.
  static let bufferSize = 10

  var limit  = Self.bufferSize
  var cursor = Self.bufferSize
  var marker = Self.bufferSize
  var token  = Self.bufferSize
  var state  = -1

  let file: FileHandle
  // Buffer is zero-initialized, no need to write sentinel
  var buffer = ContiguousArray<UInt8>(repeating: 0, count: Self.bufferSize + 1)
}

extension State {
  mutating func lex(numbers: inout Int, words: inout Int) -> Status {
    /*!conditions:re2c*/
    var yych: UInt8 = 0
    lex: while true {
      self.token = self.cursor
      /*!re2c
        re2c:api = custom;
        re2c:eof = 0;
        re2c:YYPEEK     = "self.buffer[self.cursor]";
        re2c:YYSKIP     = "self.cursor += 1";
        re2c:YYBACKUP   = "self.marker = self.cursor";
        re2c:YYRESTORE  = "self.cursor = self.marker";
        re2c:YYSHIFT    = "self.cursor += @@";
        re2c:YYLESSTHAN = "self.limit <= self.cursor";
        re2c:YYGETSTATE = "self.state";
        re2c:YYSETSTATE = "self.state = @@";
        re2c:YYFILL     = "return .waiting";

        digit  = [0-9];
        letter = [a-z];
        space  = [ \t];

        <*> * { return .badPacket }
        <*> $ { return .end }

        <INIT> "" / digit  :=> NUMBER
        <INIT> "" / letter :=> WORD
        <INIT> "" / space  :=> SPACES

        <SPACES> space+ => INIT { continue lex }

        <NUMBER> digit+ => SPACES {
          numbers += 1
          continue lex
        }
        <WORD> letter+ => SPACES {
          words += 1
          continue lex
        }
      */
    }
    fatalError("unreachable")
  }

  mutating func fill() -> Status {
    let shift = self.token
    let used = self.limit - self.token
    let free = Self.bufferSize - used

    // Error: No space. In the real world we can reallocate a larger buffer.
    if free < 1 {
      return .bigPacket
    }

    // Shift buffer contents, discarding everything up to the current lexeme.
    self.buffer.replaceSubrange(..<used, with: self.buffer[shift..<self.limit])
    self.limit  -= shift
    self.cursor -= shift
    self.marker -= shift
    self.token = 0

    // Fill free space at the end of buffer with new data.
    do {
      if let data = try self.file.read(upToCount: free) {
        self.buffer.replaceSubrange(self.limit..<(self.limit + data.count), with: data)
        self.limit += data.count
      }
    } catch {
      fatalError("cannot read from file: \(error.localizedDescription)")
    }
    self.buffer[self.limit] = 0  // append sentinel

    return .ready
  }

  enum Status {
    case end, ready, waiting, badPacket, bigPacket
  }
}

func test(_ packets: [StaticString],
    _ expectStatus: State.Status, _ expectNumbers: Int, _ expectWords: Int
) {
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
  var status: State.Status
  var send = 0, numCount = 0, wordCount = 0
  loop: while true {
    switch state.lex(numbers: &numCount, words: &wordCount) {
      case .end:
        log("done: got \(numCount) and \(wordCount) words")
        status = .end
        break loop
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
        status = state.fill()
        state.buffer.withUnsafeBytes {
          let buf = $0.bindMemory(to: CChar.self)
          log("queue: '\(String(utf8String: buf.baseAddress!) ?? "")'")
        }
        if status == .bigPacket {
          log("error: packet too big")
          break loop
        }
        assert(status == .ready)
      case .badPacket:
        log("error: ill-formed packet")
        status = .badPacket
        break loop
      default:
        fatalError("unreachable")
    }
  }

  // Check results.
  assert(status == expectStatus, "expected status `\(expectStatus)`, got `\(status)`")
  if status == .end {
    assert(numCount == expectNumbers,
      "expected number count \(expectNumbers), got \(numCount)")
    assert(wordCount == expectWords,
      "expected word count \(expectWords), got \(wordCount)")
  }
}

@main struct Program {
  static func main() {
    test([], .end, 0, 0)
    test([ " zero one", " ", "123", "4 tw", "o  456789" ], .end, 2, 3)
    test([ "zer0" ], .badPacket, -1, -1)
    test([ "looooooooooong;" ], .bigPacket, -1, -1)
  }
}
