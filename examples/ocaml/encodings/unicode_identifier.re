(* re2ocaml $INPUT -o $OUTPUT --utf8 -i *)

open String

%{include "unicode_categories.re" %}

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable yyaccept: int;
}

%{
    re2c:YYFN = ["lex;bool", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    // Simplified "Unicode Identifier and Pattern Syntax"
    // (see https://unicode.org/reports/tr31)
    id_start    = L | Nl | [$_];
    id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
    identifier  = id_start id_continue*;

    identifier { true }
    *          { false }
%}

let main () =
    let st = {
        yyinput = "_Ыдентификатор\x00";
        yycursor = 0;
        yymarker = 0;
        yyaccept = 0;
    }
    in if not (lex st) then raise (Failure "error")

let _ = main ()
