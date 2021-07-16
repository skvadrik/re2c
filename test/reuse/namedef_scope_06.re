// re2c $INPUT -o $OUTPUT -i
// Test that there is no error when a rules block and a subsequent normal block
// inherit the same global name definition, and the normal block uses the rules
// block with a `!use` directive.

// ok, name 'x' is defined in global scope
/*!re2c
    re2c:yyfill:enable = 0;
    x = [x];
*/

// ok, name 'x' is inherited by a rules block 'R'
/*!rules:re2c:R
    y = [y];
*/

// ok, symtab for 'R' is merged into the inherited one. There is no collision,
// although both symtabs have an inherited definition for 'x'.
/*!re2c
    !use:R;
    x { x }
    y { y }
    * { * }
*/
