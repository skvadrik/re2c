package re2c;

// JNI bindings to libre2c library.
public class RE2C {
    static {
        System.loadLibrary("re2c_jni");
    }

    // Must be in sync with libre2c.
    public static final int TAG_BASE = 1 << 15;

    public static native long regcomp(String pattern, boolean nfa,
        boolean regless, boolean subhist, boolean tstring, boolean autotags);
    public static native int regexec(long re, String string);
    public static native void regfree(long re);
    public static native void regfreesub(long re);
    public static native int getNmatch(long re);
    public static native int getNtags(long re);
    public static native long getStartOffset(long re, int index);
    public static native long getEndOffset(long re, int index);
    public static native char[] getTstring(long re);

    public static void printRegs(long re) {
        int nmatch = getNmatch(re);
        for (int j = 0; j < nmatch; ++j) {
            System.out.printf("(%d,%d)", getStartOffset(re, j), getEndOffset(re, j));
        }
        System.out.printf("\n");
    }

    public static String showTstring(char[] tstring) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < tstring.length; i++){
            char c = tstring[i];
            if (c < TAG_BASE) {
                // Alphabet character.
                sb.append(c);
            } else {
                // Tag, shifted to the upper half of a t-string character.
                if (i > 0 && tstring[i - 1] >= TAG_BASE) {
                    sb.append(' ');
                }
                sb.append(c - TAG_BASE);
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        final String[] res =
            {"a"
            , "ab"
            , "[a-c]*"
            , "()"
            , "(a*)"
            , "(a*)(a*)"
            };
        final String[][] ss =
            { {"a", "b"}
            , {"ab", "aba"}
            , {"", "a", "b", "c", "abc"}
            , {""}
            , {"", "a", "aaa"}
            , {"", "a", "aaa"}
            };

        for (int k = 0; k < res.length; ++k) {
            String re = res[k];

            long reg = regcomp(re, false, false, false, false, false);
            if (reg == 0) {
                System.err.printf("regcomp failed on RE %s\n", re);
                System.exit(1);
            }

            for (int i = 0; i < ss[k].length; ++i) {
                String s = ss[k][i];

                int e = regexec(reg, s);
                System.out.printf("regexec on RE %s, string %s: ", re, s);
                if (e != 0) {
                    System.out.printf("NOMATCH\n");
                } else {
                    printRegs(reg);
                }
            }

            regfree(reg);
            System.out.printf("\n");
        }
    }
}

