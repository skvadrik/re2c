// re2c $INPUT -o $OUTPUT -ic

/*!conditions:re2c*/

// conditions `x`, `y`, `z` have their own rules; condition `w` has only * rule - but that's fine
/*!re2c
    <x> [y] => y { x->y }
    <x> [z] => z { x->z }
    <x> [w] => w { x->w }
    <y> [y] { y }
    <z> [z] { z }
    <*> * { * }
*/

// conditions `z`, `w` have their own rules
/*!re2c
    <z> [z] { z }
    <w> [w] { w }
    <*> * { * }
*/
