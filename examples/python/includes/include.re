# re2py $INPUT -o $OUTPUT

/*!include:re2c "definitions.py" */

def lex(str):
    cur = 0
    /*!re2c
        re2c:define:YYPEEK    = "str[cur]";
        re2c:define:YYSKIP    = "cur += 1";
        re2c:define:YYBACKUP  = "mar = cur";
        re2c:define:YYRESTORE = "cur = mar";
        re2c:yyfill:enable = 0;
        re2c:indent:top = 1;

        *      { return Num.NAN }
        number { return Num.INT }
        !include "extra_rules.re.inc";
    */

assert lex(b"123\0") == Num.INT
assert lex(b"123.4567\0") == Num.FLOAT
