// re2c $INPUT -o $OUTPUT -i --tags
// This test revealed a bug in liveness analyses that takes place
// during tag deduplication: in loops, live tags added by non-looping
// child paths failed to propagate into looping paths.

// These two cases differ: in one case looping transition goes first (and tags are lost),
// in the other case non-looping transition goes first (and tags are not lost).

/*!re2c
    (@p "ac")* "b" { p }
    * {}
*/

/*!re2c
    (@p "bc")* "a" { p }
    * {}
*/
