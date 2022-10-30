// re2c $INPUT -o $OUTPUT -if
// This tests that a use block (that always has its own state switch)
// preceding a non-use block does not affect the generation of a global
// implicit state switch for non-use blocks.

/*!rules:re2c
    [a]* { return 1; }
*/

// expect local state switch for a use block
/*!use:re2c*/

// expect global implicit state switch for blocks 'b' and 'c'
/*!re2c:b
    [b]* { return 2; }
*/

// expect local state switch for a use block
/*!use:re2c*/

// expect no state switch
/*!re2c:c
    [c]* { return 3; }
*/
