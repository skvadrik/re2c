//go:generate re2go $INPUT -o $OUTPUT -i --nested-ifs
package main                              //
                                          // Go code
func lex(str string) {                    //
    var cursor int                        //
/*!re2c
    re2c:define:YYCTYPE = byte;           //
    re2c:define:YYPEEK = "str[cursor]";   // configurations
    re2c:define:YYSKIP = "cursor += 1";   //
    re2c:yyfill:enable = 0;               //

    number = [1-9][0-9]*;                 // named definition

    number { return }                     // rules
    *      { panic("error!") }            //
*/
}                                         //
                                          //
func main() {                             // Go code
    lex("1234\x00")                       //
}                                         //
