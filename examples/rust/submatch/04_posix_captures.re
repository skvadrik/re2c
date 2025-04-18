// re2rust $INPUT -o $OUTPUT --api simple

// Maximum number of capturing groups among all rules.
/*!maxnmatch:re2c*/

#[derive(Debug, PartialEq)]
struct SemVer(u32, u32, u32); // version: (major, minor, patch)

const NONE: usize = std::usize::MAX;

fn s2n(str: &[u8]) -> u32 { // convert a pre-parsed string to a number
    let mut n = 0;
    for i in str { n = n * 10 + *i as u32 - 48; }
    return n;
}

fn parse(yyinput: &[u8]) -> Option<SemVer> {
    assert_eq!(yyinput.last(), Some(&0)); // expect null-terminated input

    let (mut yycursor, mut yymarker) = (0, 0);

    // Allocate memory for capturing parentheses (twice the number of groups).
    let yynmatch: usize;
    let mut yypmatch = [0; YYMAXNMATCH*2];

    // Intermediate tag variables used by the lexer (must be autogenerated).
    /*!stags:re2c format = 'let mut @@ = NONE;'; */

    /*!re2c
        re2c:YYCTYPE = u8;
        re2c:yyfill:enable = 0;
        re2c:posix-captures = 1;

        num = [0-9]+;

        (num) "." (num) ("." num)? [\x00] {
            // `yynmatch` is the number of capturing groups
            assert_eq!(yynmatch, 4);

            // Even `yypmatch` values are for opening parentheses, odd values
            // are for closing parentheses, the first group is the whole match.
            let major = s2n(&yyinput[yypmatch[2]..yypmatch[3]]);
            let minor = s2n(&yyinput[yypmatch[4]..yypmatch[5]]);
            let patch = if yypmatch[6] == NONE {0}
                else {s2n(&yyinput[yypmatch[6] + 1..yypmatch[7]])};

            return Some(SemVer(major, minor, patch));
        }
        * { return None; }
    */
}

fn main() {
    assert_eq!(parse(b"23.34\0"), Some(SemVer(23, 34, 0)));
    assert_eq!(parse(b"1.2.99999\0"), Some(SemVer(1, 2, 99999)));
    assert_eq!(parse(b"1.a\0"), None);
}
