// re2v $INPUT -o $OUTPUT -i

/*!include:re2c "definitions.v" */

fn lex(yyinput string) Result {
    mut yycursor, mut yymarker := 0, 0
    /*!re2c
        re2c:yyfill:enable = 0;

        *      { return .fail }
        number { return .ok }
        !include "extra_rules.re.inc";
    */
}

fn main() {
    assert lex("123\0") == .ok
    assert lex("123.4567\0") == .ok
}
