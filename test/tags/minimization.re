// re2c $INPUT -o $OUTPUT -i
// Rules are the same except for the tag in the 2nd case.
// In the 1st case common tail "a" is deduplicated after DFA minimization.
// In the 2nd case tag prevents minimization.

/*!re2c
    "ba" | "ca" {}
    * {}
*/

/*!re2c
    re2c:flags:tags = 1;
    "b" @p "a" | "ca" { p }
    * {}
*/
