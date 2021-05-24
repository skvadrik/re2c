// re2c $INPUT -o $OUTPUT

// This test is for merging blocks with inline !use directive.
// It checks that overlapping configurations and rules are merged with correct
// priority (the first rule wins, and the last configuration wins).

/*!rules:re2c:x
    re2c:define:YYCTYPE = xchar;
    re2c:yyfill:enable = 0;
    [a] { return xa; }
    [c] { return xc; }
*/

/*!rules:re2c:y
    re2c:define:YYCTYPE = ychar;
    re2c:yyfill:enable = 1;
    re2c:flags:s = 1;
    [a] { return ya; }
    [b] { return yb; }
*/

// expect: YYCTYPE:xchar, return:a, fill:no, ifs:no
/*!re2c
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:x;
    * { return -1; }
*/

// expect: YYCTYPE:char, return:xa, fill:no, ifs:no
/*!re2c
    !use:x;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    * { return -1; }
*/

// expect: YYCTYPE:ychar, return:a, fill:yes, ifs:yes
/*!re2c
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:y;
    * { return -1; }
*/

// expect: YYCTYPE:char, return:ya, fill:yes, ifs:yes
/*!re2c
    !use:y;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    * { return -1; }
*/

// expect: YYCTYPE:ychar, return:a, fill:yes, ifs:yes
/*!re2c
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:x;
    !use:y;
    * { return -1; }
*/

// expect: YYCTYPE:xchar, return:a, fill:no, ifs:yes
/*!re2c
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:y;
    !use:x;
    * { return -1; }
*/

// expect: YYCTYPE:ychar, return:xa, fill:yes, ifs:yes
/*!re2c
    !use:x;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:y;
    * { return -1; }
*/

// expect: YYCTYPE:xchar, return:ya, fill:no, ifs:yes
/*!re2c
    !use:y;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    !use:x;
    * { return -1; }
*/

// expect: YYCTYPE:char, return:xa, fill:yes, ifs:yes
/*!re2c
    !use:x;
    !use:y;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    * { return -1; }
*/

// expect: YYCTYPE:char, return:ya, fill:no, ifs:yes
/*!re2c
    !use:y;
    !use:x;
    re2c:define:YYCTYPE = char;
    [a] { return a; }
    * { return -1; }
*/
