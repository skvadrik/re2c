// Generated by re2java
// re2java $INPUT -o $OUTPUT

class Main {
    // Expects a string without terminating null.
    static int lex(String str) {
        byte[] yyinput = str.getBytes();
        int yycursor = 0;
        int count = 0;

        loop: while (true) {
            
{
    byte yych = 0;
    int yystate = 0;
    yyl: while (true) {
        switch (yystate) {
            case 0:
                yych = (yycursor < yyinput.length) ? yyinput[yycursor] : 0;
                yycursor += 1;
                switch (yych) {
                    case 0x00:
                        yystate = 1;
                        continue yyl;
                    case 0x20:
                        yystate = 3;
                        continue yyl;
                    case 0x61:
                    case 0x62:
                    case 0x63:
                    case 0x64:
                    case 0x65:
                    case 0x66:
                    case 0x67:
                    case 0x68:
                    case 0x69:
                    case 0x6A:
                    case 0x6B:
                    case 0x6C:
                    case 0x6D:
                    case 0x6E:
                    case 0x6F:
                    case 0x70:
                    case 0x71:
                    case 0x72:
                    case 0x73:
                    case 0x74:
                    case 0x75:
                    case 0x76:
                    case 0x77:
                    case 0x78:
                    case 0x79:
                    case 0x7A:
                        yystate = 5;
                        continue yyl;
                    default:
                        yystate = 2;
                        continue yyl;
                }
            case 1:
                { return count; }
            case 2:
                { return -1; }
            case 3:
                yych = (yycursor < yyinput.length) ? yyinput[yycursor] : 0;
                switch (yych) {
                    case 0x20:
                        yycursor += 1;
                        yystate = 3;
                        continue yyl;
                    default:
                        yystate = 4;
                        continue yyl;
                }
            case 4:
                { continue loop; }
            case 5:
                yych = (yycursor < yyinput.length) ? yyinput[yycursor] : 0;
                switch (yych) {
                    case 0x61:
                    case 0x62:
                    case 0x63:
                    case 0x64:
                    case 0x65:
                    case 0x66:
                    case 0x67:
                    case 0x68:
                    case 0x69:
                    case 0x6A:
                    case 0x6B:
                    case 0x6C:
                    case 0x6D:
                    case 0x6E:
                    case 0x6F:
                    case 0x70:
                    case 0x71:
                    case 0x72:
                    case 0x73:
                    case 0x74:
                    case 0x75:
                    case 0x76:
                    case 0x77:
                    case 0x78:
                    case 0x79:
                    case 0x7A:
                        yycursor += 1;
                        yystate = 5;
                        continue yyl;
                    default:
                        yystate = 6;
                        continue yyl;
                }
            case 6:
                { count += 1; continue loop; }
            default:
                throw new IllegalStateException("internal lexer error");
        }
    }
}

        }
    }

    public static void main(String []args) {
        assert lex("") == 0;
        assert lex("one two three") == 3;
        assert lex("f0ur") == -1;
    }
};
