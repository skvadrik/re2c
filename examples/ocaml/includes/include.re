(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

%{include "definitions.ml" %}

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable yyaccept: int;
}

%{
    re2c:YYFN = ["lex;number", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    *      { NaN }
    number { Int }
    !include "extra_rules.re.inc";
%}

let test(str, num) =
    let st = {yyinput = str; yycursor = 0; yymarker = 0; yyaccept = 0}
    in if not (lex st = num) then raise (Failure "error")

let main () =
    test("123\x00", Int);
    test("123.4567\x00", Float)

let _ = main ()
