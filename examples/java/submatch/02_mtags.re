// re2java $INPUT -o $OUTPUT

import java.util.*;

class Main {
    static Optional<int[]> parse(String yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        int t1, t2;
        List<Integer> t3, t4;
        /*!stags:re2c format = "int @@ = -1;\n"; */
        /*!mtags:re2c format = "List<Integer> @@ = new ArrayList<>();\n"; */

        /*!re2c
            re2c:define:YYCTYPE = "char";
            re2c:define:YYPEEK = "yyinput.charAt(yycursor)";
            re2c:define:YYMTAGP = "@@.add(yycursor);";
            re2c:define:YYMTAGN = ""; // do nothing
            re2c:yyfill:enable = 0;
            re2c:tags = 1;

            num = [0-9]+;

            @t1 num @t2 ("." #t3 num #t4)* [\x00] {
                int[] vers = new int[t3.size() + 1];
                vers[0] = Integer.valueOf(yyinput.substring(t1, t2));
                for (int i = 0; i < t3.size(); ++i) {
                    vers[i + 1] = Integer.valueOf(yyinput.substring(t3.get(i), t4.get(i)));
                }
                return Optional.of(vers);
            }
            * { return Optional.empty(); }
        */
    }

    public static void main(String []args) {
        assert Arrays.equals(parse("1\0").get(), new int[]{1});
        assert Arrays.equals(parse("1.2.3.4.5.6.7\0").get(), new int[]{1, 2, 3, 4, 5, 6, 7});
        assert !parse("1.2.\0").isPresent();
    }
};
