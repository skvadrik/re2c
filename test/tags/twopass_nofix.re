// re2c $INPUT -o $OUTPUT -i --tags --fixed-tags none
// need two passes in liveness analyses for chains of copy commands:
// same version may occur as both LHS and RHS, e.g. 'x = y; y = z;'

/*!re2c

(@p | [^b] "ba") ("ab" | @q) @y [^a]* "b" {}
(@r [^a] @s ("ab" | "ba")*)* {}

*/
