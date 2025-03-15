/*!rules:re2c:base
    re2c:api:style   = free-form;
    re2c:YYCTYPE     = char;
    re2c:YYMTAGP     = "taglist(&@@, YYTOKEN, YYCURSOR, &in->tlp);";
    re2c:YYMTAGN     = "taglist(&@@, YYTOKEN, YYTOKEN - 1, &in->tlp);"; // negative distance -1
    re2c:YYSHIFTMTAG = "@@{tag}->dist += @@{shift};";
*/

/*!max:re2c*/

struct input_t {
    FILE* file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    /*!stags:re2c format = "char *@@;\n"; */
    /*!mtags:re2c format = "taglist_t *@@;\n"; */
    taglistpool_t tlp;
    int eof;
};

static inline void free_input(input_t *in) {
    free(in->buf);
    taglistpool_free(&in->tlp);
    if (in->file) fclose(in->file);
}

static inline int fill_buffered_eof(input_t *in) {
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free > 0);

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    /*!stags:re2c format = "if (in->@@) in->@@ -= free;\n"; */

    in->lim += fread(in->lim, 1, free, in->file);
    in->lim[0] = 0;

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
    }

    return 0;
}

static inline int fill_buffered_scc(input_t *in, size_t need) {
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free >= need);

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    /*!stags:re2c format = "if (in->@@) in->@@ -= free;\n"; */

    in->lim += fread(in->lim, 1, free, in->file);

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static inline void init_input_simple(input_t *in, const char* fname) {
    FILE* f = fopen(fname, "rb");

    fseek(f, 0, SEEK_END);
    size_t flen = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    in->file = nullptr; // unused
    in->buf = (char*) malloc(flen + 1);
    in->lim = nullptr; // unused
    in->cur = in->mar = in->tok = in->buf;
    /*!stags:re2c format = "in->@@ = 0;\n"; */
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
    taglistpool_init(&in->tlp);
    in->eof = 0; // unused

    fread(in->buf, 1, flen, f);
    in->buf[flen] = 0;

    fclose(f);
}

static inline void init_input_buffered_eof(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
    in->buf = (char*) malloc(SIZE + 1);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    /*!stags:re2c format = "in->@@ = 0;\n"; */
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
    taglistpool_init(&in->tlp);
    in->eof = 0;
    fill_buffered_eof(in);
}

static inline void init_input_buffered_scc(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    /*!stags:re2c format = "in->@@ = 0;\n"; */
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
    taglistpool_init(&in->tlp);
    in->eof = 0;
}

#define YYCURSOR cur
#define YYMARKER mar
#define YYTOKEN tok
#define TLP_CLEAR() do { \
    in->tlp.next = in->tlp.head; \
    /*!mtags:re2c format = "@@ = 0;"; */ \
} while (0)

int lex_simple(input_t *in) {
    char *cur = in->buf, *mar, *tok;
    (void) mar; // maybe unused
    (void) tok; // maybe unused
    /*!stags:re2c format = "char *@@;\n"; */
    /*!mtags:re2c format = "taglist_t *@@ = nullptr;\n"; */
    /*!svars:re2c:x format = "const char* @@;"; */
    /*!mvars:re2c:x format = "taglist_t* @@;"; */
    long count = 0;
loop:
    tok = cur;
    /*!local:re2c
        re2c:yyfill:enable = 0;

        "\x00" { return count; }

        !use:base;
        !use:main; // goes last, as it may override some configurations
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYTOKEN
#undef TLP_CLEAR

#define YYCURSOR in->cur
#define YYMARKER in->mar
#define YYLIMIT in->lim
#define YYTOKEN in->tok
#define TLP_CLEAR() do { \
    in->tlp.next = in->tlp.head; \
    /*!mtags:re2c format = "in->@@ = 0;"; */ \
} while (0)

int lex_buffered_eof(input_t *in) {
    /*!svars:re2c:x format = "const char* @@;"; */
    /*!mvars:re2c:x format = "taglist_t* @@;"; */
    long count = 0;
loop:
    in->tok = in->cur;
    /*!local:re2c:x
        re2c:define:YYFILL = "fill_buffered_eof(in) == 0";
        re2c:eof = 0;
        re2c:tags:expression = "in->@@";

        $ { return count; }

        !use:base;
        !use:main; // goes last, as it may override some configurations
    */
}

int lex_buffered_scc(input_t *in) {
    /*!svars:re2c:y format = "const char* @@;"; */
    /*!mvars:re2c:y format = "taglist_t* @@;"; */
    long count = 0;
loop:
    in->tok = in->cur;
    /*!local:re2c:y
        re2c:define:YYFILL = "if (fill_buffered_scc(in, @@) != 0) return -2;"; // propagate error
        re2c:tags:expression = "in->@@";

        "\x00" { return count; }

        !use:base;
        !use:main; // goes last, as it may override some configurations
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN
#undef TLP_CLEAR

#define FN_BENCH(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    long count = 0; \
    for (auto _ : state) { \
        input_t in; \
        init_input_##suffix(&in, input); \
        count = lex_##suffix(&in); \
        free_input(&in); \
    } \
    if (count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH(simple)
FN_BENCH(buffered_eof)
FN_BENCH(buffered_scc)
#undef FN_BENCH

#define FN_TEST(suffix) \
bool test_##suffix(const char* input, long expected) { \
    input_t in; \
    init_input_##suffix(&in, input); \
    long count = lex_##suffix(&in); \
    switch (count) { \
    default: \
        if (count != expected) { \
            fprintf(stderr, "re2c: wrong count, expected %ld, got %ld\n", expected, count); \
        } \
        break; \
    case -1: \
        fprintf(stderr, "re2c: syntax error\n"); \
        break; \
    case -2: \
        fprintf(stderr, "re2c: yyfill error\n"); \
        break; \
    } \
    free_input(&in); \
    return count == expected; \
}
FN_TEST(simple)
FN_TEST(buffered_eof)
FN_TEST(buffered_scc)
#undef FN_TEST
