<?php
// re2php $INPUT -o $OUTPUT

const fs = require('fs')

const BUFSIZE = 4096;
const OK = 0;
const EOF = 1;
const LONG_LEXEME = 2;

function fill($st) {
    if (st.eof) return EOF

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (st.token < 1) return LONG_LEXEME;

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

    return OK;
}

function lex($yyrecord, $count) {
    while (true) {
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
    $fname = "input";

    // Create input file.
    $content = str_repeat("'qu\0tes' 'are' 'fine: \\'' ", BUFSIZE);
    $handle = fopen($name, 'w+');
    fwrite($handle, $content);
    fclose($handle);

    // Init lexer state.
    $limit = BUFSIZE - 1; // exclude terminating null
    $st = new \stdClass();
    $st->file = fopen($fname, 'r');
    $st->yyinput = str_repeat("\0", BUFSIZE);
    $st->yylimit = $limit;
    $st->yycursor = $limit;
    $st->yymarker = $limit;
    $st->token = $limit;
    $st->eof = false;

    // Run lexer on the prepared file.
    if (lex($st, 0) != 3 * BUFSIZE) {
        throw new \Exception("error :[");
    }

    // Cleanup.
    fclose($st->file);
    unlink($fname);
}

main();
