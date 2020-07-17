// re2c $INPUT -o $OUTPUT -i --input custom
// overlapping trailing contexts of variable length:
// we need multiple tags and we cannot deduplicate them

/*!re2c
    "ab" / "c"{2,} { 0 }
    "a"  / "b"*    { 1 }
    *              { d }
*/
