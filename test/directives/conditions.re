// re2c $INPUT -o $OUTPUT -ci

/*!re2c re2c:yyfill:enable = 0; */

// types:re2c (expect yycC1, yycC2, yycC3, YC1, YC2)
/*!types:re2c */

// unnamed global block (conditions C1, C2)
/*!re2c
    re2c:startlabel = "Lstart";
    <C1> [a]  => C2 { goto Lstart; }
    <C2> [b] :=> C1
    <*>  *          { return; }
*/

// local block 'x' (conditions C1, C3)
/*!local:re2c:x
    re2c:condprefix = 'Lx_';
    <C1> [a]  => C3 { goto Lx_C3; }
    <C3> [b] :=> C1
    <*>  *          { return x; }
*/

// global block 'y' (conditions C1, C2)
/*!re2c:y
    re2c:startlabel = "Ly_start";
    re2c:condenumprefix = 'Y';
    <C1> [a]  => C2 { goto Ly_start; }
    <C2> [b] :=> C1
    <*>  *          { return y; }
*/

// global block 'z' (no conditions)
/*!re2c:z
    [z] { return 0; }
    *   { return 1; }
*/
