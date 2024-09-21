(* Generated by re2ocaml *)
(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
}


let rec yy0 (yyrecord : state) : bool =
	let yych = get yyrecord.yyinput yyrecord.yycursor in
	yyrecord.yycursor <- yyrecord.yycursor + 1;
	match yych with
		| '1'..'9' -> (yy2 [@tailcall]) yyrecord
		| _ -> (yy1 [@tailcall]) yyrecord

and yy1 (yyrecord : state) : bool =
	false

and yy2 (yyrecord : state) : bool =
	let yych = get yyrecord.yyinput yyrecord.yycursor in
	match yych with
		| '0'..'9' ->
			yyrecord.yycursor <- yyrecord.yycursor + 1;
			(yy2 [@tailcall]) yyrecord
		| _ -> (yy3 [@tailcall]) yyrecord

and yy3 (yyrecord : state) : bool =
	true

and lex (yyrecord : state) : bool =
	(yy0 [@tailcall]) yyrecord



let main () =
    let st = {yyinput = "1234\x00"; yycursor = 0}
    in if not (lex st) then raise (Failure "error")

let _ = main ()