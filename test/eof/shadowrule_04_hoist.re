// re2c $INPUT -o $OUTPUT -i --tags -Wno-error-deprecated-eof-rule
// EMPTY rule is shadowed and dead-code-eliminated. Empty string is a no-match.
// Tags are hoisted.
/*!re2c
@x [^] [a]* { /* R1 - here 'x' must be set */ }
""          { /* EMPTY - here 'x' must not be set */ }
*/

// EOF rule is shadowed and dead-code-eliminated.
// Tags are not hoisted because of the untagged transition to EMPTY.
/*!re2c
re2c:eof = 0;
@x [^] [a]* { /* R1 - here 'x' must be set */ }
""          { /* EMPTY - here 'x' must not be set */ }
$           { /* EOF - here 'x' must not be set */ }
*/

// EOF rule is shadowed and dead-code-eliminated.
// EMPTY rule is not shadowed and does match on empty input string.
// Tags are not hoisted because of the untagged transition to EMPTY.
/*!re2c
re2c:eof = 0;
@x [^][^] [a]* { /* R1 - here 'x' must be set */ }
""             { /* EMPTY - here 'x' must not be set */ }
$              { /* EOF - here 'x' must not be set */ }
*/
