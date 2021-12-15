// re2rust $INPUT -o $OUTPUT --no-unsafe

// expect safe YYPEEK
/*!re2c * {} */

// expect `unsafe { ... }` wrapper around YYPEEK
/*!re2c re2c:flags:unsafe = 1; * {} */

// expect safe YYPEEK
/*!re2c re2c:flags:unsafe = 0; * {} */
