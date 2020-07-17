// re2c $INPUT -o $OUTPUT -i --empty-class match-none
/*!re2c
    [] {}
*/

/*!re2c
    [^\x00-\xFF] {}
*/

/*!re2c
    [\x00-\xFF]\[\x00-\xFF] {}
*/

/*!re2c
    []\[] {}
*/

/*!re2c
    [^\x00-\xFF]\[^\x00-\xFF] {}
*/
