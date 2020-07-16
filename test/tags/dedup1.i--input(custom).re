// re2c $INPUT -o $OUTPUT -i --input custom
/*!re2c
    [a]  / "b"* {}
    [^a] / "b"* {}
    "aa" / "b"+ {}
    "aa" / "c"+ {}
*/
