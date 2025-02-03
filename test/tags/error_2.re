// re2c $INPUT -o $OUTPUT --captures
/*!re2c
    ("c"*) / "a"* {} // ok, lookahead tag is a special case
    ("c"*) @t "b"* {} // error, standalone tag mixed with captures
*/
