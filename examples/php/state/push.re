// re2js $INPUT -o $OUTPUT -f

const fs = require('fs')

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
const BUFSIZE = 10
const DEBUG = false
const END = 0
const READY = 1
const WAITING = 2
const BIG_PACKET = 3
const BAD_PACKET = 4

function log() {
    if (DEBUG) console.log.apply(console, arguments)
}

function fill(st) {
    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (st.token < 1) return BIG_PACKET

    // Shift buffer contents (discard everything up to the current token).
    st.yyinput.copy(st.yyinput, 0, st.token, st.yylimit)
    st.yycursor -= st.token;
    st.yymarker -= st.token;
    st.yylimit -= st.token;
    st.token = 0;

    // Read a new chunk of data from file and append it to `yyinput`.
    let want = BUFSIZE - st.yylimit - 1 // -1 for sentinel
    let nread = fs.readSync(st.file, st.yyinput, st.yylimit, want)
    st.yylimit += nread
    st.yyinput.writeUInt8(0, st.yylimit) // sentinel

    return READY
}

function lex(yyrecord) {
    loop: while (true) {
        yyrecord.token = yyrecord.yycursor
        /*!re2c
            re2c:api = record;
            re2c:YYPEEK = "readUInt8";
            re2c:YYFILL = "return WAITING";
            re2c:eof = 0;

            packet = [a-z]+[;];

            *      { return BAD_PACKET }
            $      { return END }
            packet { yyrecord.received += 1; continue loop }
        */
    }
}

function test(packets, expect) {
    // Emulate a "pipe" by opening the same file for reading and writing.
    let fname = "input"
    let fw = fs.openSync(fname, 'w');
    let fr = fs.openSync(fname, 'r');

    // Init lexer state.
    let limit = BUFSIZE - 1 // exclude terminating null
    let st = {
        file: fr,
        yyinput: Buffer.alloc(BUFSIZE),
        yylimit: limit,
        yycursor: limit,
        yymarker: limit,
        token: limit,
        yystate: -1,
        received: 0
    }

    // Main loop. The buffer contains incomplete data which appears packet by
    // packet. When the lexer needs more input it saves its internal state and
    // returns to the caller which should provide more input and resume lexing.
    let send = 0
    let status
    loop: while (true) {
        status = lex(st)

        if (status == END) {
            log("done: got", st.received, "packets")
            break loop
        } else if (status == WAITING) {
            log("waiting...");

            if (send < packets.length) {
                log("sent packet", send, packets[send])
                fs.writeFileSync(fw, packets[send])
                send += 1
            }

            status = fill(st)
            log("queue:", st.yyinput.toString())
            if (status == BIG_PACKET) {
                log("error: packet too big")
                break loop
            }

            if (status != READY) throw "expected READY"
        } else {
            if (status != BAD_PACKET) throw "expected BAD_PACKET"
            log("error: ill-formed packet")
            break loop
        }
    }

    // Check results.
    if (status != expect) throw "unexpected status"
    if (status == END && st.received != send) "unexpected packet count"

    // Cleanup.
    fs.unlinkSync(fname, function(err){ if (err) throw err; })
}

function main() {
    test([], END)
    test(["zero;", "one;", "two;", "three;", "four;"], END)
    test(["zer0;"], BAD_PACKET)
    test(["goooooooooogle;"], BIG_PACKET)
}

main()
