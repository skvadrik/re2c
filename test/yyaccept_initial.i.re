// re2c $INPUT -o $OUTPUT -i
// In this example initial state coincides with fallback state
// which must update 'yyaccept'. There is a loop through initial
// state that changes 'yyaccept' value, so if the initial state
// forgets to update 'yyaccept', the wrong rule will match.

/*!re2c

    "abab"* { 1 }
    "ab"*   { 2 }

*/
