#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/bitmap.h"
#include "src/codegen/emit.h"
#include "src/codegen/output.h"
#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"


namespace re2c {

static void exact_uint(Scratchbuf &o, size_t width)
{
    if (width == sizeof(char)) {
        o.cstr("unsigned char");
    }
    else if (width == sizeof(short)) {
        o.cstr("unsigned short");
    }
    else if (width == sizeof(int)) {
        o.cstr("unsigned int");
    }
    else if (width == sizeof(long)) {
        o.cstr("unsigned long");
    }
    else {
        o.cstr("uint").u64(width * 8).cstr("_t");
    }
}

static void from_le(Scratchbuf &o, const opt_t *opts, uint32_t ind, size_t size, const char *expr)
{
    o.cstr("\n").str(indent(ind, opts->indString)).cstr("/* from little-endian to host-endian */");
    o.cstr("\n").str(indent(ind, opts->indString)).cstr("unsigned char *p = (unsigned char*)&").cstr(expr).cstr(";");
    o.cstr("\n").str(indent(ind, opts->indString)).cstr(expr).cstr(" = p[0]");
    for (uint32_t i = 1; i < size; ++i) {
        o.cstr(" + (p[").u32(i).cstr("] << ").u32(i * 8).cstr("u)");
    }
    o.cstr(";");
}

const char *emit_prolog(Scratchbuf &o, const opt_t *opts)
{
    o.cstr("\n#include <stddef.h> /* size_t */");
    o.cstr("\n#include <stdio.h>");
    o.cstr("\n#include <stdlib.h> /* malloc, free */");
    o.cstr("\n#include <string.h> /* memcpy */");
    o.cstr("\n");
    o.cstr("\nstatic void *read_file");
    o.cstr("\n").str(opts->indString).cstr("( const char *fname");
    o.cstr("\n").str(opts->indString).cstr(", size_t unit");
    o.cstr("\n").str(opts->indString).cstr(", size_t padding");
    o.cstr("\n").str(opts->indString).cstr(", size_t *pfsize");
    o.cstr("\n").str(opts->indString).cstr(")");
    o.cstr("\n{");
    o.cstr("\n").str(opts->indString).cstr("void *buffer = NULL;");
    o.cstr("\n").str(opts->indString).cstr("size_t fsize = 0;");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("/* open file */");
    o.cstr("\n").str(opts->indString).cstr("FILE *f = fopen(fname, \"rb\");");
    o.cstr("\n").str(opts->indString).cstr("if(f == NULL) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("goto error;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("/* get file size */");
    o.cstr("\n").str(opts->indString).cstr("fseek(f, 0, SEEK_END);");
    o.cstr("\n").str(opts->indString).cstr("fsize = (size_t) ftell(f) / unit;");
    o.cstr("\n").str(opts->indString).cstr("fseek(f, 0, SEEK_SET);");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("/* allocate memory for file and padding */");
    o.cstr("\n").str(opts->indString).cstr("buffer = malloc(unit * (fsize + padding));");
    o.cstr("\n").str(opts->indString).cstr("if (buffer == NULL) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("goto error;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("/* read the whole file in memory */");
    o.cstr("\n").str(opts->indString).cstr("if (fread(buffer, unit, fsize, f) != fsize) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("goto error;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("fclose(f);");
    o.cstr("\n").str(opts->indString).cstr("*pfsize = fsize;");
    o.cstr("\n").str(opts->indString).cstr("return buffer;");
    o.cstr("\n");
    o.cstr("\nerror:");
    o.cstr("\n").str(opts->indString).cstr("fprintf(stderr, \"error: cannot read file '%s'\\n\", fname);");
    o.cstr("\n").str(opts->indString).cstr("free(buffer);");
    o.cstr("\n").str(opts->indString).cstr("if (f != NULL) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("fclose(f);");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n").str(opts->indString).cstr("return NULL;");
    o.cstr("\n}");
    o.cstr("\n");
    return o.flush();
}

const char *emit_start(Scratchbuf &o, const opt_t *opts, const DFA &dfa, const CodeStmts *bitmaps, Msg &msg)
{
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    const uint64_t norule = rule2key(Rule::NONE, dfa.key_size, dfa.def_rule);
    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }
    uint32_t lines = 0;
    RenderContext rctx = {o.stream(), opts, msg, 0, filename.c_str(), lines};

    o.cstr("\n#define YYCTYPE ");
    exact_uint (o, sizeof_cunit);
    o.cstr("\n#define YYKEYTYPE ");
    exact_uint (o, dfa.key_size);
    o.cstr("\n#define YYPEEK() *cursor");
    o.cstr("\n#define YYSKIP() ++cursor");
    if (dfa.need_backup) {
        o.cstr("\n#define YYBACKUP() marker = cursor");
        o.cstr("\n#define YYRESTORE() cursor = marker");
    }
    if (dfa.oldstyle_ctxmarker) {
        o.cstr("\n#define YYBACKUPCTX() ctxmarker = cursor");
        o.cstr("\n#define YYRESTORECTX() cursor = ctxmarker");
    }
    if (opts->tags) {
        o.cstr("\n#define YYSTAGP(t) t = cursor");
        o.cstr("\n#define YYSTAGN(t) t = NULL");
        o.cstr("\n#define YYMTAGP(t) yymtag(&t, cursor, &yytp)");
        o.cstr("\n#define YYMTAGN(t) yymtag(&t, NULL, &yytp)");
        o.cstr("\n#define YYRESTORETAG(t) cursor = t");
        if (opts->stadfa) {
             o.cstr("\n#define YYSTAGPD(t) t = cursor - 1");
             o.cstr("\n#define YYMTAGPD(t) yymtag(&t, cursor - 1, &yytp)");
        }
    }
    o.cstr("\n#define YYLESSTHAN(n) (limit - cursor) < n");
    o.cstr("\n#define YYFILL(n) { break; }");
    o.cstr("\n");

    o.cstr("\nstatic int action_").str(dfa.name);
    o.cstr("\n").str(opts->indString).cstr("( unsigned *pkix");
    o.cstr("\n").str(opts->indString).cstr(", const YYKEYTYPE *keys");
    o.cstr("\n").str(opts->indString).cstr(", const YYCTYPE *start");
    o.cstr("\n").str(opts->indString).cstr(", const YYCTYPE *token");
    o.cstr("\n").str(opts->indString).cstr(", const YYCTYPE **cursor");
    o.cstr("\n").str(opts->indString).cstr(", YYKEYTYPE rule_act");
    o.cstr("\n").str(opts->indString).cstr(")");
    o.cstr("\n{");
    o.cstr("\n").str(opts->indString).cstr("const unsigned kix = *pkix;");
    o.cstr("\n").str(opts->indString).cstr("const long pos = token - start;");
    o.cstr("\n").str(opts->indString).cstr("const long len_act = *cursor - token;");
    o.cstr("\n").str(opts->indString).cstr("const long len_exp = (long) keys[kix + 1];");
    o.cstr("\n").str(opts->indString).cstr("const YYKEYTYPE rule_exp = keys[kix + 2];");
    o.cstr("\n").str(opts->indString).cstr("*pkix = kix + 3;");
    o.cstr("\n").str(opts->indString).cstr("if (rule_exp == ").u64(norule).cstr(") {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("fprintf");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("( stderr");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", \"warning: lex_").str(dfa.name).cstr(": control flow is undefined for input\"");
    o.cstr("\n").str(indent(4, opts->indString)).cstr("\" at position %ld, rerun re2c with '-W'\\n\"");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", pos");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(");");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n").str(opts->indString).cstr("if (len_act == len_exp && rule_act == rule_exp) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYKEYTYPE offset = keys[kix];");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("*cursor = token + offset;");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("return 0;");
    o.cstr("\n").str(opts->indString).cstr("} else {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("fprintf");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("( stderr");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", \"error: lex_").str(dfa.name).cstr(": at position %ld (key %u):\\n\"");
    o.cstr("\n").str(indent(4, opts->indString)).cstr("\"\\texpected: match length %ld, rule %u\\n\"");
    o.cstr("\n").str(indent(4, opts->indString)).cstr("\"\\tactual:   match length %ld, rule %u\\n\"");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", pos");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", kix");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", len_exp");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", rule_exp");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", len_act");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(", rule_act");
    o.cstr("\n").str(indent(3, opts->indString)).cstr(");");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("return 1;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n}");

    if (!dfa.stagnames.empty()) {
        o.cstr("\n");
        o.cstr("\nstatic int check_stag_").str(dfa.name)
            .cstr("(unsigned *pkix, YYKEYTYPE *keys, const YYCTYPE *tag,\n")
            .str(opts->indString).cstr("const YYCTYPE *input, const YYCTYPE *token, const char *name)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("const unsigned kix = *pkix;");
        o.cstr("\n").str(opts->indString).cstr("const YYKEYTYPE\n")
            .str(indent(2, opts->indString)).cstr("exp = keys[kix],\n")
            .str(indent(2, opts->indString)).cstr("act = (YYKEYTYPE)(tag - token),\n")
            .str(indent(2, opts->indString)).cstr("NIL = (YYKEYTYPE)~0u;");
        o.cstr("\n").str(opts->indString).cstr("*pkix = kix + 1;");
        o.cstr("\n");
        o.cstr("\n").str(opts->indString).cstr("if (exp == act || (exp == NIL && tag == NULL)) return 0;");
        o.cstr("\n");
        o.cstr("\n").str(opts->indString).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"")
            .cstr("\n").str(indent(2, opts->indString)).cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\",")
            .cstr("\n").str(indent(2, opts->indString)).cstr("token - input, kix, name, exp, act);");
        o.cstr("\n").str(opts->indString).cstr("return 1;");
        o.cstr("\n}");
    }

    if (!dfa.mtagnames.empty()) {
        o.cstr("\n");
        o.cstr("\ntypedfa.def_rule struct yymtag_t {");
        o.cstr("\n").str(opts->indString).cstr("ptrdiff_t pred;");
        o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *elem;");
        o.cstr("\n} yymtag_t;");

        o.cstr("\n");
        o.cstr("\ntypedfa.def_rule struct yymtagpool_t {");
        o.cstr("\n").str(opts->indString).cstr("yymtag_t *head;");
        o.cstr("\n").str(opts->indString).cstr("yymtag_t *next;");
        o.cstr("\n").str(opts->indString).cstr("yymtag_t *last;");
        o.cstr("\n} yymtagpool_t;");

        o.cstr("\n");
        o.cstr("\nstatic void yymtagpool_clear(yymtagpool_t *tp)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("tp->next = tp->head;");
        o.cstr("\n}");

        o.cstr("\n");
        o.cstr("\nstatic void yymtagpool_init(yymtagpool_t *tp)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("static const unsigned size = 4096;");
        o.cstr("\n").str(opts->indString).cstr("tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t));");
        o.cstr("\n").str(opts->indString).cstr("tp->next = tp->head;");
        o.cstr("\n").str(opts->indString).cstr("tp->last = tp->head + size;");
        o.cstr("\n}");

        o.cstr("\n");
        o.cstr("\nstatic void yymtagpool_free(yymtagpool_t *tp)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("free(tp->head);");
        o.cstr("\n").str(opts->indString).cstr("tp->head = tp->next = tp->last = NULL;");
        o.cstr("\n}");

        o.cstr("\n");
        o.cstr("\nstatic yymtag_t *yymtagpool_next(yymtagpool_t *tp)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("if (tp->next == tp->last) {");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const unsigned size = tp->last - tp->head;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("yymtag_t *head = (yymtag_t*)malloc(2 * size * sizeof(yymtag_t));");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("memcpy(head, tp->head, size * sizeof(yymtag_t));");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("free(tp->head);");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("tp->head = head;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("tp->next = head + size;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("tp->last = head + size * 2;");
        o.cstr("\n").str(opts->indString).cstr("}");
        o.cstr("\n").str(opts->indString).cstr("return tp->next++;");
        o.cstr("\n}");

        o.cstr("\n");
        o.cstr("\nstatic void yymtag(ptrdiff_t *pt, const YYCTYPE *t, yymtagpool_t *tp)");
        o.cstr("\n{");
        o.cstr("\n").str(opts->indString).cstr("yymtag_t *n = yymtagpool_next(tp);");
        o.cstr("\n").str(opts->indString).cstr("n->pred = *pt;");
        o.cstr("\n").str(opts->indString).cstr("n->elem = t;");
        o.cstr("\n").str(opts->indString).cstr("*pt = n - tp->head;");
        o.cstr("\n}");

        o.cstr("\n");
        o.cstr("\nstatic int check_mtag_").str(dfa.name)
            .cstr("(unsigned *pkix, YYKEYTYPE *keys, const yymtagpool_t *tp, ptrdiff_t mtag,\n")
            .str(opts->indString).cstr("const YYCTYPE *input, const YYCTYPE *token, const char *name)");
        o.cstr("\n{");
//        o.cstr("\n").str(opts->indString).cstr("check_key_count_").str(name).cstr("(1) && return 1;");
        o.cstr("\n").str(opts->indString).cstr("const unsigned kix = *pkix;");
        o.cstr("\n").str(opts->indString).cstr("YYKEYTYPE n = keys[kix];");
        o.cstr("\n").str(opts->indString).cstr("*pkix = kix + n + 1;");
//        o.cstr("\n").str(opts->indString).cstr("check_key_count_").str(name).cstr("(n) && return 1;");
        o.cstr("\n").str(opts->indString).cstr("for (; n > 0; --n) {");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("if (mtag == -1) {");
        o.cstr("\n").str(indent(3, opts->indString)).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"")
            .cstr("\n").str(indent(4, opts->indString)).cstr("\"history for tag '%s' is too short\\n\",")
            .cstr("\n").str(indent(4, opts->indString)).cstr("token - input, kix + n, name);");
        o.cstr("\n").str(indent(3, opts->indString)).cstr("return 1;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("}");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYCTYPE *tag = (tp->head + mtag)->elem;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("mtag = (tp->head + mtag)->pred;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYKEYTYPE\n")
            .str(indent(3, opts->indString)).cstr("exp = keys[kix + n],\n")
            .str(indent(3, opts->indString)).cstr("act = (YYKEYTYPE)(tag - token),\n")
            .str(indent(3, opts->indString)).cstr("NIL = (YYKEYTYPE)~0u;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("if (!(exp == act || (exp == NIL && tag == NULL))) {");
        o.cstr("\n").str(indent(3, opts->indString)).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"")
            .cstr("\n").str(indent(4, opts->indString)).cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\",")
            .cstr("\n").str(indent(4, opts->indString)).cstr("token - input, kix + n, name, exp, act);");
        o.cstr("\n").str(indent(3, opts->indString)).cstr("return 1;");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("}");
        o.cstr("\n").str(opts->indString).cstr("}");
        o.cstr("\n").str(opts->indString).cstr("if (mtag != -1) {");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"")
            .cstr("\n").str(indent(3, opts->indString)).cstr("\"history for tag '%s' is too long\\n\",")
            .cstr("\n").str(indent(3, opts->indString)).cstr("token - input, kix, name);");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("return 1;");
        o.cstr("\n").str(opts->indString).cstr("}");
        o.cstr("\n").str(opts->indString).cstr("return 0;");
        o.cstr("\n}");
    }

    o.cstr("\n");
    o.cstr("\nstatic int check_key_count_").str(dfa.name).cstr("(unsigned have, unsigned used, unsigned need)");
    o.cstr("\n{");
    o.cstr("\n").str(opts->indString).cstr("if (used + need <= have) return 0;");
    o.cstr("\n").str(opts->indString).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": not enough keys\\n\");");
    o.cstr("\n").str(opts->indString).cstr("return 1;");
    o.cstr("\n}");
    o.cstr("\n");

    o.cstr("\nint lex_").str(dfa.name).cstr("()");
    o.cstr("\n{");
    o.cstr("\n").str(opts->indString).cstr("const size_t padding = ").u64(dfa.max_fill).cstr("; /* YYMAXFILL */");
    o.cstr("\n").str(opts->indString).cstr("int status = 0;");
    o.cstr("\n").str(opts->indString).cstr("size_t input_len = 0;");
    o.cstr("\n").str(opts->indString).cstr("size_t keys_count = 0;");
    o.cstr("\n").str(opts->indString).cstr("YYCTYPE *input = NULL;");
    o.cstr("\n").str(opts->indString).cstr("YYKEYTYPE *keys = NULL;");
    o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *cursor = NULL;");
    o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *limit = NULL;");
    o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *token = NULL;");
    o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *eof = NULL;");
    if (opts->posix_syntax) {
        o.cstr("\n").str(opts->indString).cstr("size_t yynmatch;");
        o.cstr("\n").str(opts->indString).cstr("const YYCTYPE *yypmatch[").u64(dfa.max_nmatch).cstr(" * 2];");
    }
    o.cstr("\n").str(opts->indString).cstr("unsigned int i = 0;");
    if (!dfa.mtagnames.empty()) {
        o.cstr("\n");
        o.cstr("\n").str(opts->indString).cstr("yymtagpool_t yytp;");
        o.cstr("\n").str(opts->indString).cstr("yymtagpool_init(&yytp);");
    }
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("input = (YYCTYPE *) read_file");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("(\"").str(filename).cstr(".").str(dfa.name).cstr(".input\"");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", sizeof (YYCTYPE)");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", padding");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", &input_len");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(");");
    o.cstr("\n").str(opts->indString).cstr("if (input == NULL) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("status = 1;");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("goto end;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    if (sizeof_cunit > 1) {
        o.cstr("\n").str(opts->indString).cstr("for (i = 0; i < input_len; ++i) {");
        from_le(o, opts, 2, sizeof_cunit, "input[i]");
        o.cstr("\n").str(opts->indString).cstr("}");
        o.cstr("\n");
    }
    o.cstr("\n").str(opts->indString).cstr("keys = (YYKEYTYPE *) read_file");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("(\"").str(filename).cstr(".").str(dfa.name).cstr(".keys\"");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", sizeof (YYKEYTYPE)");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", 0");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(", &keys_count");
    o.cstr("\n").str(indent(2, opts->indString)).cstr(");");
    o.cstr("\n").str(opts->indString).cstr("if (keys == NULL) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("status = 1;");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("goto end;");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    if (dfa.key_size > 1) {
        o.cstr("\n").str(opts->indString).cstr("for (i = 0; i < keys_count; ++i) {");
        from_le(o, opts, 2, dfa.key_size, "keys[i]");
        o.cstr("\n").str(opts->indString).cstr("}");
        o.cstr("\n");
    }
    o.cstr("\n").str(opts->indString).cstr("cursor = input;");
    o.cstr("\n").str(opts->indString).cstr("limit = input + input_len + padding;");
    o.cstr("\n").str(opts->indString).cstr("eof = input + input_len;");
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("for (i = 0; status == 0 && cursor < eof && i < keys_count;) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("token = cursor;");
    if (dfa.need_backup) {
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYCTYPE *marker = NULL;");
    }
    if (dfa.oldstyle_ctxmarker) {
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYCTYPE *ctxmarker = NULL;");
    }
    o.cstr("\n").str(indent(2, opts->indString)).cstr("YYCTYPE yych;");
    if (dfa.need_accept) {
        o.cstr("\n").str(indent(2, opts->indString)).cstr("unsigned int yyaccept = 0;");
    }

    // autogenerated stag variables
    const std::string stags_fmt = "\n" + indent(2, opts->indString) + "const YYCTYPE *@@ = NULL;";
    CodeStmt stags;
    stags.kind = CodeStmt::STAGS;
    stags.tags.fmt = stags_fmt.c_str();
    stags.tags.sep = "";
    gen_tags(o, &stags, dfa.stagnames);
    render_code_stmt(rctx, &stags);

    // user-defined stag variables
    std::set<std::string>::const_iterator
        var1 = dfa.stagvars.begin(),
        var2 = dfa.stagvars.end();
    if (var1 != var2) {
        o.cstr("\n").str(indent(2, opts->indString)).cstr("const YYCTYPE *").str(*var1);
        for (++var1; var1 != var2; ++var1) {
            o.cstr(", *").str(*var1);
        }
        o.cstr(";");
    }

    if (!dfa.mtagnames.empty()) {
        o.cstr("\n").str(indent(2, opts->indString)).cstr("yymtagpool_clear(&yytp);");

        // autogenerated mtag variables
        CodeStmt mtags;
        mtags.kind = CodeStmt::MTAGS;
        mtags.tags.fmt = "ptrdiff_t @@ = -1;";
        mtags.tags.sep = "";
        gen_tags(o, &mtags, dfa.mtagnames);
        render_code_stmt(rctx, &mtags);

        // user-defined mtag variables
        var1 = dfa.mtagvars.begin();
        var2 = dfa.mtagvars.end();
        if (var1 != var2) {
            o.cstr("\n").str(indent(2, opts->indString)).cstr("ptrdiff_t ").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", ").str(*var1);
            }
            o.cstr(";");
        }
    }

    o.cstr("\n");
    if (bitmaps) {
        rctx.ind = 2;
        render_code_stmts(rctx, bitmaps);
    }
    o.cstr("\n");

    return o.flush();
}

const char *emit_end(Scratchbuf &o, const opt_t *opts, const DFA &dfa)
{
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n").str(opts->indString).cstr("if (status == 0) {");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("if (cursor != eof) {");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("status = 1;");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("const long pos = token - input;");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": unused input strings left at position %ld\\n\", pos);");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("}");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("if (i != keys_count) {");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("status = 1;");
    o.cstr("\n").str(indent(3, opts->indString)).cstr("fprintf(stderr, \"error: lex_").str(dfa.name).cstr(": unused keys left after %u keys\\n\", i);");
    o.cstr("\n").str(indent(2, opts->indString)).cstr("}");
    o.cstr("\n").str(opts->indString).cstr("}");
    o.cstr("\n");
    o.cstr("\nend:");
    o.cstr("\n").str(opts->indString).cstr("free(input);");
    o.cstr("\n").str(opts->indString).cstr("free(keys);");
    if (!dfa.mtagnames.empty()) {
        o.cstr("\n").str(opts->indString).cstr("yymtagpool_free(&yytp);");
    }
    o.cstr("\n");
    o.cstr("\n").str(opts->indString).cstr("return status;");
    o.cstr("\n}");
    o.cstr("\n");
    o.cstr("\n#undef YYCTYPE");
    o.cstr("\n#undef YYKEYTYPE");
    o.cstr("\n#undef YYPEEK");
    o.cstr("\n#undef YYSKIP");
    if (dfa.need_backup) {
        o.cstr("\n#undef YYBACKUP");
        o.cstr("\n#undef YYRESTORE");
    }
    if (dfa.oldstyle_ctxmarker) {
        o.cstr("\n#undef YYBACKUPCTX");
        o.cstr("\n#undef YYRESTORECTX");
    }
    if (opts->tags) {
        o.cstr("\n#undef YYBACKUPTAG");
        o.cstr("\n#undef YYRESTORETAG");
        o.cstr("\n#undef YYCOPYTAG");
    }
    o.cstr("\n#undef YYLESSTHAN");
    o.cstr("\n#undef YYFILL");
    o.cstr("\n");
    return o.flush();
}

const char *emit_epilog(Scratchbuf &o, const opt_t *opts, const std::set<std::string> &names)
{
    o.cstr("\n").cstr("int main()");
    o.cstr("\n").cstr("{");

    for (std::set<std::string>::const_iterator i = names.begin(); i != names.end(); ++i) {
        o.cstr("\n").str(opts->indString).cstr("if(lex_").str(*i).cstr("() != 0) {");
        o.cstr("\n").str(indent(2, opts->indString)).cstr("return 1;");
        o.cstr("\n").str(opts->indString).cstr("}");
    }

    o.cstr("\n").str(opts->indString).cstr("return 0;");
    o.cstr("\n}");
    o.cstr("\n");

    return o.flush();
}

void emit_action(Scratchbuf &o, const opt_t *opts, uint32_t ind, const DFA &dfa, size_t rid)
{
    const std::string &name = dfa.name;
    const Rule &r = dfa.rules[rid];
    const uint64_t rkey = rule2key(rid, dfa.key_size, dfa.def_rule);
    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    o.str(indent(ind, opts->indString)).cstr("status = check_key_count_")
        .str(name).cstr("(keys_count, i, ").u64(ntag).cstr(")\n");
    o.str(indent(ind + 1, opts->indString)).cstr(" || action_").str(name)
        .cstr("(&i, keys, input, token, &cursor, ").u64(rkey).cstr(")");

    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        const std::string tname = tag_expr(tag, false);
        if (history(tag)) {
            o.cstr("\n").str(indent(ind + 1, opts->indString))
                .cstr(" || check_mtag_").str(name).cstr("(&i, keys, &yytp, ")
                .str(tname).cstr(", input, token, \"").str(tname).cstr("\")");
        }
        else {
            o.cstr("\n").str(indent(ind + 1, opts->indString))
                .cstr(" || check_stag_").str(name).cstr("(&i, keys, ")
                .str(tname).cstr(", input, token, \"").str(tname).cstr("\")");
        }
    }

    o.cstr(";\n").str(indent(ind, opts->indString)).cstr("continue;\n");
}

} // namespace re2c
