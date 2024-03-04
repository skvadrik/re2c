(* re2ocaml $INPUT -o $OUTPUT *)

/*!max:re2c*/
let bufsize = 4096

exception Fill

type state = {
    file: in_channel;
    buf: bytes;
    mutable cur: int;
    mutable mar: int;
    mutable tok: int;
    mutable lim: int;
    mutable eof: bool;
}

type status = Ok | Eof | LongLexeme

let fill (st: state) (need: int) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.tok < need then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    Bytes.blit st.buf st.tok st.buf 0 (st.lim - st.tok);
    st.cur <- st.cur - st.tok;
    st.mar <- st.mar - st.tok;
    st.lim <- st.lim - st.tok;
    st.tok <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.buf st.lim (bufsize - st.lim - 1) in (* -1 for sentinel *)
    st.lim <- st.lim + n;

    (* If read zero characters, this is end of input => add zero padding
       so that the lexer can access characters at the end of buffer. *)
    if n = 0 then
        st.eof <- true; (* end of file *)
        for i = 0 to (yymaxfill - 1) do
            Bytes.set st.buf (st.lim + i) '\x00';
            st.lim <- st.lim + yymaxfill
        done;

    Ok)

/*!re2c
    re2c:define:YYFN       = ["lex;int", "st;state", "count;int"];
    re2c:define:YYCTYPE    = char;
    re2c:define:YYPEEK     = "Bytes.get st.buf st.cur";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:define:YYLESSTHAN = "st.lim - st.cur < @@";
    re2c:define:YYFILL     = "if not (fill st @@ = Ok) then raise Fill;";

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        (* check that it is the sentinel, not some unexpected null *)
        if st.tok = st.lim - yymaxfill then count else -1
    }
    str  { lex_loop st (count + 1) }
    [ ]+ { lex_loop st count }
    *    { -1 }
*/

and lex_loop st count =
    st.tok <- st.cur;
    try lex st count with Fill -> -1

let main () =
    let fname = "input" in

    (* Prepare input file. *)
    Out_channel.with_open_bin fname
        (fun oc -> for i = 1 to bufsize do
            output_string oc "'qu\x00tes' 'are' 'fine: \\'' "
        done);

    (* Run lexer on the prepared file. *)
    In_channel.with_open_bin fname
        (fun ic ->
            let lim = bufsize - yymaxfill in
            let st = {
                file = ic;
                buf = Bytes.create bufsize;
                cur = lim;
                mar = lim;
                tok = lim;
                lim = lim;
                eof = false;
            } in if not (lex_loop st 0 = 3 * bufsize) then
                raise (Failure "error"));

    (* Cleanup. *)
    Sys.remove fname

let _ = main ()
