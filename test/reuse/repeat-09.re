// re2c $INPUT -o $OUTPUT -i
// 2nd use block must inherit options from rules block, not from the 1st use block

/*!rules:re2c
    * {}
*/

/*!use:re2c
    re2c:indent:top = 3;
*/

/*!use:re2c*/
