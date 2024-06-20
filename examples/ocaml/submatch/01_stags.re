(* re2ocaml $INPUT -o $OUTPUT *)

open String

type state = {
    str: string;
    mutable yycursor: int;
    mutable yymarker: int;
    mutable t1: int;
    mutable t2: int;
    mutable t3: int;
    mutable t4: int;
    mutable t5: int;
    /*!stags:re2c format = '\n\tmutable @@{tag}: int;'; */
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

/*!local:re2c
    re2c:define:YYFN = ["parse;semver option", "st;state"];
    re2c:variable:yyrecord = "st";
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\x00] {
        Some {
            major = s2n st.str st.t1 st.t2;
            minor = s2n st.str st.t3 st.t4;
            patch = if st.t5 = -1 then 0 else s2n st.str st.t5 (st.yycursor - 1)
        }
    }
    * { None }
*/

let test (str: string) (result: semver option) =
    let st = {
        str = str;
        yycursor = 0;
        yymarker = 0;
        t1 = -1;
        t2 = -1;
        t3 = -1;
        t4 = -1;
        t5 = -1;
        /*!stags:re2c format = '\n\t\t@@{tag} = -1;'; */
    }
    in if not (parse st = result) then raise (Failure "error")

let main () =
    test "23.34\x00" (Some {major = 23; minor = 34; patch = 0});
    test "1.2.99999\x00" (Some {major = 1; minor = 2; patch = 99999});
    test "1.a\x00" None

let _ = main ()
