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
    mutable t1: int;
    mutable t2: int;
    mutable t3: int;
    mutable t4: int;
    mutable t5: int;
    /*!stags:re2c format = '\n\tmutable @@{tag}: int;'; */
}

type status = Ok | Eof | LongLexeme

type semver = {
    major: int;
    minor: int;
    patch: int;
}

let s2n (str: bytes) (i1: int) (i2: int) : int =
    let rec f s i j n =
        if i >= j then n else f s (i + 1) j (n * 10 + Char.code (get s i) - 48)
    in f str i1 i2 0

let fill(st: state) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.tok < 1 then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    blit st.str st.tok st.str 0 (st.lim - st.tok);
    st.cur <- st.cur - st.tok;
    st.mar <- st.mar - st.tok;
    st.lim <- st.lim - st.tok;
    /*!stags:re2c format = '\n\tst.@@ <- if st.@@ = -1 then -1 else st.@@ - st.tok;'; */
    st.tok <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.str st.lim (bufsize - st.lim - 1) in (* -1 for sentinel *)
    st.lim <- st.lim + n;
    if n = 0 then
        st.eof <- true; (* end of file *)
        set st.str st.lim '\x00'; (* append sentinel *)

    Ok)

/*!re2c
    re2c:define:YYFN = ["lex;(semver list) option", "st;state", "vers;semver list"];
    re2c:define:YYFILL = "fill st = Ok";
    re2c:variable:yyrecord = "st";
    re2c:tags = 1;
    re2c:eof = 0;

    num = [0-9]+;

    @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\n] {
        let ver = {
            major = s2n st.str st.t1 st.t2;
            minor = s2n st.str st.t3 st.t4;
            patch = if st.t5 = -1 then 0 else s2n st.str st.t5 (st.cur - 1)
        } in lex_loop st (ver :: vers)
    }
    $ { Some (List.rev vers) }
    * { None }
*/

and lex_loop st vers =
    st.tok <- st.cur;
    lex st vers

let main () =
    let fname = "input" in

    (* Prepare input file. *)
    Out_channel.with_open_bin fname
        (fun oc -> for i = 1 to bufsize do
            output_string oc "1.22.333\n"
        done);

    (* Construct the expected result to compare against. *)
    let expect = Some (List.init bufsize
            (fun _ -> {major = 1; minor = 22; patch = 333;})) in

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
                t1 = -1;
                t2 = -1;
                t3 = -1;
                t4 = -1;
                t5 = -1;
                /*!stags:re2c format = '\n\t\t@@{tag} = -1;'; */
            } in if (lex_loop st [] <> expect) then
                raise (Failure "error"));

    (* Cleanup. *)
    Sys.remove fname

let _ = main ()
