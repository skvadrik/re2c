// re2c $INPUT -o $OUTPUT -ci --header cond_enum_header_and_directives.h
// This test ensures that `types:re2c` includes all necessary conditions,
// whether they are defined in the output file or in the generated header.

// expect conditions: a1, a2, b1, b2
/*!types:re2c*/
// expect conditions: b2, a2
/*!types:re2c:X:Y*/

/*!header:re2c:on*/
// header start

// expect conditions: a1, a2, b1, b2
/*!types:re2c*/
// expect conditions: a2, b2
/*!types:re2c:Y:X*/

// unnamed header block with condition b1
/*!re2c   <b1> * {} */
// header block X with condition b2
/*!re2c:X <b2> * {} */

// expect conditions: a1, a2, b1, b2
/*!types:re2c*/
// expect conditions: a2, b2
/*!types:re2c:Y:X*/

// header end
/*!header:re2c:off*/

// unnamed block with condition a1
/*!re2c   <a1> * {} */
// block Y with condition a2
/*!re2c:Y <a2> * {} */

// expect conditions: a1, a2, b1, b2
/*!types:re2c*/
// expect conditions: b2, a2
/*!types:re2c:X:Y*/
