(* re2ocaml $INPUT -o $OUTPUT *)

open Bytes

%{max %}
let bufsize = 4096

exception Fill

type state = {
    file: in_channel;
    yyinput: bytes;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable yylimit: int;
    mutable token: int;
    mutable eof: bool;
}

type status = Ok | Eof | LongLexeme

let fill (st: state) (need: int) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.token < need then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    blit st.yyinput st.token st.yyinput 0 (st.yylimit - st.token);
    st.yycursor <- st.yycursor - st.token;
    st.yymarker <- st.yymarker - st.token;
    st.yylimit <- st.yylimit - st.token;
    st.token <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.yyinput st.yylimit (bufsize - st.yylimit - 1) in (* -1 for sentinel *)
    st.yylimit <- st.yylimit + n;

    (* If read zero characters, this is end of input => add zero padding
       so that the lexer can access characters at the end of buffer. *)
    if n = 0 then
        st.eof <- true; (* end of file *)
        for i = 0 to (yymaxfill - 1) do
            set st.yyinput (st.yylimit + i) '\x00';
            st.yylimit <- st.yylimit + yymaxfill
        done;

    Ok)

%{
    re2c:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:YYFILL = "if not (fill yyrecord @@ = Ok) then raise Fill;";

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        (* check that it is the sentinel, not some unexpected null *)
        if yyrecord.token = yyrecord.yylimit - yymaxfill then count else -1
    }
    str  { lex_loop yyrecord (count + 1) }
    [ ]+ { lex_loop yyrecord count }
    *    { -1 }
%}

and lex_loop st count =
    st.token <- st.yycursor;
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
            let yylimit = bufsize - yymaxfill in
            let st = {
                file = ic;
                yyinput = create bufsize;
                yycursor = yylimit;
                yymarker = yylimit;
                yylimit = yylimit;
                token = yylimit;
                eof = false;
            } in if not (lex_loop st 0 = 3 * bufsize) then
                raise (Failure "error"));

    (* Cleanup. *)
    Sys.remove fname

let _ = main ()
