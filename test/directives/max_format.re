// re2c $INPUT -o $OUTPUT --posix-captures
// Test `max:re2c` and `maxnmatch:re2c` directives with optional format.

// default
/*!max:re2c */
// #define YYMAXFILL @@
/*!max:re2c format = "#define YYMAXFILL @@"; */
// static const int MaxFill = @@{max};
/*!max:re2c
    format = "static const int MaxFill = @@{max};";
*/
// line 12

// default
/*!maxnmatch:re2c */
// #define YYMAXFILL @@
/*!maxnmatch:re2c format = "#define YYMAXNMATCH @@"; */
// static const int MaxNMatch = @@{max};
/*!maxnmatch:re2c
    format = "static const int MaxNMatch = @@{max};";
*/
// line 22

/*!re2c
    "a" { a }
    *   { x }
*/
