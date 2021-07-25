//go:generate re2go $INPUT -o $OUTPUT -i

package main                              //
                                          //
func lex(str string) {                    // Go code
    var cursor int                        //
                                          //
/*!re2c
    re2c:define:YYCTYPE = byte;           //
    re2c:define:YYPEEK = "str[cursor]";   //
    re2c:define:YYSKIP = "cursor += 1";   // configurations
    re2c:yyfill:enable = 0;               //
    re2c:flags:nested-ifs = 1;            //
                                          //
    number = [1-9][0-9]*;                 // named definition
                                          //
    number { return }                     // rules
    *      { panic("error!"); }           //
*/
}                                         //
                                          //
func main() {                             // Go code
    lex("1234\x00")                       //
}                                         //
