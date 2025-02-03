(* re2ocaml $INPUT -o $OUTPUT -fi *)

open Bytes

(* Use a small buffer to cover the case when a lexeme doesn't fit.
   In real world use a larger buffer. *)
let bufsize = 10

let debug = false
let log format = (if debug then Printf.eprintf else Printf.ifprintf stderr) format

type state = {
    file: in_channel;
    yyinput: bytes;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable yylimit: int;
    mutable token: int;
    mutable yystate: int;
    mutable recv: int;
}

type status = End | Ready | Waiting | BadPacket | BigPacket

let fill(st: state) : status =
    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.token < 1 then BigPacket else (

    (* Shift buffer contents (discard everything up to the current token). *)
    blit st.yyinput st.token st.yyinput 0 (st.yylimit - st.token);
    st.yycursor <- st.yycursor - st.token;
    st.yymarker <- st.yymarker - st.token;
    st.yylimit <- st.yylimit - st.token;
    st.token <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = In_channel.input st.file st.yyinput st.yylimit (bufsize - st.yylimit - 1) in
    st.yylimit <- st.yylimit + n;
    set st.yyinput st.yylimit '\x00'; (* append sentinel *)

    Ready)

%{
    re2c:YYFN = ["lex;status", "yyrecord;state"];
    re2c:YYFILL = "Waiting";
    re2c:eof = 0;

    packet = [a-z]+[;];

    *      { BadPacket }
    $      { End }
    packet { yyrecord.recv <- yyrecord.recv + 1; lex_loop yyrecord }
%}

and lex_loop st =
    st.token <- st.yycursor;
    lex st

let test (packets: string list) (sts: status) =
    let fname = "pipe" in

    let oc = Out_channel.open_bin fname in
    let ic = In_channel.open_bin fname in

    let yylimit = bufsize - 1 in
    let st = {
        file = ic;
        (* Sentinel (at `yylimit` offset) is set to null, which triggers YYFILL. *)
        yyinput = create bufsize;
        yycursor = yylimit;
        yymarker = yylimit;
        yylimit = yylimit;
        token = yylimit;
        yystate = -1;
        recv = 0;
    } in

    let rec loop packets = match lex_loop st with
        | End ->
            log "done: got %d packets\n" st.recv;
            End
        | Waiting ->
            log "waiting...\n";
            let packets' = match packets with
                | [] -> []
                | p :: ps ->
                    log "sent packet '%s'\n" p;
                    Out_channel.output_string oc p;
                    Out_channel.flush oc; (* without `flush` write happens too late *)
                    ps
            in (match fill st with
                | BigPacket ->
                    log "error: packet too big\n";
                    BigPacket
                | Ready -> loop packets'
                | _ -> raise (Failure "unexpected status after fill"))
        | BadPacket ->
            log "error: ill-formed packet\n";
            BadPacket
        | _ -> raise (Failure "unexpected status")

    in if not (loop packets = sts) then
        raise (Failure "error");

    In_channel.close ic;
    Out_channel.close oc;
    Sys.remove fname

let main () =
    test [] End;
    test ["zero;"; "one;"; "two;"; "three;"; "four;"] End;
    test ["zer0;"] BadPacket;
    test ["goooooooooogle;"] BigPacket

let _ = main ()
