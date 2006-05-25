/*!re2c

[a][b]+ "cc"  { return 1; }
[\000-\377]   { return 0; }

*/
