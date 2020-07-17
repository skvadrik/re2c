// re2c $INPUT -o $OUTPUT -i --tags
// EMPTY rule is shadowed and dead-code-eliminated. Empty string is a no-match.
// Tags are hoisted.
/*!re2c
@x [^] [a]* { /* R1 - here 'x' must be set */ }
""          { /* EMPTY - here 'x' must not be set */ }
*/

// EMPTY rule is not shadowed and does match on empty input string. Tags are
// not hoisted because of the untagged fallback transition to EMPTY.
/*!re2c
re2c:eof = 0;
@x [^] [a]* { /* R1 - here 'x' must be set */ }
""          { /* EMPTY - here 'x' must not be set */ }
$           { /* EOF - here 'x' must not be set */ }
*/
