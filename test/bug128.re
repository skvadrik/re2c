// re2c $INPUT -o $OUTPUT 
// This test produces a big DFA (which is further minimized).
// It used to be very slow and generated lots of code.

/*!re2c
    [ac]{0,14} [a] [ac]{0,14} {}
    * {}
*/
