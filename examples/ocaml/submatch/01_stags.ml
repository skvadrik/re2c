(* Generated by re2ocaml *)
#1 "ocaml/submatch/01_stags.re"
(* re2ocaml $INPUT -o $OUTPUT *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    (* Final tag variables available in semantic action. *)
    
#14 "ocaml/submatch/01_stags.ml"

	mutable t1: int;
	mutable t2: int;
	mutable t3: int;
	mutable t4: int;
	mutable t5: int;
#10 "ocaml/submatch/01_stags.re"

    (* Intermediate tag variables used by the lexer (must be autogenerated). *)
    
#25 "ocaml/submatch/01_stags.ml"

	mutable yyt1: int;
	mutable yyt2: int;
	mutable yyt3: int;
	mutable yyt4: int;
#12 "ocaml/submatch/01_stags.re"

}

type semver = {
    major: int;
    minor: int;
    patch: int;
}

let s2n (str: string) (i1: int) (i2: int) : int =
    let rec f s i j n =
        if i >= j then n else f s (i + 1) j (n * 10 + Char.code s.[i] - 48)
    in f str i1 i2 0


#47 "ocaml/submatch/01_stags.ml"
let rec yy0 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '0'..'9' ->
			st.yyt1 <- st.yycursor;
			st.yycursor <- st.yycursor + 1;
			(yy3 [@tailcall]) st
		| _ ->
			st.yycursor <- st.yycursor + 1;
			(yy1 [@tailcall]) st

and yy1 (st : state) : semver option =
	(yy2 [@tailcall]) st

and yy2 (st : state) : semver option =
#41 "ocaml/submatch/01_stags.re"
	None
#65 "ocaml/submatch/01_stags.ml"

and yy3 (st : state) : semver option =
	st.yymarker <- st.yycursor;
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '.' ->
			st.yycursor <- st.yycursor + 1;
			(yy4 [@tailcall]) st
		| '0'..'9' ->
			st.yycursor <- st.yycursor + 1;
			(yy6 [@tailcall]) st
		| _ -> (yy2 [@tailcall]) st

and yy4 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '0'..'9' ->
			st.yyt2 <- st.yycursor;
			st.yycursor <- st.yycursor + 1;
			(yy7 [@tailcall]) st
		| _ -> (yy5 [@tailcall]) st

and yy5 (st : state) : semver option =
	st.yycursor <- st.yymarker;
	(yy2 [@tailcall]) st

and yy6 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '.' ->
			st.yycursor <- st.yycursor + 1;
			(yy4 [@tailcall]) st
		| '0'..'9' ->
			st.yycursor <- st.yycursor + 1;
			(yy6 [@tailcall]) st
		| _ -> (yy5 [@tailcall]) st

and yy7 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '\x00' ->
			st.yyt3 <- st.yycursor;
			st.yyt4 <- -1;
			st.yycursor <- st.yycursor + 1;
			(yy8 [@tailcall]) st
		| '.' ->
			st.yyt3 <- st.yycursor;
			st.yycursor <- st.yycursor + 1;
			(yy9 [@tailcall]) st
		| '0'..'9' ->
			st.yycursor <- st.yycursor + 1;
			(yy7 [@tailcall]) st
		| _ -> (yy5 [@tailcall]) st

and yy8 (st : state) : semver option =
	st.t1 <- st.yyt1;
	st.t3 <- st.yyt2;
	st.t4 <- st.yyt3;
	st.t5 <- st.yyt4;
	st.t2 <- st.yyt2;
	st.t2 <- st.t2 - 1;
#34 "ocaml/submatch/01_stags.re"
	
        Some {
            major = s2n st.yyinput st.t1 st.t2;
            minor = s2n st.yyinput st.t3 st.t4;
            patch = if st.t5 = -1 then 0 else s2n st.yyinput st.t5 (st.yycursor - 1)
        }

#135 "ocaml/submatch/01_stags.ml"

and yy9 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '0'..'9' ->
			st.yyt4 <- st.yycursor;
			st.yycursor <- st.yycursor + 1;
			(yy10 [@tailcall]) st
		| _ -> (yy5 [@tailcall]) st

and yy10 (st : state) : semver option =
	let yych = get st.yyinput st.yycursor in
	match yych with
		| '\x00' ->
			st.yycursor <- st.yycursor + 1;
			(yy8 [@tailcall]) st
		| '0'..'9' ->
			st.yycursor <- st.yycursor + 1;
			(yy10 [@tailcall]) st
		| _ -> (yy5 [@tailcall]) st

and parse (st : state) : semver option =
	(yy0 [@tailcall]) st

#42 "ocaml/submatch/01_stags.re"


let test (str: string) (result: semver option) =
    let st = {
        yyinput = str;
        yycursor = 0;
        yymarker = 0;
        
#169 "ocaml/submatch/01_stags.ml"

		t1 = -1;
		t2 = -1;
		t3 = -1;
		t4 = -1;
		t5 = -1;
#49 "ocaml/submatch/01_stags.re"

        
#179 "ocaml/submatch/01_stags.ml"

		yyt1 = -1;
		yyt2 = -1;
		yyt3 = -1;
		yyt4 = -1;
#50 "ocaml/submatch/01_stags.re"

    }
    in if not (parse st = result) then raise (Failure "error")

let main () =
    test "23.34\x00" (Some {major = 23; minor = 34; patch = 0});
    test "1.2.99999\x00" (Some {major = 1; minor = 2; patch = 99999});
    test "1.a\x00" None

let _ = main ()