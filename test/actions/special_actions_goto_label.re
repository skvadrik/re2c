// re2c $INPUT -o $OUTPUT -ci

/*!re2c:x
    [a]*       { return a; }
    !entry     { /* entry ... */ }
    !pre_rule  { /* pre_rule ... */ }
    !post_rule { /* post_rule ... */ }
*/

/*!conditions:re2c*/
/*!re2c:y
    <a> [a]*   { return a; }
    <b> [b]*   { return b; }
    <*> !entry     { /* entry * ... */ }
    <*> !pre_rule  { /* pre_rule * ... */ }
    <*> !post_rule { /* post_rule * ... */ }
    <a> !entry     { /* entry a ... */ }
    <b> !pre_rule  { /* pre_rule b ... */ }
    <b> !post_rule { /* post_rule b ... */ }
*/
