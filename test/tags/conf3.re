// re2c $INPUT -o $OUTPUT -i --tags
#include <stddef.h>
#include <stdio.h>

static inline unsigned parse_oct(const char *s, const char *e)
{
    unsigned oct = 0;
    for (; s != e; ++s) {
        oct = oct * 10 + *s - '0';
    }
    return oct;
}

struct tags_t
{
    /*!stags:re2c format = "const char *@@;"; */

    tags_t();
    void push(/*!stags:re2c
        format = "const char *arg_@@";
        separator = ","; */);
    void pop(/*!stags:re2c
        format = "const char *&arg_@@";
        separator = ","; */);
};

static void lex(const char *YYCURSOR)
{
    const char *YYMARKER, *p0, *p1, *p2, *p3;
    tags_t tags;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:tags:expression = "tags.@@";

        oct = [0-9]{1,3};
        d   = ".";

        * { printf("error\n"); return; }

        @p0
          oct @p1
        d oct @p2
        d oct @p3
        d oct {
            printf("%u.%u.%u.%u\n",
                parse_oct(p0, p1),
                parse_oct(p1 + 1, p2),
                parse_oct(p2 + 1, p3),
                parse_oct(p3 + 1, YYCURSOR));
            return;
        }
    */
}

tags_t::tags_t(): /*!stags:re2c
    format = "@@(0)";
    separator = ",";
*/ {}

void tags_t::push(/*!stags:re2c
    format = "const char *arg_@@";
    separator = ","; */)
{
    /*!stags:re2c format = "@@ = arg_@@;"; */
}

void tags_t::pop(/*!stags:re2c
    format = "const char *&arg_@@";
    separator = ","; */)
{
    /*!stags:re2c format = "arg_@@ = @@;"; */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
