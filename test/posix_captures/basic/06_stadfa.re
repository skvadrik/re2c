// re2c $INPUT -o $OUTPUT -i --flex-syntax --stadfa
/*!re2c
    re2c:flags:posix-captures = 1;

    (a*)(b{0,1})(b{1,})b{3}
    {}
    "" {}
*/
