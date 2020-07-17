// re2c $INPUT -o $OUTPUT -ci
/*!types:re2c*/

/*!re2c
    "a" { a }
    *   { * }
*/

/*!re2c
    <b> "b" { b }
    <c> "c" { c }
    <*> *   { * }
*/

/*!re2c
    <d> "d" { d }
    <*> *   { * }
*/

/*!re2c
    re2c:flags:s = 1;
*/

/*!re2c
    "e" { e }
    *   { * }
*/

/*!re2c
    <b> "B" { B }
    <f> "f" { f }
    <*> *   { * }
*/
