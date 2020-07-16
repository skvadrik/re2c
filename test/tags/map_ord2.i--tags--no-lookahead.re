// re2c $INPUT -o $OUTPUT -i --tags --no-lookahead
// incorrect automaton if mapping of TDFA states ignores version order
/*!re2c

(@t "aa")? ("a"?"aaa")* {}

*/
