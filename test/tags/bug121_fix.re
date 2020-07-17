// re2c $INPUT -o $OUTPUT -i --input custom
// generic API, overlapping trailing contexts of fixed length => no tags
/*!re2c
    "aba" / "ba" { 0 }
    "a"   / "ba" { 1 }
    *            { * }
*/
