// re2c $INPUT -o $OUTPUT -rfi
/*!rules:re2c
  [a]* { a }
*/

// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:state:nextlabel = 0;
*/

// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:state:nextlabel = 1;
*/

// re2c:startlabel = 0;
// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:startlabel = 0;
  re2c:state:nextlabel = 0;
*/

// re2c:startlabel = 0;
// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:startlabel = 0;
  re2c:state:nextlabel = 1;
*/

// re2c:startlabel = 1;
// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:startlabel = 1;
  re2c:state:nextlabel = 0;
*/

// re2c:startlabel = 1;
// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:startlabel = 1;
  re2c:state:nextlabel = 1;
*/

// re2c:startlabel = Lstart;
// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:state:nextlabel = 0;
*/

// re2c:startlabel = Lstart;
// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:state:nextlabel = 1;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 0;
// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 0;
  re2c:state:nextlabel = 0;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 0;
// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 0;
  re2c:state:nextlabel = 1;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 1;
// re2c:state:nextlabel = 0;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 1;
  re2c:state:nextlabel = 0;
*/

// re2c:startlabel = Lstart;
// re2c:startlabel = 1;
// re2c:state:nextlabel = 1;
/*!use:re2c
  re2c:startlabel = Lstart;
  re2c:startlabel = 1;
  re2c:state:nextlabel = 1;
*/

