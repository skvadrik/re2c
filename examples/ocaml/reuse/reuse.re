(* re2ocaml $INPUT -o $OUTPUT --input-encoding utf8 *)

(* This example supports multiple input encodings: UTF-8 and UTF-32.
   Both lexers are generated from the same rules block, and the use
   blocks add only encoding-specific configurations. *)

type state = {
    mutable cur: int;
    mutable mar: int;
}

/*!rules:re2c
    re2c:yyfill:enable    = 0;
    re2c:define:YYPEEK    = "str.(st.cur)";
    re2c:define:YYSKIP    = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP  = "st.mar <- st.cur;";
    re2c:define:YYRESTORE = "st.cur <- st.mar;";

    "∀x ∃y" { Some st.cur }
    *       { None }
*/

/*!use:re2c
    re2c:define:YYFN = ["lex8;int option", "st;state", "str;char array"];
    re2c:encoding:utf8 = 1;
    re2c:define:YYCTYPE = char;
*/

/*!use:re2c
    re2c:define:YYFN = ["lex32;int option", "st;state", "str;int array"];
    re2c:encoding:utf32 = 1;
    re2c:define:YYCTYPE = int;
*/

let main() =
    let st = {cur = 0; mar = 0} in
    let str = [|'\xe2'; '\x08'; '\x80'; '\x78'; '\x20'; '\xe2'; '\x88'; '\x83'; '\x79'|] in
    if not (lex8 st str = Some (Array.length str)) then raise (Failure "error");

    let st = {cur = 0; mar = 0} in
    let str = [|0x2200; 0x78; 0x20; 0x2203; 0x79|] in
    if not (lex32 st str = Some (Array.length str)) then raise (Failure "error");
