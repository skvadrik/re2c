(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
}

%{
    re2c:variable:yyrecord = "s''t'";
    re2c:define:YYFN = ["l'e'00x''';bool", "s''t';state"];
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { let _x' = '}' in let _x'' = '}' in let x'00'' = true in x'00'' }
    *      { let _y'' = '\'' in let _y''' = '}' in let y' = false in y' }
%}

let main () =
    let st = {yyinput = "1234\x00"; yycursor = 0}
    in if not (l'e'00x''' st) then raise (Failure "error")

let _ = main ()
