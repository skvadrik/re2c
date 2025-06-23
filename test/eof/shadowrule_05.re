// re2c $INPUT -o $OUTPUT -ci

/*!re2c
    re2c:eof = 0;
*/

// no error/warning, both rules are reachable
/*!re2c
    $  { eof }
    "" { empty }
*/

// error: unreachable rule eof
/*!re2c
    "" { empty }
    $  { eof }
*/

// error: unreachable rule eof2
/*!re2c
    $  { eof1 }
    $  { eof2 }
*/

// warning: unreachable empty, error - unreachable eof
/*!re2c
    [a]* { a }
    ""   { empty }
    $    { eof }
*/

/*!rules:re2c:x
    <*> $   { *-eof }
    <*> [a] { *-a }

    <c4> $ { c4-eof }
*/

// use block
//   c1: error: *-eof-2 shadowed by c1-empty, error: *-eof shadowed by c1-empty
//   c2: error: *-eof-2 shadowed by *-eof), *-a shadowed by c2-a but not reported because it's reachable in other conditions
//   c3: warning: *-eof-2 shadowed by c3-eof, *-eof shadowed by c3-eof but not reported because it's reachable in c1
//   c4: warning: *-eof-2 shadowed by c4-eof, error: c4-eof-2 shadowed by c4-eof
/*!use:re2c:x
    <c1> ""  { c1-empty }

    <c2> [a] { c2-a }
    <c2> *   { c2-default }

    <c3> $   { c3-eof }
    <c3> *   { c3-default }

    <c4> $   { c4-eof-2 }
    <c4> *   { c4-default }

    <*>  $   { *-eof-2 }
*/

// use directive
//   c1: error: *-eof-2 shadowed by c1-empty, error: *-eof shadowed by c1-empty
//   c2: error: *-eof-2 shadowed by *-eof), *-a shadowed by c2-a but not reported because it's reachable in other conditions
//   c3: warning: *-eof-2 shadowed by c3-eof, *-eof shadowed by c3-eof but not reported because it's reachable in c1
//   c4: warning: *-eof-2 shadowed by c4-eof, error: c4-eof-2 shadowed by c4-eof
/*!re2c
    !use:x;

    <c1> ""  { c1-empty }

    <c2> [a] { c2-a }
    <c2> *   { c2-default }

    <c3> $   { c3-eof }
    <c3> *   { c3-default }

    <c4> $   { c4-eof-2 }
    <c4> *   { c4-default }

    <*>  $   { *-eof-2 }
*/
