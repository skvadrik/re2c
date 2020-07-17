// re2c $INPUT -o $OUTPUT -rcfi
/*!rules:re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

/*!use:re2c
*/

// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = ;
*/

// re2c:startlabel = 0;
/*!use:re2c
  re2c:startlabel = 0;
*/

// re2c:startlabel = 0;
// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = 0;
  re2c:startlabel = ;
*/

// re2c:startlabel = 1;
/*!use:re2c
  re2c:startlabel = 1;
*/

// re2c:startlabel = 1;
// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = 1;
  re2c:startlabel = ;
*/

// re2c:startlabel = Lstart;
/*!use:re2c
  re2c:startlabel = Lstart;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = ;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 0;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 0;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 0;
// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 0;
  re2c:startlabel = ;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 1;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 1;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 1;
// re2c:startlabel = ;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 1;
  re2c:startlabel = ;
*/

