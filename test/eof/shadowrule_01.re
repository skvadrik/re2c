// re2c $INPUT -o $OUTPUT -i
/*!re2c
str = ['] [^']* ['];
*/

// QUOTE rule is shadowed by the greedy STRING rule, which keeps
// consuming symbols until either it matches the final quote, or
// YYFILL fails and does not return (then it is a no-match).
/*!re2c
*     { /* DEFAULT */ }
[']   { /* QUOTE   */ }
str   { /* STRING  */ }
*/

// The same situation, but with EOF rule: now when YYFILL fails
// in the middle of the STRING rule, it returns and it is posible
// to match the shorter QUOTE rule.
/*!re2c
re2c:eof = 0;
*     { /* DEFAULT */ }
$     { /* EOF     */ }
[']   { /* QUOTE   */ }
str   { /* STRING  */ }
*/
