// re2rust $INPUT -o $OUTPUT
// Test that re2c is able to lex Rust code block with braces and quotes.

'outer: loop { /*!re2c
    * {
        let c0 = '\'';
        let c1 = '\x7F';
        let c2 = '}';
        let s = "}}";

        'inner: loop {
            let c3 = '\t';
            let c4 = '\u{7FFFF}';
            if c3 == c1 {
                break 'outer;
            }
            continue 'inner;
        }

        let c5 = 'ы';
        let c6 = b'a';
        continue 'outer;
    }
*/ }
