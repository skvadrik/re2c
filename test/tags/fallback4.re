// re2c $INPUT -o $OUTPUT -i --tags
// This example shows that fallback tags should participate
// in tag optimization: there is a chance that they will be
// merged with other tags.

/*!stags:re2c format = "@@\n"; */
/*!re2c

    ("a" @p "bc")+ { p } // needs fallback tag for @p
    "" / "ab"?     {}    // trailing context interferes with @p, but not with the fallback tag
    * {}

*/
