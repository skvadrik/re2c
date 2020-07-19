// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct mtag_t
{
    int pred;
    const char *tag;
};

typedef std::vector<mtag_t> mtagpool_t;

static void mtag(int *pt, const char *t, mtagpool_t *tp)
{
    mtag_t l = {*pt, t};
    *pt = (int) tp->size();
    tp->push_back(l);
}

static void print_channels(const mtagpool_t &tp, int x, int y)
{
    if (x == -1) return;
    print_channels(tp, tp[x].pred, tp[y].pred);
    const char *px = tp[x].tag, *py = tp[y].tag;
    fprintf(stderr, "    %.*s\n", (int) (py - px), px);
}

#define YYMTAGP(t) mtag(&t, YYCURSOR, &tp)
#define YYMTAGN(t) mtag(&t, NULL,     &tp)

static int lex(const char *YYCURSOR)
{
    const char *YYMARKER, *n1, *n2, *a1, *a2, *c1, *c2;
    mtagpool_t tp;
    int h1, h2;
    /*!stags:re2c format = "const char *@@;"; */
    /*!mtags:re2c format = "int @@;"; */
loop:
    tp.clear();
    /*!mtags:re2c format = "@@ = -1;"; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:flags:tags = 1;

        end     = "\x00";
        eol     = "\n";
        wsp     = [ \t]*;
        eq      = wsp "=" wsp;
        nick    = [a-zA-Z0-9_]+;
        name    = [A-Z] ("." | [a-z]+);
        names   = name (wsp name)*;
        country = [A-Za-z ]+;
        channel = ([a-z0-9-]+ "/")? "#" [a-z0-9-]+;

        *         { fprintf(stderr, "error: %s\n", YYCURSOR); return 1; }
        end       { return 0; }
        wsp | eol { goto loop; }

        @n1 nick @n2 wsp "{" wsp eol
            wsp "name"     eq @a1 names   @a2 wsp eol
            wsp "country"  eq @c1 country @c2 wsp eol
            wsp "channels" eq (wsp #h1 channel #h2 wsp ";")* wsp eol
        wsp "}" {
            fprintf(stderr, "\n%.*s\n", (int) (n2 - n1), n1);
            fprintf(stderr, "  name:     %.*s\n", (int) (a2 - a1), a1);
            fprintf(stderr, "  country:  %.*s\n", (int) (c2 - c1), c1);
            fprintf(stderr, "  channels:\n");
            print_channels(tp, h1, h2);
            goto loop;
        }
    */
}

int main()
{
    const char *fname = "etc_passwd";
    FILE *f;

    // prepare input file
    f = fopen(fname, "w");
    fprintf(f,
        "h4cker1970 {\n"
        "    name     = Jon Smith\n"
        "    country  = UK\n"
        "    channels = freenode/#gentoo-dev; freenode/#gentoo-arch; freenode/#alpha;\n"
        "}\n"
        "\n"
        "mitek {\n"
        "    name     = Mitrofan Rygoravich\n"
        "    country  = Belarus\n"
        "    channels = bynets/#haskell; freenode/#unix;\n"
        "}\n"
        "\n");
    fclose(f);

    // read input file into buffer
    f = fopen(fname, "r");
    fseek(f, 0, SEEK_END);
    const size_t fsize = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char*) malloc(fsize + 1);
    fread(buffer, 1, fsize, f);
    buffer[fsize] = 0;
    fclose(f);

    assert(lex(buffer) == 0);

    // cleanup
    remove(fname);
    free(buffer);
    return 0;
}
