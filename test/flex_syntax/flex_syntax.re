// re2c $INPUT -o $OUTPUT -i --flex-syntax

%{
  a   { a }
  "b" { b }
  (c) { c }
  * := ;
%}

/*!re2c
  aa      { a }
  "bb"    { b }
  "c"c    { c }
  d"d"    { d }
  "e""e"  { e }
  (ff)    { f }
  (g)g    { g }
  h(h)    { h }
  (i)(i)  { i }
  "j" "j" { j }
  * := ;
*/

%{
  a|a     { a }
  "b"|b   { b }
  c|"c"   { c }
  (d)|d   { d }
  e|(e)   { e }
  (f)|(f) { f }
  * := ;
%}

/*!re2c
  a*   { a }
  "b"* { b }
  [c]* { c }
  (d)* { d }
  * := ;
%}

%{
  aa|a     { a }
  "bb"|"b" { b }
  "c"c|c   { c }
  d"d"|d   { d }
  (e)e|e   { e }
  f(f)|f   { f }
  (gg)|(g) { g }
  * := ;
*/

%{
  a|aa     { a }
  "b"|"bb" { b }
  c|"c"c   { c }
  d|d"d"   { d }
  (e)|(ee) { e }
  f|(f)f   { f }
  g|g(g)   { g }
  * := ;
%}
