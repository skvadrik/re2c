// re2js $INPUT -o $OUTPUT

const fs = require('fs')

const BUFSIZE = 4096
const OK = 0
const EOF = 1
const LONG_LEXEME = 2

function fill(st) {
    if (st.eof) return EOF

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (st.token < 1) return LONG_LEXEME

    // Shift buffer contents (discard everything up to the current token).
    st.yyinput.copy(st.yyinput, 0, st.token, st.yylimit)
    st.yycursor -= st.token;
    st.yymarker -= st.token;
    st.yylimit -= st.token;
    st.token = 0;

    // Read a new chunk of data from file and append it to `yyinput`.
    let want = BUFSIZE - st.yylimit - 1 // -1 for sentinel
    let nread = fs.readSync(st.file, st.yyinput, st.yylimit, want)
    st.eof = nread < want // end of file?
    st.yylimit += nread
    st.yyinput.writeUInt8(0, st.yylimit) // sentinel

    return OK
}

function lex(yyrecord, count) {
    loop: while (true) {
        yyrecord.token = yyrecord.yycursor
        /*!re2c
            re2c:api = record;
            re2c:YYPEEK = "readUInt8";
            re2c:YYFILL = "fill(yyrecord) == OK";
            re2c:eof = 0;

            str = ['] ([^'\\] | [\\][^])* ['];

            *    { return -1 }
            $    { return count }
            [ ]+ { continue loop }
            str  { count += 1; continue loop }
        */
    }
}

function main() {
    let fname = "input"

    // Create input file.
    let content = "'qu\0tes' 'are' 'fine: \\'' ".repeat(BUFSIZE)
    fs.writeFileSync(fname, content, function(err) { if (err) throw err; })

    // Init lexer state.
    let limit = BUFSIZE - 1 // exclude terminating null
    let st = {
        file: fs.openSync(fname, 'r'),
        yyinput: Buffer.alloc(BUFSIZE),
        yylimit: limit,
        yycursor: limit,
        yymarker: limit,
        token: limit,
        eof: false
    }

    // Run lexer on the prepared file.
    if (lex(st, 0) != 3 * BUFSIZE) { throw "error :[" }

    // Cleanup.
    fs.unlink(fname, function(err){ if (err) throw err; })
}

main()
