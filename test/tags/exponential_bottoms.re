// re2c $INPUT -o $OUTPUT -i --tags
// forbidding to map bottom version to other tag versions is a bad idea:
// example shows exponential growth in the number of DFA states

/*!re2c

(@p | "a")(@q | "b")(@z | "c") {}

*/
