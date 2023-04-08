// re2c $INPUT -o $OUTPUT -i --leftmost-captures --fixed-tags toplevel

// In POSIX mode grous capture non-empty string: the first iteration consumes
// all 'a's, and subsequent iterations are bypassed on the epsilon-transitions.
// It is a POSIX rule that there should be no optional empty repetitions.

// In leftmost mode groups capture empty string: the first iteration consumes
// all 'a's, but subsequent iterations aren't bypassed (by TNFA construction
// they have lower priority).

/*!re2c
    ((([^c]){0,10}|[a]?)*){0,10} {}
*/
