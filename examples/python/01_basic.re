# re2py $INPUT -o $OUTPUT

def lex(yyinput):
    yycursor = 0
%{
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;

    [1-9][0-9]* { return True }
    *           { return False }
%}

assert lex(b"1234\0")
