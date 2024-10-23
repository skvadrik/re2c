// re2java $INPUT -o $OUTPUT -c

class Parser {
    /*!conditions:re2c*/
    private String yyinput;
    private int yycursor;
    private int yymarker;
    private int number;

    private void add_digit(int base, int offset) throws ArithmeticException {
        number = Math.addExact(
            Math.multiplyExact(number, base),
            yyinput.charAt(yycursor - 1) - offset);
    }

    public int parse(String str) throws ArithmeticException, IllegalArgumentException {
        yyinput = str;
        yycursor = 0;
        int yycond = YYC_init;

        number = 0;
        try {
            loop: while (true) {
            /*!re2c
                re2c:YYCTYPE = "char";
                re2c:YYPEEK = "yyinput.charAt(yycursor)";
                re2c:yyfill:enable = 0;

                <*> * { throw new IllegalArgumentException("ill-formed number"); }

                <init> '0b' / [01]        :=> bin
                <init> "0"                :=> oct
                <init> ""   / [1-9]       :=> dec
                <init> '0x' / [0-9a-fA-F] :=> hex

                <bin, oct, dec, hex> "\x00" { return number; }

                <bin> [01]  { add_digit(2, 48); continue loop; }
                <oct> [0-7] { add_digit(8, 48); continue loop; }
                <dec> [0-9] { add_digit(10, 48); continue loop; }
                <hex> [0-9] { add_digit(16, 48); continue loop; }
                <hex> [a-f] { add_digit(16, 87); continue loop; }
                <hex> [A-F] { add_digit(16, 55); continue loop; }
            */
            }
        } catch (Exception e) {
            return -1;
        }
    }

    public static void main(String []args) {
        Parser parser = new Parser();
        assert parser.parse("1234567890\0") == 1234567890;
        assert parser.parse("0b1101\0") == 0b1101;
        assert parser.parse("0x007Fe\0") == 0x7fe;
        assert parser.parse("0644\0") == 0644;
        assert parser.parse("9999999999\0") == -1;
        assert parser.parse("123??\0") == -1;
    }
};
