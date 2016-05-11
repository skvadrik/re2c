// The same rules, fixed length trailing context, with different configurations:
//     1. default input API, no tags: no warning (no variable, static offset)
//     2. default input API, tags:    no warning (no variable, static offset)
//     3. generic input API, no tags: warning (need variable: lack API to to make use of fixed length)
//     4. generic input API, tags:    no warning (no variable, static offset)

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
