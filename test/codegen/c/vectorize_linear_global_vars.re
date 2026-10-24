// re2c $INPUT -o $OUTPUT -i --vectorize-linear --syntax vectorize_linear_global_vars.inc
// Global syntax file variables (nl, indent, dedent, topindent) are allowed in any code template.
// The multi-character guard is rendered inline on one line, so they have no effect on layout and a
// newline becomes a space.
int lex(const char *YYCURSOR, const char *YYLIMIT) {
    const char *YYMARKER;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:YYLIMIT = YYLIMIT;
        re2c:define:YYCTYPE = char;

        "abcdefgh" { return 1; }
        "ab"       { return 2; }
        *          { return 0; }
    */
}
