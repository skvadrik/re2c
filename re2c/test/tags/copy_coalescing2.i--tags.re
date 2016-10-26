// This test shows the need for merging non-interfering classes
// of tag versions after copy coalescing during allocation of
// tag variables.

/*!tags:re2c format = "@@\n"; */
/*!re2c
    ("a" @p "c")* { p }
    ("a" @q "d")* { q }
    * {}
*/
