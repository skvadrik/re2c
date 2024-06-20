(* re2ocaml $INPUT -o $OUTPUT --header lexer/state.ml -i *)

open State
open String

/*!header:re2c:on*/
type state = {
    str: string;
    mutable yycursor: int;
    mutable tag: int;
    /*!stags:re2c format = "mutable @@: int;"; */
}
/*!header:re2c:off*/

/*!re2c
    re2c:define:YYFN = ["lex;int", "yyrecord;State.state"];
    re2c:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/state.ml";

    [a]* @tag [b]* { yyrecord.tag }
*/

let main () =
    let st = {
        str = "ab\x00";
        yycursor = 0;
        tag = 0;
        /*!stags:re2c format = "\n\t@@ = 0;"; */
    }
    in if not (lex st = 1) then raise (Failure "error")

let _ = main ()
