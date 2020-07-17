// re2c $INPUT -o $OUTPUT -i --flex-syntax --stadfa
/*!re2c
    re2c:flags:posix-captures = 1;

    (ab|a|c|bcd){2,10}(d*)
    {}
    "" {}
*/
