(* re2ocaml $INPUT -o $OUTPUT *)
(* This example shows how to combine reusable re2c blocks: two blocks
   ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
   in both blocks; the 'fish' block takes priority because it is used
   earlier. Default rule * occurs in all three blocks; the local (not
   inherited) definition takes priority. *)

open String

type answer = Color | Fish | Dunno

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
}

%{rules:colors
    *                            { raise (Failure "ah"); }
    "red" | "salmon" | "magenta" { Color }
%}

%{rules:fish
    *                            { raise (Failure "oh"); }
    "haddock" | "salmon" | "eel" { Fish }
%}

%{
    re2c:YYFN = ["lex;answer", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    !use:fish;
    !use:colors;
    * { Dunno } // overrides inherited '*' rules
%}

let test(str, ans) =
    let st = {yyinput = str; yycursor = 0; yymarker = 0}
    in if not (lex st = ans) then raise (Failure "error")

let main () =
    test("salmon", Fish);
    test("what?", Dunno)

let _ = main ()
