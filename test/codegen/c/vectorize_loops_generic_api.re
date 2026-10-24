// re2c $INPUT -o $OUTPUT -i --vectorize-loops --api generic
// Loops are not vectorized with the generic API: the vector loop accesses input
// through YYCURSOR directly, bypassing YYPEEK and YYSKIP. The combination is
// rejected when options are checked, before any code is generated.
/*!re2c
    [a-z]+ { return 1; }
    *      { return 0; }
*/
