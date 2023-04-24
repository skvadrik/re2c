// re2c $INPUT -o $OUTPUT -i --leftmost-captures --invert-captures

// B is capturing
/*!re2c
    ([A])  { A }
    (![B]) { B }
    *      { * }
*/

// B is non-capturing, A is capturing, plus the implicit whole rule capture for A and B
/*!re2c
    re2c:invert-captures = 0;
    ([A])  { A }
    (![B]) { B }
    *      { * }
*/

// B is capturing
/*!re2c
    re2c:invert-captures = 1;
    ([A])  { A }
    (![B]) { B }
    *      { * }
*/
