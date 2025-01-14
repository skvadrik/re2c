// re2c $INPUT -o $OUTPUT -i --tags

// See bug https://github.com/skvadrik/re2c/issues/523
// Tags on all transitions going to bitmap state must be equal.
// Run as `./tags_with_bitmaps ' "aa"'`, expected output is `aa`
// (trimmed quotes ans leading whitespace).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_quoted(const char *s, const char **mbegin, const char **mend) {
    const char *YYCURSOR = s, *YYMARKER = s;

    const char *t1, *t2, *yyt1, *yyt2;
    /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:yyfill:enable = 0;

            wspc_opt = [ ]*;
            qstr     = wspc_opt ["] @t1 [^\x00]* @t2 ["] wspc_opt;

            *    { *mbegin = s; *mend = strchr(s, '\0'); return 0; }
            qstr { *mbegin = t1; *mend = t2; return 1; }
    */
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE: %s <STRING_WITH_OR_WITHOUT_DOUBLE_QUOTES>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *begin, *end;
    match_quoted(argv[1], &begin, &end);
    printf("%.*s\n", (int)(end - begin), begin);
    return EXIT_SUCCESS;
}
