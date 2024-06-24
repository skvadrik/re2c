// re2rust $INPUT -o $OUTPUT -cf --recursive-functions -Wno-nondeterministic-tags
#![allow(non_upper_case_globals)]

use std::fs::File;
use std::io::{Read, Write};

/*!conditions:re2c*/

const DEBUG: bool = false;
macro_rules! log {
    ($($fmt:expr)? $(, $args:expr)*) => { if DEBUG { println!($($fmt)? $(, $args)*) } }
}

const CON_STATE_SIZE: usize = 4095;

#[derive(Debug, PartialEq)]
enum ConStatus {Ready, Waiting, End, BigPacket, BadPacket}

const NONE: usize = std::usize::MAX;
const MTAG_ROOT: usize = NONE - 1;

struct ConState {
    file: File,
    yyinput: [u8; CON_STATE_SIZE + 1],
    yylimit: usize,
    yycursor: usize,
    yymarker: usize,
    token: usize,
    yycond: isize,
    yystate: isize,
    mtag_trie: MtagTrie,
    /*!stags:re2c format = '\n\t@@: usize,'; */
    /*!mtags:re2c format = '\n\t@@: usize,'; */
    l1: usize,
    l2: usize,
    f1: usize,
    f2: usize,
    p1: usize,
    p2: usize,
    p3: usize,
    p4: usize,
    yyaccept: usize,
}

// An m-tag tree is a way to store histories with an O(1) copy operation.
// Histories naturally form a tree, as they have common start and fork at some
// point. The tree is stored as an array of pairs (tag value, link to parent).
// An m-tag is represented with a single link in the tree (array index).
type MtagTrie = Vec::<MtagElem>;
struct MtagElem {
    elem: usize, // tag value
    pred: usize, // index of the predecessor node or root
}

// Append a single value to an m-tag history.
fn add_mtag(trie: &mut MtagTrie, mtag: usize, value: usize) -> usize {
    trie.push(MtagElem{elem: value, pred: mtag});
    return trie.len() - 1;
}

// Recursively unwind tag histories and collect version components.
fn unwind(trie: &MtagTrie, x: usize, y: usize, str: &[u8], result: &mut Vec::<String>) {
    // Reached the root of the m-tag tree, stop recursion.
    if x == MTAG_ROOT && y == MTAG_ROOT { return; }

    // Unwind history further.
    unwind(trie, trie[x].pred, trie[y].pred, str, result);

    // Get tag values. Tag histories must have equal length.
    assert!(x != MTAG_ROOT && y != MTAG_ROOT);
    let (ex, ey) = (trie[x].elem, trie[y].elem);

    if ex != NONE && ey != NONE {
        // Both tags are valid string indices, extract component.
        result.push(String::from_utf8_lossy(&str[ex..ey]).to_string());
    } else {
        // Both tags are NONE (this corresponds to zero repetitions).
        assert!(ex == NONE && ey == NONE);
    }
}

fn fill(st: &mut ConState) -> ConStatus {
    let shift = st.token;
    let used = st.yylimit - st.token;
    let free = CON_STATE_SIZE - used;

    // Error: no space. In real life can reallocate a larger buffer.
    if free < 1 { return ConStatus::BigPacket; }

    // Shift buffer contents (discard already processed data).
    unsafe {
        let p = st.yyinput.as_mut_ptr();
        std::ptr::copy(p, p.offset(shift as isize), used);
    }
    st.yylimit -= shift;
    st.yycursor -= shift;
    st.yymarker = st.yymarker.overflowing_sub(shift).0; // underflow ok if marker is unused
    st.token -= shift;
    /*!stags:re2c format = "if st.@@ != NONE { st.@@.overflowing_sub(shift).0; }\n"; */

    // Fill free space at the end of buffer with new data.
    match st.file.read(&mut st.yyinput[st.yylimit..CON_STATE_SIZE]) {
        Ok(n) => st.yylimit += n,
        Err(why) => panic!("cannot read from file: {}", why)
    }
    st.yyinput[st.yylimit] = 0; // append sentinel symbol

    return ConStatus::Ready;
}

/*!re2c
    re2c:eof = 0;
    re2c:tags = 1;
    re2c:api = record;
    re2c:variable:yyrecord = "st";
    re2c:define:YYFN       = ["lex;ConStatus", "st;&mut ConState"];
    re2c:define:YYCTYPE    = "u8";
    re2c:define:YYFILL     = "return ConStatus::Waiting;";
    re2c:define:YYMTAGP    = "@@ = add_mtag(&mut st.mtag_trie, @@, st.yycursor);";
    re2c:define:YYMTAGN    = "@@ = add_mtag(&mut st.mtag_trie, @@, NONE);";

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
        log!("media type: {}", String::from_utf8_lossy(&st.yyinput[st.l1..st.l2]));

        let mut pnames: Vec::<String> = Vec::new();
        unwind(&mut st.mtag_trie, st.p1, st.p2, &st.yyinput, &mut pnames);
        log!("pnames: {:?}", pnames);

        let mut pvals: Vec::<String> = Vec::new();
        unwind(&mut st.mtag_trie, st.p3, st.p4, &st.yyinput, &mut pvals);
        log!("pvals: {:?}", pvals);

        st.token = st.yycursor;
        return lex(st);
    }

    <header> header_field_folded crlf {
        let mut folds: Vec::<String> = Vec::new();
        unwind(&mut st.mtag_trie, st.f1, st.f2, &st.yyinput, &mut folds);
        log!("folds: {:?}", folds);

        st.token = st.yycursor;
        return lex(st);
    }

    <*> $ { return ConStatus::End; }
    <*> * { return ConStatus::BadPacket; }
*/

fn test(packets: Vec<&[u8]>, expect: ConStatus) {
    // Create a "socket" (open the same file for reading and writing).
    let fname = "pipe";
    let mut fw: File = match File::create(fname) {
        Err(why) => panic!("cannot open {}: {}", fname, why),
        Ok(file) => file,
    };
    let fr: File = match File::open(fname) {
        Err(why) => panic!("cannot read file {}: {}", fname, why),
        Ok(file) => file,
    };

    // Initialize lexer state: `state` value is -1, all offsets are at the end
    // of buffer, the character at `yylimit` offset is the sentinel (null).
    let mut state = ConState {
        file: fr,
        yyinput: [0; CON_STATE_SIZE + 1], // sentinel (at `yylimit` offset) is set to null
        yycursor: CON_STATE_SIZE,
        yymarker: CON_STATE_SIZE,
        yylimit: CON_STATE_SIZE,
        token: CON_STATE_SIZE,
        yycond: YYC_media_type,
        yystate: -1,
        /*!stags:re2c format = "@@: NONE,\n"; */
        /*!mtags:re2c format = "@@: MTAG_ROOT,\n"; */
        mtag_trie: Vec::new(),
        l1: NONE,
        l2: NONE,
        f1: MTAG_ROOT,
        f2: MTAG_ROOT,
        p1: MTAG_ROOT,
        p2: MTAG_ROOT,
        p3: MTAG_ROOT,
        p4: MTAG_ROOT,
        yyaccept: 0
    };

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    let mut status;
    let mut send = 0;
    loop {
        status = lex(&mut state);
        if status == ConStatus::End {
            log!("done");
            break;
        } else if status == ConStatus::Waiting {
            log!("waiting...");
            if send < packets.len() {
                log!("sent packet {}", send);
                match fw.write_all(packets[send]) {
                    Err(why) => panic!("cannot write to {}: {}", fname, why),
                    Ok(_) => send += 1,
                }
            }
            status = fill(&mut state);
            log!("queue: '{}'", String::from_utf8_lossy(&state.yyinput));
            if status == ConStatus::BigPacket {
                log!("error: packet too big");
                break;
            }
            assert_eq!(status, ConStatus::Ready);
        } else {
            assert_eq!(status, ConStatus::BadPacket);
            log!("error: ill-formed packet");
            break;
        }
    }

    // Check results.
    assert_eq!(status, expect);

    // Cleanup: remove input file.
    match std::fs::remove_file(fname) {
        Err(why) => panic!("cannot remove {}: {}", fname, why),
        Ok(_) => {}
    }
}

fn main() {
    test(vec![], ConStatus::End);
    test(vec![b"ap", b"plication/j", b"son;", b" charset=\"", b"utf\\\"-8\"\r", b"\n", b""], ConStatus::End);
}
