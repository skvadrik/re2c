// re2swift $INPUT -o $OUTPUT
import Foundation

/*!max:re2c*/

struct Input {
  static let bufferSize = 4096 - yymaxfill

  var file: FileHandle

  var yyinput  = ContiguousArray<UInt8>(repeating: 0, count: Self.bufferSize + yymaxfill)
  var yylimit  = Self.bufferSize
  var yycursor = Self.bufferSize
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
        re2c:yyrecord = "self";
        re2c:YYFILL   = "if self.fill(@@) != .ok { return nil }";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return self.token == self.yylimit - yymaxfill ? count : nil;
        }
        str {
          count += 1
          continue loop
        }
        [ ]+ { continue loop }
        *    { return nil }
      */
    }
  }

  mutating func fill(_ need: Int) -> FillStatus {
    guard !self.eof else {
      return .eof
    }

    let shift = self.token
    let used = self.yylimit - self.token
    let free = Self.bufferSize - used

    // Error: Lexeme too long. In the real world we can reallocate a larger buffer.
    if self.token < need {
      return .longLexeme
    }

    // Shift buffer contents, discarding everything up to the current lexeme.
    self.yyinput.replaceSubrange(..<used, with: self.yyinput[shift..<self.yylimit])
    self.yylimit  -= shift
    self.yycursor -= shift
    self.token = 0

    // Fill free space at the end of buffer with new data from file.
    let read: Int
    do {
      if let data = try self.file.read(upToCount: free) {
        read = data.count
        self.yyinput.replaceSubrange(self.yylimit..<(self.yylimit + read), with: data)
      } else {
        read = 0
      }
    } catch {
      fatalError("cannot read from file: \(error.localizedDescription)")
    }

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    self.yylimit += read
    if read < free {
      self.eof = true
      self.yyinput.withUnsafeMutableBytes {
        _ = memset($0.baseAddress! + self.yylimit, 0, yymaxfill)
      }
      self.yylimit += yymaxfill
    }

    return .ok
  }

  enum FillStatus {
    case ok, eof, longLexeme
  }
}

let fileName = "input"
let content = "'qu\0tes' 'are' 'fine: \\'' ";

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
// This immediately triggers YYFILL, as the check `in.yycursor < in.yylimit` fails.
guard let file = FileHandle(forReadingAtPath: fileName) else {
  throw NSError(domain: NSCocoaErrorDomain, code: CocoaError.fileReadNoSuchFile.rawValue)
}
var `in` = Input(file: file)

// Run the lexer
assert(`in`.lex() == count)

// Cleanup: remove input file
try file.close()
try FileManager.default.removeItem(atPath: fileName)
