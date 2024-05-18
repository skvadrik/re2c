(* re2ocaml $INPUT -o $OUTPUT *)

let none = max_int;

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
    /*!stags:re2c format = '\n\tmutable @@{tag}: int;'; */
    mutable t1: int;
    mutable t2: int;
    /*!mtags:re2c format = '\n\tmutable @@{tag}: int list;'; */
    mutable t3: int list;
    mutable t4: int list;
}

let s2n (str: string) (i1: int) (i2: int) : int =
    let rec f s i j n =
        if i >= j then n else f s (i + 1) j (n * 10 + Char.code s.[i] - 48)
    in f str i1 i2 0

/*!local:re2c
    re2c:define:YYFN      = ["parse;(int list) option", "st;state"];
    re2c:define:YYCTYPE   = char;
    re2c:define:YYPEEK    = "st.str.[st.cur]";
    re2c:define:YYSKIP    = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP  = "st.mar <- st.cur;";
    re2c:define:YYRESTORE = "st.cur <- st.mar;";
    re2c:define:YYSTAGP   = "@@{tag} <- st.cur;";
    re2c:define:YYSTAGN   = "@@{tag} <- none;";
    re2c:define:YYMTAGP   = "@@ <- st.cur :: @@;";
    re2c:define:YYMTAGN   = ""; // alternatively could add `none` to the list
    re2c:tags = 1;
    re2c:tags:expression = "st.@@";
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @t1 num @t2 ("." #t3 num #t4)* [\x00] {
        let x = s2n st.str st.t1 st.t2 in
        let xs = List.rev (List.map2 (fun x y -> s2n st.str x y) st.t3 st.t4) in
        Some (x :: xs)
    }
    * { None }
*/

let test (str: string) (result: (int list) option) =
    let st = {
        str = str;
        cur = 0;
        mar = 0;
        /*!stags:re2c format = '\n\t\t@@{tag} = none;'; */
        t1 = none;
        t2 = none;
        /*!mtags:re2c format = '\n\t\t@@{tag} = [];'; */
        t3 = [];
        t4 = [];
    }
    in if not (parse st = result) then raise (Failure "error")

let main () =
    test "1\x00" (Some [1]);
    test "1.2.3.4.5.6.7\x00" (Some [1; 2; 3; 4; 5; 6; 7;]);
    test "1.2.\x00" None

let _ = main ()
