// re2java $INPUT -o $OUTPUT

import java.io.*;
import java.nio.file.*;
import java.util.Arrays;

class Lexer {
    /*!max:re2c*/
    public static final int BUFSIZE = 4096;

    private BufferedInputStream stream;
    private byte[] yyinput;
    private int yycursor;
    private int yylimit;
    private int token;
    private boolean eof;

    public Lexer(File file) throws FileNotFoundException {
        stream = new BufferedInputStream(new FileInputStream(file));
        // Prepare lexer state: all offsets are at the end of buffer.
        // This immediately triggers YYFILL, as the YYLESSTHAN condition is true.
        yyinput = new byte[BUFSIZE + YYMAXFILL];
        yycursor = yylimit = token = BUFSIZE;
        eof = false;
    }

    private int fill(int need) throws IOException {
        if (eof) { return -1; } // unexpected EOF

        // Error: lexeme too long. In real life can reallocate a larger buffer.
        if (token < need) { return -2; }

        // Shift buffer contents (discard everything up to the current token).
        System.arraycopy(yyinput, token, yyinput, 0, yylimit - token); 
        yycursor -= token;
        yylimit -= token;
        token = 0;

        // Fill free space at the end of buffer with new data from file.
        yylimit += stream.read(yyinput, yylimit, BUFSIZE - yylimit);
        yyinput[yylimit] = 0; // append sentinel symbol

        // If read less than expected, this is the end of input.
        if (yylimit < BUFSIZE) {
            eof = true;
            Arrays.fill(yyinput, yylimit, yylimit + YYMAXFILL, (byte)0);
            yylimit += YYMAXFILL;
        }

        return 0;
    }

    // Expects a null-terminated string.
    public int lex() throws IOException {
        int count = 0;
        loop: while (true) {
            token = yycursor;
            /*!re2c
                re2c:YYCTYPE = "byte";
                re2c:YYPEEK = "yyinput[yycursor]";
                re2c:YYFILL = "if (fill(@@) != 0) { return -2; }";

                str = ['] ([^'\\] | [\\][^])* ['];

                [\x00] {
                    // Check that it is the sentinel, not some unexpected null.
                    return (token == yylimit - YYMAXFILL) ? count : -1;
                }
                str  { count += 1; continue loop; }
                [ ]+ { continue loop; }
                *    { return -1; }
            */
        }
    }

    public static void main(String []args) throws FileNotFoundException, IOException {
        String fname = "input";
        String content = "'qu\0tes' 'are' 'fine: \\'' ".repeat(Lexer.BUFSIZE);

        // Prepare input file: a few times the size of the buffer, containing
        // strings with zeroes and escaped quotes.
        Files.writeString(Paths.get(fname), content);

        int count = 3 * Lexer.BUFSIZE; // number of quoted strings written to file

        // Prepare lexer state: all offsets are at the end of buffer.
        File file = new File(".", fname);
        Lexer lexer = new Lexer(file);

        // Run the lexer.
        int n = lexer.lex();
        assert n == count;

        // Cleanup: remove input file.
        file.delete();
    }
};
