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

static void from_le(Output &output, CodeStmts *code, const char *expr, size_t size)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    append_stmt(code, code_stmt_text(alc, "/* from little-endian to host-endian */"));
    o.cstr("unsigned char *p = (unsigned char*)&").cstr(expr).cstr(";");
    append_stmt(code, code_stmt_text(alc, o.flush()));
    o.cstr(expr).cstr(" = p[0]");
    for (uint32_t i = 1; i < size; ++i) {
        o.cstr(" + (p[").u32(i).cstr("] << ").u32(i * 8).cstr("u)");
    }
    o.cstr(";");
    append_stmt(code, code_stmt_text(alc, o.flush()));
}

CodeStmt *emit_skeleton_prolog(Output &output)
{
    code_alc_t &alc = output.allocator;
    CodeText if_cond;
    CodeStmts *if_code;

    CodeStmts *code = code_stmts(alc);

    append_stmt(code, code_stmt_textraw(alc, ""));
    append_stmt(code, code_stmt_textraw(alc, "#include <stddef.h> /* size_t */"));
    append_stmt(code, code_stmt_textraw(alc, "#include <stdio.h>"));
    append_stmt(code, code_stmt_textraw(alc, "#include <stdlib.h> /* malloc, free */"));
    append_stmt(code, code_stmt_textraw(alc, "#include <string.h> /* memcpy */"));
    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code, code_stmt_text(alc, "static void *read_file"));

    CodeStmts *params = code_stmts(alc);
    append_stmt(params, code_stmt_text(alc, "( const char *fname"));
    append_stmt(params, code_stmt_text(alc, ", size_t unit"));
    append_stmt(params, code_stmt_text(alc, ", size_t padding"));
    append_stmt(params, code_stmt_text(alc, ", size_t *pfsize"));
    append_stmt(params, code_stmt_text(alc, ")"));
    append_stmt(code, code_block(alc, params, CodeBlock::INDENTED));

    CodeStmts *block = code_stmts(alc);

    append_stmt(block, code_stmt_text(alc, "void *buffer = NULL;"));
    append_stmt(block, code_stmt_text(alc, "size_t fsize = 0;"));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "/* open file */"));
    append_stmt(block, code_stmt_text(alc, "FILE *f = fopen(fname, \"rb\");"));
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "goto error;"));
    append_stmt(block, code_stmt_if_then_else(alc, "f == NULL", if_code, NULL, false));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "/* get file size */"));
    append_stmt(block, code_stmt_text(alc, "fseek(f, 0, SEEK_END);"));
    append_stmt(block, code_stmt_text(alc, "fsize = (size_t) ftell(f) / unit;"));
    append_stmt(block, code_stmt_text(alc, "fseek(f, 0, SEEK_SET);"));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "/* allocate memory for file and padding */"));
    append_stmt(block, code_stmt_text(alc, "buffer = malloc(unit * (fsize + padding));"));
    if_cond = "buffer == NULL";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "goto error;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL, false));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "/* read the whole file in memory */"));
    if_cond = "fread(buffer, unit, fsize, f) != fsize";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "goto error;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL, false));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "fclose(f);"));
    append_stmt(block, code_stmt_text(alc, "*pfsize = fsize;"));
    append_stmt(block, code_stmt_text(alc, "return buffer;"));

    append_stmt(block, code_stmt_textraw(alc, ""));
    append_stmt(block, code_stmt_textraw(alc, "error:"));

    append_stmt(block, code_stmt_text(alc,
        "fprintf(stderr, \"error: cannot read file '%s'\\n\", fname);"));
    append_stmt(block, code_stmt_text(alc, "free(buffer);"));
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "fclose(f);"));
    append_stmt(block, code_stmt_if_then_else(alc, "f != NULL", if_code, NULL, false));
    append_stmt(block, code_stmt_text(alc, "return NULL;"));

    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    return code_block(alc, code, CodeBlock::RAW);
}

static void emit_skeleton_defines(Output &output, CodeStmts *code, const DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();

    append_stmt(code, code_stmt_textraw(alc, ""));

    o.cstr("#define YYCTYPE ");
    exact_uint(o, sizeof_cunit);
    append_stmt(code, code_stmt_textraw(alc, o.flush()));

    o.cstr("#define YYKEYTYPE ");
    exact_uint(o, dfa.key_size);
    append_stmt(code, code_stmt_textraw(alc, o.flush()));

    append_stmt(code, code_stmt_textraw(alc, "#define YYPEEK() *cursor"));
    append_stmt(code, code_stmt_textraw(alc, "#define YYSKIP() ++cursor"));

    if (dfa.need_backup) {
        append_stmt(code, code_stmt_textraw(alc, "#define YYBACKUP() marker = cursor"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYRESTORE() cursor = marker"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append_stmt(code,
            code_stmt_textraw(alc, "#define YYBACKUPCTX() ctxmarker = cursor"));
        append_stmt(code,
            code_stmt_textraw(alc, "#define YYRESTORECTX() cursor = ctxmarker"));
    }
    if (opts->tags) {
        append_stmt(code, code_stmt_textraw(alc, "#define YYSTAGP(t) t = cursor"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYSTAGN(t) t = NULL"));
        append_stmt(code,
            code_stmt_textraw(alc, "#define YYMTAGP(t) yymtag(&t, cursor, &yytp)"));
        append_stmt(code,
            code_stmt_textraw(alc, "#define YYMTAGN(t) yymtag(&t, NULL, &yytp)"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYRESTORETAG(t) cursor = t"));
        if (opts->stadfa) {
            append_stmt(code,
                code_stmt_textraw(alc, "#define YYSTAGPD(t) t = cursor - 1"));
            append_stmt(code, code_stmt_textraw(alc,
                "#define YYMTAGPD(t) yymtag(&t, cursor - 1, &yytp)"));
        }
    }
    append_stmt(code,
        code_stmt_textraw(alc, "#define YYLESSTHAN(n) (limit - cursor) < n"));
    append_stmt(code, code_stmt_textraw(alc, "#define YYFILL(n) { break; }"));
    append_stmt(code, code_stmt_textraw(alc, ""));
}

static void emit_skeleton_function_action(Output &output, CodeStmts *code, const DFA &dfa)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const uint64_t norule = rule2key(Rule::NONE, dfa.key_size, dfa.def_rule);

    o.cstr("static int action_").str(dfa.name);
    append_stmt(code, code_stmt_text(alc, o.flush()));

    CodeStmts *params = code_stmts(alc);
    append_stmt(params, code_stmt_text(alc, "( unsigned *pkix"));
    append_stmt(params, code_stmt_text(alc, ", const YYKEYTYPE *keys"));
    append_stmt(params, code_stmt_text(alc, ", const YYCTYPE *start"));
    append_stmt(params, code_stmt_text(alc, ", const YYCTYPE *token"));
    append_stmt(params, code_stmt_text(alc, ", const YYCTYPE **cursor"));
    append_stmt(params, code_stmt_text(alc, ", YYKEYTYPE rule_act"));
    append_stmt(params, code_stmt_text(alc, ")"));
    append_stmt(code, code_block(alc, params, CodeBlock::INDENTED));

    CodeStmts *body = code_stmts(alc);

    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "const long pos = token - start;"));
    append_stmt(body, code_stmt_text(alc, "const long len_act = *cursor - token;"));
    append_stmt(body, code_stmt_text(alc, "const long len_exp = (long) keys[kix + 1];"));
    append_stmt(body, code_stmt_text(alc, "const YYKEYTYPE rule_exp = keys[kix + 2];"));
    append_stmt(body, code_stmt_text(alc, "*pkix = kix + 3;"));

    o.cstr("rule_exp == ").u64(norule);
    CodeText if1_cond = o.flush();

    CodeStmts *if1_code = code_stmts(alc);
    append_stmt(if1_code, code_stmt_text(alc, "fprintf"));

    CodeStmts *args1 = code_stmts(alc);
    append_stmt(args1, code_stmt_text(alc, "( stderr"));
    o.cstr(", \"warning: lex_").str(dfa.name)
        .cstr(": control flow is undefined for input\"");
    append_stmt(args1, code_stmt_text(alc, o.flush()));
    CodeStmts *hang1 = code_stmts(alc);
    append_stmt(hang1, code_stmt_text(alc,
        "\" at position %ld, rerun re2c with '-W'\\n\""));
    append_stmt(args1, code_block(alc, hang1, CodeBlock::INDENTED));
    append_stmt(args1, code_stmt_text(alc, ", pos"));
    append_stmt(args1, code_stmt_text(alc, ");"));
    append_stmt(if1_code, code_block(alc, args1, CodeBlock::INDENTED));

    append_stmt(body, code_stmt_if_then_else(alc, if1_cond, if1_code, NULL));

    CodeText if2_cond = "len_act == len_exp && rule_act == rule_exp";

    CodeStmts *if2_code = code_stmts(alc);
    append_stmt(if2_code, code_stmt_text(alc, "const YYKEYTYPE offset = keys[kix];"));
    append_stmt(if2_code, code_stmt_text(alc, "*cursor = token + offset;"));
    append_stmt(if2_code, code_stmt_text(alc, "return 0;"));

    CodeStmts *else2_code = code_stmts(alc);
    append_stmt(else2_code, code_stmt_text(alc, "fprintf"));

    CodeStmts *args2 = code_stmts(alc);
    append_stmt(args2, code_stmt_text(alc, "( stderr"));
    o.cstr(", \"error: lex_").str(dfa.name).cstr(": at position %ld (key %u):\\n\"");
    append_stmt(args2, code_stmt_text(alc, o.flush()));
    CodeStmts *hang2 = code_stmts(alc);
    append_stmt(hang2, code_stmt_text(alc,
        "\"\\texpected: match length %ld, rule %u\\n\""));
    append_stmt(hang2, code_stmt_text(alc,
        "\"\\tactual:   match length %ld, rule %u\\n\""));
    append_stmt(args2, code_block(alc, hang2, CodeBlock::INDENTED));
    append_stmt(args2, code_stmt_text(alc, ", pos"));
    append_stmt(args2, code_stmt_text(alc, ", kix"));
    append_stmt(args2, code_stmt_text(alc, ", len_exp"));
    append_stmt(args2, code_stmt_text(alc, ", rule_exp"));
    append_stmt(args2, code_stmt_text(alc, ", len_act"));
    append_stmt(args2, code_stmt_text(alc, ", rule_act"));
    append_stmt(args2, code_stmt_text(alc, ");"));
    append_stmt(else2_code, code_block(alc, args2, CodeBlock::INDENTED));

    append_stmt(else2_code, code_stmt_text(alc, "return 1;"));

    append_stmt(body, code_stmt_if_then_else(alc, if2_cond, if2_code, else2_code));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_stags(Output &output, CodeStmts *code, const DFA &dfa)
{
    if (dfa.stagnames.empty()) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    append_stmt(code, code_stmt_textraw(alc, ""));

    o.cstr("static int check_stag_").str(dfa.name)
        .cstr("(unsigned *pkix, YYKEYTYPE *keys, const YYCTYPE *tag,");
    append_stmt(code, code_stmt_text(alc, o.flush()));
    CodeStmts *params = code_stmts(alc);
    append_stmt(params, code_stmt_text(alc,
        "const YYCTYPE *input, const YYCTYPE *token, const char *name)"));
    append_stmt(code, code_block(alc, params, CodeBlock::INDENTED));

    CodeStmts *body = code_stmts(alc);

    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "const YYKEYTYPE"));
    CodeStmts *block1 = code_stmts(alc);
    append_stmt(block1, code_stmt_text(alc, "exp = keys[kix],"));
    append_stmt(block1, code_stmt_text(alc, "act = (YYKEYTYPE)(tag - token),"));
    append_stmt(block1, code_stmt_text(alc, "NIL = (YYKEYTYPE)~0u;"));
    append_stmt(body, code_block(alc, block1, CodeBlock::INDENTED));

    append_stmt(body, code_stmt_text(alc, "*pkix = kix + 1;"));
    append_stmt(body, code_stmt_textraw(alc, ""));

    CodeText if_cond = "exp == act || (exp == NIL && tag == NULL)";
    CodeStmts *if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "return 0;"));
    append_stmt(body, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(body, code_stmt_textraw(alc, ""));

    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"");
    append_stmt(body, code_stmt_text(alc, o.flush()));
    CodeStmts *args = code_stmts(alc);
    append_stmt(args, code_stmt_text(alc,
        "\"wrong value for tag '%s': expected %u, actual %u\\n\","));
    append_stmt(args, code_stmt_text(alc,
        "token - input, kix, name, exp, act);"));
    append_stmt(body, code_block(alc, args, CodeBlock::INDENTED));

    append_stmt(body, code_stmt_text(alc, "return 1;"));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_mtags(Output &output, CodeStmts *code, const DFA &dfa)
{
    if (dfa.mtagnames.empty()) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeStmts *block;

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code, code_stmt_text(alc, "typedef struct yymtag_t {"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "ptrdiff_t pred;"));
    append_stmt(block, code_stmt_text(alc, "const YYCTYPE *elem;"));
    append_stmt(code, code_block(alc, block, CodeBlock::INDENTED));
    append_stmt(code, code_stmt_text(alc, "} yymtag_t;"));

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code, code_stmt_text(alc, "typedef struct yymtagpool_t {"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "yymtag_t *head;"));
    append_stmt(block, code_stmt_text(alc, "yymtag_t *next;"));
    append_stmt(block, code_stmt_text(alc, "yymtag_t *last;"));
    append_stmt(code, code_block(alc, block, CodeBlock::INDENTED));
    append_stmt(code, code_stmt_text(alc, "} yymtagpool_t;"));

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code,
        code_stmt_text(alc, "static void yymtagpool_clear(yymtagpool_t *tp)"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "tp->next = tp->head;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));
    append_stmt(code,
        code_stmt_text(alc, "static void yymtagpool_init(yymtagpool_t *tp)"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "static const unsigned size = 4096;"));
    append_stmt(block,
        code_stmt_text(alc, "tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t));"));
    append_stmt(block, code_stmt_text(alc, "tp->next = tp->head;"));
    append_stmt(block, code_stmt_text(alc, "tp->last = tp->head + size;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code,
        code_stmt_text(alc, "static void yymtagpool_free(yymtagpool_t *tp)"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "free(tp->head);"));
    append_stmt(block, code_stmt_text(alc, "tp->head = tp->next = tp->last = NULL;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code, code_stmt_text(alc,
        "static yymtag_t *yymtagpool_next(yymtagpool_t *tp)"));
    block = code_stmts(alc);
    CodeText if_cond = "tp->next == tp->last";
    CodeStmts *if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc,
        "const unsigned size = tp->last - tp->head;"));
    append_stmt(if_code, code_stmt_text(alc,
        "yymtag_t *head = (yymtag_t*)malloc(2 * size * sizeof(yymtag_t));"));
    append_stmt(if_code, code_stmt_text(alc,
        "memcpy(head, tp->head, size * sizeof(yymtag_t));"));
    append_stmt(if_code, code_stmt_text(alc, "free(tp->head);"));
    append_stmt(if_code, code_stmt_text(alc, "tp->head = head;"));
    append_stmt(if_code, code_stmt_text(alc, "tp->next = head + size;"));
    append_stmt(if_code, code_stmt_text(alc, "tp->last = head + size * 2;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));
    append_stmt(block, code_stmt_text(alc, "return tp->next++;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    append_stmt(code, code_stmt_text(alc,
        "static void yymtag(ptrdiff_t *pt, const YYCTYPE *t, yymtagpool_t *tp)"));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "yymtag_t *n = yymtagpool_next(tp);"));
    append_stmt(block, code_stmt_text(alc, "n->pred = *pt;"));
    append_stmt(block, code_stmt_text(alc, "n->elem = t;"));
    append_stmt(block, code_stmt_text(alc, "*pt = n - tp->head;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    o.cstr("static int check_mtag_").str(dfa.name)
        .cstr("(unsigned *pkix, YYKEYTYPE *keys, const yymtagpool_t *tp, ptrdiff_t mtag,");
    append_stmt(code, code_stmt_text(alc, o.flush()));
    CodeStmts *params = code_stmts(alc);
    append_stmt(params, code_stmt_text(alc,
        "const YYCTYPE *input, const YYCTYPE *token, const char *name)"));
    append_stmt(code, code_block(alc, params, CodeBlock::INDENTED));

    CodeStmts *body = code_stmts(alc);
    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "YYKEYTYPE n = keys[kix];"));
    append_stmt(body, code_stmt_text(alc, "*pkix = kix + n + 1;"));

    o.cstr("for (; n > 0; --n) {");
    append_stmt(body, code_stmt_text(alc, o.flush()));

    CodeStmts *block1 = code_stmts(alc); // for loop

    CodeText if1_cond = "mtag == -1";
    CodeStmts *if1_code = code_stmts(alc);
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"");
    append_stmt(if1_code, code_stmt_text(alc, o.flush()));
    CodeStmts *args1 = code_stmts(alc);
    append_stmt(args1, code_stmt_text(alc, "\"history for tag '%s' is too short\\n\","));
    append_stmt(args1, code_stmt_text(alc, "token - input, kix + n, name);"));
    append_stmt(if1_code, code_block(alc, args1, CodeBlock::INDENTED));
    append_stmt(if1_code, code_stmt_text(alc, "return 1;"));
    append_stmt(block1, code_stmt_if_then_else(alc, if1_cond, if1_code, NULL));

    append_stmt(block1, code_stmt_text(alc,
        "const YYCTYPE *tag = (tp->head + mtag)->elem;"));
    append_stmt(block1, code_stmt_text(alc, "mtag = (tp->head + mtag)->pred;"));

    append_stmt(block1, code_stmt_text(alc, "const YYKEYTYPE"));
    CodeStmts *hang1 = code_stmts(alc);
    append_stmt(hang1, code_stmt_text(alc, "exp = keys[kix + n],"));
    append_stmt(hang1, code_stmt_text(alc, "act = (YYKEYTYPE)(tag - token),"));
    append_stmt(hang1, code_stmt_text(alc, "NIL = (YYKEYTYPE)~0u;"));
    append_stmt(block1, code_block(alc, hang1, CodeBlock::INDENTED));

    CodeText if2_cond = "!(exp == act || (exp == NIL && tag == NULL))";
    CodeStmts *if2_code = code_stmts(alc);
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"");
    append_stmt(if2_code, code_stmt_text(alc, o.flush()));
    CodeStmts *args2 = code_stmts(alc);
    append_stmt(args2, code_stmt_text(alc,
        "\"wrong value for tag '%s': expected %u, actual %u\\n\","));
    append_stmt(args2, code_stmt_text(alc, "token - input, kix + n, name, exp, act);"));
    append_stmt(if2_code, code_block(alc, args2, CodeBlock::INDENTED));
    append_stmt(if2_code, code_stmt_text(alc, "return 1;"));
    append_stmt(block1, code_stmt_if_then_else(alc, if2_cond, if2_code, NULL));

    append_stmt(body, code_block(alc, block1, CodeBlock::INDENTED));
    append_stmt(body, code_stmt_text(alc, "}")); // end of for loop

    CodeText if3_cond = "mtag != -1";
    CodeStmts *if3_code = code_stmts(alc);
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"");
    append_stmt(if3_code, code_stmt_text(alc, o.flush()));
    CodeStmts *args3 = code_stmts(alc);
    append_stmt(args3, code_stmt_text(alc, "\"history for tag '%s' is too long\\n\","));
    append_stmt(args3, code_stmt_text(alc, "token - input, kix, name);"));
    append_stmt(if3_code, code_block(alc, args3, CodeBlock::INDENTED));
    append_stmt(if3_code, code_stmt_text(alc, "return 1;"));
    append_stmt(body, code_stmt_if_then_else(alc, if3_cond, if3_code, NULL));

    append_stmt(body, code_stmt_text(alc, "return 0;"));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

void emit_skeleton(Output &output, CodeStmts *code, DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    std::set<std::string>::const_iterator var1, var2;
    CodeStmts *block, *block2, *args, *if_code;
    CodeText if_cond;

    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }

    emit_skeleton_defines(output, code, dfa);
    emit_skeleton_function_action(output, code, dfa);
    emit_skeleton_stags(output, code, dfa);
    emit_skeleton_mtags(output, code, dfa);

    append_stmt(code, code_stmt_textraw(alc, ""));

    o.cstr("static int check_key_count_").str(dfa.name)
        .cstr("(unsigned have, unsigned used, unsigned need)");
    append_stmt(code, code_stmt_text(alc, o.flush()));
    block = code_stmts(alc);
    if_cond = "used + need <= have";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "return 0;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": not enough keys\\n\");");
    append_stmt(block, code_stmt_text(alc, o.flush()));
    append_stmt(block, code_stmt_text(alc, "return 1;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    o.cstr("int lex_").str(dfa.name).cstr("()");
    append_stmt(code, code_stmt_text(alc, o.flush()));
    block = code_stmts(alc);
    o.cstr("const size_t padding = ").u64(dfa.max_fill).cstr("; /* YYMAXFILL */");
    append_stmt(block, code_stmt_text(alc, o.flush()));
    append_stmt(block, code_stmt_text(alc, "int status = 0;"));
    append_stmt(block, code_stmt_text(alc, "size_t input_len = 0;"));
    append_stmt(block, code_stmt_text(alc, "size_t keys_count = 0;"));
    append_stmt(block, code_stmt_text(alc, "YYCTYPE *input = NULL;"));
    append_stmt(block, code_stmt_text(alc, "YYKEYTYPE *keys = NULL;"));
    append_stmt(block, code_stmt_text(alc, "const YYCTYPE *cursor = NULL;"));
    append_stmt(block, code_stmt_text(alc, "const YYCTYPE *limit = NULL;"));
    append_stmt(block, code_stmt_text(alc, "const YYCTYPE *token = NULL;"));
    append_stmt(block, code_stmt_text(alc, "const YYCTYPE *eof = NULL;"));
    if (opts->posix_syntax) {
        append_stmt(block, code_stmt_text(alc, "size_t yynmatch;"));
        o.cstr("const YYCTYPE *yypmatch[").u64(dfa.max_nmatch).cstr(" * 2];");
        append_stmt(block, code_stmt_text(alc, o.flush()));
    }
    append_stmt(block, code_stmt_text(alc, "unsigned int i = 0;"));
    if (!dfa.mtagnames.empty()) {
        append_stmt(block, code_stmt_textraw(alc, ""));
        append_stmt(block, code_stmt_text(alc, "yymtagpool_t yytp;"));
        append_stmt(block, code_stmt_text(alc, "yymtagpool_init(&yytp);"));
    }

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc, "input = (YYCTYPE *) read_file"));
    args = code_stmts(alc);
    o.cstr("(\"").str(filename).cstr(".").str(dfa.name).cstr(".input\"");
    append_stmt(args, code_stmt_text(alc, o.flush()));
    append_stmt(args, code_stmt_text(alc, ", sizeof (YYCTYPE)"));
    append_stmt(args, code_stmt_text(alc, ", padding"));
    append_stmt(args, code_stmt_text(alc, ", &input_len"));
    append_stmt(args, code_stmt_text(alc, ");"));
    append_stmt(block, code_block(alc, args, CodeBlock::INDENTED));
    if_cond = "input == NULL";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if_code, code_stmt_text(alc, "goto end;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(block, code_stmt_textraw(alc, ""));

    if (sizeof_cunit > 1) {
        o.cstr("for (i = 0; i < input_len; ++i) {");
        append_stmt(block, code_stmt_text(alc, o.flush()));
        block2 = code_stmts(alc);
        from_le(output, block2, "input[i]", opts->encoding.szCodeUnit());
        append_stmt(block, code_block(alc, block2, CodeBlock::INDENTED));
        append_stmt(block, code_stmt_text(alc, "}"));
        append_stmt(block, code_stmt_textraw(alc, ""));
    }

    append_stmt(block, code_stmt_text(alc, "keys = (YYKEYTYPE *) read_file"));
    args = code_stmts(alc);
    o.cstr("(\"").str(filename).cstr(".").str(dfa.name).cstr(".keys\"");
    append_stmt(args, code_stmt_text(alc, o.flush()));
    append_stmt(args, code_stmt_text(alc, ", sizeof (YYKEYTYPE)"));
    append_stmt(args, code_stmt_text(alc, ", 0"));
    append_stmt(args, code_stmt_text(alc, ", &keys_count"));
    append_stmt(args, code_stmt_text(alc, ");"));
    append_stmt(block, code_block(alc, args, CodeBlock::INDENTED));
    if_cond = "keys == NULL";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if_code, code_stmt_text(alc, "goto end;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(block, code_stmt_textraw(alc, ""));

    if (dfa.key_size > 1) {
        o.cstr("for (i = 0; i < keys_count; ++i) {");
        append_stmt(block, code_stmt_text(alc, o.flush()));
        block2 = code_stmts(alc);
        from_le(output, block2, "keys[i]", dfa.key_size);
        append_stmt(block, code_block(alc, block2, CodeBlock::INDENTED));
        append_stmt(block, code_stmt_text(alc, "}"));
        append_stmt(block, code_stmt_textraw(alc, ""));
    }

    append_stmt(block, code_stmt_text(alc, "cursor = input;"));
    append_stmt(block, code_stmt_text(alc, "limit = input + input_len + padding;"));
    append_stmt(block, code_stmt_text(alc, "eof = input + input_len;"));

    append_stmt(block, code_stmt_textraw(alc, ""));

    append_stmt(block, code_stmt_text(alc,
        "for (i = 0; status == 0 && cursor < eof && i < keys_count;) {"));
    block2 = code_stmts(alc);
    append_stmt(block2, code_stmt_text(alc, "token = cursor;"));
    if (dfa.need_backup) {
        append_stmt(block2, code_stmt_text(alc, "const YYCTYPE *marker = NULL;"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append_stmt(block2, code_stmt_text(alc, "const YYCTYPE *ctxmarker = NULL;"));
    }
    append_stmt(block2, code_stmt_text(alc, "YYCTYPE yych;"));
    if (dfa.need_accept) {
        append_stmt(block2, code_stmt_text(alc, "unsigned int yyaccept = 0;"));
    }

    // autogenerated stag variables
    const std::string stags_fmt = "\n" + indent(2, opts->indString)
        + "const YYCTYPE *@@ = NULL;";
    CodeStmt *stags = code_tags(alc, stags_fmt, "", false);
    gen_tags(o, stags, dfa.stagnames);
    append_stmt(block2, stags);

    // user-defined stag variables
    var1 = dfa.stagvars.begin();
    var2 = dfa.stagvars.end();
    if (var1 != var2) {
        o.cstr("const YYCTYPE *").str(*var1);
        for (++var1; var1 != var2; ++var1) {
            o.cstr(", *").str(*var1);
        }
        o.cstr(";");
        append_stmt(block2, code_stmt_text(alc, o.flush()));
    }

    if (!dfa.mtagnames.empty()) {
        append_stmt(block2, code_stmt_text(alc, "yymtagpool_clear(&yytp);"));

        // autogenerated mtag variables
        CodeStmt *mtags = code_tags(alc, "ptrdiff_t @@ = -1;", "", true);
        gen_tags(o, mtags, dfa.mtagnames);
        append_stmt(block2, mtags);

        // user-defined mtag variables
        var1 = dfa.mtagvars.begin();
        var2 = dfa.mtagvars.end();
        if (var1 != var2) {
            o.cstr("ptrdiff_t ").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", ").str(*var1);
            }
            o.cstr(";");
            append_stmt(block2, code_stmt_text(alc, o.flush()));
        }
    }

    append_stmts(block2, dfa.bitmaps.gen(output));
    append_stmt(block2, code_stmt_textraw(alc, ""));
    dfa.emit_body(output, block2);
    append_stmt(block2, code_stmt_textraw(alc, ""));

    append_stmt(block, code_block(alc, block2, CodeBlock::INDENTED));
    append_stmt(block, code_stmt_text(alc, "}"));

    if_code = code_stmts(alc);

    CodeStmts *if1_code = code_stmts(alc);
    append_stmt(if1_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if1_code, code_stmt_text(alc, "const long pos = token - input;"));
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused input strings left at position %ld\\n\", pos);");
    append_stmt(if1_code, code_stmt_text(alc, o.flush()));
    append_stmt(if_code,
        code_stmt_if_then_else(alc, "cursor != eof", if1_code, NULL, false));

    CodeStmts *if2_code = code_stmts(alc);
    append_stmt(if2_code, code_stmt_text(alc, "status = 1;"));
    o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused keys left after %u keys\\n\", i);");
    append_stmt(if2_code, code_stmt_text(alc, o.flush()));
    append_stmt(if_code,
        code_stmt_if_then_else(alc, "i != keys_count", if2_code, NULL, false));

    append_stmt(block,
        code_stmt_if_then_else(alc, "status == 0", if_code, NULL, false));

    append_stmt(block, code_stmt_textraw(alc, ""));
    append_stmt(block, code_stmt_textraw(alc, "end:"));
    append_stmt(block, code_stmt_text(alc, "free(input);"));
    append_stmt(block, code_stmt_text(alc, "free(keys);"));
    if (!dfa.mtagnames.empty()) {
        append_stmt(block, code_stmt_text(alc, "yymtagpool_free(&yytp);"));
    }
    append_stmt(block, code_stmt_textraw(alc, ""));
    append_stmt(block, code_stmt_text(alc, "return status;"));

    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));
    append_stmt(code, code_stmt_textraw(alc, "#undef YYCTYPE"));
    append_stmt(code, code_stmt_textraw(alc, "#undef YYKEYTYPE"));
    append_stmt(code, code_stmt_textraw(alc, "#undef YYPEEK"));
    append_stmt(code, code_stmt_textraw(alc, "#undef YYSKIP"));
    if (dfa.need_backup) {
        append_stmt(code, code_stmt_textraw(alc, "#undef YYBACKUP"));
        append_stmt(code, code_stmt_textraw(alc, "#undef YYRESTORE"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append_stmt(code, code_stmt_textraw(alc, "#undef YYBACKUPCTX"));
        append_stmt(code, code_stmt_textraw(alc, "#undef YYRESTORECTX"));
    }
    if (opts->tags) {
        append_stmt(code, code_stmt_textraw(alc, "#undef YYBACKUPTAG"));
        append_stmt(code, code_stmt_textraw(alc, "#undef YYRESTORETAG"));
        append_stmt(code, code_stmt_textraw(alc, "#undef YYCOPYTAG"));
    }
    append_stmt(code, code_stmt_textraw(alc, "#undef YYLESSTHAN"));
    append_stmt(code, code_stmt_textraw(alc, "#undef YYFILL"));
}

CodeStmt *emit_skeleton_epilog(Output &output)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeStmts *stmts = code_stmts(alc);
    const std::set<std::string> &xs = output.skeletons;
    for (std::set<std::string>::const_iterator i = xs.begin(); i != xs.end(); ++i) {
        o.cstr("lex_").str(*i).cstr("() != 0");
        CodeText if_cond = o.flush();

        CodeStmts *if_code = code_stmts(alc);
        append_stmt(if_code, code_stmt_text(alc, "return 1;"));

        append_stmt(stmts, code_stmt_if_then_else(alc, if_cond, if_code, NULL, false));
    }
    append_stmt(stmts, code_stmt_text(alc, "return 0;"));

    CodeStmts *main = code_stmts(alc);
    append_stmt(main, code_stmt_text(alc, ""));
    append_stmt(main, code_stmt_text(alc, "int main()"));
    append_stmt(main, code_block(alc, stmts, CodeBlock::WRAPPED));

    return code_block(alc, main, CodeBlock::RAW);
}

void emit_skeleton_action(Output &output, CodeStmts *code, const DFA &dfa, size_t rid)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const std::string &name = dfa.name;
    const Rule &r = dfa.rules[rid];
    const uint64_t rkey = rule2key(rid, dfa.key_size, dfa.def_rule);

    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    o.cstr("status = check_key_count_").str(dfa.name).cstr("(keys_count, i, ")
        .u64(ntag).cstr(")");
    append_stmt(code, code_stmt_text(alc, o.flush()));

    CodeStmts *hang = code_stmts(alc);

    o.cstr(" || action_").str(name).cstr("(&i, keys, input, token, &cursor, ")
        .u64(rkey).cstr(")");
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        append_stmt(hang, code_stmt_text(alc, o.flush()));

        const std::string tname = tag_expr(tag, false);
        if (history(tag)) {
            o.cstr(" || check_mtag_").str(name).cstr("(&i, keys, &yytp, ");
        }
        else {
            o.cstr(" || check_stag_").str(name).cstr("(&i, keys, ");
        }
        o.str(tname).cstr(", input, token, \"").str(tname).cstr("\")");
    }
    o.cstr(";");
    append_stmt(hang, code_stmt_text(alc, o.flush()));

    append_stmt(code, code_block(alc, hang, CodeBlock::INDENTED));
    append_stmt(code, code_stmt_text(alc, "continue;"));
}

} // namespace re2c
