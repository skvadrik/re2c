// re2c $INPUT -o $OUTPUT -i --posix-captures --fixed-tags toplevel
// POSIX and leftmost policies produce the same results.
/*!re2c
    (([a])) | [b] | [b] | ([b]) | [b] {}
    "" {}
*/
