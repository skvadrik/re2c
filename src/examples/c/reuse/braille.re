// re2c $INPUT -o $OUTPUT -cri
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

template<typename char_t>
struct input_t {
    size_t len;
    char_t *str;

    input_t(FILE *f) : len(0), str(NULL)
    {
        fseek(f, 0, SEEK_END);
        len = ftell(f) / sizeof(char_t);
        fseek(f, 0, SEEK_SET);
        str = new char_t[len + 1];
        fread(str, sizeof(char_t), len, f);
        str[len] = 0;
    }
    ~input_t() { delete[] str; }
};

typedef input_t<unsigned char>  iutf8_t;
typedef input_t<unsigned short> iutf16_t;
typedef input_t<unsigned int>   iutf32_t;
typedef input_t<unsigned short> iucs2_t;

struct out_t {
    bool caps;

    out_t() : caps(false) {}
    void prt(char c)
    {
        fprintf(stderr, "%c", caps ? toupper(c) : c);
        caps = false;
    }
    void err()
    {
        fprintf(stderr, " ... error\n");
    }
};

/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:api:style = free-form;
    re2c:flags:8 = 1;
    re2c:define:YYGETCONDITION = "c";
    re2c:define:YYSETCONDITION = "c = @@;";

    // letters
    l = "\u2830";
    la = "\u2801"; lb = "\u2803"; lc = "\u2809"; ld = "\u2819"; le = "\u2811";
    lf = "\u280b"; lg = "\u281b"; lh = "\u2813"; li = "\u280a"; lj = "\u281a";
    lk = "\u2805"; ll = "\u2807"; lm = "\u280d"; ln = "\u281d"; lo = "\u2815";
    lp = "\u280f"; lq = "\u281f"; lr = "\u2817"; ls = "\u280e"; lt = "\u281e";
    lu = "\u2825"; lv = "\u2827"; lw = "\u283a"; lx = "\u282d"; ly = "\u283d";
    lz = "\u2835";

    // numbers
    n = "\u283c";
    n1 = "\u2801"; n2 = "\u2803"; n3 = "\u2809"; n4 = "\u2819"; n5 = "\u2811";
    n6 = "\u280b"; n7 = "\u281b"; n8 = "\u2813"; n9 = "\u280a"; n0 = "\u281a";

    // punctuation
    pcom = "\u2802"; psem = "\u2806"; pcln = "\u2812";
    pdot = "\u2832"; pxcl = "\u2816"; pqst = "\u2826";
    past = "\u2814"; pdsh = "\u2804"; phyp = "\u2824";

    // formatting
    fcp = "\u2820"; fsp = "\u2800" | "\x20"; fnl = "\n" | "\n\r";

    <*> *      { out.err(); return; }
    <*> "\x00" { if (YYCURSOR != in.str + in.len + 1) out.err(); return; }

    <*> l :=> l
    <l> la { out.prt('a'); goto yyc_l; }
    <l> lb { out.prt('b'); goto yyc_l; }
    <l> lc { out.prt('c'); goto yyc_l; }
    <l> ld { out.prt('d'); goto yyc_l; }
    <l> le { out.prt('e'); goto yyc_l; }
    <l> lf { out.prt('f'); goto yyc_l; }
    <l> lg { out.prt('g'); goto yyc_l; }
    <l> lh { out.prt('h'); goto yyc_l; }
    <l> li { out.prt('i'); goto yyc_l; }
    <l> lj { out.prt('j'); goto yyc_l; }
    <l> lk { out.prt('k'); goto yyc_l; }
    <l> ll { out.prt('l'); goto yyc_l; }
    <l> lm { out.prt('m'); goto yyc_l; }
    <l> ln { out.prt('n'); goto yyc_l; }
    <l> lo { out.prt('o'); goto yyc_l; }
    <l> lp { out.prt('p'); goto yyc_l; }
    <l> lq { out.prt('q'); goto yyc_l; }
    <l> lr { out.prt('r'); goto yyc_l; }
    <l> ls { out.prt('s'); goto yyc_l; }
    <l> lt { out.prt('t'); goto yyc_l; }
    <l> lu { out.prt('u'); goto yyc_l; }
    <l> lv { out.prt('v'); goto yyc_l; }
    <l> lw { out.prt('w'); goto yyc_l; }
    <l> lx { out.prt('x'); goto yyc_l; }
    <l> ly { out.prt('y'); goto yyc_l; }
    <l> lz { out.prt('z'); goto yyc_l; }

    <*> n :=> n
    <n> n1 { out.prt('1'); goto yyc_n; }
    <n> n2 { out.prt('2'); goto yyc_n; }
    <n> n3 { out.prt('3'); goto yyc_n; }
    <n> n4 { out.prt('4'); goto yyc_n; }
    <n> n5 { out.prt('5'); goto yyc_n; }
    <n> n6 { out.prt('6'); goto yyc_n; }
    <n> n7 { out.prt('7'); goto yyc_n; }
    <n> n8 { out.prt('8'); goto yyc_n; }
    <n> n9 { out.prt('9'); goto yyc_n; }
    <n> n0 { out.prt('0'); goto yyc_n; }

    <*> pcom { out.prt(','); goto yyc_l; }
    <*> psem { out.prt(';'); goto yyc_l; }
    <*> pcln { out.prt(':'); goto yyc_l; }
    <*> pdot { out.prt('.'); goto yyc_l; }
    <*> pxcl { out.prt('!'); goto yyc_l; }
    <*> pqst { out.prt('?'); goto yyc_l; }
    <*> past { out.prt('*'); goto yyc_l; }
    <*> pdsh { out.prt('\''); goto yyc_l; }
    <*> phyp { out.prt('-'); goto yyc_l; }

    <*> fcp { out.caps = true; goto yyc_l; }
    <*> fsp { out.prt(' '); goto yyc_l; }
    <*> fnl { out.prt('\n'); goto yyc_l; }
*/

/*!types:re2c*/

static void lex_utf8(const iutf8_t & in)
{
    const unsigned char *YYCURSOR = in.str, *YYMARKER;
    int c = yycl;
    out_t out;
    /*!use:re2c
        re2c:define:YYCTYPE = "unsigned char";
        re2c:flags:8 = 1;
    */
}

static void lex_utf16(const iutf16_t & in)
{
    const unsigned short *YYCURSOR = in.str;
    int c = yycl;
    out_t out;
    /*!use:re2c
        re2c:define:YYCTYPE = "unsigned int";
        re2c:flags:x = 1;
    */
}

static void lex_utf32(const iutf32_t & in)
{
    const unsigned int *YYCURSOR = in.str;
    int c = yycl;
    out_t out;
    /*!use:re2c
        re2c:define:YYCTYPE = "unsigned int";
        re2c:flags:u = 1;
    */
}

static void lex_ucs2(const iucs2_t & in)
{
    const unsigned short *YYCURSOR = in.str;
    int c = yycl;
    out_t out;
    /*!use:re2c
        re2c:define:YYCTYPE = "unsigned int";
        re2c:flags:w = 1;
    */
}

int main()
{
    FILE *f;

    assert(f = fopen("braille.utf8.txt", "rb"));
    fprintf(stderr, "utf8:\n");
    iutf8_t in8(f);
    lex_utf8(in8);
    fclose(f);

    assert(f = fopen("braille.utf16.txt", "rb"));
    fprintf(stderr, "utf16:\n");
    iutf16_t in16(f);
    lex_utf16(in16);
    fclose(f);

    assert(f = fopen("braille.utf32.txt", "rb"));
    fprintf(stderr, "utf32:\n");
    iutf32_t in32(f);
    lex_utf32(in32);
    fclose(f);

    assert(f = fopen("braille.ucs2.txt", "rb"));
    fprintf(stderr, "ucs2:\n");
    iucs2_t in2(f);
    lex_ucs2(in2);
    fclose(f);

    return 0;
}
