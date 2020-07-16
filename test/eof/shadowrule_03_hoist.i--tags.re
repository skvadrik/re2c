// re2c $INPUT -o $OUTPUT -i --tags
// R1 matches any string of two characters (or more). Because of greediness
// ANY rule cannot match on a single-character string (it is shadowed and
// gets eliminated) => tags are hoisted
/*!re2c
[^] @x [^] [a]* { /* R1, x must be set */ }
[^]             { /* ANY, x must not be set */ }
*               { /* DEFAULT, x must not be set */ }
*/

// R1 matches any string of two characters (or more). ANY rule is not shadowed
// because with EOF rule YYFILL returns and rolls back to ANY. Untagged
// fallback transition to ANY prevents tag hoisting.
/*!re2c
re2c:eof = 0;
[^] @x [^] [a]* { /* R1, x must be set */ }
[^]             { /* ANY, x must not be set */ }
$               { /* EOF, x must not be set */ }
*               { /* DEFAULT, x must not be set */ }
*/
