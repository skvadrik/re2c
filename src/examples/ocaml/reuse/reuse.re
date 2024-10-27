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

%{rules
    re2c:yyfill:enable = 0;

    "∀x ∃y" { Some yyrecord.yycursor }
    *       { None }
%}

%{use
    re2c:YYFN = ["lex8;int option", "yyrecord;char state"];
    re2c:encoding:utf8 = 1;
%}

%{use
    re2c:YYFN = ["lex32;int option", "yyrecord;int state"];
    re2c:encoding:utf32 = 1;
%}

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
