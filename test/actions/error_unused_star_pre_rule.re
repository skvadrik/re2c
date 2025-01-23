// re2c $INPUT -o $OUTPUT -c

/*!re2c
    <*> !pre_rule { /* pre-rule * ... */ }
    <a> !pre_rule { /* pre-rule a ... */ }
    <a> [a]       { return a; }
*/
