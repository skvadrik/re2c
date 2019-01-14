#include <stdio.h>

#include "src/util/c99_stdint.h"

#include "src/encoding/enc.h"
#include "src/parse/ast.h"
#include "src/options/msg.h"
#include "src/util/range.h"
#include "parse.h"
#include "libre2c_posix/lex.h"


extern YYSTYPE yylval;

namespace re2c {

static int32_t lex_cls_chr(const char *&, uint32_t &);

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYMARKER = mar;
    re2c:define:YYCTYPE = char;

    eof = "\x00";
    esc = "\\";
*/

int lex(const char *&cur)
{
    const char *mar;
    std::vector<ASTRange> cls;
    bool neg = false;
    uint32_t l, u;

/*!re2c
    * { goto err; }

    eof { return 0; }

    [{}()|*+?] { return cur[-1]; }

    "[^" { neg = true; goto cls; }
    "["  { goto cls; }

    "." {
        yylval.regexp = ast_dot(0, 0);
        return REGEXP;
    }

    [0-9] {
        yylval.number = static_cast<uint32_t>(cur[-1] - '0');
        return DIGIT;
    }

    [a-zA-Z] {
        ASTChar c(static_cast<uint32_t>(cur[-1]), 0);
        std::vector<ASTChar> *str = new std::vector<ASTChar>;
        str->push_back(c);
        yylval.regexp = ast_str(0, 0, str, false);
        return REGEXP;
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
    cls.push_back(ASTRange(l, u, 0));
/*!re2c
    ""  { goto cls; }
    "]" {
        std::vector<ASTRange> *p = new std::vector<ASTRange>;
        p->swap(cls);
        yylval.regexp = ast_cls(0, 0, p, neg);
        return REGEXP;
    }
*/

err:
    error("syntax error: %s\n", cur);
    return ERROR;
}

int32_t lex_cls_chr(const char *&cur, uint32_t &c)
{
/*!re2c
    *    { return 1; }
    "[." { error("collating characters not supported"); return 1; }
    "[:" { error("character classes not supported"); return 1; }
    "[=" { error("equivalence classes not supported"); return 1; }

    [^] \ eof { c = static_cast<uint8_t>(cur[-1]); return 0; }
*/
}

} // namespace re2c
