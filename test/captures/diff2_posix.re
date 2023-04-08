// re2c $INPUT -o $OUTPUT -i --posix-captures --fixed-tags toplevel
// POSIX and leftmost policies produce different results.
/*!re2c
    ((([^a]){0,3})*"c"*){0,3} {}
*/
