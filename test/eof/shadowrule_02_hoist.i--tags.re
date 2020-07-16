// re2c $INPUT -o $OUTPUT -i --tags
// R1 matches any single character => all transitions from the initial
// state have the same tags which can be hoisted
/*!re2c
@x [^] [b]* { /* R1, x must be set */  }
*           { /* DEFAULT, x must not be set */ }
*/

// R1 matches any single character, but it is also possible to match zero
// characters with EOF rule => tags cannot be hoisted in the initial state
// because of the possible untagged transition to EOF rule
/*!re2c
re2c:eof = 0;
@x [^] [b]* { /* R1, x must be set */  }
$           { /* EOF, x must not be set */ }
*           { /* DEFAULT, x must not be set */ }
*/
