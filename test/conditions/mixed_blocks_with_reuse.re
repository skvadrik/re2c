// re2c $INPUT -o $OUTPUT -rci
/*!types:re2c*/

/*!rules:re2c
    "a" { a }
*/

/*!use:re2c
    "b" { b }
    *   { xb }
*/

/*!rules:re2c
    <c> "c" { c }
    <d> "d" { d }
*/

/*!re2c
    <f> "f" { f }
    <*> *   { xf }
*/

/*!re2c
    "g" { g }
    *   { xg }
*/

/*!use:re2c
    <e> "e" { e }
    <*> *   { xe }
*/

/*!rules:re2c
    * { x }
*/

/*!use:re2c*/

/*!rules:re2c
    <*> * { xx }
*/

/*!use:re2c*/

/*!use:re2c
    <h> "h" { h }
*/
