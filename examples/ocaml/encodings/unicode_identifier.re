(* re2ocaml $INPUT -o $OUTPUT --utf8 -i *)

open String

/*!include:re2c "unicode_categories.re" */

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    mutable yyaccept: int;
}

/*!re2c
    re2c:define:YYFN = ["lex;bool", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    // Simplified "Unicode Identifier and Pattern Syntax"
    // (see https://unicode.org/reports/tr31)
    id_start    = L | Nl | [$_];
    id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
    identifier  = id_start id_continue*;

    identifier { true }
    *          { false }
*/

let main () =
    let st = {
        str = "_Ыдентификатор\x00";
        cur = 0;
        mar = 0;
        yyaccept = 0;
    }
    in if not (lex st) then raise (Failure "error")

let _ = main ()
