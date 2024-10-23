(* re2ocaml $INPUT -o $OUTPUT *)

open Bytes

let bufsize = 4096

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

let fill(st: state) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.token < 1 then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    blit st.yyinput st.token st.yyinput 0 (st.yylimit - st.token);
    st.yycursor <- st.yycursor - st.token;
    st.yymarker <- st.yymarker - st.token;
    st.yylimit <- st.yylimit - st.token;
    st.token <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.yyinput st.yylimit (bufsize - st.yylimit - 1) in (* -1 for sentinel *)
    st.yylimit <- st.yylimit + n;
    if n = 0 then
        st.eof <- true; (* end of file *)
        set st.yyinput st.yylimit '\x00'; (* append sentinel *)

    Ok)

%{
    re2c:YYFN = ["lex;int", "yyrecord;state", "count;int"];
    re2c:YYFILL = "fill yyrecord = Ok";
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { -1 }
    $    { count }
    str  { lex_loop yyrecord (count + 1) }
    [ ]+ { lex_loop yyrecord count }
%}

and lex_loop st count =
    st.token <- st.yycursor;
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
            let yylimit = bufsize - 1 in
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
