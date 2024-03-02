(* re2ocaml $INPUT -o $OUTPUT *)

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    lim: int;
}

(* expect a null-terminated string *)
/*!re2c
    re2c:define:YYFN       = ["lex;int", "st;state", "count;int"];
    re2c:define:YYCTYPE    = char;
    re2c:define:YYPEEK     = "st.str.[st.cur]";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:define:YYLESSTHAN = "st.cur >= st.lim";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { -1 }
    $    { count }
    str  { lex st (count + 1) }
    [ ]+ { lex st count }
*/

let test(str, count) =
    let st = {
        str = str;
        cur = 0;
        mar = 0;
        lim = String.length str - 1; (* termunating null not included *)
    }
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("\x00", 0);
    test("'qu\x00tes' 'are' 'fine: \\'' \x00", 3);
    test("'unterminated\\'\x00", -1)

let _ = main ()
