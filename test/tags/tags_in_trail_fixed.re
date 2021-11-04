// re2c $INPUT -o $OUTPUT -i --tags

// fixed trailing context, fixed tags p and q
/*!re2c
    @p "a" / "b" @q "cd" {}
    * {}
*/

// variable trailing context, fixed tags p and q
/*!re2c
    @p "a" / "b"? @q "cd" {}
    * {}
*/
