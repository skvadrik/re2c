// overlapping trailing contexts of fixed length:
// because of generic API we cannot take advantage of
// fixed length and have to use multiple tags
// (deduplication doesn't help)

/*!re2c
    "aba" / "ba" { 0 }
    "a"   / "ba" { 1 }
    *            { d }
*/
