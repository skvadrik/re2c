// re2c $INPUT -o $OUTPUT -c

/*!re2c
    <*> !post_rule { /* post-rule * ... */ }
    <a> !post_rule { /* post-rule a ... */ }
    <a> [a]        { return a; }
*/
