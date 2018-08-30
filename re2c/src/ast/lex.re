#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <string.h>
#include <algorithm>
#include <limits>
#include <string>

#include "src/conf/msg.h"
#include "src/code/output.h"
#include "src/re/encoding/enc.h"
#include "src/ast/input.h"
#include "src/ast/ast.h"
#include "src/ast/scanner.h"
#include "src/ast/parser.h" // needed by "y.tab.h"
#include "src/ast/unescape.h"
#include "src/util/range.h"
#include "src/util/s_to_n32_unsafe.h"
#include "src/util/string_utils.h"
#include "y.tab.h"

extern YYSTYPE yylval;

#define    YYCTYPE        unsigned char
#define    YYCURSOR    cur
#define    YYLIMIT        lim
#define    YYMARKER    mar
#define    YYCTXMARKER    ctx
#define    YYFILL(n)    { fill (n); }

namespace re2c
{

// source code is in ASCII: pointers have type 'char *'
// but re2c makes an implicit assumption that YYCTYPE is unsigned
// when it generates comparisons
/*!re2c
    re2c:yych:conversion = 1;
*/

/*!re2c
eof     = "\000";
dstring = "\"" ((. \ [\\"] ) | "\\" .)* "\"";
sstring = "'"  ((. \ [\\'] ) | "\\" .)* "'" ;
letter  = [a-zA-Z];
digit   = [0-9];
lineno  = [1-9] digit*;
name    = (letter|"_") (letter|digit|"_")*;
space   = [ \t];
ws      = (space | [\r\n]);
eol     = "\r"? "\n";
eoc     = "*" "/";
lineinf = lineno (space+ dstring)? eol;

    esc = "\\";
    hex_digit = [0-9a-fA-F];
    esc_hex = esc ("x" hex_digit{2} | [uX] hex_digit{4} | "U" hex_digit{8});
    esc_oct = esc [0-3] [0-7]{2}; // max 1-byte octal value is '\377'
    esc_simple = esc [abfnrtv\\];
*/

Scanner::ParseMode Scanner::echo(OutputFile &out)
{
    if (eof && cur == eof) // Catch EOF
    {
        return Stop;
    }

    tok = cur;
echo:
    ptr = cur;

/*!re2c
    "%{" | "/*!re2c" {
        out.wraw(tok, ptr);
        return Parse;
    }

    "/*!rules:re2c" {
        out.wraw(tok, ptr);
        return Rules;
    }

    "/*!use:re2c" {
        out.wraw(tok, ptr);
        return Reuse;
    }

    "/*!ignore:re2c" {
        out.wraw(tok, ptr);
        lex_end_of_comment(out);
        goto echo;
    }

    "/*!max:re2c" {
        out.wraw(tok, ptr);
        out.wdelay_yymaxfill();
        lex_end_of_comment(out);
        goto echo;
    }

    "/*!maxnmatch:re2c" {
        out.wraw(tok, ptr);
        out.wdelay_yymaxnmatch();
        lex_end_of_comment(out);
        goto echo;
    }

    "/*!getstate:re2c" {
        out.wraw(tok, ptr);
        out.wdelay_state_goto(0);
        lex_end_of_comment(out);
        goto echo;
    }

    "/*!types:re2c" {
        out.wraw(tok, ptr);
        out.wdelay_line_info_output();
        out.wdelay_types();
        out.wdelay_line_info_input(cline, get_fname());
        lex_end_of_comment(out);
        goto echo;
    }

    "/*!stags:re2c" {
        out.wraw(tok, ptr);
        lex_tags(out, false);
        goto echo;
    }

    "/*!mtags:re2c" {
        out.wraw(tok, ptr);
        lex_tags(out, true);
        goto echo;
    }

    eof {
        if (cur != eof) goto echo;
        out.wraw(tok, ptr);
        return Stop;
    }

    eol space* "#" space* "line" space+ / lineinf {
        out.wraw(tok, ptr + 1);
        set_sourceline();
        goto echo;
    }

    eol {
        cline++;
        pos = cur;
        goto echo;
    }

    * { goto echo; }
*/
}

void Scanner::lex_end_of_comment(OutputFile &out)
{
    uint32_t ignored = 0;
    for (;;) {/*!re2c
        eof { fatal_lc(get_cline(), get_column(), "expected end of block"); }

        *    { continue; }
        eol  { ++ignored; continue; }
        eoc  {
            if (ignored > 0) {
                cline += ignored;
                out.wdelay_line_info_input(cline, get_fname());
            }
            tok = pos = cur;
            return;
        }
    */}
}

void Scanner::lex_tags(OutputFile &out, bool mtags)
{
    std::string fmt, sep;
    for (;;) {/*!re2c
        * { fatal_lc(get_cline(), get_column(), "unrecognized configuration"); }

        "format"    { fmt = lex_conf_string(); continue; }
        "separator" { sep = lex_conf_string(); continue; }

        space+ { continue; }
        eol    { ++cline; continue; }
        eoc    {
            out.wdelay_tags(new ConfTags(fmt, sep), mtags);
            tok = pos = cur;
            return;
        }
    */}
}

int Scanner::scan(const conopt_t *globopts)
{
    uint32_t depth, code_line;
scan:
    tchar = cur - pos;
    tok = cur;
/*!re2c
    "{"            {
                    depth = 1;
                    code_line = cline;
                    goto code;
                }

    ":" / "=>"    {
                    return *tok;
                }

    ":="        {
                    tok += 2; /* skip ":=" */
                    depth = 0;
                    code_line = cline;
                    goto code;
                }

        "//"            {
                goto nextLine;
            }
    "/*"        {
                    depth = 1;
                    goto comment;
                }

   endRE    =  "%}" | "*/";
   endRE    {
                    tok = cur;
                    return 0;
                }

    "'"  { yylval.regexp = lex_str('\''); return TOKEN_REGEXP; }
    "\"" { yylval.regexp = lex_str('"'); return TOKEN_REGEXP; }
    "["  { yylval.regexp = lex_cls(false); return TOKEN_REGEXP; }
    "[^" { yylval.regexp = lex_cls(true);  return TOKEN_REGEXP; }

    [@#] name {
        const std::string *name = new std::string(tok + 1, tok_len() - 1);
        yylval.regexp = ast_tag(cline, get_column(), name, tok[0] == '#');
        return TOKEN_REGEXP;
    }

    [*+?<>!,()|=;/\\] { return *tok; }

    "{" [0-9]+ "}"    {
                    if (!s_to_u32_unsafe (tok + 1, cur - 1, yylval.bounds.min))
                    {
                        fatal_lc(get_cline(), get_column(), "repetition count overflow");
                    }
                    yylval.bounds.max = yylval.bounds.min;
                    return TOKEN_CLOSESIZE;
                }

    "{" [0-9]+ "," [0-9]+ "}"    {
                    const char * p = strchr (tok, ',');
                    if (!s_to_u32_unsafe (tok + 1, p, yylval.bounds.min))
                    {
                        fatal_lc(get_cline(), get_column(), "repetition lower bound overflow");
                    }
                    if (!s_to_u32_unsafe (p + 1, cur - 1, yylval.bounds.max))
                    {
                        fatal_lc(get_cline(), get_column(), "repetition upper bound overflow");
                    }
                    return TOKEN_CLOSESIZE;
                }

    "{" [0-9]+ ",}"        {
                    if (!s_to_u32_unsafe (tok + 1, cur - 2, yylval.bounds.min))
                    {
                        fatal_lc(get_cline(), get_column(), "repetition lower bound overflow");
                    }
                    yylval.bounds.max = std::numeric_limits<uint32_t>::max();
                    return TOKEN_CLOSESIZE;
                }

    "{" [0-9]* ","        {
                    fatal_lc(get_cline(), get_column(), "illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers");
                }

    "{" name "}"    {
                    if (!globopts->FFlag) {
                        fatal_lc(get_cline(), get_column(), "curly braces for names only allowed with -F switch");
                    }
                    yylval.str = new std::string (tok + 1, tok_len () - 2); // -2 to omit braces
                    return TOKEN_ID;
                }

    "re2c:" { return TOKEN_CONF; }

    name / (space+ [^=>,])    {
                    yylval.str = new std::string (tok, tok_len ());
                    if (globopts->FFlag)
                    {
                        lexer_state = LEX_FLEX_NAME;
                        return TOKEN_FID;
                    }
                    else
                    {
                        return TOKEN_ID;
                    }
                }

    name / (space* [=>,])    {
                    yylval.str = new std::string (tok, tok_len ());
                    return TOKEN_ID;
                }

    name / [^]    {
                    if (!globopts->FFlag) {
                        yylval.str = new std::string (tok, tok_len());
                        return TOKEN_ID;
                    } else {
                        std::vector<ASTChar> *str = new std::vector<ASTChar>;
                        for (char *s = tok; s < cur; ++s) {
                            const uint32_t
                                chr = static_cast<uint8_t>(*s),
                                col = static_cast<uint32_t>(s - tok);
                            str->push_back(ASTChar(chr, col));
                        }
                        yylval.regexp = ast_str(cline, get_column(), str, false);
                        return TOKEN_REGEXP;
                    }
                }

    "."            {
                    yylval.regexp = ast_dot(cline, get_column());
                    return TOKEN_REGEXP;
                }

    space+        {
                    goto scan;
                }

    eol space* "#" space* "line" space+ / lineinf {
        set_sourceline ();
        return TOKEN_LINE_INFO;
    }

    eol {
        if (cur == eof) return 0;
        pos = cur;
        cline++;
        if (lexer_state == LEX_FLEX_NAME) {
            lexer_state = LEX_NORMAL;
            return TOKEN_FID_END;
        } else {
            goto scan;
        }
    }

    *            {
                    fatal_lc(get_cline(), get_column(), "unexpected character: '%c'", *tok);
                    goto scan;
                }
*/

code:
/*!re2c
    "}"            {
                    if (depth == 0)
                    {
                        fatal_l(get_cline(), "Curly braces are not allowed after ':='");
                    }
                    else if (--depth == 0)
                    {
                        yylval.code = new Code(get_fname (), code_line, tok, tok_len ());
                        return TOKEN_CODE;
                    }
                    goto code;
                }
    "{"            {
                    if (depth == 0)
                    {
                        fatal_l(get_cline(), "Curly braces are not allowed after ':='");
                    }
                    else
                    {
                        ++depth;
                    }
                    goto code;
                }
    "\n" space* "#" space* "line" space+ / lineinf {
                    set_sourceline ();
                    goto code;
                }
    "\n" /  ws    {
                    if (depth == 0)
                    {
                        goto code;
                    }
                    else if (cur == eof)
                    {
                        fatal_l(get_cline(), "missing '}'");
                    }
                    pos = cur;
                    cline++;
                    goto code;
                }
    "\n"        {
                    if (depth == 0)
                    {
                        tok += strspn(tok, " \t\r\n");
                        while (cur > tok && strchr(" \t\r\n", cur[-1]))
                        {
                            --cur;
                        }
                        yylval.code = new Code(get_fname (), code_line, tok, tok_len ());
                        return TOKEN_CODE;
                    }
                    else if (cur == eof)
                    {
                        fatal_l(get_cline(), "missing '}'");
                    }
                    pos = cur;
                    cline++;
                    goto code;
                }
    eof        {
                    if (cur == eof)
                    {
                        if (depth)
                        {
                            fatal_l(get_cline(), "missing '}'");
                        }
                        return 0;
                    }
                    goto code;
                }
    dstring | sstring    {
                    goto code;
                }
    *            {
                    goto code;
                }
*/

comment:
/*!re2c
    "*" "/"        {
                    if (--depth == 0)
                    {
                        goto scan;
                    }
                    else
                    {
                        goto comment;
                    }
                }
    "/" "*"        {
                    ++depth;
                    fatal_lc(get_cline(), get_column(), "ambiguous /* found");
                    goto comment;
                }
    "\n" space* "#" space* "line" space+ / lineinf {
                    set_sourceline ();
                    goto comment;
                }
    "\n"        {
                    if (cur == eof)
                    {
                        return 0;
                    }
                    tok = pos = cur;
                    cline++;
                    goto comment;
                }
    *            {
                    if (cur == eof)
                    {
                        return 0;
                    }
                    goto comment;
                }
*/

nextLine:
/*!re2c                                  /* resync emacs */
   "\n"     { if(cur == eof) {
                  return 0;
               }
               tok = pos = cur;
               cline++;
               goto scan;
            }
   *        {  if(cur == eof) {
                  return 0;
               }
               goto nextLine;
            }
*/
}

const AST *Scanner::lex_cls(bool neg)
{
    std::vector<ASTRange> *cls = new std::vector<ASTRange>;
    uint32_t u, l, c, c0 = get_column();
fst:
    tok = cur;
    c = get_column();
    /*!re2c
        "]" { return ast_cls(cline, c0, cls, neg); }
        ""  { l = lex_cls_chr(); goto snd; }
    */
snd:
    /*!re2c
        ""          { u = l; goto add; }
        "-" / [^\]] {
            u = lex_cls_chr();
            if (l > u) {
                warn.swapped_range(cline, l, u);
                std::swap(l, u);
            }
            goto add;
        }
    */
add:
    cls->push_back(ASTRange(l, u, c));
    goto fst;
}

uint32_t Scanner::lex_cls_chr()
{
    tok = cur;
    const uint32_t l = get_cline(), c = get_column();
    /*!re2c
        *          { fatal_lc(l, c, "syntax error"); }
        esc? eol   { fatal_lc(l, c, "newline in character class"); }
        esc [xXuU] { fatal_lc(l, c, "syntax error in hexadecimal escape sequence"); }
        esc [0-7]  { fatal_lc(l, c, "syntax error in octal escape sequence"); }
        esc        { fatal_lc(l, c, "syntax error in escape sequence"); }

        . \ esc    { return static_cast<uint8_t>(tok[0]); }
        esc_hex    { return unesc_hex(tok, cur); }
        esc_oct    { return unesc_oct(tok, cur); }
        esc "a"    { return static_cast<uint8_t>('\a'); }
        esc "b"    { return static_cast<uint8_t>('\b'); }
        esc "f"    { return static_cast<uint8_t>('\f'); }
        esc "n"    { return static_cast<uint8_t>('\n'); }
        esc "r"    { return static_cast<uint8_t>('\r'); }
        esc "t"    { return static_cast<uint8_t>('\t'); }
        esc "v"    { return static_cast<uint8_t>('\v'); }
        esc "\\"   { return static_cast<uint8_t>('\\'); }
        esc "-"    { return static_cast<uint8_t>('-'); }
        esc "]"    { return static_cast<uint8_t>(']'); }
        esc .      {
            warn.useless_escape(cline, get_column(), tok[1]);
            return static_cast<uint8_t>(tok[1]);
        }
    */
}

uint32_t Scanner::lex_str_chr(char quote, bool &end)
{
    end = false;
    tok = cur;
    const uint32_t l = get_cline(), c = get_column();
    /*!re2c
        *          { fatal_lc(l, c, "syntax error"); }
        esc? eol   { fatal_lc(l, c, "newline in character string"); }
        esc [xXuU] { fatal_lc(l, c, "syntax error in hexadecimal escape sequence"); }
        esc [0-7]  { fatal_lc(l, c, "syntax error in octal escape sequence"); }
        esc        { fatal_lc(l, c, "syntax error in escape sequence"); }

        . \ esc    {
            end = tok[0] == quote;
            return static_cast<uint8_t>(tok[0]);
        }
        esc_hex    { return unesc_hex(tok, cur); }
        esc_oct    { return unesc_oct(tok, cur); }
        esc "a"    { return static_cast<uint8_t>('\a'); }
        esc "b"    { return static_cast<uint8_t>('\b'); }
        esc "f"    { return static_cast<uint8_t>('\f'); }
        esc "n"    { return static_cast<uint8_t>('\n'); }
        esc "r"    { return static_cast<uint8_t>('\r'); }
        esc "t"    { return static_cast<uint8_t>('\t'); }
        esc "v"    { return static_cast<uint8_t>('\v'); }
        esc "\\"   { return static_cast<uint8_t>('\\'); }
        esc .      {
            if (tok[1] != quote) {
                warn.useless_escape(cline, get_column(), tok[1]);
            }
            return static_cast<uint8_t>(tok[1]);
        }
    */
}

const AST *Scanner::lex_str(char quote)
{
    const uint32_t column = get_column();
    std::vector<ASTChar> *str = new std::vector<ASTChar>;
    for (bool end;;) {
        const uint32_t c = lex_str_chr(quote, end);
        if (end) return ast_str(cline, column, str, quote == '\'');
        str->push_back(ASTChar(c, get_column()));
    }
}

void Scanner::set_sourceline ()
{
sourceline:
    tok = cur;
/*!re2c    
    lineno {
        if (!s_to_u32_unsafe (tok, cur, cline)) {
            fatal_lc(get_cline(), get_column(), "line number overflow");
        }
        goto sourceline;
    }

    dstring {
        in.escaped_file_name = std::string (tok + 1, tok_len () - 2); // strip quotes
        strrreplace (in.escaped_file_name, "\\", "\\\\");
        goto sourceline;
    }

    eol {
        tok = cur;
        return;
    }

    eof {
        --cur;
        tok = cur;
        return;
    }

    * { goto sourceline; }
*/
}

} // end namespace re2c
