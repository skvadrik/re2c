// re2java $INPUT -o $OUTPUT

import java.io.*;
import java.nio.file.*;

class Lexer {
    public static final int BUFSIZE = 4096;

    private BufferedInputStream stream;
    private byte[] yyinput;
    private int yycursor;
    private int yymarker;
    private int yylimit;
    private int token;
    private boolean eof;

    public Lexer(File file) throws FileNotFoundException {
        stream = new BufferedInputStream(new FileInputStream(file));
        // Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
        yyinput = new byte[BUFSIZE + 1];
        yycursor = yymarker = yylimit = token = BUFSIZE;
        eof = false;
    }

    private int fill() throws IOException {
        if (eof) { return -1; } // unexpected EOF

        // Error: lexeme too long. In real life can reallocate a larger buffer.
        if (token < 1) { return -2; }

        // Shift buffer contents (discard everything up to the current token).
        System.arraycopy(yyinput, token, yyinput, 0, yylimit - token); 
        yycursor -= token;
        yymarker -= token;
        yylimit -= token;
        token = 0;

        // Fill free space at the end of buffer with new data from file.
        yylimit += stream.read(yyinput, yylimit, BUFSIZE - yylimit);
        yyinput[yylimit] = 0; // append sentinel symbol

        // If read less than expected, this is the end of input.
        eof = yylimit < BUFSIZE;

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
                re2c:YYFILL = "fill() == 0";
                re2c:eof = 0;

                str = ['] ([^'\\] | [\\][^])* ['];

                *    { return -1; }
                $    { return count; }
                str  { count += 1; continue loop; }
                [ ]+ { continue loop; }
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
