#include <stdio.h>

#include "src/util/c99_stdint.h"

#include "src/encoding/enc.h"
#include "src/parse/ast.h"
#include "src/options/msg.h"
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
    const loc_t nowhere(0, 0, "void");

/*!re2c
    * { goto err; }

    nil { return 0; }

    [()|*+?] { return cur[-1]; }

    [$^] {
        error("anchors are not supported");
        return ERROR;
    }

    "[^" { neg = true; goto cls; }
    "["  { goto cls; }

    "{" @x num "}" {
        if (!s_to_u32_unsafe(x, cur - 1, yylval.bounds.min)) goto err_cnt;
        yylval.bounds.max = yylval.bounds.min;
        return COUNT;
    }

    "{" @x num "," @y num "}" {
        if (!s_to_u32_unsafe(x, y - 1, yylval.bounds.min)
            || !s_to_u32_unsafe(y, cur - 1, yylval.bounds.max)) goto err_cnt;
        return COUNT;
    }

    "{" @x num ",}" {
        if (!s_to_u32_unsafe(x, cur - 2, yylval.bounds.min)) goto err_cnt;
        yylval.bounds.max = AST::MANY;
        return COUNT;
    }

    "." {
        yylval.regexp = ast_dot(nowhere);
        return REGEXP;
    }

    [^] \ nil {
        ASTChar c(static_cast<uint32_t>(cur[-1]), nowhere);
        std::vector<ASTChar> *str = new std::vector<ASTChar>;
        str->push_back(c);
        yylval.regexp = ast_str(nowhere, str, false);
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
    cls.push_back(ASTRange(l, u, nowhere));
/*!re2c
    ""  { goto cls; }
    "]" {
        std::vector<ASTRange> *p = new std::vector<ASTRange>;
        p->swap(cls);
        yylval.regexp = ast_cls(nowhere, p, neg);
        return REGEXP;
    }
*/

err:
    error("syntax error: %s\n", cur);
    return ERROR;

err_cnt:
    error("repetition count overflow");
    return ERROR;
}

int32_t lex_cls_chr(const char *&cur, uint32_t &c)
{
/*!re2c
    *    { return 1; }
    "[." { error("collating characters not supported"); return 1; }
    "[:" { error("character classes not supported"); return 1; }
    "[=" { error("equivalence classes not supported"); return 1; }

    [^] \ nil { c = static_cast<uint8_t>(cur[-1]); return 0; }
*/
}

} // namespace re2c
