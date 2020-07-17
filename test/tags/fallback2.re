// re2c $INPUT -o $OUTPUT -i --tags
// This test shows that tag liveness should be attributed to DFA edges,
// not to DFA states. State granularity is too crude: there might be
// two different paths to the same state, with some tag alive on one
// path but not on the other. If liveness is attributed to states, then
// tag liveness on one path implies tag liveness in the join state,
// which affects the other path. But if liveness is attributed to
// edges, then liveness of one path won't affect liveness of the other.

// In this example tag 'p' is loop-invariant: it should be moved out
// of loop and set once in the very end. However, if liveness is
// attributed to states rather than edges, the accepting state (dispatch
// on 'yyaccept') will force liveness on the looping path and prevent
// tag from hoisting out of loop.

/*!re2c

    ("ab" @p)* { p }

*/
