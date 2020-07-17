// re2c $INPUT -o $OUTPUT -i --tags
// incorrect automaton if mapping of TDFA states ignores version order
/*!re2c

(@t "a")? ("aa""a"?)* {}

*/
