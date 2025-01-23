// re2c $INPUT -o $OUTPUT -c

/*!re2c
    <*> !entry { /* entry * ... */ }
    <a> !entry { /* entry a ... */ }
    <a> [a]    { return a; }
*/
