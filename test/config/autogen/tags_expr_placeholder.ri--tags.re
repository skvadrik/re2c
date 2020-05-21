/*!rules:re2c
  (@p [a])+ { a }
  *         { x }
*/

/*!use:re2c
*/

// re2c:placeholder = #;
/*!use:re2c
  re2c:placeholder = #;
*/

// re2c:placeholder = @@;
/*!use:re2c
  re2c:placeholder = @@;
*/

// re2c:tags:expression = "xyz->#";
/*!use:re2c
  re2c:tags:expression = "xyz->#";
*/

// re2c:tags:expression = "xyz->#";
// re2c:placeholder = #;
/*!use:re2c
  re2c:tags:expression = "xyz->#";
  re2c:placeholder = #;
*/

// re2c:tags:expression = "xyz->#";
// re2c:placeholder = @@;
/*!use:re2c
  re2c:tags:expression = "xyz->#";
  re2c:placeholder = @@;
*/

// re2c:tags:expression = "@@";
/*!use:re2c
  re2c:tags:expression = "@@";
*/

// re2c:tags:expression = "@@";
// re2c:placeholder = #;
/*!use:re2c
  re2c:tags:expression = "@@";
  re2c:placeholder = #;
*/

// re2c:tags:expression = "@@";
// re2c:placeholder = @@;
/*!use:re2c
  re2c:tags:expression = "@@";
  re2c:placeholder = @@;
*/

