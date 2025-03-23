// re2swift $INPUT -o $OUTPUT --api generic --recursive-functions -cf
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

/*!conditions:re2c*/
let bufferSize = 4096-32-248-1
let tagNone = -1

class State {
  init() {}

  var cursor = bufferSize
  var marker = bufferSize
  var token  = bufferSize
  var limit  = bufferSize
  var cond   = yycmedia_type
  var state  = -1
  var accept = 0

  private var mTagPool = [MTag]()

  /*!stags:re2c format = "  var @@ = tagNone\n"; */
  /*!mtags:re2c format = "  var @@: MTag? = nil\n"; */


  var l1 = 0, l2 = 0
  var f1: MTag? = nil, f2: MTag? = nil
  var p1: MTag? = nil, p2: MTag? = nil, p3: MTag? = nil, p4: MTag? = nil

  // Buffer is zero-initialized, no need to write sentinel
  var buffer = ContiguousArray<UInt8>(repeating: 0, count: bufferSize + 1)
}

/*!re2c
  re2c:eof  = 0;
  re2c:tags = 1;
  re2c:tags:negative   = "nil";
  re2c:tags:expression = "s.@@";
  re2c:yyaccept   = "s.accept";
  re2c:yyfn:throw = "throws(ParseError)";
  re2c:YYFN       = ["parse;State.Status", "s;State"];
  re2c:YYPEEK     = "s.buffer[s.cursor]";
  re2c:YYSKIP     = "s.cursor += 1";
  re2c:YYBACKUP   = "s.marker = s.cursor";
  re2c:YYRESTORE  = "s.cursor = s.marker";
  re2c:YYGETCOND  = "s.cond";
  re2c:YYSETCOND  = "s.cond = @@";
  re2c:YYGETSTATE = "s.state";
  re2c:YYSETSTATE = "s.state = @@";
  re2c:YYLESSTHAN = "s.limit <= s.cursor";
  re2c:YYFILL     = "return .waiting";
  re2c:YYSTAGP    = "@@ = s.cursor";
  re2c:YYSTAGN    = "@@ = tagNone";
  re2c:YYMTAGP    = "@@ = s.add(tag: @@, value: s.cursor)";
  re2c:YYMTAGN    = "@@ = s.add(tag: @@, value: tagNone)";

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
    print("media type: \(s.getString(s.l1..<s.l2))")

    var pnameStart = s.p1, pnameEnd = s.p2
    var pvalStart  = s.p3, pvalEnd  = s.p4

    while pnameStart != nil {
      log("\t\(s.getString(pnameStart!.elem..<pnameEnd!.elem)) = \(s.getString(pvalStart!.elem..<pvalEnd!.elem))")
      pnameStart = pnameStart!.prev
      pnameEnd   = pnameEnd!.prev
      pvalStart  = pvalStart!.prev
      pvalEnd    = pvalEnd!.prev
    }

    return .done
  }

  <header> header_field_folded crlf {
    var foldStart = s.f1, foldEnd = s.f2
    while foldStart != nil {
      log("\t\(s.getString(foldStart!.elem..<foldEnd!.elem))")
      foldStart = foldStart!.prev
      foldEnd   = foldEnd!.prev
    }

    return .done
  }

  <*> $ { return .end }
  <*> * { throw .unexpectedCharacter }
*/

extension State {
  // Feed the next data packet into the buffer
  func feed(string: StaticString) throws(ParseError) {
    let shift = self.token
    let free = bufferSize - (self.limit - shift)

    // Error: no free space, in the real world we can reallocate a larger buffer.
    if (free < string.utf8CodeUnitCount) {
      throw .bigPacket(string.utf8CodeUnitCount, free)
    }

    string.withUTF8Buffer { chunk in
      if (shift > 0) {
        // Shift buffer contents, discarding already processed data.
        self.buffer.replaceSubrange(..<(bufferSize - shift), with: self.buffer[shift..<bufferSize])
        self.limit  -= shift
        self.cursor -= shift
        self.marker -= shift
        self.token = 0
        /*!stags:re2c format = "        if self.@@ != tagNone { self.@@ -= shift }\n"; */
      }

      // Fill remaining space with new data.
      self.buffer.replaceSubrange(self.limit..<(self.limit + chunk.count), with: chunk)
      self.limit += chunk.count
    }
  }

  // Append a single value to an m-tag history.
  func add(tag prevTag: MTag?, value: Int) -> MTag {
    let tag = MTag(prev: prevTag, element: value)
    self.mTagPool.append(tag)
    return tag
  }

  // Decode a string from a slice of the buffer.
  func getString(_ range: Range<Int>) -> String {
    String(data: Data(self.buffer[range]), encoding: .utf8)!
  }

  enum Status {
    case waiting, done, end
  }
}

enum ParseError: Error {
  case unexpectedCharacter
  case bigPacket(Int, Int)
}

extension ParseError: LocalizedError {
  public var errorDescription: String? {
    switch self {
      case .unexpectedCharacter: "Malformed stream"
      case .bigPacket(let size, let free): "Token (\(size) bytes) too long for receive buffer (\(free) free)"
    }
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
  let c = State()

  // Main loop. The buffer contains incomplete data which appears packet by
  // packet. When the lexer needs more input it saves its internal state and
  // returns to the caller which should provide more input and resume lexing.
  var chunkIdx = 0
  do {
    finally: while true {
      switch try parse(c) {
        case .waiting:
          print("waiting")
          try c.feed(string: packets[chunkIdx])
          chunkIdx += 1
        case .done:
          print("done")
        case .end:
          print("end")
          break finally
      }
    }
    return 0
  } catch {
    log("Parse error:", error.localizedDescription)
    return 1
  }
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
