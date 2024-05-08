// re2c $INPUT -o $OUTPUT --posix-captures

/*!rules:re2c
    (([a]))? {}
*/

/*!use:re2c
    re2c:api = custom;
*/

/*!use:re2c
    re2c:api = default;
*/
