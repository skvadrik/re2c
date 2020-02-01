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

static void exact_uint(Output &o, size_t width)
{
    if (width == sizeof(char)) {
        o.ws("unsigned char");
    } else if (width == sizeof(short)) {
        o.ws("unsigned short");
    } else if (width == sizeof(int)) {
        o.ws("unsigned int");
    } else if (width == sizeof(long)) {
        o.ws("unsigned long");
    } else {
        o.ws("uint").wu64(width * 8).ws("_t");
    }
}

static void from_le(Output &o, uint32_t ind, size_t size, const char *expr)
{
    o.ws("\n").wind(ind).ws("/* from little-endian to host-endian */");
    o.ws("\n").wind(ind).ws("unsigned char *p = (unsigned char*)&").ws(expr).ws(";");
    o.ws("\n").wind(ind).ws(expr).ws(" = p[0]");
    for (uint32_t i = 1; i < size; ++i) {
        o.ws(" + (p[").wu32(i).ws("] << ").wu32(i * 8).ws("u)");
    }
    o.ws(";");
}

void emit_prolog(Output &o)
{
    o.ws("\n#include <stddef.h> /* size_t */");
    o.ws("\n#include <stdio.h>");
    o.ws("\n#include <stdlib.h> /* malloc, free */");
    o.ws("\n#include <string.h> /* memcpy */");
    o.ws("\n");
    o.ws("\nstatic void *read_file");
    o.ws("\n").wind(1).ws("( const char *fname");
    o.ws("\n").wind(1).ws(", size_t unit");
    o.ws("\n").wind(1).ws(", size_t padding");
    o.ws("\n").wind(1).ws(", size_t *pfsize");
    o.ws("\n").wind(1).ws(")");
    o.ws("\n{");
    o.ws("\n").wind(1).ws("void *buffer = NULL;");
    o.ws("\n").wind(1).ws("size_t fsize = 0;");
    o.ws("\n");
    o.ws("\n").wind(1).ws("/* open file */");
    o.ws("\n").wind(1).ws("FILE *f = fopen(fname, \"rb\");");
    o.ws("\n").wind(1).ws("if(f == NULL) {");
    o.ws("\n").wind(2).ws("goto error;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    o.ws("\n").wind(1).ws("/* get file size */");
    o.ws("\n").wind(1).ws("fseek(f, 0, SEEK_END);");
    o.ws("\n").wind(1).ws("fsize = (size_t) ftell(f) / unit;");
    o.ws("\n").wind(1).ws("fseek(f, 0, SEEK_SET);");
    o.ws("\n");
    o.ws("\n").wind(1).ws("/* allocate memory for file and padding */");
    o.ws("\n").wind(1).ws("buffer = malloc(unit * (fsize + padding));");
    o.ws("\n").wind(1).ws("if (buffer == NULL) {");
    o.ws("\n").wind(2).ws("goto error;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    o.ws("\n").wind(1).ws("/* read the whole file in memory */");
    o.ws("\n").wind(1).ws("if (fread(buffer, unit, fsize, f) != fsize) {");
    o.ws("\n").wind(2).ws("goto error;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    o.ws("\n").wind(1).ws("fclose(f);");
    o.ws("\n").wind(1).ws("*pfsize = fsize;");
    o.ws("\n").wind(1).ws("return buffer;");
    o.ws("\n");
    o.ws("\nerror:");
    o.ws("\n").wind(1).ws("fprintf(stderr, \"error: cannot read file '%s'\\n\", fname);");
    o.ws("\n").wind(1).ws("free(buffer);");
    o.ws("\n").wind(1).ws("if (f != NULL) {");
    o.ws("\n").wind(2).ws("fclose(f);");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n").wind(1).ws("return NULL;");
    o.ws("\n}");
    o.ws("\n");
}

void emit_start(Output &o, size_t maxfill, size_t maxnmatch, const std::string &name,
    size_t sizeof_key, size_t def, bool backup, bool accept, bool oldstyle_ctxmarker,
    const std::set<std::string> &stagnames, const std::set<std::string> &stagvars,
    const std::set<std::string> &mtagnames, const std::set<std::string> &mtagvars,
    bitmaps_t &bitmaps)
{
    const opt_t *opts = o.block().opts;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    const uint64_t norule = rule2key(Rule::NONE, sizeof_key, def);
    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }

    o.ws("\n#define YYCTYPE ");
    exact_uint (o, sizeof_cunit);
    o.ws("\n#define YYKEYTYPE ");
    exact_uint (o, sizeof_key);
    o.ws("\n#define YYPEEK() *cursor");
    o.ws("\n#define YYSKIP() ++cursor");
    if (backup) {
        o.ws("\n#define YYBACKUP() marker = cursor");
        o.ws("\n#define YYRESTORE() cursor = marker");
    }
    if (oldstyle_ctxmarker) {
        o.ws("\n#define YYBACKUPCTX() ctxmarker = cursor");
        o.ws("\n#define YYRESTORECTX() cursor = ctxmarker");
    }
    if (opts->tags) {
        o.ws("\n#define YYSTAGP(t) t = cursor");
        o.ws("\n#define YYSTAGN(t) t = NULL");
        o.ws("\n#define YYMTAGP(t) yymtag(&t, cursor, &yytp)");
        o.ws("\n#define YYMTAGN(t) yymtag(&t, NULL, &yytp)");
        o.ws("\n#define YYRESTORETAG(t) cursor = t");
        if (opts->stadfa) {
             o.ws("\n#define YYSTAGPD(t) t = cursor - 1");
             o.ws("\n#define YYMTAGPD(t) yymtag(&t, cursor - 1, &yytp)");
        }
    }
    o.ws("\n#define YYLESSTHAN(n) (limit - cursor) < n");
    o.ws("\n#define YYFILL(n) { break; }");
    o.ws("\n");

    o.ws("\nstatic int action_").wstring(name);
    o.ws("\n").wind(1).ws("( unsigned *pkix");
    o.ws("\n").wind(1).ws(", const YYKEYTYPE *keys");
    o.ws("\n").wind(1).ws(", const YYCTYPE *start");
    o.ws("\n").wind(1).ws(", const YYCTYPE *token");
    o.ws("\n").wind(1).ws(", const YYCTYPE **cursor");
    o.ws("\n").wind(1).ws(", YYKEYTYPE rule_act");
    o.ws("\n").wind(1).ws(")");
    o.ws("\n{");
    o.ws("\n").wind(1).ws("const unsigned kix = *pkix;");
    o.ws("\n").wind(1).ws("const long pos = token - start;");
    o.ws("\n").wind(1).ws("const long len_act = *cursor - token;");
    o.ws("\n").wind(1).ws("const long len_exp = (long) keys[kix + 1];");
    o.ws("\n").wind(1).ws("const YYKEYTYPE rule_exp = keys[kix + 2];");
    o.ws("\n").wind(1).ws("*pkix = kix + 3;");
    o.ws("\n").wind(1).ws("if (rule_exp == ").wu64(norule).ws(") {");
    o.ws("\n").wind(2).ws("fprintf");
    o.ws("\n").wind(3).ws("( stderr");
    o.ws("\n").wind(3).ws(", \"warning: lex_").wstring(name).ws(": control flow is undefined for input\"");
    o.ws("\n").wind(4).ws("\" at position %ld, rerun re2c with '-W'\\n\"");
    o.ws("\n").wind(3).ws(", pos");
    o.ws("\n").wind(3).ws(");");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n").wind(1).ws("if (len_act == len_exp && rule_act == rule_exp) {");
    o.ws("\n").wind(2).ws("const YYKEYTYPE offset = keys[kix];");
    o.ws("\n").wind(2).ws("*cursor = token + offset;");
    o.ws("\n").wind(2).ws("return 0;");
    o.ws("\n").wind(1).ws("} else {");
    o.ws("\n").wind(2).ws("fprintf");
    o.ws("\n").wind(3).ws("( stderr");
    o.ws("\n").wind(3).ws(", \"error: lex_").wstring(name).ws(": at position %ld (key %u):\\n\"");
    o.ws("\n").wind(4).ws("\"\\texpected: match length %ld, rule %u\\n\"");
    o.ws("\n").wind(4).ws("\"\\tactual:   match length %ld, rule %u\\n\"");
    o.ws("\n").wind(3).ws(", pos");
    o.ws("\n").wind(3).ws(", kix");
    o.ws("\n").wind(3).ws(", len_exp");
    o.ws("\n").wind(3).ws(", rule_exp");
    o.ws("\n").wind(3).ws(", len_act");
    o.ws("\n").wind(3).ws(", rule_act");
    o.ws("\n").wind(3).ws(");");
    o.ws("\n").wind(2).ws("return 1;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n}");

    if (!stagnames.empty()) {
        o.ws("\n");
        o.ws("\nstatic int check_stag_").wstring(name)
            .ws("(unsigned *pkix, YYKEYTYPE *keys, const YYCTYPE *tag,\n")
            .wind(1).ws("const YYCTYPE *input, const YYCTYPE *token, const char *name)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("const unsigned kix = *pkix;");
        o.ws("\n").wind(1).ws("const YYKEYTYPE\n")
            .wind(2).ws("exp = keys[kix],\n")
            .wind(2).ws("act = (YYKEYTYPE)(tag - token),\n")
            .wind(2).ws("NIL = (YYKEYTYPE)~0u;");
        o.ws("\n").wind(1).ws("*pkix = kix + 1;");
        o.ws("\n");
        o.ws("\n").wind(1).ws("if (exp == act || (exp == NIL && tag == NULL)) return 0;");
        o.ws("\n");
        o.ws("\n").wind(1).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": at position %ld, key %u: \"")
            .ws("\n").wind(2).ws("\"wrong value for tag '%s': expected %u, actual %u\\n\",")
            .ws("\n").wind(2).ws("token - input, kix, name, exp, act);");
        o.ws("\n").wind(1).ws("return 1;");
        o.ws("\n}");
    }

    if (!mtagnames.empty()) {
        o.ws("\n");
        o.ws("\ntypedef struct yymtag_t {");
        o.ws("\n").wind(1).ws("ptrdiff_t pred;");
        o.ws("\n").wind(1).ws("const YYCTYPE *elem;");
        o.ws("\n} yymtag_t;");

        o.ws("\n");
        o.ws("\ntypedef struct yymtagpool_t {");
        o.ws("\n").wind(1).ws("yymtag_t *head;");
        o.ws("\n").wind(1).ws("yymtag_t *next;");
        o.ws("\n").wind(1).ws("yymtag_t *last;");
        o.ws("\n} yymtagpool_t;");

        o.ws("\n");
        o.ws("\nstatic void yymtagpool_clear(yymtagpool_t *tp)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("tp->next = tp->head;");
        o.ws("\n}");

        o.ws("\n");
        o.ws("\nstatic void yymtagpool_init(yymtagpool_t *tp)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("static const unsigned size = 4096;");
        o.ws("\n").wind(1).ws("tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t));");
        o.ws("\n").wind(1).ws("tp->next = tp->head;");
        o.ws("\n").wind(1).ws("tp->last = tp->head + size;");
        o.ws("\n}");

        o.ws("\n");
        o.ws("\nstatic void yymtagpool_free(yymtagpool_t *tp)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("free(tp->head);");
        o.ws("\n").wind(1).ws("tp->head = tp->next = tp->last = NULL;");
        o.ws("\n}");

        o.ws("\n");
        o.ws("\nstatic yymtag_t *yymtagpool_next(yymtagpool_t *tp)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("if (tp->next == tp->last) {");
        o.ws("\n").wind(2).ws("const unsigned size = tp->last - tp->head;");
        o.ws("\n").wind(2).ws("yymtag_t *head = (yymtag_t*)malloc(2 * size * sizeof(yymtag_t));");
        o.ws("\n").wind(2).ws("memcpy(head, tp->head, size * sizeof(yymtag_t));");
        o.ws("\n").wind(2).ws("free(tp->head);");
        o.ws("\n").wind(2).ws("tp->head = head;");
        o.ws("\n").wind(2).ws("tp->next = head + size;");
        o.ws("\n").wind(2).ws("tp->last = head + size * 2;");
        o.ws("\n").wind(1).ws("}");
        o.ws("\n").wind(1).ws("return tp->next++;");
        o.ws("\n}");

        o.ws("\n");
        o.ws("\nstatic void yymtag(ptrdiff_t *pt, const YYCTYPE *t, yymtagpool_t *tp)");
        o.ws("\n{");
        o.ws("\n").wind(1).ws("yymtag_t *n = yymtagpool_next(tp);");
        o.ws("\n").wind(1).ws("n->pred = *pt;");
        o.ws("\n").wind(1).ws("n->elem = t;");
        o.ws("\n").wind(1).ws("*pt = n - tp->head;");
        o.ws("\n}");

        o.ws("\n");
        o.ws("\nstatic int check_mtag_").wstring(name)
            .ws("(unsigned *pkix, YYKEYTYPE *keys, const yymtagpool_t *tp, ptrdiff_t mtag,\n")
            .wind(1).ws("const YYCTYPE *input, const YYCTYPE *token, const char *name)");
        o.ws("\n{");
//        o.ws("\n").wind(1).ws("check_key_count_").wstring(name).ws("(1) && return 1;");
        o.ws("\n").wind(1).ws("const unsigned kix = *pkix;");
        o.ws("\n").wind(1).ws("YYKEYTYPE n = keys[kix];");
        o.ws("\n").wind(1).ws("*pkix = kix + n + 1;");
//        o.ws("\n").wind(1).ws("check_key_count_").wstring(name).ws("(n) && return 1;");
        o.ws("\n").wind(1).ws("for (; n > 0; --n) {");
        o.ws("\n").wind(2).ws("if (mtag == -1) {");
        o.ws("\n").wind(3).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": at position %ld, key %u: \"")
            .ws("\n").wind(4).ws("\"history for tag '%s' is too short\\n\",")
            .ws("\n").wind(4).ws("token - input, kix + n, name);");
        o.ws("\n").wind(3).ws("return 1;");
        o.ws("\n").wind(2).ws("}");
        o.ws("\n").wind(2).ws("const YYCTYPE *tag = (tp->head + mtag)->elem;");
        o.ws("\n").wind(2).ws("mtag = (tp->head + mtag)->pred;");
        o.ws("\n").wind(2).ws("const YYKEYTYPE\n")
            .wind(3).ws("exp = keys[kix + n],\n")
            .wind(3).ws("act = (YYKEYTYPE)(tag - token),\n")
            .wind(3).ws("NIL = (YYKEYTYPE)~0u;");
        o.ws("\n").wind(2).ws("if (!(exp == act || (exp == NIL && tag == NULL))) {");
        o.ws("\n").wind(3).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": at position %ld, key %u: \"")
            .ws("\n").wind(4).ws("\"wrong value for tag '%s': expected %u, actual %u\\n\",")
            .ws("\n").wind(4).ws("token - input, kix + n, name, exp, act);");
        o.ws("\n").wind(3).ws("return 1;");
        o.ws("\n").wind(2).ws("}");
        o.ws("\n").wind(1).ws("}");
        o.ws("\n").wind(1).ws("if (mtag != -1) {");
        o.ws("\n").wind(2).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": at position %ld, key %u: \"")
            .ws("\n").wind(3).ws("\"history for tag '%s' is too long\\n\",")
            .ws("\n").wind(3).ws("token - input, kix, name);");
        o.ws("\n").wind(2).ws("return 1;");
        o.ws("\n").wind(1).ws("}");
        o.ws("\n").wind(1).ws("return 0;");
        o.ws("\n}");
    }

    o.ws("\n");
    o.ws("\nstatic int check_key_count_").wstring(name).ws("(unsigned have, unsigned used, unsigned need)");
    o.ws("\n{");
    o.ws("\n").wind(1).ws("if (used + need <= have) return 0;");
    o.ws("\n").wind(1).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": not enough keys\\n\");");
    o.ws("\n").wind(1).ws("return 1;");
    o.ws("\n}");
    o.ws("\n");

    o.ws("\nint lex_").wstring(name).ws("()");
    o.ws("\n{");
    o.ws("\n").wind(1).ws("const size_t padding = ").wu64(maxfill).ws("; /* YYMAXFILL */");
    o.ws("\n").wind(1).ws("int status = 0;");
    o.ws("\n").wind(1).ws("size_t input_len = 0;");
    o.ws("\n").wind(1).ws("size_t keys_count = 0;");
    o.ws("\n").wind(1).ws("YYCTYPE *input = NULL;");
    o.ws("\n").wind(1).ws("YYKEYTYPE *keys = NULL;");
    o.ws("\n").wind(1).ws("const YYCTYPE *cursor = NULL;");
    o.ws("\n").wind(1).ws("const YYCTYPE *limit = NULL;");
    o.ws("\n").wind(1).ws("const YYCTYPE *token = NULL;");
    o.ws("\n").wind(1).ws("const YYCTYPE *eof = NULL;");
    if (opts->posix_syntax) {
        o.ws("\n").wind(1).ws("size_t yynmatch;");
        o.ws("\n").wind(1).ws("const YYCTYPE *yypmatch[").wu64(maxnmatch).ws(" * 2];");
    }
    o.ws("\n").wind(1).ws("unsigned int i = 0;");
    if (!mtagnames.empty()) {
        o.ws("\n");
        o.ws("\n").wind(1).ws("yymtagpool_t yytp;");
        o.ws("\n").wind(1).ws("yymtagpool_init(&yytp);");
    }
    o.ws("\n");
    o.ws("\n").wind(1).ws("input = (YYCTYPE *) read_file");
    o.ws("\n").wind(2).ws("(\"").wstring(filename).ws(".").wstring(name).ws(".input\"");
    o.ws("\n").wind(2).ws(", sizeof (YYCTYPE)");
    o.ws("\n").wind(2).ws(", padding");
    o.ws("\n").wind(2).ws(", &input_len");
    o.ws("\n").wind(2).ws(");");
    o.ws("\n").wind(1).ws("if (input == NULL) {");
    o.ws("\n").wind(2).ws("status = 1;");
    o.ws("\n").wind(2).ws("goto end;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    if (sizeof_cunit > 1) {
        o.ws("\n").wind(1).ws("for (i = 0; i < input_len; ++i) {");
        from_le(o, 2, sizeof_cunit, "input[i]");
        o.ws("\n").wind(1).ws("}");
        o.ws("\n");
    }
    o.ws("\n").wind(1).ws("keys = (YYKEYTYPE *) read_file");
    o.ws("\n").wind(2).ws("(\"").wstring(filename).ws(".").wstring(name).ws(".keys\"");
    o.ws("\n").wind(2).ws(", sizeof (YYKEYTYPE)");
    o.ws("\n").wind(2).ws(", 0");
    o.ws("\n").wind(2).ws(", &keys_count");
    o.ws("\n").wind(2).ws(");");
    o.ws("\n").wind(1).ws("if (keys == NULL) {");
    o.ws("\n").wind(2).ws("status = 1;");
    o.ws("\n").wind(2).ws("goto end;");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    if (sizeof_key > 1)
    {
        o.ws("\n").wind(1).ws("for (i = 0; i < keys_count; ++i) {");
        from_le(o, 2, sizeof_key, "keys[i]");
        o.ws("\n").wind(1).ws("}");
        o.ws("\n");
    }
    o.ws("\n").wind(1).ws("cursor = input;");
    o.ws("\n").wind(1).ws("limit = input + input_len + padding;");
    o.ws("\n").wind(1).ws("eof = input + input_len;");
    o.ws("\n");
    o.ws("\n").wind(1).ws("for (i = 0; status == 0 && cursor < eof && i < keys_count;) {");
    o.ws("\n").wind(2).ws("token = cursor;");
    if (backup) {
        o.ws("\n").wind(2).ws("const YYCTYPE *marker = NULL;");
    }
    if (oldstyle_ctxmarker) {
        o.ws("\n").wind(2).ws("const YYCTYPE *ctxmarker = NULL;");
    }
    o.ws("\n").wind(2).ws("YYCTYPE yych;");
    if (accept) {
        o.ws("\n").wind(2).ws("unsigned int yyaccept = 0;");
    }

    // autogenerated stag variables
    ConfTags conf("\n" + indent(2, opts->indString) + "const YYCTYPE *@@ = NULL;", "");
    output_tags(o.stream(), 0, conf, stagnames, opts);
    // user-defined stag variables
    std::set<std::string>::const_iterator
        var1 = stagvars.begin(),
        var2 = stagvars.end();
    if (var1 != var2) {
        o.ws("\n").wind(2).ws("const YYCTYPE *").wstring(*var1);
        for (++var1; var1 != var2; ++var1) {
            o.ws(", *").wstring(*var1);
        }
        o.ws(";");
    }
    if (!mtagnames.empty()) {
        o.ws("\n").wind(2).ws("yymtagpool_clear(&yytp);");
        // autogenerated mtag variables
        conf.format = "ptrdiff_t @@ = -1;";
        output_tags(o.stream(), 0, conf, mtagnames, opts);
        // user-defined mtag variables
        var1 = mtagvars.begin();
        var2 = mtagvars.end();
        if (var1 != var2) {
            o.ws("\n").wind(2).ws("ptrdiff_t ").wstring(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.ws(", ").wstring(*var1);
            }
            o.ws(";");
        }
    }

    o.ws("\n");
    if (opts->bFlag) {
        bitmaps.gen(o, 2);
    }
    o.ws("\n");
}

void emit_end(Output &o, const std::string &name, bool backup, bool oldstyle_ctxmarker,
    const std::set<std::string> &mtagnames)
{
    o.ws("\n").wind(1).ws("}");
    o.ws("\n").wind(1).ws("if (status == 0) {");
    o.ws("\n").wind(2).ws("if (cursor != eof) {");
    o.ws("\n").wind(3).ws("status = 1;");
    o.ws("\n").wind(3).ws("const long pos = token - input;");
    o.ws("\n").wind(3).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": unused input strings left at position %ld\\n\", pos);");
    o.ws("\n").wind(2).ws("}");
    o.ws("\n").wind(2).ws("if (i != keys_count) {");
    o.ws("\n").wind(3).ws("status = 1;");
    o.ws("\n").wind(3).ws("fprintf(stderr, \"error: lex_").wstring(name).ws(": unused keys left after %u keys\\n\", i);");
    o.ws("\n").wind(2).ws("}");
    o.ws("\n").wind(1).ws("}");
    o.ws("\n");
    o.ws("\nend:");
    o.ws("\n").wind(1).ws("free(input);");
    o.ws("\n").wind(1).ws("free(keys);");
    if (!mtagnames.empty()) {
        o.ws("\n").wind(1).ws("yymtagpool_free(&yytp);");
    }
    o.ws("\n");
    o.ws("\n").wind(1).ws("return status;");
    o.ws("\n}");
    o.ws("\n");
    o.ws("\n#undef YYCTYPE");
    o.ws("\n#undef YYKEYTYPE");
    o.ws("\n#undef YYPEEK");
    o.ws("\n#undef YYSKIP");
    if (backup) {
        o.ws("\n#undef YYBACKUP");
        o.ws("\n#undef YYRESTORE");
    }
    if (oldstyle_ctxmarker) {
        o.ws("\n#undef YYBACKUPCTX");
        o.ws("\n#undef YYRESTORECTX");
    }
    if (o.block().opts->tags) {
        o.ws("\n#undef YYBACKUPTAG");
        o.ws("\n#undef YYRESTORETAG");
        o.ws("\n#undef YYCOPYTAG");
    }
    o.ws("\n#undef YYLESSTHAN");
    o.ws("\n#undef YYFILL");
    o.ws("\n");
}

void emit_epilog(Output &o, const std::set<std::string> &names)
{
    o.ws("\n").ws("int main()");
    o.ws("\n").ws("{");

    for (std::set<std::string>::const_iterator i = names.begin(); i != names.end(); ++i) {
        o.ws("\n").wind(1).ws("if(lex_").wstring(*i).ws("() != 0) {");
        o.ws("\n").wind(2).ws("return 1;");
        o.ws("\n").wind(1).ws("}");
    }

    o.ws("\n").wind(1).ws("return 0;");
    o.ws("\n}");
    o.ws("\n");
}

void emit_action(Output &o, uint32_t ind, const DFA &dfa, size_t rid)
{
    const std::string &name = dfa.name;
    const Rule &r = dfa.rules[rid];
    const uint64_t rkey = rule2key(rid, dfa.key_size, dfa.def_rule);
    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    o.wind(ind).ws("status = check_key_count_").wstring(name).ws("(keys_count, i, ")
        .wu64(ntag).ws(")\n").wind(ind + 1).ws(" || action_").wstring(name)
        .ws("(&i, keys, input, token, &cursor, ").wu64(rkey).ws(")");

    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        const std::string tname = tag_expr(tag, false);
        if (history(tag)) {
            o.ws("\n").wind(ind + 1).ws(" || check_mtag_").wstring(name)
                .ws("(&i, keys, &yytp, ").wstring(tname).ws(", input, token, \"")
                .wstring(tname).ws("\")");
        }
        else {
            o.ws("\n").wind(ind + 1).ws(" || check_stag_").wstring(name)
                .ws("(&i, keys, ").wstring(tname).ws(", input, token, \"")
                .wstring(tname).ws("\")");
        }
    }

    o.ws(";\n");
    o.wind(ind).ws("continue;\n");
}

} // namespace re2c
