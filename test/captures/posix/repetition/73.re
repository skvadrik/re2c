// re2c $INPUT -o $OUTPUT -i --flex-syntax
/*!re2c
    re2c:flags:posix-captures = 1;

    (a|ab|c|bcd){0,10}(d*)
    {}
    "" {}
*/
