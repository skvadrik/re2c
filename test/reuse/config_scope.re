// re2c $INPUT -o $OUTPUT -i
/*!re2c
    re2c:yyfill:enable = 0;
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

/*!rules:re2c:xa
    re2c:define:YYCTYPE = xachar;
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

/*!rules:re2c:xb
    re2c:define:YYCTYPE = xbchar;
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

// expect xachar
/*!use:re2c:xa
    "" {}
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

// expect xbchar
/*!use:re2c:xb
    "" {}
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

// expect xachar
/*!local:re2c
    !use:xa;
    "" {}
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

// expect xbchar
/*!local:re2c
    !use:xb;
    "" {}
*/

// expect YYCTYPE
/*!re2c
    "" {}
*/

// expect xachar
/*!re2c
    !use:xa;
    "" {}
*/

// expect xachar
/*!re2c
    "" {}
*/

// expect xbchar
/*!re2c
    !use:xb;
    "" {}
*/

// expect xbchar
/*!re2c
    "" {}
*/

// expect xcchar
/*!local:re2c
    re2c:define:YYCTYPE = xcchar;
    "" {}
*/

// expect xbchar
/*!re2c
    "" {}
*/

// expect xcchar
/*!re2c
    re2c:define:YYCTYPE = xcchar;
    "" {}
*/

// expect xcchar
/*!re2c
    "" {}
*/
