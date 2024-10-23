(* re2ocaml $INPUT -o $OUTPUT *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    yylimit: int;
}

(* expect a null-terminated string *)
%{
    re2c:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { -1 }
    $    { count }
    str  { lex yyrecord (count + 1) }
    [ ]+ { lex yyrecord count }
%}

let test(str, count) =
    let st = {
        yyinput = str;
        yycursor = 0;
        yymarker = 0;
        yylimit = length str - 1; (* terminating null not included *)
    }
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("\x00", 0);
    test("'qu\x00tes' 'are' 'fine: \\'' \x00", 3);
    test("'unterminated\\'\x00", -1)

let _ = main ()
