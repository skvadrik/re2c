// This example shows the neccesity of tracking interference
// induced by copy commands: fallback tag interferes with another
// tag in a way that makes it impossible to spot interference
// unless we examine the copy command.

// On input "cdabe" 2nd rule should match with '@q' pointing to 'd'.

/*!tags:re2c format = "@@\n"; */
/*!re2c

    (@p "ab" | "c"    "d")*     { p } // fallback tag for @p
    (   "ab" | "c" @q "d")* "e" { q } // @q interferes with fallback tag
    * {}

*/
