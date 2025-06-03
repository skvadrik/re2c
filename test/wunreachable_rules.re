// re2c $INPUT -o $OUTPUT -ci
/*!re2c
    [^a]* ("aa"|"a") { 0 }
    [^]              { 1 }
*/

/*!re2c
    [^a]* "a"{1,3} { 0 }
    [^]            { 1 }
*/

/*!re2c
    [^a]* "a"? { 0 }
    [^]        { 1 }
*/

/*!re2c
    [^a]* "a"+ { 0 }
    [^]        { 1 }
*/

// test that <*> rules are only reported when shadowed in all conditions
// specifically check that block reuse doesn't mess things up
/*!rules:re2c:x
    <x> [a] {}
    <*> [a] {}
    <*> * {}
*//*!use:re2c:x
    <y> [b] {}
*//*!use:re2c:x
    <z> [a] {}
*/
