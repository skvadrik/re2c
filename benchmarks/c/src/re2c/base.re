/*!rules:re2c:base
    re2c:api:style   = free-form;
    re2c:YYCTYPE     = char;
    re2c:YYCURSOR    = in->cur;
    re2c:YYMARKER    = in->mar;
    re2c:YYLIMIT     = in->lim;
    re2c:YYMTAGP     = "taglist(&@@, in->tok, in->cur, &in->tlp);";
    re2c:YYMTAGN     = "taglist(&@@, in->tok, in->tok - 1, &in->tlp);"; // negative distance -1
    re2c:YYSHIFTMTAG = "@@{tag}->dist += @@{shift};";
    re2c:tags:expression = "in->@@";
*/

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

static inline void taglistpool_clear(taglistpool_t *tlp, input_t *in) {
    tlp->next = tlp->head;
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
}

static inline void taglistpool_init(taglistpool_t *tlp) {
    static const unsigned size = 1024 * 1024;
    tlp->head = (taglist_t*)malloc(size * sizeof(taglist_t));
    tlp->next = tlp->head;
    tlp->last = tlp->head + size;
}

static inline void taglistpool_free(taglistpool_t *tlp) {
    free(tlp->head);
    tlp->head = tlp->next = tlp->last = NULL;
}

static inline void taglist(taglist_t **ptl, const char *b, const char *t, taglistpool_t *tlp) {
#ifdef GROW_MTAG_LIST
    if (tlp->next >= tlp->last) {
        const unsigned size = tlp->last - tlp->head;
        taglist_t *head = (taglist_t*)malloc(2 * size * sizeof(taglist_t));
        memcpy(head, tlp->head, size * sizeof(taglist_t));
        free(tlp->head);
        tlp->head = head;
        tlp->next = head + size;
        tlp->last = head + size * 2;
    }
#else
    assert(tlp->next < tlp->last);
#endif
    taglist_t *tl = tlp->next++;
    tl->pred = *ptl;
    tl->dist = t - b;
    *ptl = tl;
}

static inline void free_input(input_t *in) {
    free(in->buf);
    taglistpool_free(&in->tlp);
    fclose(in->file);
}

/*!rules:re2c:fill_eofrule
    re2c:define:YYFILL = "fill_eofrule(in) == 0";
    re2c:eof = 0;

    $ { return count; }
*/

/*!rules:re2c:fill_padding
    re2c:define:YYFILL = "if (fill_padding(in, @@) != 0) return -2;"; // error if YYFILL fails
    "\x00" { return count; }
*/

/*!max:re2c*/

static inline int fill_eofrule(input_t *in) {
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

static inline int fill_padding(input_t *in, size_t need) {
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

static inline void init_input_eofrule(input_t *in, const char* fname) {
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
    fill_eofrule(in);
}

static inline void init_input_padding(input_t *in, const char* fname) {
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

int lex_yyfill_eofrule(input_t *in) {
    long count = 0;
    /*!svars:re2c:x format = "const char* @@;"; */
    /*!mvars:re2c:x format = "taglist_t* @@;"; */
loop:
    in->tok = in->cur;
    /*!local:re2c:x
        !use:base;
        !use:fill_eofrule;
        !use:main; // goes last, as it may override some configurations
    */
}

int lex_yyfill_padding(input_t *in) {
    long count = 0;
    /*!svars:re2c:y format = "const char* @@;"; */
    /*!mvars:re2c:y format = "taglist_t* @@;"; */
loop:
    in->tok = in->cur;
    /*!local:re2c:y
        !use:base;
        !use:fill_padding;
        !use:main; // goes last, as it may override some configurations
        re2c:bit-vectors = 1;
    */
}

#define FN_BENCH(suffix) \
void bench_yyfill_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    long count; \
    for (auto _ : state) { \
        input_t in; \
        init_input_##suffix(&in, input); \
        count = lex_yyfill_##suffix(&in); \
        free_input(&in); \
    } \
    if (count != expected) state.SkipWithError("error"); \
}
FN_BENCH(eofrule)
FN_BENCH(padding)
#undef FN_BENCH

#define FN_TEST(suffix) \
bool test_yyfill_##suffix(const char* input, long expected) { \
    input_t in; \
    init_input_##suffix(&in, input); \
    \
    long count = lex_yyfill_##suffix(&in); \
    switch (count) { \
    default: \
        if (count != expected) { \
            fprintf(stderr, "wrong count, expected %ld, got %ld\n", expected, count); \
        } \
        break; \
    case -1: \
        fprintf(stderr, "syntax error\n"); \
        break; \
    case -2: \
        fprintf(stderr, "yyfill error\n"); \
        break; \
    } \
    \
    free_input(&in); \
    return count == expected; \
}
FN_TEST(eofrule)
FN_TEST(padding)
#undef FN_TEST
