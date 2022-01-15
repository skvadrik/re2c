// re2c $INPUT -o $OUTPUT -i --case-ranges

int lex(const char *s) {
    const char *YYCURSOR = s;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        number = [1-9][0-9]*;

        number { return 0; }
        *      { return 1; }
    */
}

int main() {
    return lex("1234");
}
