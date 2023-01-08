// re2d $INPUT -o $OUTPUT -i


enum ERROR = ulong.max;

void add(ulong BASE)( ref ulong u, int d){
    u =u*BASE+d;
    if (u > uint.max){ u = ERROR;}
}


ulong parse_u32(const(char) * s){
    const(char) *  YYCURSOR = s, YYMARKER;
    ulong u = 0;

    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYSKIP = 'YYCURSOR++;';
        re2c:define:YYSHIFT= 'YYCURSOR += @@{shift};';
        re2c:define:YYRESTORE = 'YYCURSOR = YYMARKER;';
        re2c:define:YYBACKUP = 'YYMARKER = YYCURSOR;';
        re2c:define:YYPEEK = '*YYCURSOR';
        re2c:define:YYCTYPE = char;

        end = "\x00";

        '0b' / [01]        { goto bin; }
        "0"                { goto oct; }
        "" / [1-9]         { goto dec; }
        '0x' / [0-9a-fA-F] { goto hex; }
        *                  { return ERROR; }
    */
bin:
    /*!re2c
        end   { return u; }
        [01]  { add!(2)(u, YYCURSOR[-1] - '0'); goto bin; }
        *     { return ERROR; }
    */
oct:
    /*!re2c
        end   { return u; }
        [0-7] { add!(8)(u, YYCURSOR[-1] - '0'); goto oct; }
        *     { return ERROR; }
    */
dec:
    /*!re2c
        end   { return u; }
        [0-9] { add!(10)(u, YYCURSOR[-1] - '0'); goto dec; }
        *     { return ERROR; }
    */
hex:
    /*!re2c
        end   { return u; }
        [0-9] { add!(16)(u, YYCURSOR[-1] - '0');      goto hex; }
        [a-f] { add!(16)(u, YYCURSOR[-1] - 'a' + 10); goto hex; }
        [A-F] { add!(16)(u, YYCURSOR[-1] - 'A' + 10); goto hex; }
        *     { return ERROR; }
    */
}

unittest{
    assert(parse_u32("") == ERROR);
    assert(parse_u32("1234567890") == 1234567890);
    assert(parse_u32("0b1101") == 13);
    assert(parse_u32("0x7Fe") == 2046);
    assert(parse_u32("0644") == 420);
    assert(parse_u32("9999999999") == ERROR);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}

