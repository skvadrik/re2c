// re2c $INPUT -o $OUTPUT -i --tags

// *, a @x $ | a
/*!re2c
    *              { * }
    [a] @x $ | [a] { a }
*/

// *, a | a @x $
/*!re2c
    *              { * }
    [a] | [a] @x $ { a }
*/
