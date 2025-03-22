#include <stddef.h>
#include <stdint.h>
#include <set>
#include <string>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/output.h"
#include "src/codegen/helpers.h"
#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

static void from_le(Output& output, CodeList* code, const char* expr, size_t size) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

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

Code* emit_skeleton_prolog(Output& output) {
    OutAllocator& alc = output.allocator;
    const char* if_cond;
    CodeList* code, *block, *if_code;
    CodeParams* params;

    code = code_list(alc);

    append(code, code_newline(alc));
    append(code, code_textraw(alc, "#include <stddef.h> /* size_t */"));
    append(code, code_textraw(alc, "#include <stdio.h>"));
    append(code, code_textraw(alc, "#include <stdlib.h> /* malloc, free */"));
    append(code, code_textraw(alc, "#include <string.h> /* memcpy */"));
    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "fname", "const char*"));
    append(params, code_param(alc, "unit", "size_t"));
    append(params, code_param(alc, "padding", "size_t"));
    append(params, code_param(alc, "pfsize", "size_t*"));

    block = code_list(alc);

    append(block, code_stmt(alc, "void *buffer = NULL"));
    append(block, code_stmt(alc, "size_t fsize = 0"));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* open file */"));
    append(block, code_stmt(alc, "FILE *f = fopen(fname, \"rb\")"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "goto error"));
    append(block, code_if_then_else(alc, "f == NULL", if_code, nullptr));

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
    append(block, code_if_then_else(alc, "buffer == NULL", if_code, nullptr));

    append(block, code_newline(alc));

    append(block, code_text(alc, "/* read the whole file in memory */"));
    if_cond = "fread(buffer, unit, fsize, f) != fsize";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "goto error"));
    append(block, code_if_then_else(alc, if_cond, if_code, nullptr));

    append(block, code_newline(alc));

    append(block, code_stmt(alc, "fclose(f)"));
    append(block, code_stmt(alc, "*pfsize = fsize"));
    append(block, code_stmt(alc, "return buffer"));

    append(block, code_newline(alc));
    append(block, code_slabel(alc, "error"));

    append(block, code_stmt(alc, "fprintf(stderr, \"error: cannot read file '%s'\\n\", fname)"));
    append(block, code_stmt(alc, "free(buffer)"));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "fclose(f)"));
    append(block, code_if_then_else(alc, "f != NULL", if_code, nullptr));
    append(block, code_stmt(alc, "return NULL"));

    append(code, code_fndef(alc, "read_file", "static void*", params, block));

    return code_block(alc, code, CodeBlock::Kind::RAW);
}

static void emit_skeleton_defines(Output& output, CodeList* code, const Adfa& dfa) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.cunit_size();
    const char* text;

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
    append(code, code_textraw(alc, opts->fill_eof == NOEOF
            ? "#define YYFILL(n) { goto loop_end; }"
            : "#define YYFILL(n) 1 /* fail */"));
    append(code, code_newline(alc));
}

static void emit_skeleton_function_action(Output& output, CodeList* code, const Adfa& dfa) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const opt_t* opts = output.block().opts;
    const uint64_t norule = rule2key(Rule::NONE, dfa.key_size, dfa.def_rule);
    CodeParams* params;
    CodeList* if_code, *else_code, *body;
    const char* if_cond, *text;

    params = code_params(alc);
    append(params, code_param(alc, "pkix", "unsigned*"));
    append(params, code_param(alc, "keys", "const YYKEYTYPE*"));
    append(params, code_param(alc, "start", "const YYCTYPE*"));
    append(params, code_param(alc, "token", "const YYCTYPE*"));
    append(params, code_param(alc, "cursor", "const YYCTYPE**"));
    append(params, code_param(alc, "rule_act", "YYKEYTYPE"));

    body = code_list(alc);

    append(body, code_stmt(alc, "const unsigned kix = *pkix"));
    append(body, code_stmt(alc, "const long pos = token - start"));
    append(body, code_stmt(alc, "const long len_act = *cursor - token"));
    append(body, code_stmt(alc, "const long len_exp = (long) keys[kix + 1]"));
    append(body, code_stmt(alc, "const YYKEYTYPE rule_exp = keys[kix + 2]"));
    append(body, code_stmt(alc, "*pkix = kix + 3"));

    if_cond = o.cstr("rule_exp == ").u64(norule).flush();
    // Don't use code_fncall here as the format string is too long and needs to be broken on
    // multiple lines. It's ok because the target is always C/C++.
    if_code = code_list(alc);
    append(if_code, code_text(alc, o.cstr("fprintf(stderr,").flush()));
    append(if_code, code_text(alc, o.str(opts->indent_str)
        .cstr("\"warning: lex_").str(dfa.name).cstr(": control flow is undefined\"").flush()));
    append(if_code, code_text(alc, o.str(opts->indent_str)
        .cstr("\" for input at position %ld, rerun re2c with '-W'\\n\");").flush()));
    append(body, code_if_then_else(alc, if_cond, if_code, nullptr));

    if_cond = "len_act == len_exp && rule_act == rule_exp";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "const YYKEYTYPE offset = keys[kix]"));
    append(if_code, code_stmt(alc, "*cursor = token + offset"));
    append(if_code, code_stmt(alc, "return 0"));
    // Don't use code_fncall here as the format string is too long and needs to be broken on
    // multiple lines. It's ok because the target is always C/C++.
    else_code = code_list(alc);
    append(else_code, code_text(alc, "fprintf(stderr,"));
    append(else_code, code_text(alc, o.str(opts->indent_str)
        .cstr("\"error: lex_").str(dfa.name).cstr(": at position %ld (key %u):\\n\"").flush()));
    append(else_code, code_text(alc, o.str(opts->indent_str)
        .cstr("\"\\texpected: match length %ld, rule %u\\n\"").flush()));
    append(else_code, code_text(alc, o.str(opts->indent_str)
        .cstr("\"\\tactual:   match length %ld, rule %u\\n\",").flush()));
    append(else_code, code_text(alc, o.str(opts->indent_str)
        .cstr("pos, kix, len_exp, rule_exp, len_act, rule_act);").flush()));
    append(else_code, code_text(alc, "return 1;"));
    append(body, code_if_then_else(alc, if_cond, if_code, else_code));

    text = o.cstr("action_").str(dfa.name).flush();
    append(code, code_fndef(alc, text, "static int", params, body));
}

static void emit_skeleton_stags(Output& output, CodeList* code, const Adfa& dfa) {
    const opt_t* opts = output.block().opts;
    if (dfa.stagvars.empty() && !opts->captures) return;

    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    CodeArgs* args;
    CodeParams* params;
    CodeList* if_code, *body;
    const char* if_cond, *text;

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "pkix", "unsigned*"));
    append(params, code_param(alc, "keys", "YYKEYTYPE*"));
    append(params, code_param(alc, "tag", "const YYCTYPE*"));
    append(params, code_param(alc, "input", "const YYCTYPE*"));
    append(params, code_param(alc, "token", "const YYCTYPE*"));
    append(params, code_param(alc, "name", "const char*"));

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
    append(body, code_if_then_else(alc, if_cond, if_code, nullptr));

    append(body, code_newline(alc));

    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"\n")
            .cstr("\"wrong value for tag `%s`: expected %u, actual %u\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix"));
    append(args, code_arg(alc, "name"));
    append(args, code_arg(alc, "exp"));
    append(args, code_arg(alc, "act"));
    append(body, code_fncall(alc, "fprintf", /*retval*/ nullptr, args));
    append(body, code_stmt(alc, "return 1"));

    text = o.cstr("check_stag_").str(dfa.name).flush();
    append(code, code_fndef(alc, text, "static int", params, body));
}

static void emit_skeleton_mtag_defs(Output& output, CodeList* code) {
    OutAllocator& alc = output.allocator;
    CodeParams* params;
    CodeList* if_code, *block;
    const char* if_cond;

    // Use `void *` instead of `YYCTYPE *`, as YYCTYPE may vary for different blocks. and this
    // definition must be valid throughout the whole file.

    append(code, code_newline(alc));

    append(code, code_text(alc, "typedef struct yymtag_t {"));
    block = code_list(alc);
    append(block, code_text(alc, "ptrdiff_t pred;"));
    append(block, code_text(alc, "const void *elem;"));
    append(code, code_block(alc, block, CodeBlock::Kind::INDENTED));
    append(code, code_text(alc, "} yymtag_t;"));

    append(code, code_newline(alc));

    append(code, code_text(alc, "typedef struct yymtagpool_t {"));
    block = code_list(alc);
    append(block, code_text(alc, "yymtag_t *head;"));
    append(block, code_text(alc, "yymtag_t *next;"));
    append(block, code_text(alc, "yymtag_t *last;"));
    append(code, code_block(alc, block, CodeBlock::Kind::INDENTED));
    append(code, code_text(alc, "} yymtagpool_t;"));

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "tp", "yymtagpool_t*"));
    block = code_list(alc);
    append(block, code_stmt(alc, "tp->next = tp->head"));
    append(code, code_fndef(alc, "yymtagpool_clear", "static void", params, block));

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "tp", "yymtagpool_t*"));
    block = code_list(alc);
    append(block, code_stmt(alc, "static const unsigned size = 4096"));
    append(block, code_stmt(alc, "tp->head = (yymtag_t*)malloc(size * sizeof(yymtag_t))"));
    append(block, code_stmt(alc, "tp->next = tp->head"));
    append(block, code_stmt(alc, "tp->last = tp->head + size"));
    append(code, code_fndef(alc, "yymtagpool_init", "static void", params, block));

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "tp", "yymtagpool_t*"));
    block = code_list(alc);
    append(block, code_stmt(alc, "free(tp->head)"));
    append(block, code_stmt(alc, "tp->head = tp->next = tp->last = NULL"));
    append(code, code_fndef(alc, "yymtagpool_free", "static void", params, block));

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "tp", "yymtagpool_t*"));
    block = code_list(alc);
    if_cond = "tp->next == tp->last";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "const unsigned size = tp->last - tp->head"));
    append(if_code, code_stmt(
            alc, "yymtag_t *head = (yymtag_t*)malloc(2 * size * sizeof(yymtag_t))"));
    append(if_code, code_stmt(alc, "memcpy(head, tp->head, size * sizeof(yymtag_t))"));
    append(if_code, code_stmt(alc, "free(tp->head)"));
    append(if_code, code_stmt(alc, "tp->head = head"));
    append(if_code, code_stmt(alc, "tp->next = head + size"));
    append(if_code, code_stmt(alc, "tp->last = head + size * 2"));
    append(block, code_if_then_else(alc, if_cond, if_code, nullptr));
    append(block, code_stmt(alc, "return tp->next++"));
    append(code, code_fndef(alc, "yymtagpool_next", "static yymtag_t*", params, block));

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "pt", "ptrdiff_t*"));
    append(params, code_param(alc, "t", "const void*"));
    append(params, code_param(alc, "tp", "yymtagpool_t*"));
    block = code_list(alc);
    append(block, code_stmt(alc, "yymtag_t *n = yymtagpool_next(tp)"));
    append(block, code_stmt(alc, "n->pred = *pt"));
    append(block, code_stmt(alc, "n->elem = t"));
    append(block, code_stmt(alc, "*pt = n - tp->head"));
    append(code, code_fndef(alc, "yymtag", "static void", params, block));

    append(code, code_newline(alc));
}

static void emit_skeleton_mtags(Output& output, CodeList* code, const Adfa& dfa) {
    if (dfa.mtagvars.empty()) return;

    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    CodeArgs* args;
    CodeParams* params;
    CodeList* if_code, *block, *body;
    const char* if_cond, *text;

    // Data structures for m-tags are the same for all blocks in the file. They are emitted at the
    // first block that has m-tags, because it's impossible to know earlier (when generating
    // prologue) if m-tags are needed at all.
    if (!output.done_mtag_defs) {
        output.done_mtag_defs = true;
        emit_skeleton_mtag_defs(output, code);
    }

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "pkix", "unsigned*"));
    append(params, code_param(alc, "keys", "YYKEYTYPE*"));
    append(params, code_param(alc, "tp", "const yymtagpool_t*"));
    append(params, code_param(alc, "mtag", "ptrdiff_t"));
    append(params, code_param(alc, "input", "const YYCTYPE*"));
    append(params, code_param(alc, "token", "const YYCTYPE*"));
    append(params, code_param(alc, "name", "const char*"));

    body = code_list(alc);
    append(body, code_stmt(alc, "const unsigned kix = *pkix"));
    append(body, code_stmt(alc, "YYKEYTYPE n = keys[kix]"));
    append(body, code_stmt(alc, "*pkix = kix + n + 1"));

    append(body, code_text(alc, "for (; n > 0; --n) {"));
    block = code_list(alc); // for loop

    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"\n")
            .cstr("\"history for tag `%s` is too short\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(if_code, code_fncall(alc, "fprintf", /*retval*/ nullptr, args));
    append(if_code, code_stmt(alc, "return 1"));
    append(block, code_if_then_else(alc, "mtag == -1", if_code, nullptr));

    append(block, code_stmt(alc, "const YYCTYPE *tag = (tp->head + mtag)->elem"));
    append(block, code_stmt(alc, "mtag = (tp->head + mtag)->pred"));
    append(block, code_stmt(alc, "const YYKEYTYPE exp = keys[kix + n]"));
    append(block, code_stmt(alc, "const YYKEYTYPE act = (YYKEYTYPE)(tag - token)"));
    append(block, code_stmt(alc, "const YYKEYTYPE NIL = (YYKEYTYPE)~0u"));

    if_cond = "!(exp == act || (exp == NIL && tag == NULL))";
    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"\n")
            .cstr("\"wrong value for tag `%s`: expected %u, actual %u\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(args, code_arg(alc, "exp"));
    append(args, code_arg(alc, "act"));
    append(if_code, code_fncall(alc, "fprintf", /*retval*/ nullptr, args));
    append(if_code, code_stmt(alc, "return 1"));
    append(block, code_if_then_else(alc, if_cond, if_code, nullptr));

    append(body, code_block(alc, block, CodeBlock::Kind::INDENTED));
    append(body, code_text(alc, "}")); // end of for loop

    if_code = code_list(alc);
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": at position %ld, key %u: \"\n")
            .cstr("\"history for tag `%s` is too long\\n\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "token - input"));
    append(args, code_arg(alc, "kix + n"));
    append(args, code_arg(alc, "name"));
    append(if_code, code_fncall(alc, "fprintf", /*retval*/ nullptr, args));
    append(if_code, code_stmt(alc, "return 1"));
    append(body, code_if_then_else(alc, "mtag != -1", if_code, nullptr));
    append(body, code_text(alc, "return 0;"));

    text = o.cstr("check_mtag_").str(dfa.name).flush();
    append(code, code_fndef(alc, text, "static int", params, body));
}

static void emit_skeleton_function_check_key_count(Output& output, CodeList* code, Adfa& dfa) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    CodeArgs* args;
    CodeParams* params;
    CodeList* block, *if_code;
    const char* if_cond, *text;

    append(code, code_newline(alc));

    params = code_params(alc);
    append(params, code_param(alc, "have", "unsigned"));
    append(params, code_param(alc, "used", "unsigned"));
    append(params, code_param(alc, "need", "unsigned"));
    block = code_list(alc);
    if_cond = "used + need <= have";
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "return 0"));
    append(block, code_if_then_else(alc, if_cond, if_code, nullptr));
    args = code_args(alc);
    append(args, code_arg(alc, "stderr"));
    text = o.cstr("\"error: lex_").str(dfa.name).cstr(": not enough keys\\n\"").flush();
    append(args, code_arg(alc, text));
    append(block, code_fncall(alc, "fprintf", /*retval*/ nullptr, args));
    append(block, code_stmt(alc, "return 1"));

    text = o.cstr("check_key_count_").str(dfa.name).flush();
    append(code, code_fndef(alc, text, "static int", params, block));
}

static void emit_skeleton_function_lex(Output& output, CodeList* code, Adfa& dfa) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const size_t sizeof_cunit = opts->encoding.cunit_size();
    std::set<std::string>::const_iterator var1, var2;
    CodeArgs* args;
    CodeList* block, *block2, *if_code, *if1_code;
    const char* text;

    std::string filename = opts->output_file;
    if (filename.empty()) {
        filename = "<stdout>";
    }
    filename = escape_backslashes(filename);

    append(code, code_newline(alc));

    block = code_list(alc);
    text = o.cstr("const size_t padding = ").u64(dfa.max_fill).cstr("; /* YYMAXFILL */").flush();
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
    if (opts->captures) {
        append(block, code_stmt(alc, "size_t yynmatch"));
        text = o.cstr("const YYCTYPE *yypmatch[").u64(dfa.max_nmatch).cstr(" * 2]").flush();
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
    append(block, code_fncall(alc, "input = (YYCTYPE *) read_file", /*retval*/ nullptr, args));

    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "status = 1"));
    append(if_code, code_stmt(alc, "goto end"));
    append(block, code_if_then_else(alc, "input == NULL", if_code, nullptr));

    append(block, code_newline(alc));

    if (sizeof_cunit > 1) {
        text = o.cstr("for (i = 0; i < input_len; ++i) {").flush();
        append(block, code_text(alc, text));
        block2 = code_list(alc);
        from_le(output, block2, "input[i]", opts->encoding.cunit_size());
        append(block, code_block(alc, block2, CodeBlock::Kind::INDENTED));
        append(block, code_text(alc, "}"));
        append(block, code_newline(alc));
    }

    args = code_args(alc);
    text = o.cstr("\"").str(filename).cstr(".").str(dfa.name).cstr(".keys\"").flush();
    append(args, code_arg(alc, text));
    append(args, code_arg(alc, "sizeof (YYKEYTYPE)"));
    append(args, code_arg(alc, "0"));
    append(args, code_arg(alc, "&keys_count"));
    append(block, code_fncall(alc, "keys = (YYKEYTYPE *) read_file", /*retval*/ nullptr, args));
    if_code = code_list(alc);
    append(if_code, code_stmt(alc, "status = 1"));
    append(if_code, code_stmt(alc, "goto end"));
    append(block, code_if_then_else(alc, "keys == NULL", if_code, nullptr));

    append(block, code_textraw(alc, ""));

    if (dfa.key_size > 1) {
        text = o.cstr("for (i = 0; i < keys_count; ++i) {").flush();
        append(block, code_text(alc, text));
        block2 = code_list(alc);
        from_le(output, block2, "keys[i]", dfa.key_size);
        append(block, code_block(alc, block2, CodeBlock::Kind::INDENTED));
        append(block, code_text(alc, "}"));
        append(block, code_textraw(alc, ""));
    }

    append(block, code_stmt(alc, "cursor = input"));
    append(block, code_stmt(alc, "limit = input + input_len + padding"));
    append(block, code_stmt(alc, "eof = input + input_len"));

    append(block, code_textraw(alc, ""));

    // Don't use `for` loops or `while` loops: the generated code may contain an inner loop if the
    // --loop-switch option is used, and then `continue` and `break` statements may result in
    // unexpected control flow. Use `goto` loop.
    append(block, code_stmt(alc, "i = 0"));
    append(block, code_slabel(alc, "loop"));

    block2 = code_list(alc);
    append(block2, code_stmt(alc, "goto loop_end"));
    append(block, code_if_then_else(
            alc, "!(status == 0 && cursor < eof && i < keys_count)", block2, nullptr));

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
    if (opts->code_model == CodeModel::LOOP_SWITCH) {
        append(block2, code_stmt(alc, o.cstr("unsigned int yystate = 0").flush()));
    }
    // autogenerated stag variables
    if (!dfa.stagnames.empty()) {
        o.cstr("\n").str(indent(2, opts->indent_str)).cstr("const YYCTYPE *@@ = NULL;");
        Code* stags = code_fmt(alc, CodeKind::STAGS, nullptr, o.flush(), nullptr);
        gen_tags(o, opts, stags, dfa.stagnames);
        append(block2, stags);
        append(block2, code_textraw(alc, ""));
    }
    // user-defined stag variables
    if (!dfa.stagvars.empty()) {
        o.cstr("\n").str(indent(2, opts->indent_str)).cstr("const YYCTYPE *@@ = NULL;");
        Code* stagvars = code_fmt(alc, CodeKind::SVARS, nullptr, o.flush(), nullptr);
        gen_tags(o, opts, stagvars, dfa.stagvars);
        append(block2, stagvars);
        append(block2, code_textraw(alc, ""));
    }
    // autogenerated mtag variables
    if (!dfa.mtagnames.empty()) {
        append(block2, code_text(alc, "yymtagpool_clear(&yytp);"));
        o.cstr("\n").str(indent(2, opts->indent_str)).cstr("ptrdiff_t @@ = -1;");
        Code* mtags = code_fmt(alc, CodeKind::MTAGS, nullptr, o.flush(), nullptr);
        gen_tags(o, opts, mtags, dfa.mtagnames);
        append(block2, mtags);
        append(block2, code_textraw(alc, ""));
    }
    // user-defined mtag variables
    if (!dfa.mtagvars.empty()) {
        o.cstr("\n").str(indent(2, opts->indent_str)).cstr("ptrdiff_t @@ = -1;");
        Code* mtagvars = code_fmt(alc, CodeKind::MVARS, nullptr, o.flush(), nullptr);
        gen_tags(o, opts, mtagvars, dfa.mtagvars);
        append(block2, mtagvars);
        append(block2, code_textraw(alc, ""));
    }

    if (opts->bitmaps) {
        append(block2, gen_bitmap(output, dfa.bitmap, dfa.cond));
    }
    append(block2, code_textraw(alc, ""));

    switch (opts->code_model) {
    case CodeModel::GOTO_LABEL:
        gen_dfa_as_blocks_with_labels(output, dfa, block2);
        break;
    case CodeModel::LOOP_SWITCH: {
        // In loop/switch mode there are no labels, and each block has its own state switch.
        // Restart state counter from zero so that cases start from zero.
        output.label_counter = 0;
        CodeCases* cases = code_cases(alc);
        gen_dfa_as_switch_cases(output, dfa, cases);
        wrap_dfas_in_loop_switch(output, block2, cases);
        break;
    }
    case CodeModel::REC_FUNC:
        UNREACHABLE();
        break;
    }
    append(block2, code_textraw(alc, ""));

    append(block, code_block(alc, block2, CodeBlock::Kind::WRAPPED));
    append(block, code_slabel(alc, "loop_end"));

    if_code = code_list(alc);

    if1_code = code_list(alc);
    append(if1_code, code_stmt(alc, "status = 1"));
    append(if1_code, code_stmt(alc, "const long pos = token - input"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
            .cstr(": unused input strings left at position %ld\\n\", pos)").flush();
    append(if1_code, code_stmt(alc, text));
    append(if_code, code_if_then_else(alc, "cursor != eof", if1_code, nullptr));

    if1_code = code_list(alc);
    append(if1_code, code_stmt(alc, "status = 1"));
    text = o.cstr("fprintf(stderr, \"error: lex_").str(dfa.name)
            .cstr(": unused keys left after %u keys\\n\", i)").flush();
    append(if1_code, code_stmt(alc, text));
    append(if_code, code_if_then_else(alc, "i != keys_count", if1_code, nullptr));

    append(block, code_if_then_else(alc, "status == 0", if_code, nullptr));

    append(block, code_textraw(alc, ""));
    append(block, code_slabel(alc, "end"));
    append(block, code_stmt(alc, "free(input)"));
    append(block, code_stmt(alc, "free(keys)"));
    if (!dfa.mtagnames.empty()) {
        append(block, code_stmt(alc, "yymtagpool_free(&yytp)"));
    }
    append(block, code_textraw(alc, ""));
    append(block, code_stmt(alc, "return status"));

    text = o.cstr("lex_").str(dfa.name).flush();
    append(code, code_fndef(alc, text, "int", code_params(alc), block));
}

static void emit_skeleton_undefs(Output& output, CodeList* code, Adfa& dfa) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

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

void emit_skeleton(Output& output, CodeList* code, Adfa& dfa) {
    emit_skeleton_defines(output, code, dfa);
    emit_skeleton_function_action(output, code, dfa);
    emit_skeleton_stags(output, code, dfa);
    emit_skeleton_mtags(output, code, dfa);
    emit_skeleton_function_check_key_count(output, code, dfa);
    emit_skeleton_function_lex(output, code, dfa);
    emit_skeleton_undefs(output, code, dfa);
}

Code* emit_skeleton_epilog(Output& output) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    for (const std::string& s : output.skeletons) {
        const char* if_cond = o.cstr("lex_").str(s).cstr("() != 0").flush();
        CodeList* if_code = code_list(alc);
        append(if_code, code_stmt(alc, "return 1"));
        append(stmts, code_if_then_else(alc, if_cond, if_code, nullptr));
    }
    append(stmts, code_stmt(alc, "return 0"));

    CodeList* main = code_list(alc);
    append(main, code_text(alc, ""));
    append(main, code_fndef(alc, "main", "int", code_params(alc), stmts));

    return code_block(alc, main, CodeBlock::Kind::RAW);
}

void emit_skeleton_action(Output& output, CodeList* code, const Adfa& dfa, size_t rid) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const std::string& name = dfa.name;
    const Rule& r = dfa.rules[rid];
    const uint64_t rkey = rule2key(rid, dfa.key_size, dfa.def_rule);
    std::vector<const char*> fintags;

    size_t ntag = 3;
    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag& tag = dfa.tags[t];
        if (t != r.ttag && !fictive(tag)) ++ntag;
    }

    // Don't use code_fncall here as it can't handle complex expressions with logical OR of
    // multiple function calls, and it's always the same target (C/C++).
    o.cstr("status = check_key_count_").str(dfa.name).cstr("(keys_count, i, ").u64(ntag).cstr(")");
    append(code, code_text(alc, o.flush()));

    CodeList* hangafter = code_list(alc);

    o.cstr(" || action_").str(name).cstr("(&i, keys, input, token, &cursor, ").u64(rkey).cstr(")");
    if (ntag <= 3) o.cstr(";");
    append(hangafter, code_text(alc, o.flush()));

    for (size_t t = r.ltag; t < r.htag; ++t) {
        const Tag& tag = dfa.tags[t];
        if (t == r.ttag || fictive(tag)) continue;

        const bool mtag = history(tag);
        expand_fintags(output, tag, fintags);
        const std::string tname = fintags[0];
        --ntag;

        o.cstr(" || check_").cstr(mtag ? "mtag_" : "stag_").str(name).cstr("(&i, keys, ");
        if (mtag) o.cstr("&yytp, ");
        o.str(tname).cstr(", input, token, ").cstr("\"").str(tname).cstr("\")");
        if (ntag <= 3) o.cstr(";");
        append(hangafter, code_text(alc, o.flush()));
    }

    append(code, code_block(alc, hangafter, CodeBlock::Kind::INDENTED));

    append(code, code_stmt(alc, "goto loop"));
}

} // namespace re2c
