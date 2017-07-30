// overlapping trailing contexts of fixed length:
// because of generic API we cannot take advantage of
// fixed length and have to use multiple tags, which
// further are deduplicated and we end up with single
// tag

/*!re2c
    "abb" / "c" { 0 }
    "a"   / "b" { 1 }
    *           { d }
*/
