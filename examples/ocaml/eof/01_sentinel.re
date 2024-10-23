(* re2ocaml $INPUT -o $OUTPUT *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
}

(* expect a null-terminated string *)
%{
    re2c:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:yyfill:enable = 0;

    *      { -1 }
    [\x00] { count }
    [a-z]+ { lex yyrecord (count + 1) }
    [ ]+   { lex yyrecord count }
%}

let test(yyinput, count) =
    let st = {yyinput = yyinput; yycursor = 0}
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("\x00", 0);
    test("one two three\x00", 3);
    test("f0ur\x00", -1)

let _ = main ()
