# re2py $INPUT -o $OUTPUT

def lex(yyinput):
    yycursor = 0
    yymarker = 0
%{
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;

    "\a\b\f\n\r\t\v\\'\"" { return True }
    * { return False }
%}

assert lex(b"\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\0")
