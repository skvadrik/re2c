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

static void from_le(Output &output, CodeStmts *code, const char *expr, size_t size)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeText text;

    append_stmt(code, code_stmt_text(alc, "/* from little-endian to host-endian */"));
    text = o.cstr("unsigned char *p = (unsigned char*)&").cstr(expr).cstr(";").flush();
    append_stmt(code, code_stmt_text(alc, text));
    o.cstr(expr).cstr(" = p[0]");
    for (uint32_t i = 1; i < size; ++i) {
        o.cstr(" + (p[").u32(i).cstr("] << ").u32(i * 8).cstr("u)");
    }
    text = o.cstr(";").flush();
    append_stmt(code, code_stmt_text(alc, text));
}

CodeStmt *emit_skeleton_prolog(Output &output)
{
    code_alc_t &alc = output.allocator;
    CodeText if_cond;
    CodeStmts *code, *block, *if_code;
    CodeArgs *args;

    code = code_stmts(alc);

    append_stmt(code, code_stmt_textraw(alc, ""));
    append_stmt(code, code_stmt_textraw(alc, "#include <stddef.h> /* size_t */"));
    append_stmt(code, code_stmt_textraw(alc, "#include <stdio.h>"));
    append_stmt(code, code_stmt_textraw(alc, "#include <stdlib.h> /* malloc, free */"));
    append_stmt(code, code_stmt_textraw(alc, "#include <string.h> /* memcpy */"));
    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "const char *fname"));
    append_arg(args, code_arg(alc, "size_t unit"));
    append_arg(args, code_arg(alc, "size_t padding"));
    append_arg(args, code_arg(alc, "size_t *pfsize"));
    append_stmt(code, code_fdecl(alc, "static void *read_file", args));

    block = code_stmts(alc);

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
    CodeText text;

    append_stmt(code, code_stmt_textraw(alc, ""));
    text = o.cstr("#define YYCTYPE ").exact_uint(sizeof_cunit).flush();
    append_stmt(code, code_stmt_textraw(alc, text));
    text = o.cstr("#define YYKEYTYPE ").exact_uint(dfa.key_size).flush();
    append_stmt(code, code_stmt_textraw(alc, text));
    append_stmt(code, code_stmt_textraw(alc, "#define YYPEEK() *cursor"));
    append_stmt(code, code_stmt_textraw(alc, "#define YYSKIP() ++cursor"));
    if (dfa.need_backup) {
        append_stmt(code, code_stmt_textraw(alc, "#define YYBACKUP() marker = cursor"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYRESTORE() cursor = marker"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append_stmt(code, code_stmt_textraw(alc,
            "#define YYBACKUPCTX() ctxmarker = cursor"));
        append_stmt(code, code_stmt_textraw(alc,
            "#define YYRESTORECTX() cursor = ctxmarker"));
    }
    if (opts->tags) {
        append_stmt(code, code_stmt_textraw(alc, "#define YYSTAGP(t) t = cursor"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYSTAGN(t) t = NULL"));
        append_stmt(code, code_stmt_textraw(alc,
            "#define YYMTAGP(t) yymtag(&t, cursor, &yytp)"));
        append_stmt(code, code_stmt_textraw(alc,
            "#define YYMTAGN(t) yymtag(&t, NULL, &yytp)"));
        append_stmt(code, code_stmt_textraw(alc, "#define YYRESTORETAG(t) cursor = t"));
        if (opts->stadfa) {
            append_stmt(code, code_stmt_textraw(alc,
                "#define YYSTAGPD(t) t = cursor - 1"));
            append_stmt(code, code_stmt_textraw(alc,
                "#define YYMTAGPD(t) yymtag(&t, cursor - 1, &yytp)"));
        }
    }
    append_stmt(code, code_stmt_textraw(alc,
        "#define YYLESSTHAN(n) (limit - cursor) < n"));
    append_stmt(code, code_stmt_textraw(alc, "#define YYFILL(n) { break; }"));
    append_stmt(code, code_stmt_textraw(alc, ""));
}

static void emit_skeleton_function_action(Output &output, CodeStmts *code, const DFA &dfa)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const uint64_t norule = rule2key(Rule::NONE, dfa.key_size, dfa.def_rule);
    CodeArgs *args;
    CodeStmts *if_code, *else_code, *body;
    CodeText if_cond, text;

    args = code_args(alc);
    append_arg(args, code_arg(alc, "unsigned *pkix"));
    append_arg(args, code_arg(alc, "const YYKEYTYPE *keys"));
    append_arg(args, code_arg(alc, "const YYCTYPE *start"));
    append_arg(args, code_arg(alc, "const YYCTYPE *token"));
    append_arg(args, code_arg(alc, "const YYCTYPE **cursor"));
    append_arg(args, code_arg(alc, "YYKEYTYPE rule_act"));
    text = o.cstr("static int action_").str(dfa.name).flush();
    append_stmt(code, code_fdecl(alc, text, args));

    body = code_stmts(alc);

    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "const long pos = token - start;"));
    append_stmt(body, code_stmt_text(alc, "const long len_act = *cursor - token;"));
    append_stmt(body, code_stmt_text(alc, "const long len_exp = (long) keys[kix + 1];"));
    append_stmt(body, code_stmt_text(alc, "const YYKEYTYPE rule_exp = keys[kix + 2];"));
    append_stmt(body, code_stmt_text(alc, "*pkix = kix + 3;"));

    if_cond = o.cstr("rule_exp == ").u64(norule).flush();
    if_code = code_stmts(alc);
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"warning: lex_").str(dfa.name)
        .cstr(": control flow is undefined\"\n")
        .cstr("\" for input at position %ld, rerun re2c with '-W'\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "pos"));
    append_stmt(if_code, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(body, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    if_cond = "len_act == len_exp && rule_act == rule_exp";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "const YYKEYTYPE offset = keys[kix];"));
    append_stmt(if_code, code_stmt_text(alc, "*cursor = token + offset;"));
    append_stmt(if_code, code_stmt_text(alc, "return 0;"));
    else_code = code_stmts(alc);
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld (key %u):\\n\"\n")
        .cstr("\"\\texpected: match length %ld, rule %u\\n\"\n")
        .cstr("\"\\tactual:   match length %ld, rule %u\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "pos"));
    append_arg(args, code_arg(alc, "kix"));
    append_arg(args, code_arg(alc, "len_exp"));
    append_arg(args, code_arg(alc, "rule_exp"));
    append_arg(args, code_arg(alc, "len_act"));
    append_arg(args, code_arg(alc, "rule_act"));
    append_stmt(else_code, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(else_code, code_stmt_text(alc, "return 1;"));
    append_stmt(body, code_stmt_if_then_else(alc, if_cond, if_code, else_code));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_stags(Output &output, CodeStmts *code, const DFA &dfa)
{
    if (dfa.stagnames.empty()) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeStmts *if_code, *body;
    CodeText if_cond, text;

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "unsigned *pkix"));
    append_arg(args, code_arg(alc, "YYKEYTYPE *keys"));
    append_arg(args, code_arg(alc, "const YYCTYPE *tag"));
    append_arg(args, code_arg(alc, "const YYCTYPE *input"));
    append_arg(args, code_arg(alc, "const YYCTYPE *token"));
    append_arg(args, code_arg(alc, "const char *name"));
    text = o.cstr("static int check_stag_").str(dfa.name).flush();
    append_stmt(code, code_fdecl(alc, text, args));

    body = code_stmts(alc);

    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "const YYKEYTYPE exp = keys[kix];"));
    append_stmt(body, code_stmt_text(alc,
        "const YYKEYTYPE act = (YYKEYTYPE)(tag - token);"));
    append_stmt(body, code_stmt_text(alc, "const YYKEYTYPE NIL = (YYKEYTYPE)~0u;"));
    append_stmt(body, code_stmt_text(alc, "*pkix = kix + 1;"));

    append_stmt(body, code_stmt_textraw(alc, ""));

    if_cond = "exp == act || (exp == NIL && tag == NULL)";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "return 0;"));
    append_stmt(body, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(body, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "token - input"));
    append_arg(args, code_arg(alc, "kix"));
    append_arg(args, code_arg(alc, "name"));
    append_arg(args, code_arg(alc, "exp"));
    append_arg(args, code_arg(alc, "act"));
    append_stmt(body, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(body, code_stmt_text(alc, "return 1;"));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_mtags(Output &output, CodeStmts *code, const DFA &dfa)
{
    if (dfa.mtagnames.empty()) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeStmts *if_code, *block, *body;
    CodeText if_cond, text;

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

    args = code_args(alc);
    append_arg(args, code_arg(alc, "yymtagpool_t *tp"));
    append_stmt(code, code_fdecl(alc, "static void yymtagpool_clear", args));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "tp->next = tp->head;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "yymtagpool_t *tp"));
    append_stmt(code, code_fdecl(alc, "static void yymtagpool_init", args));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "static const unsigned size = 4096;"));
    append_stmt(block, code_stmt_text(alc,
        "tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t));"));
    append_stmt(block, code_stmt_text(alc, "tp->next = tp->head;"));
    append_stmt(block, code_stmt_text(alc, "tp->last = tp->head + size;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "yymtagpool_t *tp"));
    append_stmt(code, code_fdecl(alc, "static void yymtagpool_free", args));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "free(tp->head);"));
    append_stmt(block, code_stmt_text(alc, "tp->head = tp->next = tp->last = NULL;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "yymtagpool_t *tp"));
    append_stmt(code, code_fdecl(alc, "static yymtag_t *yymtagpool_next", args));
    block = code_stmts(alc);
    if_cond = "tp->next == tp->last";
    if_code = code_stmts(alc);
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

    args = code_args(alc);
    append_arg(args, code_arg(alc, "ptrdiff_t *pt"));
    append_arg(args, code_arg(alc, "const YYCTYPE *t"));
    append_arg(args, code_arg(alc, "yymtagpool_t *tp"));
    append_stmt(code, code_fdecl(alc, "static void yymtag", args));
    block = code_stmts(alc);
    append_stmt(block, code_stmt_text(alc, "yymtag_t *n = yymtagpool_next(tp);"));
    append_stmt(block, code_stmt_text(alc, "n->pred = *pt;"));
    append_stmt(block, code_stmt_text(alc, "n->elem = t;"));
    append_stmt(block, code_stmt_text(alc, "*pt = n - tp->head;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "unsigned *pkix"));
    append_arg(args, code_arg(alc, "YYKEYTYPE *keys"));
    append_arg(args, code_arg(alc, "const yymtagpool_t *tp"));
    append_arg(args, code_arg(alc, "ptrdiff_t mtag"));
    append_arg(args, code_arg(alc, "const YYCTYPE *input"));
    append_arg(args, code_arg(alc, "const YYCTYPE *token"));
    append_arg(args, code_arg(alc, "const char *name"));
    text = o.cstr("static int check_mtag_").str(dfa.name).flush();
    append_stmt(code, code_fdecl(alc, text, args));

    body = code_stmts(alc);
    append_stmt(body, code_stmt_text(alc, "const unsigned kix = *pkix;"));
    append_stmt(body, code_stmt_text(alc, "YYKEYTYPE n = keys[kix];"));
    append_stmt(body, code_stmt_text(alc, "*pkix = kix + n + 1;"));

    append_stmt(body, code_stmt_text(alc, "for (; n > 0; --n) {"));
    block = code_stmts(alc); // for loop

    if_cond = "mtag == -1";
    if_code = code_stmts(alc);
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"history for tag '%s' is too short\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "token - input"));
    append_arg(args, code_arg(alc, "kix + n"));
    append_arg(args, code_arg(alc, "name"));
    append_stmt(if_code, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(if_code, code_stmt_text(alc, "return 1;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(block, code_stmt_text(alc,
        "const YYCTYPE *tag = (tp->head + mtag)->elem;"));
    append_stmt(block, code_stmt_text(alc, "mtag = (tp->head + mtag)->pred;"));
    append_stmt(block, code_stmt_text(alc, "const YYKEYTYPE exp = keys[kix + n];"));
    append_stmt(block, code_stmt_text(alc,
        "const YYKEYTYPE act = (YYKEYTYPE)(tag - token);"));
    append_stmt(block, code_stmt_text(alc, "const YYKEYTYPE NIL = (YYKEYTYPE)~0u;"));

    if_cond = "!(exp == act || (exp == NIL && tag == NULL))";
    if_code = code_stmts(alc);
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "token - input"));
    append_arg(args, code_arg(alc, "kix + n"));
    append_arg(args, code_arg(alc, "name"));
    append_arg(args, code_arg(alc, "exp"));
    append_arg(args, code_arg(alc, "act"));
    append_stmt(if_code, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(if_code, code_stmt_text(alc, "return 1;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(body, code_block(alc, block, CodeBlock::INDENTED));
    append_stmt(body, code_stmt_text(alc, "}")); // end of for loop

    if_cond = "mtag != -1";
    if_code = code_stmts(alc);
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"history for tag '%s' is too long\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "token - input"));
    append_arg(args, code_arg(alc, "kix + n"));
    append_arg(args, code_arg(alc, "name"));
    append_stmt(if_code, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(if_code, code_stmt_text(alc, "return 1;"));
    append_stmt(body, code_stmt_if_then_else(alc, if_cond, if_code, NULL));
    append_stmt(body, code_stmt_text(alc, "return 0;"));

    append_stmt(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_function_check_key_count(Output &output, CodeStmts *code,
    DFA &dfa)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeStmts *block, *if_code;
    CodeText if_cond, text;

    append_stmt(code, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    append_arg(args, code_arg(alc, "unsigned have"));
    append_arg(args, code_arg(alc, "unsigned used"));
    append_arg(args, code_arg(alc, "unsigned need"));
    text = o.cstr("static int check_key_count_").str(dfa.name).flush();
    append_stmt(code, code_fdecl(alc, text, args));
    block = code_stmts(alc);
    if_cond = "used + need <= have";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "return 0;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));
    args = code_args(alc);
    append_arg(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": not enough keys\\n\"").flush();
    append_arg(args, code_arg(alc, text));
    append_stmt(block, code_fcall(alc, "fprintf", args, ";"));
    append_stmt(block, code_stmt_text(alc, "return 1;"));
    append_stmt(code, code_block(alc, block, CodeBlock::WRAPPED));
}

static void emit_skeleton_function_lex(Output &output, CodeStmts *code, DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    std::set<std::string>::const_iterator var1, var2;
    CodeArgs *args;
    CodeStmts *block, *block2, *if_code, *if1_code;
    CodeText if_cond, text;

    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }

    append_stmt(code, code_stmt_textraw(alc, ""));

    text = o.cstr("int lex_").str(dfa.name).cstr("()").flush();
    append_stmt(code, code_stmt_text(alc, text));
    block = code_stmts(alc);
    text = o.cstr("const size_t padding = ").u64(dfa.max_fill)
        .cstr("; /* YYMAXFILL */").flush();
    append_stmt(block, code_stmt_text(alc, text));
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
        text = o.cstr("const YYCTYPE *yypmatch[").u64(dfa.max_nmatch)
            .cstr(" * 2];").flush();
        append_stmt(block, code_stmt_text(alc, text));
    }
    append_stmt(block, code_stmt_text(alc, "unsigned int i = 0;"));
    if (!dfa.mtagnames.empty()) {
        append_stmt(block, code_stmt_textraw(alc, ""));
        append_stmt(block, code_stmt_text(alc, "yymtagpool_t yytp;"));
        append_stmt(block, code_stmt_text(alc, "yymtagpool_init(&yytp);"));
    }

    append_stmt(block, code_stmt_textraw(alc, ""));

    args = code_args(alc);
    text = o.cstr("\"").str(filename).cstr(".").str(dfa.name).cstr(".input\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "sizeof (YYCTYPE)"));
    append_arg(args, code_arg(alc, "padding"));
    append_arg(args, code_arg(alc, "&input_len"));
    append_stmt(block, code_fcall(alc, "input = (YYCTYPE *) read_file", args, ";"));

    if_cond = "input == NULL";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if_code, code_stmt_text(alc, "goto end;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(block, code_stmt_textraw(alc, ""));

    if (sizeof_cunit > 1) {
        text = o.cstr("for (i = 0; i < input_len; ++i) {").flush();
        append_stmt(block, code_stmt_text(alc, text));
        block2 = code_stmts(alc);
        from_le(output, block2, "input[i]", opts->encoding.szCodeUnit());
        append_stmt(block, code_block(alc, block2, CodeBlock::INDENTED));
        append_stmt(block, code_stmt_text(alc, "}"));
        append_stmt(block, code_stmt_textraw(alc, ""));
    }

    args = code_args(alc);
    text = o.cstr("\"").str(filename).cstr(".").str(dfa.name).cstr(".keys\"").flush();
    append_arg(args, code_arg(alc, text));
    append_arg(args, code_arg(alc, "sizeof (YYKEYTYPE)"));
    append_arg(args, code_arg(alc, "0"));
    append_arg(args, code_arg(alc, "&keys_count"));
    append_stmt(block, code_fcall(alc, "keys = (YYKEYTYPE *) read_file", args, ";"));
    if_cond = "keys == NULL";
    if_code = code_stmts(alc);
    append_stmt(if_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if_code, code_stmt_text(alc, "goto end;"));
    append_stmt(block, code_stmt_if_then_else(alc, if_cond, if_code, NULL));

    append_stmt(block, code_stmt_textraw(alc, ""));

    if (dfa.key_size > 1) {
        text = o.cstr("for (i = 0; i < keys_count; ++i) {").flush();
        append_stmt(block, code_stmt_text(alc, text));
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
    if (!dfa.stagnames.empty()) {
        // autogenerated stag variables
        text = o.cstr("\n").str(indent(2, opts->indString))
            .cstr("const YYCTYPE *@@ = NULL;").flush();
        CodeStmt *stags = code_tags(alc, text, "", false);
        gen_tags(o, stags, dfa.stagnames);
        append_stmt(block2, stags);
        append_stmt(block2, code_stmt_textraw(alc, ""));

        // user-defined stag variables
        var1 = dfa.stagvars.begin();
        var2 = dfa.stagvars.end();
        if (var1 != var2) {
            o.cstr("const YYCTYPE *").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", *").str(*var1);
            }
            text = o.cstr(";").flush();
            append_stmt(block2, code_stmt_text(alc, text));
        }
    }
    if (!dfa.mtagnames.empty()) {
        append_stmt(block2, code_stmt_text(alc, "yymtagpool_clear(&yytp);"));

        // autogenerated mtag variables
        text = o.cstr("\n").str(indent(2, opts->indString))
            .cstr("ptrdiff_t @@ = -1;").flush();
        CodeStmt *mtags = code_tags(alc, text, "", true);
        gen_tags(o, mtags, dfa.mtagnames);
        append_stmt(block2, mtags);
        append_stmt(block2, code_stmt_textraw(alc, ""));

        // user-defined mtag variables
        var1 = dfa.mtagvars.begin();
        var2 = dfa.mtagvars.end();
        if (var1 != var2) {
            o.cstr("ptrdiff_t ").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", ").str(*var1);
            }
            text = o.cstr(";").flush();
            append_stmt(block2, code_stmt_text(alc, text));
        }
    }

    append_stmts(block2, dfa.bitmaps.gen(output));
    append_stmt(block2, code_stmt_textraw(alc, ""));
    dfa.emit_body(output, block2);
    append_stmt(block2, code_stmt_textraw(alc, ""));

    append_stmt(block, code_block(alc, block2, CodeBlock::INDENTED));
    append_stmt(block, code_stmt_text(alc, "}"));

    if_code = code_stmts(alc);

    if1_code = code_stmts(alc);
    append_stmt(if1_code, code_stmt_text(alc, "status = 1;"));
    append_stmt(if1_code, code_stmt_text(alc, "const long pos = token - input;"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused input strings left at position %ld\\n\", pos);").flush();
    append_stmt(if1_code, code_stmt_text(alc, text));
    append_stmt(if_code, code_stmt_if_then_else(alc, "cursor != eof", if1_code,
      NULL, false));

    if1_code = code_stmts(alc);
    append_stmt(if1_code, code_stmt_text(alc, "status = 1;"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused keys left after %u keys\\n\", i);").flush();
    append_stmt(if1_code, code_stmt_text(alc, text));
    append_stmt(if_code, code_stmt_if_then_else(alc, "i != keys_count",
        if1_code, NULL, false));

    append_stmt(block, code_stmt_if_then_else(alc, "status == 0", if_code,
        NULL, false));

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
}

static void emit_skeleton_undefs(Output &output, CodeStmts *code, DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;

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

void emit_skeleton(Output &output, CodeStmts *code, DFA &dfa)
{
    emit_skeleton_defines(output, code, dfa);
    emit_skeleton_function_action(output, code, dfa);
    emit_skeleton_stags(output, code, dfa);
    emit_skeleton_mtags(output, code, dfa);
    emit_skeleton_function_check_key_count(output, code, dfa);
    emit_skeleton_function_lex(output, code, dfa);
    emit_skeleton_undefs(output, code, dfa);
}

CodeStmt *emit_skeleton_epilog(Output &output)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeStmts *stmts = code_stmts(alc);
    const std::set<std::string> &xs = output.skeletons;
    for (std::set<std::string>::const_iterator i = xs.begin(); i != xs.end(); ++i) {
        CodeText if_cond = o.cstr("lex_").str(*i).cstr("() != 0").flush();
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
    CodeText text;

    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    CodeArgs *args = code_args(alc);
    append_arg(args, code_arg(alc, "keys_count"));
    append_arg(args, code_arg(alc, "i"));
    text = o.u64(ntag).flush();
    append_arg(args, code_arg(alc, text));
    text = o.cstr("status = check_key_count_").str(dfa.name).flush();
    append_stmt(code, code_fcall(alc, text, args, ""));

    CodeStmts *hangafter = code_stmts(alc);

    args = code_args(alc);
    append_arg(args, code_arg(alc, "&i"));
    append_arg(args, code_arg(alc, "keys"));
    append_arg(args, code_arg(alc, "input"));
    append_arg(args, code_arg(alc, "token"));
    append_arg(args, code_arg(alc, "&cursor"));
    text = o.u64(rkey).flush();
    append_arg(args, code_arg(alc, text));
    text = o.cstr(" || action_").str(name).flush();
    append_stmt(hangafter, code_fcall(alc, text, args, ntag > 3 ? "" : ";"));

    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        const bool mtag = history(tag);
        const std::string tname = tag_expr(tag, false);
        --ntag;

        args = code_args(alc);
        append_arg(args, code_arg(alc, "&i"));
        append_arg(args, code_arg(alc, "keys"));
        if (mtag) append_arg(args, code_arg(alc, "&yytp"));
        text = o.str(tname).flush();
        append_arg(args, code_arg(alc, text));
        append_arg(args, code_arg(alc, "input"));
        append_arg(args, code_arg(alc, "token"));
        text = o.cstr("\"").str(tname).cstr("\"").flush();
        append_arg(args, code_arg(alc, text));
        text = o.cstr(" || check_").cstr(mtag ? "mtag_" : "stag_").str(name).flush();
        append_stmt(hangafter, code_fcall(alc, text, args, ntag > 3 ? "" : ";"));
    }

    append_stmt(code, code_block(alc, hangafter, CodeBlock::INDENTED));

    append_stmt(code, code_stmt_text(alc, "continue;"));
}

} // namespace re2c
