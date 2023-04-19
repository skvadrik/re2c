// re2c $INPUT -o $OUTPUT -i --leftmost-captures

/*!local:re2c
    x = "a";
    (x)(!x) {}
    *       {}
*/

/*!local:re2c
    x = "a" "b";
    (x)(!x) {}
    *       {}
*/

/*!local:re2c
    x = "a" ("b");
    (x)(!x) {}
    *       {}
*/

/*!local:re2c
    x = "a" | "b";
    (x)(!x) {}
    *       {}
*/

/*!local:re2c
    x = "a" | ("b");
    (x)(!x) {}
    *       {}
*/

/*!local:re2c
    x = "a" | "aa";
    (x)*(!x)* {}
*/

/*!local:re2c
    x = "a" | ("aa");
    (x)*(!x)* {}
*/
