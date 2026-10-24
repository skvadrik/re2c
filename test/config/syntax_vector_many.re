// re2c $INPUT -o $OUTPUT -i -Wno-unreachable-rules --syntax syntax_vector_many.inc
// The template tests global .many before, inside and after both lists.
/*!re2c
    re2c:vectorize:loops = 1;
    re2c:YYCTYPE = "unsigned char";
    [a-z]+ { return 1; }
    * { return 0; }
*/
/*!re2c
    [ac-e]+ { return 1; }
    * { return 0; }
*/
/*!re2c
    [^]+ { return 1; }
*/
