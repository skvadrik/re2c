// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:yyfill:enable = 0;
*/

/*!rules:re2c:block1
    [1] { return 1; }
*/

/*!rules:re2c:block2
    [2] { return 2; }
*/

/*!rules:re2c
    [0] { return 0; }
*/

/*!use:re2c:block1
    * { return -1; }
*/

/*!use:re2c:block2
    * { return -1; }
*/

/*!use:re2c
    * { return -1; }
*/
