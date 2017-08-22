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
    printf("    %.*s\n", (int) (py - px), px);
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

        end     = "\x00";
        eol     = "\n";
        wsp     = [ \t]*;
        eq      = wsp "=" wsp;
        nick    = [a-zA-Z0-9_]+;
        name    = [A-Z] ("." | [a-z]+);
        names   = name (wsp name)*;
        country = [A-Za-z ]+;
        channel = ([a-z0-9-]+ "/")? "#" [a-z0-9-]+;

        *         { printf("error: %s\n", YYCURSOR); return 1; }
        end       { return 0; }
        wsp | eol { goto loop; }

        @n1 nick @n2 wsp "{" wsp eol
            wsp "name"     eq @a1 names   @a2 wsp eol
            wsp "country"  eq @c1 country @c2 wsp eol
            wsp "channels" eq (wsp #h1 channel #h2 wsp ";")* wsp eol
        wsp "}" {
            printf("\n%.*s\n", (int) (n2 - n1), n1);
            printf("  name:     %.*s\n", (int) (a2 - a1), a1);
            printf("  country:  %.*s\n", (int) (c2 - c1), c1);
            printf("  channels:\n");
            print_channels(tp, h1, h2);
            goto loop;
        }
    */
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "no input files\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    fseek(file, 0, SEEK_END);
    const size_t fsize = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*) malloc(fsize + 1);

    fread(buffer, 1, fsize, file);
    buffer[fsize] = 0;

    const int status = lex(buffer);

    fclose(file);
    free(buffer);

    return status;
}
