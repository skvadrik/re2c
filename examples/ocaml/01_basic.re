(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
}

%{
    re2c:define:YYFN = ["lex;bool", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { true }
    *      { false }
%}

let main () =
    let st = {yyinput = "1234\x00"; yycursor = 0}
    in if not (lex st) then raise (Failure "error")

let _ = main ()
