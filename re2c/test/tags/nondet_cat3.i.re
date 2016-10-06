// Same rules (fixed length trailing context), different configurations:
//     1. default input API, no tags: no warning (fixed tag => no nondeterminism)
//     2. default input API, tags:    no warning (fixed tag => no nondeterminism)
//     3. generic input API, no tags: warning (variable tag => nondeterminism)
//     4. generic input API, tags:    error (variable tag => nondeterminism)

/*!re2c
    re2c:flags:input = default;
    re2c:flags:tags = 0;
    "a"+ / "a" {}
    * {}
*/

/*!re2c
    re2c:flags:input = default;
    re2c:flags:tags = 1;
    "a"+ / "a" {}
    * {}
*/

/*!re2c
    re2c:flags:input = custom;
    re2c:flags:tags = 0;
    "a"+ / "a" {}
    * {}
*/

/*!re2c
    re2c:flags:input = custom;
    re2c:flags:tags = 1;
    "a"+ / "a" {}
    * {}
*/
