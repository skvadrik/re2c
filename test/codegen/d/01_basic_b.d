/* Generated by re2d */
#line 1 "codegen/d/01_basic_b.re"
// re2d $INPUT -o $OUTPUT -b
module main;

bool lex(const char *s) {
    size_t cursor;
    
#line 10 "codegen/d/01_basic_b.d"
{
    char yych;
    immutable char[256] yybm = [
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
        128, 128, 128, 128, 128, 128, 128, 128,
        128, 128,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0
    ];
    yych = s[cursor];
    if (yych <= '0') goto yy1;
    if (yych <= '9') goto yy2;
yy1:
    ++cursor;
#line 15 "codegen/d/01_basic_b.re"
    { return false; }
#line 54 "codegen/d/01_basic_b.d"
yy2:
    ++cursor;
    yych = s[cursor];
    if ((yybm[0+yych] & 128) != 0) goto yy2;
#line 14 "codegen/d/01_basic_b.re"
    { return true; }
#line 61 "codegen/d/01_basic_b.d"
}
#line 16 "codegen/d/01_basic_b.re"

}

void main() {
    assert(lex("1234"));
}
