// re2c $INPUT -o $OUTPUT -i

// $  (unhandled default state in-between start state and $ rule state)
/*!re2c
    $ { $ }
*/

// $, *
/*!re2c
    $ { $ }
    * { * }
*/

// $, a$
/*!re2c
    $     { $ }
    [a] $ { a$ }
*/

// $, *, a$
/*!re2c
    $     { $ }
    *     { * }
    [a] $ { a$ }
*/

// $, *, a$, a
/*!re2c
    $     { $ }
    *     { * }
    [a] $ { a$ }
    [a]   { a }
*/

// $, *, a, a$
/*!re2c
    $     { $ }
    *     { * }
    [a]   { a }
    [a] $ { a$ }
*/

// $, *, a$ | a
/*!re2c
    $           { $ }
    *           { * }
    [a] $ | [a] { a }
*/

// $, *, a$ | b
/*!re2c
    $           { $ }
    *           { * }
    [a] $ | [b] { ab }
*/

// $, *, b$ | a
/*!re2c
    $           { $ }
    *           { * }
    [b] $ | [a] { ba }
*/

// $, *, a$ | b | a[cz]
/*!re2c
    $                     { $ }
    *                     { * }
    [a] $ | [b] | [a][cz] { abcz }
*/

// $, *, a$ | a[^]
/*!re2c
    $              { $ }
    *              { * }
    [a] $ | [a][^] { a }
*/
