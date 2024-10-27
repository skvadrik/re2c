(* re2ocaml $INPUT -o $OUTPUT -ci *)

open Int64
open Option
open String

%{conditions %}

type state = {
    yyinput: string;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable yycond: yycondtype;
} 

let add (num: int option) (dgt: int) (base: int) : int option =
    match num with
        | None -> None
        | Some n ->
            let n' = add (mul (of_int n) (of_int base)) (of_int dgt)
            in if n' > (of_int32 Int32.max_int) then None else Some (to_int n')

%{
    re2c:YYFN = ["parse;int option", "st;state", "num;int option"];
    re2c:yyrecord = "st";
    re2c:yyfill:enable = 0;

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex
    <init> * { None }

    <bin> [01]  { yyfnbin st (add num (Char.code st.yyinput.[st.yycursor - 1] - 48) 2) }
    <oct> [0-7] { yyfnoct st (add num (Char.code st.yyinput.[st.yycursor - 1] - 48) 8) }
    <dec> [0-9] { yyfndec st (add num (Char.code st.yyinput.[st.yycursor - 1] - 48) 10) }
    <hex> [0-9] { yyfnhex st (add num (Char.code st.yyinput.[st.yycursor - 1] - 48) 16) }
    <hex> [a-f] { yyfnhex st (add num (Char.code st.yyinput.[st.yycursor - 1] - 87) 16) }
    <hex> [A-F] { yyfnhex st (add num (Char.code st.yyinput.[st.yycursor - 1] - 55) 16) }

    <bin, oct, dec, hex> * { num }
%}

let test (yyinput: string) (result: int option) =
    let st = {yyinput = yyinput; yycursor = 0; yymarker = 0; yycond = YYC_init} in
    if not (parse st (Some 0) = result) then raise (Failure "error")

let main () =
    test "\x00" None;
    test "1234567890\x00" (Some 1234567890);
    test "0b1101\x00" (Some 13);
    test "0x7Fe\x00" (Some 2046);
    test "0644\x00" (Some 420);
    test "9999999999\x00" None

let _ = main ()
