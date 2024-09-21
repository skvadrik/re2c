// re2rust $INPUT -o $OUTPUT

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

    // Final tag variables available in semantic action.
    /*!svars:re2c format = '#[allow(unused_mut)]\nlet mut @@;\n'; */

    // Intermediate tag variables used by the lexer (must be autogenerated).
    /*!stags:re2c format = 'let mut @@ = NONE;'; */

    /*!re2c
        re2c:api = default;
        re2c:define:YYCTYPE = u8;
        re2c:yyfill:enable = 0;
        re2c:tags = 1;

        num = [0-9]+;

        @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\x00] {
            let major = s2n(&yyinput[t1..t2]);
            let minor = s2n(&yyinput[t3..t4]);
            let patch = if t5 != NONE {s2n(&yyinput[t5..yycursor - 1])} else {0};
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