// re2swift $INPUT -o $OUTPUT -cf
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
  static let bufferSize = 4096-32-184-1
  static let tagNone = -1

  private var yylimit  = Self.bufferSize
  private var yycursor = Self.bufferSize
  private var yymarker = Self.bufferSize
  private var token    = Self.bufferSize
  private var yycond   = Self.bufferSize
  private var yystate  = -1
  private var yyaccept = -1

  private var mTagPool = [MTag]()

  /*!stags:re2c format = "  private var @@ = tagNone\n"; */
  /*!mtags:re2c format = "  private weak var @@: MTag? = nil\n"; */

  // Buffer is zero-initialized, no need to write sentinel
  private var buffer = ContiguousArray<UInt8>(repeating: 0, count: Self.bufferSize + 1)
}

extension State {
  /*!conditions:re2c*/

  mutating func parse() -> Status {
    var yych: UInt8 = 0
    var l1: Int, l2: Int
    var f1: MTag? = nil, f2: MTag? = nil
    var p1: MTag? = nil, p2: MTag? = nil, p3: MTag? = nil, p4: MTag? = nil

    /*!re2c
      re2c:api = record;
      re2c:eof = 0;
      re2c:flags:tags = 1;
      re2c:define:YYCTYPE    = UInt8;
      re2c:variable:yyrecord = self;
      re2c:YYINPUT           = self.buffer;
      re2c:define:YYFILL     = "return .waiting";
      re2c:define:YYMTAGP    = "@@ = self.add(tag: @@, value: self.yycursor)";
      re2c:define:YYMTAGN    = "@@ = self.add(tag: @@, value: Self.tagNone)";

      crlf  = '\r\n';
      sp    = ' ';
      htab  = '\t';
      ows   = (sp | htab)*;
      digit = [0-9];
      alpha = [a-zA-Z];
      vchar = [\x1f-\x7e];
      tchar = [-!#$%&'*+.^_`|~] | digit | alpha;

      obs_fold            = #f1 crlf (sp | htab)+ #f2;
      obs_text            = [\x80-\xff];
      field_name          = tchar+;
      field_vchar         = vchar | obs_text;
      field_content       = field_vchar ((sp | htab)+ field_vchar)?;
      field_value_folded  = (field_content* obs_fold field_content*)+;
      header_field_folded = field_value_folded ows;
      token               = tchar+;
      qdtext
        = htab
        | sp
        | [\x21-\x5B\x5D-\x7E] \ '"'
        | obs_text;
      quoted_pair         = '\\' ( htab | sp | vchar | obs_text );
      quoted_string       = '"' ( qdtext | quoted_pair )* '"';
      parameter           = #p1 token #p2 '=' #p3 ( token | quoted_string ) #p4;
      media_type          = @l1 token '/' token @l2 ( ows ';' ows parameter )*;


      <media_type> media_type ows crlf {
        print("media type: \(getString(l1..<l2))")

        var pnameStart = p1, pnameEnd = p2
        var pvalStart  = p3, pvalEnd  = p4

        while pnameStart != nil {
          log("\t\(getString(pnameStart!.elem..<pnameEnd!.elem)) = \(getString(pvalStart!.elem..<pvalEnd!.elem))")
          pnameStart = pnameStart!.prev
          pnameEnd   = pnameEnd!.prev
          pvalStart  = pvalStart!.prev
          pvalEnd    = pvalEnd!.prev
        }

        return .done
      }

      <header> header_field_folded crlf {
        var foldStart = f1, foldEnd = f2
        while foldStart != nil {
          log("\t\(getString(foldStart!.elem..<foldEnd!.elem))")
          foldStart = foldStart!.prev
          foldEnd   = foldEnd!.prev
        }

        return .done
      }

      <*> $ { return .end }
      <*> * { return .error }
    */
  }

  // Feed the next data packet into the buffer
  mutating func feed(string: StaticString) -> Bool {
    let shift = self.token
    let free = Self.bufferSize - (self.yylimit - shift)

    return string.withUTF8Buffer { chunk in
      // Error: no free space, in the real world we can reallocate a larger buffer.
      if (free < chunk.count) {
        log("Token too long for receive buffer:", self.buffer.count)
        return false
      }

      if (shift > 0) {
        // Shift buffer contents, discarding already processed data.
        self.buffer.replaceSubrange(..<(Self.bufferSize - shift), with: self.buffer[shift..<Self.bufferSize])
        self.yylimit  -= shift
        self.yycursor -= shift
        self.yymarker -= shift
        self.token = 0
        /*!stags:re2c format = "        if self.@@ != Self.tagNone { self.@@ -= shift }\n"; */
      }

      // Fill remaining space with new data.
      self.buffer.replaceSubrange(self.yylimit..<(self.yylimit + chunk.count), with: chunk)
      self.yylimit += chunk.count

      return true
    }
  }

  // Append a single value to an m-tag history.
  private mutating func add(tag prevTag: MTag?, value: Int) -> MTag {
    let tag = MTag(prev: prevTag, element: value)
    self.mTagPool.append(tag)
    return tag
  }

  // Decode a string from a slice of the buffer.
  private func getString(_ range: Range<Int>) -> String {
    String(data: Data(self.buffer[range]), encoding: .utf8)!
  }

  enum Status {
    case waiting
    case done
    case end
    case error
  }
}

// An m-tag tree is a way to store histories with an O(1) copy operation.
// Histories naturally form a tree, as they have a common start and fork
// at some point. The tree is stored as an array of pairs (tag value,
// link to parent). An m-tag is represented with a single index in the tree.
class MTag {
  weak var prev: MTag?
  var elem: Int

  init(prev: MTag?, element: Int) {
    self.prev = prev
    self.elem = element
  }
}

func test(packets: [StaticString]) -> Int32 {
  var c = State()

  // Main loop. The buffer contains incomplete data which appears packet by
  // packet. When the lexer needs more input it saves its internal state and
  // returns to the caller which should provide more input and resume lexing.
  var chunkIdx = 0
  finally: while true {
    switch (c.parse()) {
      case .waiting:
        print("waiting")
        guard c.feed(string: packets[chunkIdx]) else {
          return 1
        }
        chunkIdx += 1
      case .done:
        print("done")
      case .end:
        print("end")
        break finally
      case .error:
        print("error")
        return 1
    }
  }
  return 0
}

@main struct Program {
  static func main() {
    let packets: [StaticString] = [
      "ap",
      "plication/j",
      "son;",
      " charset=\"",
      "utf\\\"-8\"\r",
      "\n",
      ""
    ];

    let code = test(packets: packets)
    if code != 0 {
      log("Error exit:", code)
    }
    exit(code)
  }
}
