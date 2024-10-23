(* re2ocaml $INPUT -o $OUTPUT *)

open String

exception Fill

type state = {
    yyinput: string;
    mutable yycursor: int;
    yylimit: int;
}

%{max %}
%{
    re2c:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:YYFILL = "raise Fill;";

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        (* check that it is the sentinel, not some unexpected null *)
        if yyrecord.yycursor = length yyrecord.yyinput - yymaxfill + 1 then count else -1
    }
    str  { lex yyrecord (count + 1) }
    [ ]+ { lex yyrecord count }
    *    { -1 }
%}

let test(str, count) =
    let buf = cat str (make yymaxfill '\x00') in
    let st = {yyinput = buf; yycursor = 0; yylimit = length buf} in
    let result = try lex st 0 with Fill -> -1 in
    if not (result = count) then raise (Failure "error")

let main () =
    test("", 0);
    test("'unterminated\\'", -1);
    test("'qu\x00tes' 'are' 'fine: \\'' ", 3);
    test("'unexpected \x00 null", -1)

let _ = main ()
