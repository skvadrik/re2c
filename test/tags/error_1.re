// re2c $INPUT -o $OUTPUT 
/*!re2c
    x = "a" @p "b"; // unused; ok
    "a" @q "b" {}   // used without '-T, --tags'; error
*/
