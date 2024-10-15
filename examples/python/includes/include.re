# re2py $INPUT -o $OUTPUT

%{include "definitions.py" %}

def lex(yyinput):
    yycursor = 0
%{
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;

    *      { return Num.NAN }
    number { return Num.INT }
    !include "extra_rules.re.inc";
%}

assert lex(b"123\0") == Num.INT
assert lex(b"123.4567\0") == Num.FLOAT
