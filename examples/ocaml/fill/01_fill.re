(* re2ocaml $INPUT -o $OUTPUT *)

open Bytes

let bufsize = 4096

type state = {
    file: in_channel;
    str: bytes;
    mutable cur: int;
    mutable mar: int;
    mutable tok: int;
    mutable lim: int;
    mutable eof: bool;
}

type status = Ok | Eof | LongLexeme

let fill(st: state) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.tok < 1 then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    blit st.str st.tok st.str 0 (st.lim - st.tok);
    st.cur <- st.cur - st.tok;
    st.mar <- st.mar - st.tok;
    st.lim <- st.lim - st.tok;
    st.tok <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.str st.lim (bufsize - st.lim - 1) in (* -1 for sentinel *)
    st.lim <- st.lim + n;
    if n = 0 then
        st.eof <- true; (* end of file *)
        set st.str st.lim '\x00'; (* append sentinel *)

    Ok)

/*!re2c
    re2c:define:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:define:YYCTYPE = "char";
    re2c:define:YYFILL = "fill yyrecord = Ok";
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { -1 }
    $    { count }
    str  { lex_loop yyrecord (count + 1) }
    [ ]+ { lex_loop yyrecord count }
*/

and lex_loop st count =
    st.tok <- st.cur;
    lex st count

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
            let lim = bufsize - 1 in
            let st = {
                file = ic;
                str = create bufsize;
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
