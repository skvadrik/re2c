// re2c $INPUT -o $OUTPUT --captures
/*!re2c
    ("c"*) / "a"* {} // error, lookahead tag mixed with captures
    ("c"*) @t "b"* {} // error, standalone tag mixed with captures
*/
