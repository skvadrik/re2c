// re2java $INPUT -o $OUTPUT

class Parser {
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
        number = 0;

        try {
            /*!re2c
                re2c:YYCTYPE = "char";
                re2c:YYPEEK = "yyinput.charAt(yycursor)";
                re2c:yyfill:enable = 0;

                end = "\x00";

                '0b' / [01]        { return parse_bin(); }
                "0"                { return parse_oct(); }
                ""   / [1-9]       { return parse_dec(); }
                '0x' / [0-9a-fA-F] { return parse_hex(); }
                *                  { throw new IllegalArgumentException("not a number"); }
            */
        } catch (Exception e) {
            return -1;
        }
    }

    private int parse_bin() throws ArithmeticException, IllegalArgumentException {
        /*!re2c
            end   { return number; }
            [01]  { add_digit(2, 48); return parse_bin(); }
            *     { throw new IllegalArgumentException("ill-formed binary number"); }
        */
    }

    private int parse_oct() throws ArithmeticException, IllegalArgumentException {
        /*!re2c
            end   { return number; }
            [0-7] { add_digit(8, 48); return parse_oct(); }
            *     { throw new IllegalArgumentException("ill-formed octal number"); }
        */
    }

    private int parse_dec() throws ArithmeticException, IllegalArgumentException {
        /*!re2c
            end   { return number; }
            [0-9] { add_digit(10, 48); return parse_dec(); }
            *     { throw new IllegalArgumentException("ill-formed decimal number"); }
        */
    }

    private int parse_hex() throws ArithmeticException, IllegalArgumentException {
        /*!re2c
            end   { return number; }
            [0-9] { add_digit(16, 48); return parse_hex(); }
            [a-f] { add_digit(16, 87); return parse_hex(); }
            [A-F] { add_digit(16, 55); return parse_hex(); }
            *     { throw new IllegalArgumentException("ill-formed hexadecimal number"); }
        */
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
