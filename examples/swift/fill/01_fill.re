// re2swift $INPUT -o $OUTPUT
import Foundation

struct Input {
  static let bufferSize = 4095

  var file: FileHandle

  var yyinput  = ContiguousArray<UInt8>(repeating: 0, count: Self.bufferSize + 1)
  var yylimit  = Self.bufferSize
  var yycursor = Self.bufferSize
  var yymarker = Self.bufferSize
  var token    = -1
  var eof      = false
}

extension Input {
  mutating func lex() -> Int? {
    var count = 0
    loop: while true {
      self.token = self.yycursor
      /*!re2c
        re2c:api = record;
        re2c:eof = 0;
        re2c:yyrecord = "self";
        re2c:YYFILL   = "self.fill() == .ok";

        str = ['] ([^'\\] | [\\][^])* ['];

        str {
          count += 1
          continue loop
        }
        [ ]+ { continue loop }
        $    { return count }
        *    { return nil }
      */
    }
  }

  mutating func fill() -> FillStatus {
    guard !self.eof else {
      return .eof
    }

    let shift = self.token
    let used = self.yylimit - self.token
    let free = Self.bufferSize - used

    // Error: Lexeme too long. In the real world we can reallocate a larger buffer.
    if self.token < 1 {
      return .longLexeme
    }

    // Shift buffer contents, discarding everything up to the current lexeme.
    self.yyinput.replaceSubrange(..<used, with: self.yyinput[shift..<self.yylimit])
    self.yylimit  -= shift
    self.yycursor -= shift
    self.yymarker &-= shift  // May underflow if marker is unused
    self.token = 0

    // Fill free space at the end of buffer with new data from file.
    do {
      if let data = try self.file.read(upToCount: free) {
        self.yyinput.replaceSubrange(self.yylimit..<(self.yylimit + data.count), with: data)
        self.yylimit += data.count
      }
    } catch {
      fatalError("cannot read from file: \(error.localizedDescription)")
    }
    self.yyinput[self.yylimit] = 0  // append sentinel
    self.eof = self.yylimit < Self.bufferSize

    return .ok
  }

  enum FillStatus {
    case ok, eof, longLexeme
  }
}

let fileName = "input"
let content = "'qu\0tes' 'are' 'fine: \\'' "

// Prepare input file: a few times the size of the buffer,
// containing strings with zeroes and escaped quotes.
guard FileManager.default.createFile(
    atPath: fileName,
    contents: Data(String(repeating: content, count: Input.bufferSize).utf8)
) else {
  fatalError("failed to write file \"\(fileName)\"")
}

// Number of quoted strings written to file
let count = 3 * Input.bufferSize

// Initialize lexer state
guard let file = FileHandle(forReadingAtPath: fileName) else {
  throw NSError(domain: NSCocoaErrorDomain, code: CocoaError.fileReadNoSuchFile.rawValue)
}
var `in` = Input(file: file)

// Run the lexer
assert(`in`.lex() == count)

// Cleanup: remove input file
try file.close()
try FileManager.default.removeItem(atPath: fileName)
