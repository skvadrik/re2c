// re2c $INPUT -o $OUTPUT -i --tags --fixed-tags none
// This test demonstrates the need for copy coalescing during
// allocation of tag variables: low interference allows for many
// ways of partitioning tag versions into equivalence classes.

// Without copy coalescing the choice is arbitrary: operands of
// copy command may or may not get into the same class.
// Coalescing adds bias to this choice: we first try to merge
// copy operands, then examine the rest of tags.

/*!stags:re2c format = "@@\n"; */
/*!re2c
    ("a" @p "c" @q)* { p q }
    ("a" @r "d" @s)* { r s }
    * {}
*/
