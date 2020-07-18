// re2c $INPUT -o $OUTPUT -ci
/*!re2c
 <*>        "a" { a }
 <  *  >    "b" { b }
 <x>        "c" { c }
 <x,y0>     "d" { d }
 <x,y0,z11> "e" { e }
 <  x  >    "f" { f }
 <x, y>     "g" { g }
 <x ,y>     "h" { h }
 <x , y>    "i" { i }
 <!x>           { j }
 <  !  y>       { k }
 <! y0, z11>    { l }
 <>             { m }
 <*> *          { n }
*/
