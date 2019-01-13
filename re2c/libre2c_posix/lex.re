#include <stdio.h>

#include "src/util/c99_stdint.h"

#include "src/encoding/enc.h"
#include "src/parse/ast.h"
#include "src/util/range.h"
#include "parse.h"
#include "libre2c_posix/lex.h"

extern YYSTYPE yylval;

namespace re2c {

int lex(const char *&cur)
{
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCURSOR = cur;
        re2c:define:YYCTYPE = char;

        *          { printf("syntax error: %s\n", cur); exit(1); }
        "\x00"     { return 0; }
        [{}()|*+?] { return cur[-1]; }

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
}

} // namespace re2c
