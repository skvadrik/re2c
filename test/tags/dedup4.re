// re2c $INPUT -o $OUTPUT -i --tags
/*!re2c
    "a" @p "b"* / "d"* { 1 p }
    "a" @p "b"* / "c"* { 2 p }
    * {}
*/

/*!re2c
    "a" @p "b"*        { 1 p }
    "a" @p "b"* / "c"* { 2 p }
    * {}
*/

/*!re2c
    "a" @p "b"*         { 1 p }
    "a" @p "b"* / "cd"* { 2 p }
    * {}
*/

/*!re2c
    "a" @p "b"+         { 1 p }
    "a" @p "b"+ / "cd"* { 2 p }
    * {}
*/
