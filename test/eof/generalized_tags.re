// re2c $INPUT -o $OUTPUT -i --tags

// posix-captures, $
// positive tags around the whole rule
/*!local:re2c
    re2c:eof = 0;
    re2c:posix-captures = 1;
    $ { $ }
    * { * }
*/

// a @x $ @y | a
// positive tags in $ alternative
/*!re2c
    [a] @x $ @y | [a] { a }
    * { * }
*/

// a | a @x $ @y
// positive tags in $ alternative, shadowed
/*!re2c
    [a] | [a] @x $ @y { a }
    * { * }
*/

// a $ | @x a @y
// negative tags in $ alternative
/*!re2c
    [a] $ | @x [a] @y { a }
    * { * }
*/

// @x [a] @y $ @z | @w [a] @u
// positive and negative tags in $ alternative
/*!re2c
    @x [a] @y $ @z | @w [a] @u { a }
    * { * }
*/
