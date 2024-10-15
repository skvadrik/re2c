// re2js $INPUT -o $OUTPUT --header lexer/state.js

let state = require('./lexer/state.js');

/*!header:re2c:on*/
exports.mk_state = function(str) {
    return {
        yyinput: str,
        /*!stags:re2c format = "@@: 0,\n"; */
        yycursor: 0
    }
}
/*!header:re2c:off*/

function lex(yyrecord) {
    let t
    /*!re2c
        re2c:api = record;
        re2c:tags = 1;
        re2c:yyfill:enable = 0;
        re2c:header = "lexer/state.js";

        [a]* @t [b]* { return t }
    */
}

if (lex(state.mk_state("ab\0")) != 1) {
    throw "error!"
}
