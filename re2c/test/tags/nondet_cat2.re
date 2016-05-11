// The same rules, nondeterministic trailing context, with different configurations:
//     1. tags:    error
//     2. no tags: warning

/*!re2c
    re2c:flags:tags = 1;
    "a"+ / "a"+ {}
    * {}
*/

/*!re2c
    re2c:flags:tags = 0;
    "a"+ / "a"+ {}
    * {}
*/
