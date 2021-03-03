// re2c $INPUT -o $OUTPUT --depfile $DEPFILE
/*!include:re2c "include003.re.b.inc" */
/*!include:re2c "include003.re.c.inc" */

/*!re2c
    b {}
    c {}
    * {}
*/
