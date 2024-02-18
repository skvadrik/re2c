(* re2ocaml $INPUT -o $OUTPUT -i *)

type state = {
    str: string;
    mutable cur: int;
}

/*!re2c
    re2c:define:YYFN    = ["lex;bool", "st;state"];
    re2c:define:YYCTYPE = int;
    re2c:define:YYPEEK  = "Char.code st.str.[st.cur]";
    re2c:define:YYSKIP  = "st.cur <- st.cur + 1;";
    re2c:yyfill:enable  = 0;

    number = [1-9][0-9]*;

    number { true }
    *      { false }
*/

let main () =
    let st = {str = "1234\x00"; cur = 0}
    in if not (lex st) then raise (Failure "error")

let _ = main ()
