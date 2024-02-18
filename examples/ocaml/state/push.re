(* re2ocaml $INPUT -o $OUTPUT -fi *)

(* Use a small buffer to cover the case when a lexeme doesn't fit.
   In real world use a larger buffer. *)
let bufsize = 10

let debug = false
let log format = (if debug then Printf.eprintf else Printf.ifprintf stderr) format

type state = {
    file: in_channel;
    buf: bytes;
    mutable cur: int;
    mutable mar: int;
    mutable tok: int;
    mutable lim: int;
    mutable state: int;
    mutable recv: int;
}

type status = End | Ready | Waiting | BadPacket | BigPacket

let fill(st: state) : status =
    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.tok < 1 then BigPacket else (

    (* Shift buffer contents (discard everything up to the current token). *)
    Bytes.blit st.buf st.tok st.buf 0 (st.lim - st.tok);
    st.cur <- st.cur - st.tok;
    st.mar <- st.mar - st.tok;
    st.lim <- st.lim - st.tok;
    st.tok <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = In_channel.input st.file st.buf st.lim (bufsize - st.lim - 1) in (* -1 for sentinel *)
    st.lim <- st.lim + n;
    Bytes.set st.buf st.lim '\x00'; (* append sentinel *)

    Ready)

/*!re2c
    re2c:define:YYFN       = ["lex;status", "st;state"];
    re2c:define:YYCTYPE    = int;
    re2c:define:YYPEEK     = "Char.code (Bytes.get st.buf st.cur)";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:define:YYGETSTATE = "st.state";
    re2c:define:YYSETSTATE = "st.state <- @@;";
    re2c:define:YYLESSTHAN = "st.cur >= st.lim";
    re2c:define:YYFILL     = "Waiting";
    re2c:eof = 0;

    packet = [a-z]+[;];

    *      { BadPacket }
    $      { End }
    packet { st.recv <- st.recv + 1; lex_loop st }
*/

and lex_loop st =
    st.tok <- st.cur;
    lex st

let test (packets: string list) (sts: status) =
    let fname = "pipe" in

    let oc = Out_channel.open_bin fname in
    let ic = In_channel.open_bin fname in

    let lim = bufsize - 1 in
    let st = {
        file = ic;
        (* Sentinel (at `lim` offset) is set to null, which triggers YYFILL. *)
        buf = Bytes.create bufsize;
        cur = lim;
        mar = lim;
        tok = lim;
        lim = lim;
        state = -1;
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
