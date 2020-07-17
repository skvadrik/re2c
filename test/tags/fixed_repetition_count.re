// re2c $INPUT -o $OUTPUT -is --tags
/*!stags:re2c format = "@@\n"; */
/*!re2c
    @p "aaaa"                          { a }
    @p "b"{4}                          { b }
    @p "c" "c" "c" "c"                 { c }
    @p "d"{2} "dd"                     { d }
    @p "e" ("ee" | "e"{2}) "e"         { e }
    @p ("ffff" | "f"{2} "ff" | "f"{4}) { f }
    @p "g"{3} "g"                      { g }
    *                                  { * }
*/
