/* Generated by re2c */
// re2rust $INPUT -o $OUTPUT

const YYMAXFILL: usize = 1;


fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut yycursor = 0;
    let yylimit = s.len() + YYMAXFILL;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut yyinput = Vec::with_capacity(yylimit);
    yyinput.extend_from_slice(s);
    yyinput.extend([0 as u8; YYMAXFILL]);

    'lex: loop { 
{
	#[allow(unused_assignments)]
	let mut yych : u8 = 0;
	let mut yystate : usize = 0;
	'yyl: loop {
		match yystate {
			0 => {
				if yylimit <= yycursor {
					return -1;
				}
				yych = unsafe {*yyinput.get_unchecked(yycursor)};
				yycursor += 1;
				match yych {
					0x00 => {
						yystate = 1;
						continue 'yyl;
					}
					0x20 => {
						yystate = 3;
						continue 'yyl;
					}
					0x27 => {
						yystate = 5;
						continue 'yyl;
					}
					_ => {
						yystate = 2;
						continue 'yyl;
					}
				}
			}
			1 => {
            // Check that it is the sentinel, not some unexpected null.
            return if yycursor == s.len() + 1 { count } else { -1 }
        },
			2 => { return -1; },
			3 => {
				if yylimit <= yycursor {
					return -1;
				}
				yych = unsafe {*yyinput.get_unchecked(yycursor)};
				match yych {
					0x20 => {
						yycursor += 1;
						yystate = 3;
						continue 'yyl;
					}
					_ => {
						yystate = 4;
						continue 'yyl;
					}
				}
			}
			4 => { continue 'lex; },
			5 => {
				if yylimit <= yycursor {
					return -1;
				}
				yych = unsafe {*yyinput.get_unchecked(yycursor)};
				yycursor += 1;
				match yych {
					0x27 => {
						yystate = 6;
						continue 'yyl;
					}
					0x5C => {
						yystate = 7;
						continue 'yyl;
					}
					_ => {
						yystate = 5;
						continue 'yyl;
					}
				}
			}
			6 => { count += 1; continue 'lex; },
			7 => {
				if yylimit <= yycursor {
					return -1;
				}
				yycursor += 1;
				yystate = 5;
				continue 'yyl;
			}
			_ => panic!("internal lexer error"),
		}
	}
}
}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(lex(b"'unterminated\\'"), -1);
    assert_eq!(lex(b"'unexpected \0 null"), -1);
}
