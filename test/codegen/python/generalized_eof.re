# re2py $INPUT -o $OUTPUT

%{rules:x
    $           { return 0 }
    *           { return 1 }
    [a] $       { return 2 }
    [a]         { return 3 }
    [b] $ | [b] { return 4 }
    [c]+ $      { return 5 }
%}

def lex_simple(yyinput):
    yycursor = 0
    yymarker = 0
    yylimit = len(yyinput) - 1
    %{use:x
        re2c:yyfill:enable = 0;
    %}

def lex_eof(yyinput):
    yycursor = 0
    yymarker = 0
    yylimit = len(yyinput) - 1
    %{use:x
        re2c:YYFILL = "False"; // always fails
        re2c:YYEND = "yycursor == yylimit";
        re2c:eof = 0;
    %}

%{max %}

def lex_scc(str):
    yyinput = str + (b"\0" * YYMAXFILL)
    yycursor = 0
    yylimit = len(yyinput)
    end = len(str) - 1
    %{use:x
        re2c:YYFILL = "return -1"; // always fails
        re2c:YYEND = "yycursor == end";
    %}

def test(str, ret):
    if lex_simple(str) != ret: raise "error simple"
    if lex_eof(str) != ret: raise "error eof" + lex_eof(str) + ret
    if lex_scc(str) != ret: raise "error scc"

test(b"\0", 0)
test(b"a\0", 2)
test(b"ax\0", 3)
test(b"b\0", 4)
test(b"bx\0", 4)
test(b"ccc\0", 5)
