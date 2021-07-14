#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"


namespace re2c {

static void from_le(Output &output, CodeList *code, const char *expr, size_t size)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const char *text;

    append(code, code_text(alc, "/* from little-endian to host-endian */"));
    text = o.cstr("unsigned char *p = (unsigned char*)&").cstr(expr).flush();
    append(code, code_stmt(alc, text));
    o.cstr(expr).cstr(" = p[0]");
    for (uint32_t i = 1; i < size; ++i) {
        o.cstr(" + (p[").u32(i).cstr("] << ").u32(i * 8).cstr("u)");
    }
    text = o.flush();
    append(code, code_stmt(alc, text));
}

Code *emit_skeleton_prolog(Output &output)
{
    code_alc_t &alc = output.allocator;
    const char *if_cond;
    CodeList *code, *block, *if_code;
    CodeArgs *args;

    code = code_list(alc);

    append(code, code_newline(alc));
    append(code, code_textraw(alc, "#include <stddef.h> /* size_t */"));
    append(code, code_textraw(alc, "#include <stdio.h>"));
    append(code, code_textraw(alc, "#include <stdlib.h> /* malloc, free */"));
    append(code, code_textraw(alc, "#include <string.h> /* memcpy */"));
    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "const char *fname"));
    append(args, code_arg(alc, "size_t unit"));
    append(args, code_arg(alc, "size_t padding"));
    append(args, code_arg(alc, "size_t *pfsize"));
    append(code, code_fdecl(alc, "static void *read_file", args));

    block = code_list(alc);

    append(block, code_stmt(alc, "void *buffer = NULL"));
    append(block, code_stmt(alc, "size_t fsize = 0"));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* open file */"));
    append(block, code_stmt(alc, "FILE *f = fopen(fname, \"rb\")"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "goto error"));
    append(block, code_if_then_else(alc, "f == NULL", if_code, NULL, false));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* get file size */"));
    append(block, code_stmt(alc, "fseek(f, 0, SEEK_END)"));
    append(block, code_stmt(alc, "fsize = (size_t) ftell(f) / unit"));
    append(block, code_stmt(alc, "fseek(f, 0, SEEK_SET)"));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* allocate memory for file and padding */"));
    append(block, code_stmt(alc, "buffer = malloc(unit * (fsize + padding))"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "goto error"));
    append(block, code_if_then_else(alc, "buffer == NULL", if_code, NULL, false));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* read the whole file in memory */"));
    if_cond = "fread(buffer, unit, fsize, f) != fsize";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "goto error"));
    append(block, code_if_then_else(alc, if_cond, if_code, NULL, false));

    append(block, code_newline(alc));

    append(block, code_stmt(alc, "fclose(f)"));
    append(block, code_stmt(alc, "*pfsize = fsize"));
    append(block, code_stmt(alc, "return buffer"));

    append(block, code_newline(alc));
    append(block, code_slabel(alc, "error"));

    append(block, code_stmt(alc,
        "fprintf(stderr, \"error: cannot read file '%s'\\n\", fname)"));
    append(block, code_stmt(alc, "free(buffer)"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "fclose(f)"));
    append(block, code_if_then_else(alc, "f != NULL", if_code, NULL, false));
    append(block, code_stmt(alc, "return NULL"));

    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    return code_block(alc, code, CodeBlock::RAW);
}

static void emit_skeleton_defines(Output &output, CodeList *code, const DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    const char *text;

    append(code, code_newline(alc));
    text = o.cstr("#define YYCTYPE ").exact_uint(sizeof_cunit).flush();
    append(code, code_textraw(alc, text));
    text = o.cstr("#define YYKEYTYPE ").exact_uint(dfa.key_size).flush();
    append(code, code_textraw(alc, text));
    append(code, code_textraw(alc, "#define YYPEEK() *cursor"));
    append(code, code_textraw(alc, "#define YYSKIP() ++cursor"));
    if (dfa.need_backup) {
        append(code, code_textraw(alc, "#define YYBACKUP() marker = cursor"));
        append(code, code_textraw(alc, "#define YYRESTORE() cursor = marker"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append(code, code_textraw(alc, "#define YYBACKUPCTX() ctxmarker = cursor"));
        append(code, code_textraw(alc, "#define YYRESTORECTX() cursor = ctxmarker"));
    }
    if (opts->tags) {
        append(code, code_textraw(alc, "#define YYSTAGP(t) t = cursor"));
        append(code, code_textraw(alc, "#define YYSTAGN(t) t = NULL"));
        append(code, code_textraw(alc, "#define YYMTAGP(t) yymtag(&t, cursor, &yytp)"));
        append(code, code_textraw(alc, "#define YYMTAGN(t) yymtag(&t, NULL, &yytp)"));
        append(code, code_textraw(alc, "#define YYSHIFTSTAG(t, o) t += o"));
        append(code, code_textraw(alc, "#define YYSHIFTMTAG(t, o) yytp.head[t].elem += o"));
        append(code, code_textraw(alc, "#define YYRESTORETAG(t) cursor = t"));
    }
    append(code, code_textraw(alc, "#define YYSHIFT(o) cursor += o"));
    append(code, code_textraw(alc, "#define YYLESSTHAN(n) (limit - cursor) < n"));
    append(code, code_textraw(alc, opts->eof == NOEOF
        ? "#define YYFILL(n) { break; }"
        : "#define YYFILL(n) 1 /* fail */"));
    append(code, code_newline(alc));
}

static void emit_skeleton_function_action(Output &output, CodeList *code, const DFA &dfa)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const uint64_t norule = rule2key(Rule::NONE, dfa.key_size, dfa.def_rule);
    CodeArgs *args;
    CodeList *if_code, *else_code, *body;
    const char *if_cond, *text;

    args = code_args(alc);
    append(args, code_arg(alc, "unsigned *pkix"));
    append(args, code_arg(alc, "const YYKEYTYPE *keys"));
    append(args, code_arg(alc, "const YYCTYPE *start"));
    append(args, code_arg(alc, "const YYCTYPE *token"));
    append(args, code_arg(alc, "const YYCTYPE **cursor"));
    append(args, code_arg(alc, "YYKEYTYPE rule_act"));
    text = o.cstr("static int action_").str(dfa.name).flush();
    append(code, code_fdecl(alc, text, args));

    body = code_list(alc);

    append(body, code_stmt(alc, "const unsigned kix = *pkix"));
    append(body, code_stmt(alc, "const long pos = token - start"));
    append(body, code_stmt(alc, "const long len_act = *cursor - token"));
    append(body, code_stmt(alc, "const long len_exp = (long) keys[kix + 1]"));
    append(body, code_stmt(alc, "const YYKEYTYPE rule_exp = keys[kix + 2]"));
    append(body, code_stmt(alc, "*pkix = kix + 3"));

    if_cond = o.cstr("rule_exp == ").u64(norule).flush();
    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"warning: lex_").str(dfa.name)
        .cstr(": control flow is undefined\"\n")
        .cstr("\" for input at position %ld, rerun re2c with '-W'\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "pos"));
    append(if_code, code_fcall(alc, "fprintf", args, ";"));
    append(body, code_if_then_else(alc, if_cond, if_code, NULL));

    if_cond = "len_act == len_exp && rule_act == rule_exp";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "const YYKEYTYPE offset = keys[kix]"));
    append(if_code, code_stmt(alc, "*cursor = token + offset"));
    append(if_code, code_stmt(alc, "return 0"));
    else_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld (key %u):\\n\"\n")
        .cstr("\"\\texpected: match length %ld, rule %u\\n\"\n")
        .cstr("\"\\tactual:   match length %ld, rule %u\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "pos"));
    append(args, code_arg(alc, "kix"));
    append(args, code_arg(alc, "len_exp"));
    append(args, code_arg(alc, "rule_exp"));
    append(args, code_arg(alc, "len_act"));
    append(args, code_arg(alc, "rule_act"));
    append(else_code, code_fcall(alc, "fprintf", args, ";"));
    append(else_code, code_text(alc, "return 1;"));
    append(body, code_if_then_else(alc, if_cond, if_code, else_code));

    append(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_stags(Output &output, CodeList *code, const DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    if (dfa.stagvars.empty() && !opts->posix_syntax) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeList *if_code, *body;
    const char *if_cond, *text;

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "unsigned *pkix"));
    append(args, code_arg(alc, "YYKEYTYPE *keys"));
    append(args, code_arg(alc, "const YYCTYPE *tag"));
    append(args, code_arg(alc, "const YYCTYPE *input"));
    append(args, code_arg(alc, "const YYCTYPE *token"));
    append(args, code_arg(alc, "const char *name"));
    text = o.cstr("static int check_stag_").str(dfa.name).flush();
    append(code, code_fdecl(alc, text, args));

    body = code_list(alc);

    append(body, code_stmt(alc, "const unsigned kix = *pkix"));
    append(body, code_stmt(alc, "const YYKEYTYPE exp = keys[kix]"));
    append(body, code_stmt(alc, "const YYKEYTYPE act = (YYKEYTYPE)(tag - token)"));
    append(body, code_stmt(alc, "const YYKEYTYPE NIL = (YYKEYTYPE)~0u"));
    append(body, code_stmt(alc, "*pkix = kix + 1"));

    append(body, code_newline(alc));

    if_cond = "exp == act || (exp == NIL && tag == NULL)";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "return 0"));
    append(body, code_if_then_else(alc, if_cond, if_code, NULL));

    append(body, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix"));
    append(args, code_arg(alc, "name"));
    append(args, code_arg(alc, "exp"));
    append(args, code_arg(alc, "act"));
    append(body, code_fcall(alc, "fprintf", args, ";"));
    append(body, code_stmt(alc, "return 1"));

    append(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_mtag_defs(Output &output, CodeList *code)
{
    code_alc_t &alc = output.allocator;
    CodeArgs *args;
    CodeList *if_code, *block;
    const char *if_cond;

    // Use `void *` instead of `YYCTYPE *`, as YYCTYPE may vary for different
    // blocks. and this definition must be valid throughout the whole file.

    append(code, code_newline(alc));

    append(code, code_text(alc, "typedef struct yymtag_t {"));
    block = code_list(alc);
    append(block, code_text(alc, "ptrdiff_t pred;"));
    append(block, code_text(alc, "const void *elem;"));
    append(code, code_block(alc, block, CodeBlock::INDENTED));
    append(code, code_text(alc, "} yymtag_t;"));

    append(code, code_newline(alc));

    append(code, code_text(alc, "typedef struct yymtagpool_t {"));
    block = code_list(alc);
    append(block, code_text(alc, "yymtag_t *head;"));
    append(block, code_text(alc, "yymtag_t *next;"));
    append(block, code_text(alc, "yymtag_t *last;"));
    append(code, code_block(alc, block, CodeBlock::INDENTED));
    append(code, code_text(alc, "} yymtagpool_t;"));

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "yymtagpool_t *tp"));
    append(code, code_fdecl(alc, "static void yymtagpool_clear", args));
    block = code_list(alc);
    append(block, code_stmt(alc, "tp->next = tp->head"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "yymtagpool_t *tp"));
    append(code, code_fdecl(alc, "static void yymtagpool_init", args));
    block = code_list(alc);
    append(block, code_stmt(alc, "static const unsigned size = 4096"));
    append(block, code_stmt(alc,
        "tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t))"));
    append(block, code_stmt(alc, "tp->next = tp->head"));
    append(block, code_stmt(alc, "tp->last = tp->head + size"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "yymtagpool_t *tp"));
    append(code, code_fdecl(alc, "static void yymtagpool_free", args));
    block = code_list(alc);
    append(block, code_stmt(alc, "free(tp->head)"));
    append(block, code_stmt(alc, "tp->head = tp->next = tp->last = NULL"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "yymtagpool_t *tp"));
    append(code, code_fdecl(alc, "static yymtag_t *yymtagpool_next", args));
    block = code_list(alc);
    if_cond = "tp->next == tp->last";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "const unsigned size = tp->last - tp->head"));
    append(if_code, code_stmt(alc,
        "yymtag_t *head = (yymtag_t*)malloc(2 * size * sizeof(yymtag_t))"));
    append(if_code, code_stmt(alc, "memcpy(head, tp->head, size * sizeof(yymtag_t))"));
    append(if_code, code_stmt(alc, "free(tp->head)"));
    append(if_code, code_stmt(alc, "tp->head = head"));
    append(if_code, code_stmt(alc, "tp->next = head + size"));
    append(if_code, code_stmt(alc, "tp->last = head + size * 2"));
    append(block, code_if_then_else(alc, if_cond, if_code, NULL));
    append(block, code_stmt(alc, "return tp->next++"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "ptrdiff_t *pt"));
    append(args, code_arg(alc, "const void *t"));
    append(args, code_arg(alc, "yymtagpool_t *tp"));
    append(code, code_fdecl(alc, "static void yymtag", args));
    block = code_list(alc);
    append(block, code_stmt(alc, "yymtag_t *n = yymtagpool_next(tp)"));
    append(block, code_stmt(alc, "n->pred = *pt"));
    append(block, code_stmt(alc, "n->elem = t"));
    append(block, code_stmt(alc, "*pt = n - tp->head"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));

    append(code, code_newline(alc));
}

static void emit_skeleton_mtags(Output &output, CodeList *code, const DFA &dfa)
{
    if (dfa.mtagvars.empty()) return;

    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeList *if_code, *block, *body;
    const char *if_cond, *text;

    // Data structures for m-tags are the same for all blocks in the file. They
    // are emitted at the first block that has m-tags, because it's impossible
    // to know earlier (when generating prologue) if m-tags are needed at all.
    if (!output.done_mtag_defs) {
        output.done_mtag_defs = true;
        emit_skeleton_mtag_defs(output, code);
    }

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "unsigned *pkix"));
    append(args, code_arg(alc, "YYKEYTYPE *keys"));
    append(args, code_arg(alc, "const yymtagpool_t *tp"));
    append(args, code_arg(alc, "ptrdiff_t mtag"));
    append(args, code_arg(alc, "const YYCTYPE *input"));
    append(args, code_arg(alc, "const YYCTYPE *token"));
    append(args, code_arg(alc, "const char *name"));
    text = o.cstr("static int check_mtag_").str(dfa.name).flush();
    append(code, code_fdecl(alc, text, args));

    body = code_list(alc);
    append(body, code_stmt(alc, "const unsigned kix = *pkix"));
    append(body, code_stmt(alc, "YYKEYTYPE n = keys[kix]"));
    append(body, code_stmt(alc, "*pkix = kix + n + 1"));

    append(body, code_text(alc, "for (; n > 0; --n) {"));
    block = code_list(alc); // for loop

    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"history for tag '%s' is too short\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(if_code, code_fcall(alc, "fprintf", args, ";"));
    append(if_code, code_stmt(alc, "return 1"));
    append(block, code_if_then_else(alc, "mtag == -1", if_code, NULL));

    append(block, code_stmt(alc, "const YYCTYPE *tag = (tp->head + mtag)->elem"));
    append(block, code_stmt(alc, "mtag = (tp->head + mtag)->pred"));
    append(block, code_stmt(alc, "const YYKEYTYPE exp = keys[kix + n]"));
    append(block, code_stmt(alc, "const YYKEYTYPE act = (YYKEYTYPE)(tag - token)"));
    append(block, code_stmt(alc, "const YYKEYTYPE NIL = (YYKEYTYPE)~0u"));

    if_cond = "!(exp == act || (exp == NIL && tag == NULL))";
    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"wrong value for tag '%s': expected %u, actual %u\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(args, code_arg(alc, "exp"));
    append(args, code_arg(alc, "act"));
    append(if_code, code_fcall(alc, "fprintf", args, ";"));
    append(if_code, code_stmt(alc, "return 1"));
    append(block, code_if_then_else(alc, if_cond, if_code, NULL));

    append(body, code_block(alc, block, CodeBlock::INDENTED));
    append(body, code_text(alc, "}")); // end of for loop

    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name)
        .cstr(": at position %ld, key %u: \"\n")
        .cstr("\"history for tag '%s' is too long\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(if_code, code_fcall(alc, "fprintf", args, ";"));
    append(if_code, code_stmt(alc, "return 1"));
    append(body, code_if_then_else(alc, "mtag != -1", if_code, NULL));
    append(body, code_text(alc, "return 0;"));

    append(code, code_block(alc, body, CodeBlock::WRAPPED));
}

static void emit_skeleton_function_check_key_count(Output &output, CodeList *code,
    DFA &dfa)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    CodeArgs *args;
    CodeList *block, *if_code;
    const char *if_cond, *text;

    append(code, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "unsigned have"));
    append(args, code_arg(alc, "unsigned used"));
    append(args, code_arg(alc, "unsigned need"));
    text = o.cstr("static int check_key_count_").str(dfa.name).flush();
    append(code, code_fdecl(alc, text, args));
    block = code_list(alc);
    if_cond = "used + need <= have";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "return 0"));
    append(block, code_if_then_else(alc, if_cond, if_code, NULL));
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": not enough keys\\n\"").flush();
    append(args, code_arg(alc, text));
    append(block, code_fcall(alc, "fprintf", args, ";"));
    append(block, code_stmt(alc, "return 1"));
    append(code, code_block(alc, block, CodeBlock::WRAPPED));
}

static void emit_skeleton_function_lex(Output &output, CodeList *code, DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.szCodeUnit();
    std::set<std::string>::const_iterator var1, var2;
    CodeArgs *args;
    CodeList *block, *block2, *if_code, *if1_code;
    const char *text;

    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }
    filename = escape_backslashes(filename);

    append(code, code_newline(alc));

    text = o.cstr("int lex_").str(dfa.name).cstr("()").flush();
    append(code, code_text(alc, text));
    block = code_list(alc);
    text = o.cstr("const size_t padding = ").u64(dfa.max_fill)
        .cstr("; /* YYMAXFILL */").flush();
    append(block, code_text(alc, text));
    append(block, code_stmt(alc, "int status = 0"));
    append(block, code_stmt(alc, "size_t input_len = 0"));
    append(block, code_stmt(alc, "size_t keys_count = 0"));
    append(block, code_stmt(alc, "YYCTYPE *input = NULL"));
    append(block, code_stmt(alc, "YYKEYTYPE *keys = NULL"));
    append(block, code_stmt(alc, "const YYCTYPE *cursor = NULL"));
    append(block, code_stmt(alc, "const YYCTYPE *limit = NULL"));
    append(block, code_stmt(alc, "const YYCTYPE *token = NULL"));
    append(block, code_stmt(alc, "const YYCTYPE *eof = NULL"));
    if (opts->posix_syntax) {
        append(block, code_stmt(alc, "size_t yynmatch"));
        text = o.cstr("const YYCTYPE *yypmatch[").u64(dfa.max_nmatch)
            .cstr(" * 2]").flush();
        append(block, code_stmt(alc, text));
    }
    append(block, code_stmt(alc, "unsigned int i = 0"));
    if (!dfa.mtagnames.empty()) {
        append(block, code_newline(alc));
        append(block, code_stmt(alc, "yymtagpool_t yytp"));
        append(block, code_stmt(alc, "yymtagpool_init(&yytp)"));
    }

    append(block, code_newline(alc));

    args = code_args(alc);
    text = o.cstr("\"").str(filename).cstr(".").str(dfa.name).cstr(".input\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "sizeof (YYCTYPE)"));
    append(args, code_arg(alc, "padding"));
    append(args, code_arg(alc, "&input_len"));
    append(block, code_fcall(alc, "input = (YYCTYPE *) read_file", args, ";"));

    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "status = 1"));
    append(if_code, code_stmt(alc, "goto end"));
    append(block, code_if_then_else(alc, "input == NULL", if_code, NULL));

    append(block, code_newline(alc));

    if (sizeof_cunit > 1) {
        text = o.cstr("for (i = 0; i < input_len; ++i) {").flush();
        append(block, code_text(alc, text));
        block2 = code_list(alc);
        from_le(output, block2, "input[i]", opts->encoding.szCodeUnit());
        append(block, code_block(alc, block2, CodeBlock::INDENTED));
        append(block, code_text(alc, "}"));
        append(block, code_newline(alc));
    }

    args = code_args(alc);
    text = o.cstr("\"").str(filename).cstr(".").str(dfa.name).cstr(".keys\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "sizeof (YYKEYTYPE)"));
    append(args, code_arg(alc, "0"));
    append(args, code_arg(alc, "&keys_count"));
    append(block, code_fcall(alc, "keys = (YYKEYTYPE *) read_file", args, ";"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "status = 1"));
    append(if_code, code_stmt(alc, "goto end"));
    append(block, code_if_then_else(alc, "keys == NULL", if_code, NULL));

    append(block, code_textraw(alc, ""));

    if (dfa.key_size > 1) {
        text = o.cstr("for (i = 0; i < keys_count; ++i) {").flush();
        append(block, code_text(alc, text));
        block2 = code_list(alc);
        from_le(output, block2, "keys[i]", dfa.key_size);
        append(block, code_block(alc, block2, CodeBlock::INDENTED));
        append(block, code_text(alc, "}"));
        append(block, code_textraw(alc, ""));
    }

    append(block, code_stmt(alc, "cursor = input"));
    append(block, code_stmt(alc, "limit = input + input_len + padding"));
    append(block, code_stmt(alc, "eof = input + input_len"));

    append(block, code_textraw(alc, ""));

    append(block, code_text(alc,
        "for (i = 0; status == 0 && cursor < eof && i < keys_count;) {"));
    block2 = code_list(alc);
    append(block2, code_stmt(alc, "token = cursor"));
    if (dfa.need_backup) {
        append(block2, code_stmt(alc, "const YYCTYPE *marker = NULL"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append(block2, code_stmt(alc, "const YYCTYPE *ctxmarker = NULL"));
    }
    append(block2, code_stmt(alc, "YYCTYPE yych"));
    if (dfa.need_accept) {
        append(block2, code_stmt(alc, "unsigned int yyaccept = 0"));
    }
    // autogenerated stag variables
    if (!dfa.stagnames.empty()) {
        text = o.cstr("\n").str(indent(2, opts->indString))
            .cstr("const YYCTYPE *@@ = NULL;").flush();
        Code *stags = code_fmt(alc, CODE_STAGS, NULL, text, NULL);
        gen_tags(o, opts, stags, dfa.stagnames);
        append(block2, stags);
        append(block2, code_textraw(alc, ""));
    }
    // user-defined stag variables
    if (!dfa.stagvars.empty()) {
        var1 = dfa.stagvars.begin();
        var2 = dfa.stagvars.end();
        if (var1 != var2) {
            o.cstr("const YYCTYPE *").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", *").str(*var1);
            }
            text = o.flush();
            append(block2, code_stmt(alc, text));
        }
    }
    // autogenerated mtag variables
    if (!dfa.mtagnames.empty()) {
        append(block2, code_text(alc, "yymtagpool_clear(&yytp);"));

        text = o.cstr("\n").str(indent(2, opts->indString))
            .cstr("ptrdiff_t @@ = -1;").flush();
        Code *mtags = code_fmt(alc, CODE_MTAGS, NULL, text, NULL);
        gen_tags(o, opts, mtags, dfa.mtagnames);
        append(block2, mtags);
        append(block2, code_textraw(alc, ""));
    }
    // user-defined mtag variables
    if (!dfa.mtagvars.empty()) {
        var1 = dfa.mtagvars.begin();
        var2 = dfa.mtagvars.end();
        if (var1 != var2) {
            o.cstr("ptrdiff_t ").str(*var1);
            for (++var1; var1 != var2; ++var1) {
                o.cstr(", ").str(*var1);
            }
            text = o.flush();
            append(block2, code_stmt(alc, text));
        }
    }

    if (opts->bFlag) {
        append(block2, gen_bitmap(output, dfa.bitmap));
    }
    append(block2, code_textraw(alc, ""));

    dfa.emit_body(output, block2);
    append(block2, code_textraw(alc, ""));

    append(block, code_block(alc, block2, CodeBlock::INDENTED));
    append(block, code_text(alc, "}"));

    if_code = code_list(alc);

    if1_code = code_list(alc);
    append(if1_code, code_stmt(alc, "status = 1"));
    append(if1_code, code_stmt(alc, "const long pos = token - input"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused input strings left at position %ld\\n\", pos)").flush();
    append(if1_code, code_stmt(alc, text));
    append(if_code, code_if_then_else(alc, "cursor != eof", if1_code, NULL, false));

    if1_code = code_list(alc);
    append(if1_code, code_stmt(alc, "status = 1"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
        .cstr(": unused keys left after %u keys\\n\", i)").flush();
    append(if1_code, code_stmt(alc, text));
    append(if_code, code_if_then_else(alc, "i != keys_count", if1_code, NULL, false));

    append(block, code_if_then_else(alc, "status == 0", if_code, NULL, false));

    append(block, code_textraw(alc, ""));
    append(block, code_slabel(alc, "end"));
    append(block, code_stmt(alc, "free(input)"));
    append(block, code_stmt(alc, "free(keys)"));
    if (!dfa.mtagnames.empty()) {
        append(block, code_stmt(alc, "yymtagpool_free(&yytp)"));
    }
    append(block, code_textraw(alc, ""));
    append(block, code_stmt(alc, "return status"));

    append(code, code_block(alc, block, CodeBlock::WRAPPED));
}

static void emit_skeleton_undefs(Output &output, CodeList *code, DFA &dfa)
{
    const opt_t *opts = output.block().opts;
    code_alc_t &alc = output.allocator;

    append(code, code_textraw(alc, ""));
    append(code, code_textraw(alc, "#undef YYCTYPE"));
    append(code, code_textraw(alc, "#undef YYKEYTYPE"));
    append(code, code_textraw(alc, "#undef YYPEEK"));
    append(code, code_textraw(alc, "#undef YYSKIP"));
    if (dfa.need_backup) {
        append(code, code_textraw(alc, "#undef YYBACKUP"));
        append(code, code_textraw(alc, "#undef YYRESTORE"));
    }
    if (dfa.oldstyle_ctxmarker) {
        append(code, code_textraw(alc, "#undef YYBACKUPCTX"));
        append(code, code_textraw(alc, "#undef YYRESTORECTX"));
    }
    if (opts->tags) {
        append(code, code_textraw(alc, "#undef YYBACKUPTAG"));
        append(code, code_textraw(alc, "#undef YYRESTORETAG"));
        append(code, code_textraw(alc, "#undef YYCOPYTAG"));
    }
    append(code, code_textraw(alc, "#undef YYLESSTHAN"));
    append(code, code_textraw(alc, "#undef YYFILL"));
}

void emit_skeleton(Output &output, CodeList *code, DFA &dfa)
{
    emit_skeleton_defines(output, code, dfa);
    emit_skeleton_function_action(output, code, dfa);
    emit_skeleton_stags(output, code, dfa);
    emit_skeleton_mtags(output, code, dfa);
    emit_skeleton_function_check_key_count(output, code, dfa);
    emit_skeleton_function_lex(output, code, dfa);
    emit_skeleton_undefs(output, code, dfa);
}

Code *emit_skeleton_epilog(Output &output)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;

    CodeList *stmts = code_list(alc);
    const std::set<std::string> &xs = output.skeletons;
    for (std::set<std::string>::const_iterator i = xs.begin(); i != xs.end(); ++i) {
        const char *if_cond = o.cstr("lex_").str(*i).cstr("() != 0").flush();
        CodeList *if_code = code_list(alc);
        append(if_code, code_stmt(alc, "return 1"));
        append(stmts, code_if_then_else(alc, if_cond, if_code, NULL, false));
    }
    append(stmts, code_stmt(alc, "return 0"));

    CodeList *main = code_list(alc);
    append(main, code_text(alc, ""));
    append(main, code_text(alc, "int main()"));
    append(main, code_block(alc, stmts, CodeBlock::WRAPPED));

    return code_block(alc, main, CodeBlock::RAW);
}

void emit_skeleton_action(Output &output, CodeList *code, const DFA &dfa, size_t rid)
{
    code_alc_t &alc = output.allocator;
    Scratchbuf &o = output.scratchbuf;
    const std::string &name = dfa.name;
    const Rule &r = dfa.rules[rid];
    const uint64_t rkey = rule2key(rid, dfa.key_size, dfa.def_rule);
    const char *text;
    std::vector<std::string> fintags;

    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    CodeArgs *args = code_args(alc);
    append(args, code_arg(alc, "keys_count"));
    append(args, code_arg(alc, "i"));
    text = o.u64(ntag).flush();
    append(args, code_arg(alc, text));
    text = o.cstr("status = check_key_count_").str(dfa.name).flush();
    append(code, code_fcall(alc, text, args, ""));

    CodeList *hangafter = code_list(alc);

    args = code_args(alc);
    append(args, code_arg(alc, "&i"));
    append(args, code_arg(alc, "keys"));
    append(args, code_arg(alc, "input"));
    append(args, code_arg(alc, "token"));
    append(args, code_arg(alc, "&cursor"));
    text = o.u64(rkey).flush();
    append(args, code_arg(alc, text));
    text = o.cstr(" || action_").str(name).flush();
    append(hangafter, code_fcall(alc, text, args, ntag > 3 ? "" : ";"));

    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag &tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        const bool mtag = history(tag);
        expand_fintags(tag, fintags);
        const std::string tname = fintags[0];
        --ntag;

        args = code_args(alc);
        append(args, code_arg(alc, "&i"));
        append(args, code_arg(alc, "keys"));
        if (mtag) append(args, code_arg(alc, "&yytp"));
        text = o.str(tname).flush();
        append(args, code_arg(alc, text));
        append(args, code_arg(alc, "input"));
        append(args, code_arg(alc, "token"));
        text = o.cstr("\"").str(tname).cstr("\"").flush();
        append(args, code_arg(alc, text));
        text = o.cstr(" || check_").cstr(mtag ? "mtag_" : "stag_").str(name).flush();
        append(hangafter, code_fcall(alc, text, args, ntag > 3 ? "" : ";"));
    }

    append(code, code_block(alc, hangafter, CodeBlock::INDENTED));

    append(code, code_stmt(alc, "continue"));
}

} // namespace re2c
