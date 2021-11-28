// re2c $INPUT -o $OUTPUT

// line 3 of the file
/*!include:re2c "nested/include007.re.inc" *//*!include:re2c "nested/include007.re.inc" */
// line 5 of the file
/*!re2c !include "nested/include007.re.inc"; !include "nested/include007.re.inc"; */
// line 7 of the file
