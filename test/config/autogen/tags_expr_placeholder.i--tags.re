/*!re2c
  (@p [a])+ { a }
  *         { x }
*/

// re2c:placeholder = #;
/*!re2c
  re2c:placeholder = #;
  (@p [a])+ { a }
  *         { x }
*/

// re2c:placeholder = @@;
/*!re2c
  re2c:placeholder = @@;
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "xyz->#";
/*!re2c
  re2c:tags:expression = "xyz->#";
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "xyz->#";
// re2c:placeholder = #;
/*!re2c
  re2c:tags:expression = "xyz->#";
  re2c:placeholder = #;
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "xyz->#";
// re2c:placeholder = @@;
/*!re2c
  re2c:tags:expression = "xyz->#";
  re2c:placeholder = @@;
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "@@";
/*!re2c
  re2c:tags:expression = "@@";
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "@@";
// re2c:placeholder = #;
/*!re2c
  re2c:tags:expression = "@@";
  re2c:placeholder = #;
  (@p [a])+ { a }
  *         { x }
*/

// re2c:tags:expression = "@@";
// re2c:placeholder = @@;
/*!re2c
  re2c:tags:expression = "@@";
  re2c:placeholder = @@;
  (@p [a])+ { a }
  *         { x }
*/

