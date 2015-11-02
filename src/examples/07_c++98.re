#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
static const size_t SIZE = 64 * 1024;

struct input_t {
    unsigned char buf[SIZE + YYMAXFILL];
    unsigned char *lim;
    unsigned char *cur;
    unsigned char *mar;
    unsigned char *tok;
    bool eof;

    FILE *const file;

    input_t(FILE *f)
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , mar(lim)
        , tok(lim)
        , eof(false)
        , file(f)
    {}
    bool fill(size_t need)
    {
        if (eof) {
            return false;
        }

        const size_t free = tok - buf;
        if (free < need) {
            return false;
        }

        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        mar -= free;
        tok -= free;
        lim += fread(lim, 1, free, file);
        if (lim < buf + SIZE) {
            eof = true;
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

/*!re2c re2c:define:YYCTYPE = "unsigned char"; */

template<int base>
static bool adddgt(unsigned long &u, unsigned long d)
{
    if (u > (ULONG_MAX - d) / base) {
        return false;
    }
    u = u * base + d;
    return true;
}

static bool lex_int_sfx(const unsigned char *s, unsigned long u)
{
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        *           { return u < INT_MAX; }
        'u'         { return u < UINT_MAX; }
        'l'         { return u < LONG_MAX; }
        'ul' | 'lu' { return true; }
    */
}

static bool lex_oct(const unsigned char *s, bool sfx, unsigned long &u)
{
    for (u = 0, ++s;;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        [0-7] { if (adddgt<8>(u, s[-1] - 0x30u)) continue; return false; }
        ""    { return !sfx || lex_int_sfx(s, u); }
    */
    }
}

static bool lex_dec(const unsigned char *s, bool sfx, unsigned long &u)
{
    for (u = 0;;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        [0-9] { if (adddgt<10>(u, s[-1] - 0x30u)) continue; return false; }
        ""    { return !sfx || lex_int_sfx(s, u); }
    */
    }
}

static bool lex_hex(const unsigned char *s, bool sfx, unsigned long &u)
{
    for (u = 0, s += 2;;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        [0-9] { if (adddgt<16>(u, s[-1] - 0x30u))      continue; return false; }
        [a-f] { if (adddgt<16>(u, s[-1] - 0x61u + 10)) continue; return false; }
        [A-F] { if (adddgt<16>(u, s[-1] - 0x41u + 10)) continue; return false; }
        ""    { return !sfx || lex_int_sfx(s, u); }
    */
    }
}

static bool lex_str(input_t &in, unsigned char q)
{
    printf("%c", q);
    for (unsigned long u = q;; printf("\\x%lx", u)) {
        in.tok = in.cur;
        /*!re2c
            re2c:define:YYCURSOR = in.cur;
            re2c:define:YYMARKER = in.mar;
            re2c:define:YYLIMIT = in.lim;
            re2c:yyfill:enable = 1;
            re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;
            *                    { return false; }
            [^\n\\]              { u = in.tok[0]; if (u == q) break; continue; }
            "\\a"                { u = '\a'; continue; }
            "\\b"                { u = '\b'; continue; }
            "\\f"                { u = '\f'; continue; }
            "\\n"                { u = '\n'; continue; }
            "\\r"                { u = '\r'; continue; }
            "\\t"                { u = '\t'; continue; }
            "\\v"                { u = '\v'; continue; }
            "\\\\"               { u = '\\'; continue; }
            "\\'"                { u = '\''; continue; }
            "\\\""               { u = '"';  continue; }
            "\\?"                { u = '?';  continue; }
            "\\" [0-7]{1,3}      { lex_oct(in.tok, false, u); continue; }
            "\\u" [0-9a-fA-F]{4} { lex_hex(in.tok, false, u); continue; }
            "\\U" [0-9a-fA-F]{8} { lex_hex(in.tok, false, u); continue; }
            "\\x" [0-9a-fA-F]+   { if (!lex_hex(in.tok, false, u)) return false; continue; }
        */
    }
    printf("%c", q);
    return true;
}

static bool lex_flt(const unsigned char *s)
{
    double d = 0;
    double x = 1;
    int e = 0;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
    */
mant_int:
    /*!re2c
        "."   { goto mant_frac; }
        [eE]  { goto exp_sign; }
        *     { d = (d * 10) + (s[-1] - '0'); goto mant_int; }
    */
mant_frac:
    /*!re2c
        ""    { goto sfx; }
        [eE]  { goto exp_sign; }
        [0-9] { d += (x /= 10) * (s[-1] - '0'); goto mant_frac; }
    */
exp_sign:
    /*!re2c
        "+"?  { x = 1e+1; goto exp; }
        "-"   { x = 1e-1; goto exp; }
    */
exp:
    /*!re2c
        ""    { for (; e > 0; --e) d *= x;    goto sfx; }
        [0-9] { e = (e * 10) + (s[-1] - '0'); goto exp; }
    */
sfx:
    /*!re2c
        *     { goto end; }
        [fF]  { if (d > FLT_MAX) return false; goto end; }
    */
end:
    printf("%g", d);
    return true;
}

static bool lex(input_t &in)
{
    unsigned long u;
    for (;;) {
        in.tok = in.cur;
        /*!re2c
            re2c:define:YYCURSOR = in.cur;
            re2c:define:YYMARKER = in.mar;
            re2c:define:YYLIMIT = in.lim;
            re2c:yyfill:enable = 1;
            re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;

            end = "\x00";

            *   { return false; }
            end { return in.lim - in.tok == YYMAXFILL; }

            // macros
            macro = ("#" | "%:") ([^\n] | "\\\n")* "\n";
            macro { continue; }

            // whitespaces
            mcm = "/*" ([^*] | ("*" [^/]))* "*""/";
            scm = "//" [^\n]* "\n";
            wsp = ([ \t\v\n\r] | scm | mcm)+;
            wsp { printf(" "); continue; }

            // character and string literals
            "L"? ['"] { if (!lex_str(in, in.cur[-1])) return false; continue; }
            "L"? "''" { return false; }

            // integer literals
            int_sfx = 'u' | 'l' | 'ul' | 'lu';
            oct = "0" [0-7]*        int_sfx?;
            dec = [1-9][0-9]*       int_sfx?;
            hex = '0x' [0-9a-fA-F]+ int_sfx?;
            oct { if (!lex_oct(in.tok, true, u)) return false; printf("%lu", u); continue; }
            dec { if (!lex_dec(in.tok, true, u)) return false; printf("%lu", u); continue; }
            hex { if (!lex_hex(in.tok, true, u)) return false; printf("%lu", u); continue; }

            // floating literals
            frc = [0-9]* "." [0-9]+ | [0-9]+ ".";
            exp = 'e' [+-]? [0-9]+;
            flt = (frc exp? | [0-9]+ exp) [fFlL]?;
            flt { if (lex_flt(in.tok)) continue; return false; }

            // boolean literals
            "false" { printf("false"); continue; }
            "true"  { printf("true");  continue; }

            // keywords
            "asm"              { printf("ASM");              continue; }
            "auto"             { printf("AUTO");             continue; }
            "bool"             { printf("BOOL");             continue; }
            "break"            { printf("BREAK");            continue; }
            "case"             { printf("CASE");             continue; }
            "catch"            { printf("CATCH");            continue; }
            "char"             { printf("CHAR");             continue; }
            "class"            { printf("CLASS");            continue; }
            "const"            { printf("CONST");            continue; }
            "const_cast"       { printf("CONST_CAST");       continue; }
            "continue"         { printf("CONTINUE");         continue; }
            "default"          { printf("DEFAULT");          continue; }
            "do"               { printf("DO");               continue; }
            "double"           { printf("DOUBLE");           continue; }
            "dynamic_cast"     { printf("DYNAMIC_CAST");     continue; }
            "else"             { printf("ELSE");             continue; }
            "enum"             { printf("ENUM");             continue; }
            "explicit"         { printf("EXPLICIT");         continue; }
            "export"           { printf("EXPORT");           continue; }
            "extern"           { printf("EXTERN");           continue; }
            "float"            { printf("FLOAT");            continue; }
            "for"              { printf("FOR");              continue; }
            "friend"           { printf("FRIEND");           continue; }
            "goto"             { printf("GOTO");             continue; }
            "if"               { printf("IF");               continue; }
            "inline"           { printf("INLINE");           continue; }
            "int"              { printf("INT");              continue; }
            "long"             { printf("LONG");             continue; }
            "mutable"          { printf("MUTABLE");          continue; }
            "namespace"        { printf("NAMESPACE");        continue; }
            "operator"         { printf("OPERATOR");         continue; }
            "private"          { printf("PRIVATE");          continue; }
            "protected"        { printf("PROTECTED");        continue; }
            "public"           { printf("PUBLIC");           continue; }
            "register"         { printf("REGISTER");         continue; }
            "reinterpret_cast" { printf("REINTERPRET_CAST"); continue; }
            "return"           { printf("RETURN");           continue; }
            "short"            { printf("SHORT");            continue; }
            "signed"           { printf("SIGNED");           continue; }
            "sizeof"           { printf("SIZEOF");           continue; }
            "static"           { printf("STATIC");           continue; }
            "static_cast"      { printf("STATIC_CAST");      continue; }
            "struct"           { printf("STRUCT");           continue; }
            "switch"           { printf("SWITCH");           continue; }
            "template"         { printf("TEMPLATE");         continue; }
            "this"             { printf("THIS");             continue; }
            "throw"            { printf("THROW");            continue; }
            "try"              { printf("TRY");              continue; }
            "typedef"          { printf("TYPEDEF");          continue; }
            "typeid"           { printf("TYPEID");           continue; }
            "typename"         { printf("TYPENAME");         continue; }
            "union"            { printf("UNION");            continue; }
            "unsigned"         { printf("UNSIGNED");         continue; }
            "using"            { printf("USING");            continue; }
            "virtual"          { printf("VIRTUAL");          continue; }
            "void"             { printf("VOID");             continue; }
            "volatile"         { printf("VOLATILE");         continue; }
            "wchar_t"          { printf("WCHAR_T");          continue; }
            "while"            { printf("WHILE");            continue; }

            // operators and punctuation (including preprocessor)
            ("{" | "<%")      { printf("{");      continue; }
            ("}" | "%>")      { printf("}");      continue; }
            ("[" | "<:")      { printf("[");      continue; }
            ("]" | ":>")      { printf("]");      continue; }
            "("               { printf("(");      continue; }
            ")"               { printf(")");      continue; }
            ";"               { printf(";");      continue; }
            ":"               { printf(":");      continue; }
            "..."             { printf("...");    continue; }
            "new"             { printf("new");    continue; }
            "delete"          { printf("delete"); continue; }
            "?"               { printf("?");      continue; }
            "::"              { printf("::");     continue; }
            "."               { printf(".");      continue; }
            ".*"              { printf(".");      continue; }
            "+"               { printf("+");      continue; }
            "-"               { printf("-");      continue; }
            "*"               { printf("*");      continue; }
            "/"               { printf("/");      continue; }
            "%"               { printf("%%");     continue; }
            ("^" | "xor")     { printf("^");      continue; }
            ("&" | "bitand")  { printf("&");      continue; }
            ("|" | "bitor")   { printf("|");      continue; }
            ("~" | "compl")   { printf("~");      continue; }
            ("!" | "not")     { printf("!");      continue; }
            "="               { printf("=");      continue; }
            "<"               { printf("<");      continue; }
            ">"               { printf(">");      continue; }
            "+="              { printf("+=");     continue; }
            "-="              { printf("-=");     continue; }
            "*="              { printf("*=");     continue; }
            "/="              { printf("/=");     continue; }
            "%="              { printf("%%=");    continue; }
            ("^=" | "xor_eq") { printf("^=");     continue; }
            ("&=" | "and_eq") { printf("&=");     continue; }
            ("|=" | "or_eq")  { printf("|=");     continue; }
            "<<"              { printf("<<");     continue; }
            ">>"              { printf(">>");     continue; }
            ">>="             { printf(">>=");    continue; }
            "<<="             { printf("<<=");    continue; }
            "=="              { printf("==");     continue; }
            ("!=" | "not_eq") { printf("!=");     continue; }
            "<="              { printf("<=");     continue; }
            ">="              { printf(">=");     continue; }
            ("&&" | "and")    { printf("&&");     continue; }
            ("||" | "or")     { printf("||");     continue; }
            "++"              { printf("++");     continue; }
            "--"              { printf("--");     continue; }
            ","               { printf(",");      continue; }
            "->*"             { printf("->*");    continue; }
            "->"              { printf("->");     continue; }

            // identifiers
            id = [a-zA-Z_][a-zA-Z_0-9]*;
            id { printf("%.*s", in.cur - in.tok, in.tok); continue; }
        */
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf ("usage: ./example <filename>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("error: cannot open file: %s\n", argv[1]);
        return 1;
    }

    input_t in(file);
    if (!lex(in)) {
        printf("... error\n");
    } else {
        printf("\n");
    }

    fclose(file);
    return 0;
}
