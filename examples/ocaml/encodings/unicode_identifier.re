(* re2ocaml $INPUT -o $OUTPUT --utf8 -i *)

/*!include:re2c "unicode_categories.re" */

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    mutable accept: int;
}

/*!re2c
    re2c:define:YYFN       = ["lex;bool", "st;state"];
    re2c:define:YYCTYPE    = int;
    re2c:define:YYPEEK     = "Char.code st.str.[st.cur]";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:variable:yyaccept = "st.accept";
    re2c:yyfill:enable     = 0;

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
        accept = 0;
    }
    in if not (lex st) then raise (Failure "error")

let _ = main ()
