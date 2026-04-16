// re2php $INPUT -o $OUTPUT
<?php

const BUFSIZE = 4096;
define('STATUS_OK', 0);
define('STATUS_EOF', 1);
define('STATUS_LONG_LEXEME', 2);

function fill(object $st): int {
    if ($st->eof) return STATUS_EOF;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if ($st->token < 1) return STATUS_LONG_LEXEME;

    // Shift buffer contents (discard everything up to the current token).
    $st->yyinput = substr($st->yyinput, $st->token, $st->yylimit - $st->token);
    $st->yycursor -= $st->token;
    $st->yymarker -= $st->token;
    $st->yylimit -= $st->token;
    $st->token = 0;

    // Read a new chunk of data from file and append it to the buffer.
    $want = BUFSIZE - $st->yylimit - 1; // -1 for sentinel
    $chunk = fread($st->file, $want);
    $nread = ($chunk !== false) ? strlen($chunk) : 0;
    $st->eof = $nread < $want; // end of file?
    $st->yyinput .= ($chunk !== false ? $chunk : '') . "\0"; // append data and sentinel
    $st->yylimit += $nread;

    return STATUS_OK;
}

function lex(object $yyrecord, int $count): int {
    lex_top:
    $yyrecord->token = $yyrecord->yycursor;
    /*!re2c
        re2c:api = record;
        re2c:yyrecord = $yyrecord;
        re2c:YYFILL = "fill($yyrecord) === STATUS_OK";
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return $count; }
        [ ]+ { goto lex_top; }
        str  { $count += 1; goto lex_top; }
    */
}

function main(): void {
    $fname = tempnam(sys_get_temp_dir(), 're2php_fill_');

    // Create input file.
    $f = fopen($fname, 'wb');
    $line = "'qu\0tes' 'are' 'fine: \\'' ";
    for ($i = 0; $i < BUFSIZE; $i++) {
        fwrite($f, $line);
    }
    fclose($f);

    // Init lexer state (cursor at limit triggers initial YYFILL).
    $limit = BUFSIZE - 1; // exclude terminating null
    $st = new \stdClass();
    $st->file = fopen($fname, 'rb');
    $st->yyinput = str_repeat("\0", BUFSIZE);
    $st->yycursor = $limit;
    $st->yymarker = $limit;
    $st->yylimit = $limit;
    $st->token = $limit;
    $st->eof = false;

    assert(lex($st, 0) === 3 * BUFSIZE);

    fclose($st->file);
    unlink($fname);
}

main();
