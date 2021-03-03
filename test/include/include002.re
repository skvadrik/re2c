// re2c $INPUT -o $OUTPUT --depfile $DEPFILE
/*!include:re2c "nested/include002.re.b.inc" */

/*!re2c
    b1 {}
    b2 {}
    * {}
*/

/*!include:re2c "nested/include002.re.c.inc" */

/*!re2c
    c1 {}
    c2 {}
    * {}
*/
