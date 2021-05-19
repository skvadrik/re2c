// re2c $INPUT -o $OUTPUT -i --depfile $DEPFILE
/*!re2c
    * { return -1; }

    [1] { return 1; }

    // Include file specifies overlapping rules for [1] and [2].
    // The rule for [1] is ignored because it has already been defined.
    // The rule for [2] takes precedence over the one in this file.
    !include "include004_inline.re.inc";

    [2] { return 2; }
*/
