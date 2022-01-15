// re2rust $INPUT -o $OUTPUT --no-unsafe

// Have to use Cell for cursor, otherwise borrow checker does not allow
// to have closures YYPEEK (that does immutable borrow of cursor) and
// YYSKIP (that does mutable borrow).
use std::cell::Cell;

#[allow(non_snake_case)]
fn lex(s: &[u8]) -> bool {
    let cur = Cell::new(0);
    let YYPEEK = || unsafe { *s.get_unchecked(cur.get()) };
    let YYSKIP = || { cur.set(cur.get() + 1); };

/*!re2c
    re2c:api:style = functions;
    re2c:define:YYCTYPE = u8;
    re2c:yyfill:enable = 0;

    alpha = [a-zA-Z];
    ident = alpha (alpha | [0-9])*;

    ident  { return true; }
    *      { return false; }
*/
}

fn main() {
    assert!(lex(b"qwerty42\0"));
}
