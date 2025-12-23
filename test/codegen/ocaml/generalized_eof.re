(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    yylimit: int;
    yyend: int;
}

exception Fill

%{rules:x
    $           { 0 }
    *           { 1 }
    [a] $       { 2 }
    [a]         { 3 }
    [b] $ | [b] { 4 }
    [c]+ $      { 5 }
%}

%{use:x
    re2c:YYFN = ["lex_simple;int", "yyrecord;state"];
    re2c:yyfill:enable = 0;
%}

let test_simple str ret =
    let st = {yyinput = str; yycursor = 0; yymarker = 0; yylimit = length str - 1; yyend = -1} in
    let result = try lex_simple st with Fill -> -1 in
    if not (result = ret) then raise (Failure "error simple")

%{use:x
    re2c:YYFN = ["lex_eof;int", "yyrecord;state"];
    re2c:YYFILL = "false";
    re2c:YYEND = "yyrecord.yycursor == yyrecord.yylimit";
    re2c:eof = 0;
%}

let test_eof str ret =
    let st = {yyinput = str; yycursor = 0; yymarker = 0; yylimit = length str - 1; yyend = -1} in
    let result = try lex_eof st with Fill -> -1 in
    if not (result = ret) then raise (Failure "error eof")

%{max %}

%{use:x
    re2c:YYFN = ["lex_scc;int", "yyrecord;state"];
    re2c:YYFILL = "raise Fill;";
    re2c:YYEND = "yyrecord.yycursor == yyrecord.yyend";
%}

let test_scc str ret =
    let buf = cat str (make yymaxfill '\x00') in
    let st = {yyinput = buf; yycursor = 0; yymarker = 0; yylimit = length buf; yyend = length str - 1} in
    let result = try lex_scc st with Fill -> -1 in
    if not (result = ret) then raise (Failure "error scc")

let test str ret =
    test_simple str ret;
    test_eof str ret;
    test_scc str ret

let main () =
    test "\x00" 0;
    test "a\x00" 2;
    test "ax\x00" 3;
    test "b\x00" 4;
    test "bx\x00" 4;
    test "ccc\x00" 5

let _ = main ()
