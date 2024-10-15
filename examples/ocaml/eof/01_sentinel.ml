(* Generated by re2ocaml *)
#1 "ocaml/eof/01_sentinel.re"
(* re2ocaml $INPUT -o $OUTPUT *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
}

(* expect a null-terminated string *)

#15 "ocaml/eof/01_sentinel.ml"
let rec yy0 (yyrecord : state) (count : int) : int =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    yyrecord.yycursor <- yyrecord.yycursor + 1;
    match yych with
        | '\x00' -> (yy1 [@tailcall]) yyrecord count
        | ' ' -> (yy3 [@tailcall]) yyrecord count
        | 'a'..'z' -> (yy5 [@tailcall]) yyrecord count
        | _ -> (yy2 [@tailcall]) yyrecord count

and yy1 (yyrecord : state) (count : int) : int =
#16 "ocaml/eof/01_sentinel.re"
    count
#28 "ocaml/eof/01_sentinel.ml"

and yy2 (yyrecord : state) (count : int) : int =
#15 "ocaml/eof/01_sentinel.re"
    -1
#33 "ocaml/eof/01_sentinel.ml"

and yy3 (yyrecord : state) (count : int) : int =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | ' ' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy3 [@tailcall]) yyrecord count
        | _ -> (yy4 [@tailcall]) yyrecord count

and yy4 (yyrecord : state) (count : int) : int =
#18 "ocaml/eof/01_sentinel.re"
    lex yyrecord count
#46 "ocaml/eof/01_sentinel.ml"

and yy5 (yyrecord : state) (count : int) : int =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | 'a'..'z' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy5 [@tailcall]) yyrecord count
        | _ -> (yy6 [@tailcall]) yyrecord count

and yy6 (yyrecord : state) (count : int) : int =
#17 "ocaml/eof/01_sentinel.re"
    lex yyrecord (count + 1)
#59 "ocaml/eof/01_sentinel.ml"

and lex (yyrecord : state) (count : int) : int =
    (yy0 [@tailcall]) yyrecord count

#19 "ocaml/eof/01_sentinel.re"


let test(yyinput, count) =
    let st = {yyinput = yyinput; yycursor = 0}
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("\x00", 0);
    test("one two three\x00", 3);
    test("f0ur\x00", -1)

let _ = main ()
