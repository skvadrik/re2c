// re2c $INPUT -o $OUTPUT -i --posix-captures --fixed-tags toplevel
// test for epsilon closure construction:
// exponential blowup if paths are not merged
// as soon as they arrive at the same NFA state
/*!re2c
    ((""){0,100}){0,100} {}
*/
