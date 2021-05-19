// re2c $INPUT -o $OUTPUT -i --depfile $DEPFILE
/*!re2c
    * { return -1; }

    // Including this file causes an error, because it contains another
    // definition for the default rule.
    !include "include005_redef_error.re.inc";
*/
