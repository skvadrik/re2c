// re2c $INPUT -o $OUTPUT -ic

/*!conditions:re2c*/

// defined: x, y, z; undefined: w
/*!re2c
    <x> [y] => y { x->y }
    <x> [z] => z { x->z }
    <x> [w] => w { x->w }
    <y> [y] { y }
    <z> [z] { z }
    <*> * { * }
*/

// defined: z, w
/*!re2c
    <z> [z] { z }
    <w> [w] { w }
    <*> * { * }
*/
