// re2c $INPUT -o $OUTPUT -ci
/*!re2c

re2c:eof = 0;

<>         { return NULL; }
<*> *      { return "*"; }
<*> $      { return "$"; }
<x, y> "a" { return "a"; }
<y> $      { return "$y"; }

*/
