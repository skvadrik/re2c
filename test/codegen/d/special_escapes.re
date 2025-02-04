// re2d $INPUT -o $OUTPUT -i
module main;

private bool lex(const(char)* yycursor) {
    const(char)* yymarker;
    /*!re2c
        re2c:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        "\a\b\f\n\r\t\v\\'\"" { return true; }
        * {
            auto _ = ['\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"']; // unused
            return false;
        }
    */
}

void main() {
    assert(lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\""));
}
