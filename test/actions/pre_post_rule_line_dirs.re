// re2c $INPUT -o $OUTPUT

/*!re2c
    [a]+       { return 0; }
    *          { return 1; }
    !pre_rule  { /* pre_rule ... */ }
    !post_rule { /* post_rule ... */ }
*/
