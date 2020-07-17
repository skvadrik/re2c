// re2c $INPUT -o $OUTPUT -i --tags
// This example shows the need of backuping tags in fallback
// states: if the rule is self-overlapping and the overlapping
// part has tags, these tags might be overwritten by an unsuccessful
// attempt to match longer input.

/*!re2c

    ("a" @p "bc")+ { p }
    * {}

*/
