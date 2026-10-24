// re2c $INPUT -o $OUTPUT -i --vectorize-linear
// The multi-character guard always checks YYLIMIT. With YYFILL enabled but its check disabled the
// lexer need not declare YYLIMIT, so without an explicit YYLIMIT configuration linear
// vectorization is disabled with a warning.
int lex(const char *YYCURSOR) {
    const char *YYMARKER;
    /*!re2c
        re2c:yyfill:check = 0;
        re2c:define:YYCTYPE = char;

        "abcdefgh" { return 1; }
        "ab"       { return 2; }
        *          { return 0; }
    */
}
