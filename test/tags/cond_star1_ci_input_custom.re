// re2c $INPUT -o $OUTPUT -ci --input custom
/*!re2c

    <c1> "ab" / "c"* {}

    <c2> "a" / "c"* {}

    <*> "a"  / "b"* {}
    <*> * {}

*/
