(* re2ocaml $INPUT -o $OUTPUT -i *)

open Printf

let none = -1;

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    /*!stags:re2c:b1:b2 format = '\n\tmutable @@{tag}: int;'; */
    mutable x: int;
    mutable y: int;
    mutable yynmatch: int; (* number of capturing groups *)
    mutable yypmatch: int array; (* memory for capturing parentheses *)
}

/*!re2c
    re2c:api = custom;
    re2c:define:YYCTYPE = char;
    re2c:define:YYPEEK = "st.str.[st.cur]";
    re2c:define:YYSKIP = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP = "st.mar <- st.cur;";
    re2c:define:YYRESTORE = "st.cur <- st.mar;";
    re2c:define:YYSTAGP = "@@{tag} <- st.cur;";
    re2c:define:YYSTAGN = "@@{tag} <- none;";
    re2c:define:YYSHIFTSTAG = "@@{tag} <- @@{tag} + @@{shift};";
    re2c:yyfill:enable = 0;
    re2c:tags:expression = "st.@@";
*/

/*!re2c:b1
    re2c:define:YYFN = ["lex_tags;int", "st;state"];
    re2c:tags = 1;

    ([b] @x [a] @y)? { if st.x = none then none else st.y - st.x }
*/

/*!maxnmatch:re2c:b2*/

/*!re2c:b2
    re2c:define:YYFN = ["lex_captures;int", "st;state"];
    re2c:posix-captures = 1;

    (([a]))? { st.yypmatch.(4) }
*/

let make_state (str: string) : state =
    let st = {
        str = str;
        cur = 0;
        mar = 0;
        /*!stags:re2c:b1:b2 format = '\n\t\t@@{tag} = none;'; */
        x = none;
        y = none;
        yynmatch = 0;
        yypmatch = Array.make (2 * yymaxnmatch) none;
    } in st

let test_tags (str: string) (expect: int) =
    if (lex_tags (make_state str) <> expect) then raise (Failure "error")

let test_captures (str: string) (expect: int) =
    if (lex_captures (make_state str) <> expect) then raise (Failure "error")

let main () =
    test_tags "\x00" (-1);
    test_tags "ba\x00" 1;
    test_captures "\x00" (-1);
    test_captures "a\x00" 0;
    ()

let _ = main ()
