// re2v $INPUT -o $OUTPUT -i

/*!include:re2c "definitions.v" */

fn lex(str string) Result {
    mut cur, mut mar := 0, 0
    /*!re2c
        re2c:define:YYCTYPE   = u8;
        re2c:define:YYPEEK    = "str[cur]";
        re2c:define:YYSKIP    = "cur += 1";
        re2c:define:YYBACKUP  = "mar = cur";
        re2c:define:YYRESTORE = "cur = mar";
        re2c:yyfill:enable    = 0;

        *      { return .fail }
        number { return .ok }
        !include "extra_rules.re.inc";
    */
}

fn main() {
    assert lex("123\0") == .ok
    assert lex("123.4567\0") == .ok
}
