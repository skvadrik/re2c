// re2c $INPUT -o $OUTPUT -i
// Normally re2c generates one 'yyaccept' value for each rule
// that is shadowed by a longer rule.
// However, if two different accepting states accept the same
// rule, but their epsilon-transitions to this rule have
// different sets of tags, re2c should split 'yyaccept' value.

/*!re2c
  "a" / "bc"? {}
  "abcde"     {}
  *           {}
*/
