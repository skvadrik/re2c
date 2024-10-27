(* re2ocaml $INPUT -o $OUTPUT *)

type state = {
    str: string;
    mutable cur: int;
    lim: int;
}

(* expect a string without terminating null *)
%{
    re2c:api = generic;
    re2c:YYFN = ["lex;int", "st;state", "count;int"];
    re2c:YYPEEK = "if st.cur < st.lim then st.str.[st.cur] else '\\x00'";
    re2c:YYSKIP = "st.cur <- st.cur + 1;";
    re2c:yyfill:enable = 0;

    *      { -1 }
    [\x00] { count }
    [a-z]+ { lex st (count + 1) }
    [ ]+   { lex st count }
%}

let test(str, count) =
    let st = {str = str; cur = 0; lim = String.length str}
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("", 0);
    test("one two three", 3);
    test("f0ur", -1)

let _ = main ()
