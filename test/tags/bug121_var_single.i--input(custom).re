// re2c $INPUT -o $OUTPUT -i --input custom
// overlapping trailing contexts of variable length:
// in principle, we need multiple tags here, but in this
// particular case all tags can be implemented using sinle
// variable (due to tag deduplication)

/*!re2c
    "ab" / "c"* { 0 }
    "a"  / "b"* { 1 }
    *           { d }
*/
