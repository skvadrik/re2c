// overlapping trailing contexts of fixed length:
// we don't need any tags at all

/*!re2c
    "abb" / "c" { 0 }
    "a"   / "b" { 1 }
    *           { d }
*/
