// re2c $INPUT -o $OUTPUT --recursive-functions -cfi

// getstate (no list), uses global options
/*!getstate:re2c*/

// getstate:z:y, uses z options
// initial case -1 goes to condition dispatch of block z, other cases go directly to YYFILL states
/*!getstate:re2c:z:x*/

// block x
/*!re2c:x
    re2c:define:YYFN = ["lex_x", "void", "x", "T"];
    [x] { x }
    *   { * }
*/

// block (no name)
/*!re2c
    re2c:define:YYFN = ["lex_y", "void", "y", "T"];
    [y] { y }
    *   { y }
*/

// block z
/*!local:re2c:z
    re2c:define:YYFN = ["lex_z", "void", "z", "T"];
    re2c:state:abort = 1;
    <c1,c2> [z] { z }
    <*>     *   { * }
*/

// block w
/*!re2c:w
    re2c:define:YYFN = ["lex_w", "void", "w", "T"];
    [w] { w }
    *   { * }
*/

// getstate (no list), uses global options
/*!getstate:re2c*/

// getstate:w:z, uses w options
/*!getstate:re2c:w:z*/

/*!re2c
    re2c:define:YYFN = ["lex", "void", "q", "T"];
*/
