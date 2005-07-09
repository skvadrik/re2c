/*!re2c

any = [\000-\377];

.{1,3}"\000"       { return 0; }
.                  { return 1; }
any                { return 2; }

*/
