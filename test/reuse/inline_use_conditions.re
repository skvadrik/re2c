// re2c $INPUT -o $OUTPUT -c

// Test that rules are merged with correct priority. For normal rules
// the earliest rule has the highest priority (either inherited or
// local). For special rules *, $ and <!> local condition specific
// rules have the highest priority, followed by inherited condition
// specific rules, followed by local generic (star condition) rules,
// followed by inherited generic rules.

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:eof = 0;
*/

/*!rules:re2c:x
    <c1, c2> [a]        { return xa; }
    <c1>     [bc] => c2 { return xbc; }
    <c1>     *          { return xdef1; }
    <*>      *          { return xdef; }
    <c2>     $          { return xeof2; }
    <*>      $          { return xeof; }
    <!c2>               { f2(x); }
    <!*>                { f(x); }
*/

/*!rules:re2c:y
    <c1, c3> [a]        { return ya; }
    <c1>     [bd] => c3 { return ybd; }
    <c1>     *          { return ydef1; }
    <*>      *          { return ydef; }
    <c3>     $          { return yeof3; }
    <*>      $          { return yeof; }
    <!c3>               { f3(y); }
    <!*>                { f(y); }
*/

// Expect:
//     c1: xdef1, eof,   f1()
//     c2: def,   eof2,  f2(x)
//     c3: def,   yeof3, f3(y)
/*!re2c
    !use:x;
    !use:y;
    <*>   * { return def; }
    <*>   $ { return eof; }
    <c2>  $ { return eof2; }
    <!*>    { f(); }
    <!c1>   { f1(); }
*/

// Expect:
//     c1: ydef1, yeof,  f(y)
//     c2: ydef,  xeof2, f2(x)
//     c3: ydef,  yeof3, f3(y)
/*!re2c
    !use:y;
    !use:x;
*/
