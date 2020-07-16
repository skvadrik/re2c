// re2c $INPUT -o $OUTPUT 
/*!re2c

[]/[]       { return 0; }
[\000-\377] { return 1; }

*/
