#include <stdio.h>

#include "src/util/c99_stdint.h"

#include "src/encoding/enc.h"
#include "src/parse/ast.h"
#include "src/parse/unescape.h"
#include "src/util/range.h"
#include "src/util/s_to_n32_unsafe.h"
#include "parse.h"
#include "lib/lex.h"


extern YYSTYPE yylval;

namespace re2c {

static int32_t lex_cls_chr(const char *&, uint32_t &);

/*!re2c
    re2c:flags:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYMARKER = mar;
    re2c:define:YYCTYPE = char;

    nil = "\x00";
    num = [0-9]+;
*/

int lex(const char *&cur)
{
    /*!stags:re2c format = "const char *@@;"; */
    const char *mar, *x, *y;
    std::vector<ASTRange> cls;
    bool neg = false;
    uint32_t l, u;

/*!re2c
    * { goto err; }

    nil { return 0; }

    [()|*+?] { return cur[-1]; }

    [$^] {
        error("anchors are not supported");
        return TOKEN_ERROR;
    }

    "[^" { neg = true; goto cls; }
    "["  { goto cls; }

    "{" @x num "}" {
        if (!s_to_u32_unsafe(x, cur - 1, yylval.bounds.min)) goto err_cnt;
        yylval.bounds.max = yylval.bounds.min;
        return TOKEN_COUNT;
    }

    "{" @x num "," @y num "}" {
        if (!s_to_u32_unsafe(x, y - 1, yylval.bounds.min)
            || !s_to_u32_unsafe(y, cur - 1, yylval.bounds.max)) goto err_cnt;
        return TOKEN_COUNT;
    }

    "{" @x num ",}" {
        if (!s_to_u32_unsafe(x, cur - 2, yylval.bounds.min)) goto err_cnt;
        yylval.bounds.max = AST::MANY;
        return TOKEN_COUNT;
    }

    "." {
        yylval.regexp = ast_dot(NOWHERE);
        return TOKEN_REGEXP;
    }

    [^] \ nil {
        ASTChar c = {static_cast<uint32_t>(cur[-1]), NOWHERE};
        std::vector<ASTChar> *str = new std::vector<ASTChar>;
        str->push_back(c);
        yylval.regexp = ast_str(NOWHERE, str, false);
        return TOKEN_REGEXP;
    }
*/

cls:
    if (lex_cls_chr(cur, l) != 0) goto err;
/*!re2c
    ""          { u = l; goto add; }
    "-" / [^\]] { if (lex_cls_chr(cur, u) != 0) goto err; goto add; }
*/
add:
    if (l > u) goto err;
    cls.push_back(ASTRange(l, u, NOWHERE));
/*!re2c
    ""  { goto cls; }
    "]" {
        std::vector<ASTRange> *p = new std::vector<ASTRange>;
        p->swap(cls);
        yylval.regexp = ast_cls(NOWHERE, p, neg);
        return TOKEN_REGEXP;
    }
*/

err:
    error("syntax error: %s\n", cur);
    return TOKEN_ERROR;

err_cnt:
    error("repetition count overflow");
    return TOKEN_ERROR;
}

int32_t lex_cls_chr(const char *&cur, uint32_t &c)
{
    const char *mar, *p = cur;
/*!re2c
    *    { return 1; }
    "[." { error("collating characters not supported"); return 1; }
    "[:" { error("character classes not supported");    return 1; }
    "[=" { error("equivalence classes not supported");  return 1; }

    "\\x"[0-9a-fA-F]{2} { c = unesc_hex(p, cur); return 0; }

    "\\"      { c = static_cast<uint8_t>('\\');    return 0; }
    "\\a"     { c = static_cast<uint8_t>('\a');    return 0; }
    "\\b"     { c = static_cast<uint8_t>('\b');    return 0; }
    "\\f"     { c = static_cast<uint8_t>('\f');    return 0; }
    "\\n"     { c = static_cast<uint8_t>('\n');    return 0; }
    "\\r"     { c = static_cast<uint8_t>('\r');    return 0; }
    "\\t"     { c = static_cast<uint8_t>('\t');    return 0; }
    "\\v"     { c = static_cast<uint8_t>('\v');    return 0; }
    "\\\\"    { c = static_cast<uint8_t>('\\');    return 0; }
    "\\]"     { c = static_cast<uint8_t>(']');     return 0; }

    [^] \ nil { c = static_cast<uint8_t>(cur[-1]); return 0; }
*/
}

} // namespace re2c
