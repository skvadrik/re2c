(* Generated by re2ocaml *)
#1 "ocaml/reuse/reuse.re"
(* re2ocaml $INPUT -o $OUTPUT --input-encoding utf8 *)
(* This example supports multiple input encodings: UTF-8 and UTF-32.
   Both lexers are generated from the same rules block, and the use
   blocks add only encoding-specific configurations. *)

open Array

type 'a state = {
    yyinput: 'a array;
    mutable yycursor: int;
    mutable yymarker: int;
}

#19 "ocaml/reuse/reuse.re"



#21 "ocaml/reuse/reuse.ml"
let rec yy0 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    yyrecord.yycursor <- yyrecord.yycursor + 1;
    match yych with
        | '\xE2' -> (yy3 [@tailcall]) yyrecord
        | _ -> (yy1 [@tailcall]) yyrecord

and yy1 (yyrecord : char state) : int option =
    (yy2 [@tailcall]) yyrecord

and yy2 (yyrecord : char state) : int option =
#18 "ocaml/reuse/reuse.re"
    None
#35 "ocaml/reuse/reuse.ml"

and yy3 (yyrecord : char state) : int option =
    yyrecord.yymarker <- yyrecord.yycursor;
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | '\x88' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy4 [@tailcall]) yyrecord
        | _ -> (yy2 [@tailcall]) yyrecord

and yy4 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | '\x80' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy6 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy5 (yyrecord : char state) : int option =
    yyrecord.yycursor <- yyrecord.yymarker;
    (yy2 [@tailcall]) yyrecord

and yy6 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | 'x' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy7 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy7 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | ' ' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy8 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy8 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | '\xE2' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy9 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy9 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | '\x88' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy10 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy10 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | '\x83' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy11 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy11 (yyrecord : char state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    match yych with
        | 'y' ->
            yyrecord.yycursor <- yyrecord.yycursor + 1;
            (yy12 [@tailcall]) yyrecord
        | _ -> (yy5 [@tailcall]) yyrecord

and yy12 (yyrecord : char state) : int option =
#17 "ocaml/reuse/reuse.re"
    Some yyrecord.yycursor
#109 "ocaml/reuse/reuse.ml"

and lex8 (yyrecord : char state) : int option =
    (yy0 [@tailcall]) yyrecord

#24 "ocaml/reuse/reuse.re"



#118 "ocaml/reuse/reuse.ml"
let rec yy13 (yyrecord : int state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    yyrecord.yycursor <- yyrecord.yycursor + 1;
    if (yych == 0x00002200) then (yy16 [@tailcall]) yyrecord
    else (yy14 [@tailcall]) yyrecord

and yy14 (yyrecord : int state) : int option =
    (yy15 [@tailcall]) yyrecord

and yy15 (yyrecord : int state) : int option =
#18 "ocaml/reuse/reuse.re"
    None
#131 "ocaml/reuse/reuse.ml"

and yy16 (yyrecord : int state) : int option =
    yyrecord.yymarker <- yyrecord.yycursor;
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    if (yych == 0x00000078) then (
        yyrecord.yycursor <- yyrecord.yycursor + 1;
        (yy17 [@tailcall]) yyrecord
    ) else (
        (yy15 [@tailcall]) yyrecord
    )

and yy17 (yyrecord : int state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    if (yych == 0x00000020) then (
        yyrecord.yycursor <- yyrecord.yycursor + 1;
        (yy19 [@tailcall]) yyrecord
    ) else (
        (yy18 [@tailcall]) yyrecord
    )

and yy18 (yyrecord : int state) : int option =
    yyrecord.yycursor <- yyrecord.yymarker;
    (yy15 [@tailcall]) yyrecord

and yy19 (yyrecord : int state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    if (yych == 0x00002203) then (
        yyrecord.yycursor <- yyrecord.yycursor + 1;
        (yy20 [@tailcall]) yyrecord
    ) else (
        (yy18 [@tailcall]) yyrecord
    )

and yy20 (yyrecord : int state) : int option =
    let yych = get yyrecord.yyinput yyrecord.yycursor in
    if (yych == 0x00000079) then (
        yyrecord.yycursor <- yyrecord.yycursor + 1;
        (yy21 [@tailcall]) yyrecord
    ) else (
        (yy18 [@tailcall]) yyrecord
    )

and yy21 (yyrecord : int state) : int option =
#17 "ocaml/reuse/reuse.re"
    Some yyrecord.yycursor
#177 "ocaml/reuse/reuse.ml"

and lex32 (yyrecord : int state) : int option =
    (yy13 [@tailcall]) yyrecord

#29 "ocaml/reuse/reuse.re"


let main() =
    let st8 = {
        yyinput = [|'\xe2'; '\x08'; '\x80'; '\x78'; '\x20'; '\xe2'; '\x88'; '\x83'; '\x79'|];
        yycursor = 0;
        yymarker = 0;
    } in if not (lex8 st8 = Some (Array.length st8.yyinput)) then raise (Failure "error");

    let st32 = {
        yycursor = 0;
        yymarker = 0;
        yyinput = [|0x2200; 0x78; 0x20; 0x2203; 0x79|];
    } in if not (lex32 st32 = Some (Array.length st32.yyinput)) then raise (Failure "error");
