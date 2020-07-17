// re2c $INPUT -o $OUTPUT -i --tags
// Tag is nondeterministic: fixed length helps only in top-level

/*!re2c
    "a"+ @p "a" | "b" { @p }
    * {}
*/
