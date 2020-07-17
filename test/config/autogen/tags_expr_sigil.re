// re2c $INPUT -o $OUTPUT -ri --tags
/*!rules:re2c
  (@p [a])+ { a }
  *         { x }
*/

/*!use:re2c
*/

// re2c:api:sigil = #;
/*!use:re2c
  re2c:api:sigil = #;
*/

// re2c:api:sigil = @@;
/*!use:re2c
  re2c:api:sigil = @@;
*/

// re2c:tags:expression = "xyz->#";
/*!use:re2c
  re2c:tags:expression = "xyz->#";
*/

// re2c:tags:expression = "xyz->#";
// re2c:api:sigil = #;
/*!use:re2c
  re2c:tags:expression = "xyz->#";
  re2c:api:sigil = #;
*/

// re2c:tags:expression = "xyz->#";
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:tags:expression = "xyz->#";
  re2c:api:sigil = @@;
*/

// re2c:tags:expression = "@@";
/*!use:re2c
  re2c:tags:expression = "@@";
*/

// re2c:tags:expression = "@@";
// re2c:api:sigil = #;
/*!use:re2c
  re2c:tags:expression = "@@";
  re2c:api:sigil = #;
*/

// re2c:tags:expression = "@@";
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:tags:expression = "@@";
  re2c:api:sigil = @@;
*/

