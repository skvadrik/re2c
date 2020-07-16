// re2c $INPUT -o $OUTPUT  --empty-class error
/*!re2c

[]/[]       { return 0; }
[\000-\377] { return 1; }

*/
