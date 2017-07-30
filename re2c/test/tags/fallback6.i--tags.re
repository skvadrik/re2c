/*!stags:re2c format = "@@\n"; */
/*!re2c

    (@p "ab" | "c"    "d")*     { p }
    (   "ab" | "c" @q "d")* "e" { q }
    * {}

*/
