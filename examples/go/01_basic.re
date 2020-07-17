//go:generate re2go $INPUT -o $OUTPUT -i
package main                             //
                                         //
func lex(str string) int {               // Go code
    var cursor int                       //

    /*!re2c                              // start of re2c block
    re2c:define:YYCTYPE = byte;          // configuration
    re2c:define:YYPEEK = "str[cursor]";  // configuration
    re2c:define:YYSKIP = "cursor += 1";  // configuration
    re2c:yyfill:enable = 0;              // configuration
    re2c:flags:nested-ifs = 1;           // configuration
                                         //
    number = [1-9][0-9]*;                // named definition
                                         //
    number { return 0; }                 // normal rule
    *      { return 1; }                 // default rule
    */
}                                        //
                                         //
func main() {                            //
    if lex("1234\x00") != 0 {            // Go code
        panic("failed!")                 //
    }                                    //
}                                        //
