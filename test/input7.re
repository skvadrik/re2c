// re2c $INPUT -o $OUTPUT 
/*!re2c

any = [\000-\377];

.       { return 0; }
any     { return 1; }

*/
