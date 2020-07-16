// re2c $INPUT -o $OUTPUT -i --tags
// ensure 'r+' (one or more repetitions) expansion does not duplicate 'r'
// this is crucial if 'r' contains tags (tag duplication is forbidden)

/*!re2c
    (@p "a")+ { p }
    *         { d }
*/
