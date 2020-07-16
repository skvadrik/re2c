// re2c $INPUT -o $OUTPUT -ci
/*!re2c

    <c1> "ab" / "c"* {}

    <c2> "a"  / "c"* {}
    <c2> [a]  / "b"* {}
    <c2> [^a] / "b"* {}
    <c2> "aa" / "b"+ {}
    <c2> "aa" / "c"+ {}

    <*> "a"  / "b"* {}
    <*> * {}

*/
