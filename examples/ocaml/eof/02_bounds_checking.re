(* re2ocaml $INPUT -o $OUTPUT *)

exception Fill

type state = {
    buf: string;
    mutable cur: int;
    lim: int;
}

/*!max:re2c*/
/*!re2c
    re2c:define:YYFN       = ["lex;int", "st;state", "count;int"];
    re2c:define:YYCTYPE    = char;
    re2c:define:YYPEEK     = "st.buf.[st.cur]";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYLESSTHAN = "st.cur + @@ > st.lim";
    re2c:define:YYFILL     = "raise Fill;";

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        (* check that it is the sentinel, not some unexpected null *)
        if st.cur = String.length st.buf - yymaxfill + 1 then count else -1
    }
    str  { lex st (count + 1) }
    [ ]+ { lex st count }
    *    { -1 }
*/

let test(str, count) =
    let buf = String.cat str (String.make yymaxfill '\x00') in
    let st = {buf = buf; cur = 0; lim = String.length buf} in
    let result = try lex st 0 with Fill -> -1 in
    if not (result = count) then raise (Failure "error")

let main () =
    test("", 0);
    test("'unterminated\\'", -1);
    test("'qu\x00tes' 'are' 'fine: \\'' ", 3);
    test("'unexpected \x00 null", -1)

let _ = main ()
