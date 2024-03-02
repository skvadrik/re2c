(* re2ocaml $INPUT -o $OUTPUT -i *)

/*!include:re2c "definitions.ml" */

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    mutable accept: int;
}

/*!re2c
    re2c:define:YYFN       = ["lex;number", "st;state"];
    re2c:define:YYCTYPE    = char;
    re2c:define:YYPEEK     = "st.str.[st.cur]";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:variable:yyaccept = "st.accept";
    re2c:yyfill:enable     = 0;

    *      { NaN }
    number { Int }
    !include "extra_rules.re.inc";
*/

let test(str, num) =
    let st = {str = str; cur = 0; mar = 0; accept = 0}
    in if not (lex st = num) then raise (Failure "error")

let main () =
    test("123\x00", Int);
    test("123.4567\x00", Float)

let _ = main ()
