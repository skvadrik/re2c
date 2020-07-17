// re2c $INPUT -o $OUTPUT -i
// default API: no warning (fixed tag => no nondeterminism)
/*!re2c
    re2c:flags:input = default;
    re2c:flags:tags = 0;
    "a"+ / "a" {}
    * {}
*/

// generic API: no warning (fixed tag => no nondeterminism)
/*!re2c
    re2c:flags:input = custom;
    re2c:flags:tags = 0;
    "a"+ / "a" {}
    * {}
*/

// default API: warning (variable tag => nondeterminism), old-style context marker
/*!re2c
    re2c:flags:input = default;
    re2c:flags:tags = 0;
    "a"+ / "a"+ {}
    * {}
*/

// default API: warning (variable tag => nondeterminism), tag variable
/*!re2c
    re2c:flags:input = default;
    re2c:flags:tags = 1;
    "a"+ / "a"+ {}
    * {}
*/

// generic API: warning (variable tag => nondeterminism), old-style context marker
/*!re2c
    re2c:flags:input = custom;
    re2c:flags:tags = 0;
    "a"+ / "a"+ {}
    * {}
*/

// generic API: warning (variable tag => nondeterminism), tag variable
/*!re2c
    re2c:flags:input = custom;
    re2c:flags:tags = 1;
    "a"+ / "a"+ {}
    * {}
*/
