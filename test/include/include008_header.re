// re2c $INPUT -o $OUTPUT --depfile $DEPFILE --header include008.h
/*!include:re2c "include008.re.b.inc" */

/*!header:re2c:on */
/*!include:re2c "include008.re.c.inc" */
/*!header:re2c:off */
