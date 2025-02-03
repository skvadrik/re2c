#include <stdint.h>
#include <stdio.h>

#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/parse/ast.h"
#include "src/util/range.h"
#include "src/util/string_utils.h"
#include "parse.h"
#include "lib/lex.h"



namespace re2c {

static int32_t lex_cls_chr(const uint8_t*&, uint32_t&);

/*!re2c
    re2c:flags:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYMARKER = mar;
    re2c:define:YYCTYPE = uint8_t;

    nil = "\x00";
    num = [0-9]+;
*/

int lex(RE2C_LIB_STYPE* yylval, const uint8_t*& cur, Ast& ast) {
    /*!stags:re2c format = "const uint8_t* @@;"; */
    const uint8_t* mar, *x, *y;
    bool neg = false;
    uint32_t l, u;

/*!local:re2c
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
        if (!s_to_u32_unsafe(x, cur - 1, yylval->bounds.min)) goto err_cnt;
        yylval->bounds.max = yylval->bounds.min;
        return TOKEN_COUNT;
    }

    "{" @x num "," @y num "}" {
        if (!s_to_u32_unsafe(x, y - 1, yylval->bounds.min)
            || !s_to_u32_unsafe(y, cur - 1, yylval->bounds.max)) goto err_cnt;
        return TOKEN_COUNT;
    }

    "{" @x num ",}" {
        if (!s_to_u32_unsafe(x, cur - 2, yylval->bounds.min)) goto err_cnt;
        yylval->bounds.max = Ast::MANY;
        return TOKEN_COUNT;
    }

    "." {
        yylval->regexp = ast.dot(NOWHERE);
        return TOKEN_REGEXP;
    }

    [^] \ nil {
        ast.temp_chars.push_back({cur[-1], NOWHERE});
        yylval->regexp = ast.str(NOWHERE, false);
        return TOKEN_REGEXP;
    }
*/

cls:
    if (lex_cls_chr(cur, l) != 0) goto err;
/*!local:re2c
    ""          { u = l; goto add; }
    "-" / [^\]] { if (lex_cls_chr(cur, u) != 0) goto err; goto add; }
*/
add:
    if (l > u) goto err;
    ast.temp_ranges.push_back(AstRange(l, u, NOWHERE));
/*!local:re2c
    ""  { goto cls; }
    "]" {
        yylval->regexp = ast.cls(NOWHERE, neg);
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

int32_t lex_cls_chr(const uint8_t*& cur, uint32_t& c) {
    const uint8_t* mar, *p = cur;
/*!local:re2c
    *    { return 1; }
    "[." { error("collating characters not supported"); return 1; }
    "[:" { error("character classes not supported");    return 1; }
    "[=" { error("equivalence classes not supported");  return 1; }

    "\\x"[0-9a-fA-F]{2} { c = unesc_hex(p, cur); return 0; }

    "\\"      { c = '\\'_u8; return 0; }
    "\\a"     { c = '\a'_u8; return 0; }
    "\\b"     { c = '\b'_u8; return 0; }
    "\\f"     { c = '\f'_u8; return 0; }
    "\\n"     { c = '\n'_u8; return 0; }
    "\\r"     { c = '\r'_u8; return 0; }
    "\\t"     { c = '\t'_u8; return 0; }
    "\\v"     { c = '\v'_u8; return 0; }
    "\\\\"    { c = '\\'_u8; return 0; }
    "\\]"     { c = ']'_u8;  return 0; }

    [^] \ nil { c = cur[-1]; return 0; }
*/
}

} // namespace re2c
