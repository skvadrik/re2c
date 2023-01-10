// re2d $INPUT -o $OUTPUT -i

import core.stdc.string;
import core.stdc.stdio;



/*!max:re2c*/
enum SIZE = 64 * 1024;

struct input_t {
    char[SIZE + YYMAXFILL] buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    bool eof;

    FILE * file;

    this(FILE *f){
        lim = buf.ptr + SIZE;
        cur = lim;
        mar = lim;
        tok = lim;
        file = f;
    }

    bool fill(size_t need)
    {
        if (eof) {
            return false;
        }
        const size_t free = tok - buf.ptr;
        if (free < need) {
            return false;
        }
        memmove(buf.ptr, tok, lim - tok);
        lim -= free;
        cur -= free;
        mar -= free;
        tok -= free;
        lim += fread(lim, 1, free, file);
        if (lim < buf.ptr + SIZE) {
            eof = true;
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

/*!re2c re2c:define:YYCTYPE = "char"; */

bool adddgt(ulong base)(ref ulong u, ulong d)
{
    if (u > (ulong.max - d) / base) {
        return false;
    }
    u = u * base + d;
    return true;
}

bool lex_oct(const(char) *s, const(char) *e, ref ulong u)
{
    for (u = 0, ++s; s < e; ++s) {
        if (!adddgt!(8)(u, *s - 0x30u)) {
            return false;
        }
    }
    return true;
}

bool lex_dec(const(char) *s, const(char) *e, ref ulong u)
{
    for (u = 0; s < e; ++s) {
        if (!adddgt!(10)(u, *s - 0x30u)) {
            return false;
        }
    }
    return true;
}

bool lex_hex(const(char) *s, const(char) *e, ref ulong u)
{
    for (u = 0, s += 2; s < e;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        re2c:define:YYSKIP = 's++;';
        re2c:define:YYPEEK = '*s';
        *     { if (!adddgt!(16)(u, s[-1] - 0x30u))      return false; continue; }
        [a-f] { if (!adddgt!(16)(u, s[-1] - 0x61u + 10)) return false; continue; }
        [A-F] { if (!adddgt!(16)(u, s[-1] - 0x41u + 10)) return false; continue; }
    */
    }
    return true;
}

bool lex_str(ref input_t inp, char q)
{
    fprintf(stderr, "%c", q);
    for (ulong u = q;; fprintf(stderr, "\\x%lx", u)) {
        inp.tok = inp.cur;
        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = inp.cur;
            re2c:define:YYMARKER = inp.mar;
            re2c:define:YYLIMIT = inp.lim;
            re2c:define:YYPEEK = '*inp.cur';
            re2c:define:YYSKIP = 'inp.cur++;';
            re2c:define:YYBACKUP = 'inp.mar=inp.cur;';
            re2c:define:YYLESSTHAN = 'inp.lim <= inp.cur';
            re2c:define:YYRESTORE = 'inp.cur=inp.mar;';
            re2c:define:YYFILL = "if (!inp.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;
            *                    { return false; }
            [^\n\\]              { u = inp.tok[0]; if (u == q) break; continue; }
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
            "\\" [0-7]{1,3}      { lex_oct(inp.tok, inp.cur, u); continue; }
            "\\u" [0-9a-fA-F]{4} { lex_hex(inp.tok, inp.cur, u); continue; }
            "\\U" [0-9a-fA-F]{8} { lex_hex(inp.tok, inp.cur, u); continue; }
            "\\x" [0-9a-fA-F]+   { if (!lex_hex(inp.tok, inp.cur, u)) return false; continue; }
        */
    }
    fprintf(stderr, "%c", q);
    return true;
}

bool lex_flt(const(char) *s)
{
    double d = 0;
    double x = 1;
    int e = 0;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = s;
        re2c:define:YYPEEK = '*s';
        re2c:define:YYSKIP = 's++;';
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
        [fF]  { if (d > float.max) return false; goto end; }
    */
end:
    fprintf(stderr, "%g", d);
    return true;
}

bool lex(ref input_t inp)
{
    ulong u;
    for (;;) {
        inp.tok = inp.cur;
        /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = inp.cur;
            re2c:define:YYMARKER = inp.mar;
            re2c:define:YYLIMIT = inp.lim;
            re2c:define:YYPEEK = '*inp.cur';
            re2c:define:YYSKIP = '++inp.cur;';
            re2c:define:YYBACKUP = 'inp.mar=inp.cur;';
            re2c:define:YYLESSTHAN = 'inp.lim <= inp.cur';
            re2c:define:YYRESTORE = 'inp.cur=inp.mar;';
            re2c:define:YYFILL = "if (!inp.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;

            end = "\x00";

            *   { return false; }
            end {
                fprintf(stderr, "\n");
                return inp.lim - inp.tok == YYMAXFILL;
            }

            // macros
            macro = ("#" | "%:") ([^\n] | "\\\n")* "\n";
            macro { continue; }

            // whitespaces
            mcm = "/*" ([^*] | ("*" [^/]))* "*""/";
            scm = "//" [^\n]* "\n";
            wsp = ([ \t\v\n\r] | scm | mcm)+;
            wsp { fprintf(stderr, " "); continue; }

            // character and string literals
            "L"? ['"] { if (!lex_str(inp, inp.cur[-1])) return false; continue; }
            "L"? "''" { return false; }

            // integer literals
            oct = "0" [0-7]*;
            dec = [1-9][0-9]*;
            hex = '0x' [0-9a-fA-F]+;
            oct { if (!lex_oct(inp.tok, inp.cur, u)) return false; goto sfx; }
            dec { if (!lex_dec(inp.tok, inp.cur, u)) return false; goto sfx; }
            hex { if (!lex_hex(inp.tok, inp.cur, u)) return false; goto sfx; }

            // floating literals
            frc = [0-9]* "." [0-9]+ | [0-9]+ ".";
            exp = 'e' [+-]? [0-9]+;
            flt = (frc exp? | [0-9]+ exp) [fFlL]?;
            flt { if (lex_flt(inp.tok)) continue; return false; }

            // boolean literals
            "false" { fprintf(stderr, "false"); continue; }
            "true"  { fprintf(stderr, "true");  continue; }

            // keywords
            "asm"              { fprintf(stderr, "ASM");              continue; }
            "auto"             { fprintf(stderr, "AUTO");             continue; }
            "bool"             { fprintf(stderr, "BOOL");             continue; }
            "break"            { fprintf(stderr, "BREAK");            continue; }
            "case"             { fprintf(stderr, "CASE");             continue; }
            "catch"            { fprintf(stderr, "CATCH");            continue; }
            "char"             { fprintf(stderr, "CHAR");             continue; }
            "class"            { fprintf(stderr, "CLASS");            continue; }
            "const"            { fprintf(stderr, "CONST");            continue; }
            "const_cast"       { fprintf(stderr, "CONST_CAST");       continue; }
            "continue"         { fprintf(stderr, "CONTINUE");         continue; }
            "default"          { fprintf(stderr, "DEFAULT");          continue; }
            "do"               { fprintf(stderr, "DO");               continue; }
            "double"           { fprintf(stderr, "DOUBLE");           continue; }
            "dynamic_cast"     { fprintf(stderr, "DYNAMIC_CAST");     continue; }
            "else"             { fprintf(stderr, "ELSE");             continue; }
            "enum"             { fprintf(stderr, "ENUM");             continue; }
            "explicit"         { fprintf(stderr, "EXPLICIT");         continue; }
            "export"           { fprintf(stderr, "EXPORT");           continue; }
            "extern"           { fprintf(stderr, "EXTERN");           continue; }
            "float"            { fprintf(stderr, "FLOAT");            continue; }
            "for"              { fprintf(stderr, "FOR");              continue; }
            "friend"           { fprintf(stderr, "FRIEND");           continue; }
            "goto"             { fprintf(stderr, "GOTO");             continue; }
            "if"               { fprintf(stderr, "IF");               continue; }
            "inline"           { fprintf(stderr, "INLINE");           continue; }
            "int"              { fprintf(stderr, "INT");              continue; }
            "long"             { fprintf(stderr, "LONG");             continue; }
            "mutable"          { fprintf(stderr, "MUTABLE");          continue; }
            "namespace"        { fprintf(stderr, "NAMESPACE");        continue; }
            "operator"         { fprintf(stderr, "OPERATOR");         continue; }
            "private"          { fprintf(stderr, "PRIVATE");          continue; }
            "protected"        { fprintf(stderr, "PROTECTED");        continue; }
            "public"           { fprintf(stderr, "PUBLIC");           continue; }
            "register"         { fprintf(stderr, "REGISTER");         continue; }
            "reinterpret_cast" { fprintf(stderr, "REINTERPRET_CAST"); continue; }
            "return"           { fprintf(stderr, "RETURN");           continue; }
            "short"            { fprintf(stderr, "SHORT");            continue; }
            "signed"           { fprintf(stderr, "SIGNED");           continue; }
            "sizeof"           { fprintf(stderr, "SIZEOF");           continue; }
            "static"           { fprintf(stderr, "STATIC");           continue; }
            "static_cast"      { fprintf(stderr, "STATIC_CAST");      continue; }
            "struct"           { fprintf(stderr, "STRUCT");           continue; }
            "switch"           { fprintf(stderr, "SWITCH");           continue; }
            "template"         { fprintf(stderr, "TEMPLATE");         continue; }
            "this"             { fprintf(stderr, "THIS");             continue; }
            "throw"            { fprintf(stderr, "THROW");            continue; }
            "try"              { fprintf(stderr, "TRY");              continue; }
            "typedef"          { fprintf(stderr, "TYPEDEF");          continue; }
            "typeid"           { fprintf(stderr, "TYPEID");           continue; }
            "typename"         { fprintf(stderr, "TYPENAME");         continue; }
            "union"            { fprintf(stderr, "UNION");            continue; }
            "unsigned"         { fprintf(stderr, "UNSIGNED");         continue; }
            "using"            { fprintf(stderr, "USING");            continue; }
            "virtual"          { fprintf(stderr, "VIRTUAL");          continue; }
            "void"             { fprintf(stderr, "VOID");             continue; }
            "volatile"         { fprintf(stderr, "VOLATILE");         continue; }
            "wchar_t"          { fprintf(stderr, "WCHAR_T");          continue; }
            "while"            { fprintf(stderr, "WHILE");            continue; }

            // operators and punctuation (including preprocessor)
            ("{" | "<%")      { fprintf(stderr, "{");      continue; }
            ("}" | "%>")      { fprintf(stderr, "}");      continue; }
            ("[" | "<:")      { fprintf(stderr, "[");      continue; }
            ("]" | ":>")      { fprintf(stderr, "]");      continue; }
            "("               { fprintf(stderr, "(");      continue; }
            ")"               { fprintf(stderr, ")");      continue; }
            ";"               { fprintf(stderr, ";");      continue; }
            ":"               { fprintf(stderr, ":");      continue; }
            "..."             { fprintf(stderr, "...");    continue; }
            "new"             { fprintf(stderr, "new");    continue; }
            "delete"          { fprintf(stderr, "delete"); continue; }
            "?"               { fprintf(stderr, "?");      continue; }
            "::"              { fprintf(stderr, "::");     continue; }
            "."               { fprintf(stderr, ".");      continue; }
            ".*"              { fprintf(stderr, ".");      continue; }
            "+"               { fprintf(stderr, "+");      continue; }
            "-"               { fprintf(stderr, "-");      continue; }
            "*"               { fprintf(stderr, "*");      continue; }
            "/"               { fprintf(stderr, "/");      continue; }
            "%"               { fprintf(stderr, "%%");     continue; }
            ("^" | "xor")     { fprintf(stderr, "^");      continue; }
            ("&" | "bitand")  { fprintf(stderr, "&");      continue; }
            ("|" | "bitor")   { fprintf(stderr, "|");      continue; }
            ("~" | "compl")   { fprintf(stderr, "~");      continue; }
            ("!" | "not")     { fprintf(stderr, "!");      continue; }
            "="               { fprintf(stderr, "=");      continue; }
            "<"               { fprintf(stderr, "<");      continue; }
            ">"               { fprintf(stderr, ">");      continue; }
            "+="              { fprintf(stderr, "+=");     continue; }
            "-="              { fprintf(stderr, "-=");     continue; }
            "*="              { fprintf(stderr, "*=");     continue; }
            "/="              { fprintf(stderr, "/=");     continue; }
            "%="              { fprintf(stderr, "%%=");    continue; }
            ("^=" | "xor_eq") { fprintf(stderr, "^=");     continue; }
            ("&=" | "and_eq") { fprintf(stderr, "&=");     continue; }
            ("|=" | "or_eq")  { fprintf(stderr, "|=");     continue; }
            "<<"              { fprintf(stderr, "<<");     continue; }
            ">>"              { fprintf(stderr, ">>");     continue; }
            ">>="             { fprintf(stderr, ">>=");    continue; }
            "<<="             { fprintf(stderr, "<<=");    continue; }
            "=="              { fprintf(stderr, "==");     continue; }
            ("!=" | "not_eq") { fprintf(stderr, "!=");     continue; }
            "<="              { fprintf(stderr, "<=");     continue; }
            ">="              { fprintf(stderr, ">=");     continue; }
            ("&&" | "and")    { fprintf(stderr, "&&");     continue; }
            ("||" | "or")     { fprintf(stderr, "||");     continue; }
            "++"              { fprintf(stderr, "++");     continue; }
            "--"              { fprintf(stderr, "--");     continue; }
            ","               { fprintf(stderr, ",");      continue; }
            "->*"             { fprintf(stderr, "->*");    continue; }
            "->"              { fprintf(stderr, "->");     continue; }

            // identifiers
            id = [a-zA-Z_][a-zA-Z_0-9]*;
            id { fprintf(stderr, "%.*s", cast(int)(inp.cur - inp.tok), inp.tok); continue; }
        */
sfx:
        /*!re2c
            ""          { if (u > int.max)  return false; fprintf(stderr, "%d",  cast(int)(u));      continue; }
            'u'         { if (u > uint.max) return false; fprintf(stderr, "%u",  cast(uint)(u)); continue; }
            'l'         { if (u > long.max) return false; fprintf(stderr, "%ld", cast(long)(u));     continue; }
            'ul' | 'lu' { fprintf(stderr, "%lu", u); continue; }
        */
    }
    assert(0);
}

unittest
{
    const char *fname = "example.cpp";
    FILE *f;

    // prepare input file
    f = fopen(fname, "w");
    fprintf(f,
        `
#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number:\n");
    scanf("%%d", &n);

    int f = 1;
    for(int i = 1; i <= n; ++i) {
        f *= i;
    }

    printf("Factorial of %%d is %%d\n", n, f);
    return 0;
}
        `);
    fclose(f);

    f = fopen(fname, "rb");
    input_t inp = input_t(f);
    assert(lex(inp));
    fclose(f);

    // cleanup
    remove(fname);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}


