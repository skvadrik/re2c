#include <stdio.h>
#include <stdlib.h>

/*!max:re2c*/

static int lex(const char *YYCURSOR)
{
    const char *YYMARKER, *n, *p, *u, *g, *f, *h, *c;
    /*!stags:re2c format = 'const char *@@;'; */
loop:
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        end  = "\x00";
        eol  = "\n";
        sep  = [:];
        char = [^] \ (end | eol | sep);
        user = char+;
        pass = char*;
        uid  = [0-9]+;
        gid  = [0-9]+;
        info = char*;
        home = "/" char*;
        cmd  = "/" char*;

        *   { printf("error\n"); return 1; }
        end { return 0; }

        @n user sep
        @p pass sep
        @u uid  sep
        @g gid  sep
        @f info sep
        @h home sep
        @c cmd  eol {
            printf("user:     %.*s\n", (int)(p - n) - 1, n);
            printf("password: %.*s\n", (int)(u - p) - 1, p);
            printf("UID:      %.*s\n", (int)(g - u) - 1, u);
            printf("GID:      %.*s\n", (int)(f - g) - 1, g);
            printf("info:     %.*s\n", (int)(h - f) - 1, f);
            printf("home:     %.*s\n", (int)(c - h) - 1, h);
            printf("command:  %.*s\n", (int)(YYCURSOR - c - 1), c);
            printf("\n");
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
