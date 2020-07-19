// re2c $INPUT -o $OUTPUT -i --flex-syntax
/*!re2c
    re2c:flags:posix-captures = 1;

    (aba|ab|a)(aba|ab|a)
    {}
    "" {}
*/
