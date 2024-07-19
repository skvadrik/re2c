// re2v $INPUT -o $OUTPUT -cf --recursive-functions -Wno-nondeterministic-tags

import arrays
import log
import os

/*!conditions:re2c*/

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
const bufsize = 100

const mtag_root = -1
const tag_none = -1

// An m-tag tree is a way to store histories with an O(1) copy operation.
// Histories naturally form a tree, as they have common start and fork at some
// point. The tree is stored as an array of pairs (tag value, link to parent).
// An m-tag is represented with a single link in the tree (array index).
struct MtagElem {
    elem int
    pred int
}
type MtagTrie = []MtagElem

// Append a single value to an m-tag history.
fn add_mtag(mut trie &MtagTrie, mtag int, value int) int {
    trie = arrays.concat(trie, MtagElem{value, mtag})
    return trie.len - 1
}

// Recursively unwind tag histories and collect version components.
fn unwind(trie MtagTrie, x int, y int, str []u8) []string {
    // Reached the root of the m-tag tree, stop recursion.
    if x == mtag_root && y == mtag_root {
        return []
    }

    // Unwind history further.
    mut result := unwind(trie, trie[x].pred, trie[y].pred, str)

    // Get tag values. Tag histories must have equal length.
    if x == mtag_root || y == mtag_root {
        panic("tag histories have different length")
    }
    ex := trie[x].elem
    ey := trie[y].elem

    if ex != tag_none && ey != tag_none {
        // Both tags are valid string indices, extract component.
        result = arrays.concat(result, str[ex..ey].str())
    } else if !(ex == tag_none && ey == tag_none) {
        panic("both tags should be tagNone")
    }
    return result
}

struct State {
mut:
    file     os.File
    yyinput  []u8
    yycursor int
    yymarker int
    yylimit  int
    token    int
    yycond   YYCONDTYPE
    yystate  int
    trie     MtagTrie
    /*!stags:re2c format = '\n\t@@ int'; */
    /*!mtags:re2c format = '\n\t@@ int'; */
    l1       int
    l2       int
    f1       int
    f2       int
    p1       int
    p2       int
    p3       int
    p4       int
    yyaccept int
}

enum Status {
    lex_end
    lex_ready
    lex_waiting
    lex_bad_packet
    lex_big_packet
}

fn fill(mut st &State) Status {
    shift := st.token
    used := st.yylimit - st.token
    free := bufsize - used

    // Error: no space. In real life can reallocate a larger buffer.
    if free < 1 { return .lex_big_packet }

    // Shift buffer contents (discard already processed data).
    copy(mut &st.yyinput, st.yyinput[shift..shift+used])
    st.yycursor -= shift
    st.yymarker -= shift
    st.yylimit -= shift
    st.token -= shift
    /*!stags:re2c format = '\n\tif st.@@ != tag_none { st.@@ -= shift };'; */

    // Fill free space at the end of buffer with new data.
    pos := st.file.tell() or { 0 }
    if n := st.file.read_bytes_into(u64(pos), mut st.yyinput[st.yylimit..bufsize]) {
        st.yylimit += n
    }
    st.yyinput[st.yylimit] = 0 // append sentinel symbol

    return .lex_ready
}

/*!re2c
    re2c:api = record;
    re2c:eof = 0;
    re2c:tags = 1;
    re2c:tags:negative = "tag_none";
    re2c:variable:yyrecord = st;
    re2c:define:YYCTYPE = u8;
    re2c:define:YYFN = ["lex;Status", "mut st;State"];
    re2c:define:YYFILL = "return .lex_waiting";
    re2c:define:YYMTAGP = "@@ = add_mtag(mut &st.trie, @@, st.yycursor)";
    re2c:define:YYMTAGN = "@@ = add_mtag(mut &st.trie, @@, tag_none)";

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
        mt := st.yyinput[st.l1..st.l2].str()
        log.debug("media type: $mt")

        pnames := unwind(st.trie, st.p1, st.p2, st.yyinput)
        log.debug("pnames: $pnames")

        pvals := unwind(st.trie, st.p3, st.p4, st.yyinput)
        log.debug("pvals: $pvals")

        st.token = st.yycursor
        return lex(mut st)
    }

    <header> header_field_folded crlf {
        folds := unwind(st.trie, st.f1, st.f2, st.yyinput)
        log.debug("folds: $folds")

        st.token = st.yycursor
        return lex(mut st)
    }

    <*> * { return .lex_bad_packet }
    <*> $ { return .lex_end }
*/

fn test(expect Status, packets []string) {
    // Create a "socket" (open the same file for reading and writing).
    fname := "pipe"
    mut fw := os.create(fname) or { panic("cannot create file") }
    mut fr := os.open(fname) or { panic("cannot open file") }

    // Initialize lexer state: `state` value is -1, all offsets are at the end
    // of buffer.
    mut st := &State{
        file:     fr,
        // Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
        yyinput:  []u8{len: bufsize + 1},
        yycursor: bufsize,
        yymarker: bufsize,
        yylimit:  bufsize,
        token:    bufsize,
        yycond:   .yycmedia_type,
        yystate:  -1,
        trie:     []MtagElem{},
        /*!stags:re2c format = '\n\t\t@@: tag_none,'; */
        /*!mtags:re2c format = '\n\t\t@@: mtag_root,'; */
        l1:       tag_none,
        l2:       tag_none,
        f1:       mtag_root,
        f2:       mtag_root,
        p1:       mtag_root,
        p2:       mtag_root,
        p3:       mtag_root,
        p4:       mtag_root,
        yyaccept: 0,
    }
    // yyinput is zero-initialized, no need to write sentinel

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    mut status := Status.lex_ready
    mut send := 0
    for {
        status = lex(mut st)
        if status == .lex_end {
            break
        } else if status == .lex_waiting {
            if send < packets.len {
                log.debug("sending packet $send")
                fw.write_string(packets[send]) or { panic("cannot write to file") }
                fw.flush()
                send += 1
            }
            status = fill(mut st)
            log.debug("filled buffer $st.yyinput, status $status")
            if status != .lex_ready {
                break
            }
        } else if status == .lex_bad_packet {
            break
        }
    }

    // Check results.
    if status != expect {
        panic("expected $expect, got $status")
    }

    // Cleanup: remove input file.
    fr.close()
    fw.close()
    os.rm(fname) or { panic("cannot remove file") }
}

fn main() {
    //log.set_level(.debug)
    test(.lex_end, ["ap", "plication/j", "son;", " charset=\"", "utf\\\"-8\"\r", "\n", ""])
}
