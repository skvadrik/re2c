(* re2ocaml $INPUT -o $OUTPUT -i *)

open String

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
}

%{
    re2c:YYFN = ["lex;bool", "yyrecord;state"];
    re2c:yyfill:enable = 0;

    "\a\b\f\n\r\t\v\\'\"" { true }
    * {
        let _ = ['\b', '\n', '\r', '\t', '\\', '\'', '\"'] in
        false
    }
%}

let main () =
    let st = {yyinput = "\x07\x08\x0c\x0a\x0d\x09\x0b\\'\""; yycursor = 0; yymarker = 0}
    in if not (lex st) then raise (Failure "error")

let _ = main ()
