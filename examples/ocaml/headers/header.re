(* re2ocaml $INPUT -o $OUTPUT --header lexer/state.ml -i *)

open State

/*!header:re2c:on*/
type state = {
    str: string;
    mutable cur: int;
    mutable tag: int;
    /*!stags:re2c format = "mutable @@: int;"; */
}
/*!header:re2c:off*/

/*!re2c
    re2c:define:YYFN    = ["lex;int", "st;State.state"];
    re2c:define:YYCTYPE = int;
    re2c:define:YYPEEK  = "Char.code st.str.[st.cur]";
    re2c:define:YYSKIP  = "st.cur <- st.cur + 1;";
    re2c:define:YYSTAGP = "@@ <- st.cur;";
    re2c:tags = 1;
    re2c:tags:expression = "st.@@";
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/state.ml";

    [a]* @tag [b]* { st.tag }
*/

let main () =
    let st = {
        str = "ab\x00";
        cur = 0;
        tag = 0;
        /*!stags:re2c format = "\n\t@@ = 0;"; */
    }
    in if not (lex st = 1) then raise (Failure "error")

let _ = main ()
