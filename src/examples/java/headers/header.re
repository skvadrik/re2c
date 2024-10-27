// re2java $INPUT -o $OUTPUT --header lexer/state.java

package headers;

import headers.lexer.State;

/*!header:re2c:on*/
package headers.lexer;

public class State {
    public String yyinput;
    public int yycursor;
    /*!stags:re2c format = "public int @@;\n"; */

    public State(String str) {
        yyinput = str;
        yycursor = 0;
        /*!stags:re2c format = "@@ = 0;\n"; */
    }
};
/*!header:re2c:off*/

class Main {
    static int lex(String str) {
        State yyrecord = new State(str);
        int t;
        /*!re2c
            re2c:api = record;
            re2c:tags = 1;
            re2c:yyfill:enable = 0;
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyrecord.yyinput.charAt(yyrecord.yycursor)";
            re2c:header = "lexer/state.java";

            [a]* @t [b]* { return t; }
        */
    }

    public static void main(String []args) {
        assert lex("ab\0") == 1;
    }
};
