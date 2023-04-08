// re2c $INPUT -o $OUTPUT -i --leftmost-captures --fixed-tags toplevel
// POSIX and leftmost policies produce the same results.
/*!re2c
    (("a")* | ("a"*))* {}
*/
