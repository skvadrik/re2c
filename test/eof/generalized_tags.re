// re2c $INPUT -o $OUTPUT -i --tags

// posix-captures, $
// positive tags around the whole rule
/*!local:re2c
    re2c:eof = 0;
    re2c:posix-captures = 1;
    $ { $ }
    * { * }
*/
