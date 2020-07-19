// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
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
        re2c:flags:tags = 1;

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

        *   { fprintf(stderr, "error\n"); return 1; }
        end { return 0; }

        @n user sep
        @p pass sep
        @u uid  sep
        @g gid  sep
        @f info sep
        @h home sep
        @c cmd  eol {
            fprintf(stderr, "user:     %.*s\n", (int)(p - n) - 1, n);
            fprintf(stderr, "password: %.*s\n", (int)(u - p) - 1, p);
            fprintf(stderr, "UID:      %.*s\n", (int)(g - u) - 1, u);
            fprintf(stderr, "GID:      %.*s\n", (int)(f - g) - 1, g);
            fprintf(stderr, "info:     %.*s\n", (int)(h - f) - 1, f);
            fprintf(stderr, "home:     %.*s\n", (int)(c - h) - 1, h);
            fprintf(stderr, "command:  %.*s\n", (int)(YYCURSOR - c - 1), c);
            fprintf(stderr, "\n");
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
        "root:x:0:0:root:/root:/bin/bash\n"
        "bin:x:1:1:bin:/bin:/bin/false\n"
        "portage:x:250:250:portage:/var/tmp/portage:/bin/false\n");
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
