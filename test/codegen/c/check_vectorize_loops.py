#!/usr/bin/env python3
"""Differential parity oracle for --vectorize-loops (C and Go, widths 16 and 32).

Usage: python3 test/codegen/c/check_vectorize_loops.py /path/to/re2c
Like re2c, this test is in the public domain.
"""

import argparse
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile


COMMON_HDR = r'''#ifndef VEC_LOOPS_COMMON_H
#define VEC_LOOPS_COMMON_H

#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern size_t g_vec_loads;

#if defined(__GNUC__) || defined(__clang__)
__attribute__((target("avx")))
#endif
static inline __m256i re2c_counted_loadu_si256(const void *p) {
    ++g_vec_loads;
    return _mm256_loadu_si256((const __m256i *)p);
}
static inline __m128i re2c_counted_loadu_si128(const void *p) {
    ++g_vec_loads;
    return _mm_loadu_si128((const __m128i *)p);
}
#undef _mm256_loadu_si256
#define _mm256_loadu_si256(p) re2c_counted_loadu_si256(p)
#undef _mm_loadu_si128
#define _mm_loadu_si128(p) re2c_counted_loadu_si128(p)

#define MAX_PAD 64

typedef struct {
    union { const unsigned char *cur; const unsigned char *yycursor; };
    union { const unsigned char *lim; const unsigned char *yylimit; };
    union { const unsigned char *mar; const unsigned char *yymarker; };
    const unsigned char *tok;
    unsigned char yych;
    unsigned int yyaccept;
    int yystate;
} Rec;

typedef struct {
    int kind;
    int len;
    int tags[20];
} UriResult;

#endif
'''


def make_grammar_rules():
    return {
        'g1': r'''
            [a-zA-Z0-9_]+ { return 1; }
            "\x00"        { return 0; }
            *             { return 2; }
        ''',
        'g2': r'''
            ["] [^"\\\x00\n]* ["] { return 1; }
            ["] ([^"\\\x00\n] | [\\] [^\x00\n])* ["] { return 2; }
            [^"\x00]+ { return 3; }
            "\x00"    { return 0; }
            *         { return 4; }
        ''',
        'g3': r'''
            [ \t\r\n]+    { return 1; }
            [^ \t\r\n\x00]+ { return 2; }
            "\x00"        { return 0; }
            *             { return 3; }
        ''',
        'g4': r'''
            "//" [^\n\x00]* { return 1; }
            [0-9]+ ("." [0-9]+)? { return 2; }
            [\x80-\xff]+    { return 3; }
            "\x00"          { return 0; }
            *               { return 4; }
        ''',
        'g5': r'''
            [a-zA-Z_][a-zA-Z0-9_]* { return 1; }
            ["] [^"\\\x00\n]* ["]  { return 2; }
            [ \t\r\n]+             { return 3; }
            [0-9]+                 { return 4; }
            "//" [^\n\x00]*        { return 5; }
            [\x80-\xff]+           { return 6; }
            "\x00"                 { return 0; }
            *                      { return 7; }
        ''',
    }


URI_GRAMMAR_BODY = r'''
    end = "\x00";
    eol = "\n";

    alpha       = [a-zA-Z];
    digit       = [0-9];
    hexdigit    = [0-9a-fA-F];
    unreserved  = alpha | digit | [-._~];
    pct_encoded = "%" hexdigit{2};
    sub_delims  = [!$&'()*+,;=];
    pchar       = unreserved | pct_encoded | sub_delims | [:@];

    scheme = @s1 alpha (alpha | digit | [-+.])* @s2;
    userinfo = @u1 (unreserved | pct_encoded | sub_delims | ":")* @u2;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
    ipv4address = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16         = hexdigit{1,4};
    ls32        = h16 ":" h16 | ipv4address;
    ipv6address
        =                            (h16 ":"){6} ls32
        |                       "::" (h16 ":"){5} ls32
        | (               h16)? "::" (h16 ":"){4} ls32
        | ((h16 ":"){0,1} h16)? "::" (h16 ":"){3} ls32
        | ((h16 ":"){0,2} h16)? "::" (h16 ":"){2} ls32
        | ((h16 ":"){0,3} h16)? "::"  h16 ":"     ls32
        | ((h16 ":"){0,4} h16)? "::"              ls32
        | ((h16 ":"){0,5} h16)? "::"              h16
        | ((h16 ":"){0,6} h16)? "::";
    ipvfuture   = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal  = "[" ( ipv6address | ipvfuture ) "]";
    reg_name    = (unreserved | pct_encoded | sub_delims)*;
    host
        = @h1 ip_literal  @h2
        | @h3 ipv4address @h4
        | @h5 reg_name    @h6;
    port      = @r1 digit* @r2;
    authority = (userinfo "@")? host (":" port)?;
    path_abempty  = ("/" pchar*)*;
    path_absolute = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless = pchar+ ("/" pchar*)*;
    path_empty    = "";
    hier_part
        = "//" authority @p1 path_abempty @p2
        | @p3 (path_absolute | path_rootless | path_empty) @p4;
    query    = @q1 (pchar | [/?])* @q2;
    fragment = @f1 (pchar | [/?])* @f2;
    uri = scheme ":" hier_part ("?" query)? ("#" fragment)?;

    *   { out->kind = -1; out->len = (int)(r->cur - start); return; }
    end { out->kind = 0;  out->len = (int)(r->cur - start); return; }
    eol { out->kind = 2;  out->len = (int)(r->cur - start); return; }
    uri {
        out->kind = 1;
        out->len = (int)(r->cur - start);
        const unsigned char *tags[20] = {
            s1, s2, u1, u2, h1, h2, h3, h4, h5, h6,
            r1, r2, p1, p2, p3, p4, q1, q2, f1, f2
        };
        for (int i = 0; i < 20; ++i) {
            out->tags[i] = tags[i] ? (int)(tags[i] - start) : -1;
        }
        return;
    }
'''


def gen_simple_variant(suffix, vec_flag):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        out.append(f'''
int lex_{gname}_{suffix}(Rec *r) {{
    /*!re2c
        re2c:vectorize:loops = {vec_flag};
        re2c:api = simple;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = r->cur;
        re2c:YYLIMIT = r->lim;
        re2c:YYMARKER = r->mar;
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        {body}
    */
}}
''')
    out.append(rf'''
void lex_uri_{suffix}(Rec *r, UriResult *out) {{
    const unsigned char *start = r->cur;
    const unsigned char *s1 = NULL, *u1 = NULL, *h1 = NULL, *h3 = NULL, *h5 = NULL,
                        *r1 = NULL, *p1 = NULL, *p3 = NULL, *q1 = NULL, *f1 = NULL,
                        *s2 = NULL, *u2 = NULL, *h2 = NULL, *h4 = NULL, *h6 = NULL,
                        *r2 = NULL, *p2 = NULL, *p4 = NULL, *q2 = NULL, *f2 = NULL;
    /*!stags:re2c:uri_{suffix} format = "const unsigned char *@@ = NULL;\n"; */
    memset(out, 0, sizeof(*out));
    for (int i = 0; i < 20; ++i) out->tags[i] = -1;
    /*!re2c:uri_{suffix}
        re2c:vectorize:loops = {vec_flag};
        re2c:api = simple;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = r->cur;
        re2c:YYLIMIT = r->lim;
        re2c:YYMARKER = r->mar;
        re2c:YYFILL = "{{ out->kind = -2; return; }}";
        re2c:YYFILL:naked = 1;
        re2c:flags:tags = 1;
        {URI_GRAMMAR_BODY}
    */
}}
''')
    return '\n'.join(out)


def gen_record_variant(suffix):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        out.append(f'''
int lex_{gname}_{suffix}(Rec *r) {{
    /*!re2c
        re2c:vectorize:loops = 1;
        re2c:api = record;
        re2c:yyrecord = r;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        {body}
    */
}}
''')
    out.append(rf'''
void lex_uri_{suffix}(Rec *r, UriResult *out) {{
    const unsigned char *start = r->cur;
    const unsigned char *s1 = NULL, *u1 = NULL, *h1 = NULL, *h3 = NULL, *h5 = NULL,
                        *r1 = NULL, *p1 = NULL, *p3 = NULL, *q1 = NULL, *f1 = NULL,
                        *s2 = NULL, *u2 = NULL, *h2 = NULL, *h4 = NULL, *h6 = NULL,
                        *r2 = NULL, *p2 = NULL, *p4 = NULL, *q2 = NULL, *f2 = NULL;
    /*!stags:re2c:uri_{suffix} format = "const unsigned char *@@ = NULL;\n"; */
    memset(out, 0, sizeof(*out));
    for (int i = 0; i < 20; ++i) out->tags[i] = -1;
    /*!re2c:uri_{suffix}
        re2c:vectorize:loops = 1;
        re2c:api = record;
        re2c:yyrecord = r;
        re2c:tags:expression = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL = "{{ out->kind = -2; return; }}";
        re2c:YYFILL:naked = 1;
        re2c:flags:tags = 1;
        {URI_GRAMMAR_BODY}
    */
}}
''')
    return '\n'.join(out)


def gen_generic_fn_variant(suffix):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        out.append(f'''
int lex_{gname}_{suffix}(Rec *r) {{
#define YYPEEK()      (*r->cur)
#define YYPEEK16()    _mm_loadu_si128((const __m128i *)r->cur)
#define YYPEEK32()    _mm256_loadu_si256((const __m256i *)r->cur)
#define YYSKIP()      (++r->cur)
#define YYBACKUP()    (r->mar = r->cur)
#define YYRESTORE()   (r->cur = r->mar)
#define YYSHIFT(n)    (r->cur += (n))
#define YYLESSTHAN(n) ((size_t)(r->lim - r->cur) < (size_t)(n))
#define YYFILL(n)     return -2
    /*!re2c
        re2c:vectorize:loops = 1;
        re2c:api = generic;
        re2c:api:style = functions;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL:naked = 0;
        {body}
    */
#undef YYPEEK
#undef YYPEEK16
#undef YYPEEK32
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYSHIFT
#undef YYLESSTHAN
#undef YYFILL
}}
''')
    out.append(rf'''
void lex_uri_{suffix}(Rec *r, UriResult *out) {{
    const unsigned char *start = r->cur;
    const unsigned char *s1 = NULL, *u1 = NULL, *h1 = NULL, *h3 = NULL, *h5 = NULL,
                        *r1 = NULL, *p1 = NULL, *p3 = NULL, *q1 = NULL, *f1 = NULL,
                        *s2 = NULL, *u2 = NULL, *h2 = NULL, *h4 = NULL, *h6 = NULL,
                        *r2 = NULL, *p2 = NULL, *p4 = NULL, *q2 = NULL, *f2 = NULL;
    /*!stags:re2c:uri_{suffix} format = "const unsigned char *@@ = NULL;\n"; */
    memset(out, 0, sizeof(*out));
    for (int i = 0; i < 20; ++i) out->tags[i] = -1;
#define YYPEEK()           (*r->cur)
#define YYPEEK16()         _mm_loadu_si128((const __m128i *)r->cur)
#define YYPEEK32()         _mm256_loadu_si256((const __m256i *)r->cur)
#define YYSKIP()           (++r->cur)
#define YYBACKUP()         (r->mar = r->cur)
#define YYRESTORE()        (r->cur = r->mar)
#define YYSHIFT(n)         (r->cur += (n))
#define YYSTAGP(t)         ((t) = r->cur)
#define YYSTAGN(t)         ((t) = NULL)
#define YYSHIFTSTAG(t, o)  ((t) += (o))
#define YYRESTORETAG(t)    (r->cur = (t))
#define YYLESSTHAN(n)      ((size_t)(r->lim - r->cur) < (size_t)(n))
#define YYFILL(n)          do {{ out->kind = -2; return; }} while (0)
    /*!re2c:uri_{suffix}
        re2c:vectorize:loops = 1;
        re2c:api = generic;
        re2c:api:style = functions;
        re2c:tags:negative = "NULL";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL:naked = 0;
        re2c:flags:tags = 1;
        {URI_GRAMMAR_BODY}
    */
#undef YYPEEK
#undef YYPEEK16
#undef YYPEEK32
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYSHIFT
#undef YYSTAGP
#undef YYSTAGN
#undef YYSHIFTSTAG
#undef YYRESTORETAG
#undef YYLESSTHAN
#undef YYFILL
}}
''')
    return '\n'.join(out)


def gen_generic_free_variant(suffix):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        out.append(f'''
int lex_{gname}_{suffix}(Rec *r) {{
    /*!re2c
        re2c:vectorize:loops = 1;
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:api:sigil = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "*r->cur";
        re2c:YYPEEK16 = "_mm_loadu_si128((const __m128i *)r->cur)";
        re2c:YYPEEK32 = "_mm256_loadu_si256((const __m256i *)r->cur)";
        re2c:YYSKIP = "++r->cur;";
        re2c:YYBACKUP = "r->mar = r->cur;";
        re2c:YYRESTORE = "r->cur = r->mar;";
        re2c:YYSHIFT = "r->cur += @@;";
        re2c:YYLESSTHAN = "(size_t)(r->lim - r->cur) < (size_t)(@@)";
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        {body}
    */
}}
''')
    out.append(rf'''
void lex_uri_{suffix}(Rec *r, UriResult *out) {{
    const unsigned char *start = r->cur;
    const unsigned char *s1 = NULL, *u1 = NULL, *h1 = NULL, *h3 = NULL, *h5 = NULL,
                        *r1 = NULL, *p1 = NULL, *p3 = NULL, *q1 = NULL, *f1 = NULL,
                        *s2 = NULL, *u2 = NULL, *h2 = NULL, *h4 = NULL, *h6 = NULL,
                        *r2 = NULL, *p2 = NULL, *p4 = NULL, *q2 = NULL, *f2 = NULL;
    /*!stags:re2c:uri_{suffix} format = "const unsigned char *@@ = NULL;\n"; */
    memset(out, 0, sizeof(*out));
    for (int i = 0; i < 20; ++i) out->tags[i] = -1;
    /*!re2c:uri_{suffix}
        re2c:vectorize:loops = 1;
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:api:sigil = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "*r->cur";
        re2c:YYPEEK16 = "_mm_loadu_si128((const __m128i *)r->cur)";
        re2c:YYPEEK32 = "_mm256_loadu_si256((const __m256i *)r->cur)";
        re2c:YYSKIP = "++r->cur;";
        re2c:YYBACKUP = "r->mar = r->cur;";
        re2c:YYRESTORE = "r->cur = r->mar;";
        re2c:YYSHIFT = "r->cur += @@;";
        re2c:YYSTAGP = "@@ = r->cur;";
        re2c:YYSTAGN = "@@ = NULL;";
        re2c:YYSHIFTSTAG = "@@{{tag}} += @@{{offset}};";
        re2c:YYRESTORETAG = "r->cur = @@;";
        re2c:YYLESSTHAN = "(size_t)(r->lim - r->cur) < (size_t)(@@)";
        re2c:YYFILL = "{{ out->kind = -2; return; }}";
        re2c:YYFILL:naked = 1;
        re2c:flags:tags = 1;
        {URI_GRAMMAR_BODY}
    */
}}
''')
    return '\n'.join(out)


def gen_rec_func_variant(suffix):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        out.append(f'''
/*!re2c
    re2c:vectorize:loops = 1;
    re2c:api:style = free-form;
    re2c:define:YYFN = ["lex_{gname}_{suffix};int", "r;Rec*"];
    re2c:YYCTYPE = "unsigned char";
    re2c:YYCURSOR = "r->cur";
    re2c:YYLIMIT = "r->lim";
    re2c:YYMARKER = "r->mar";
    re2c:YYFILL = "return -2;";
    re2c:YYFILL:naked = 1;
    {body}
*/
''')
    return '\n'.join(out)


def gen_storable_variant(suffix, use_getstate=False):
    rules = make_grammar_rules()
    out = ['#include "common.h"\n']
    for gname, body in rules.items():
        getstate_dir = f'/*!getstate:re2c:{gname}_{suffix}*/\n' if use_getstate else ''
        block_tag = f':{gname}_{suffix}' if use_getstate else ''
        out.append(f'''
int lex_{gname}_{suffix}(Rec *r) {{
    {getstate_dir}/*!re2c{block_tag}
        re2c:vectorize:loops = 1;
        re2c:api = record;
        re2c:yyrecord = r;
        re2c:YYCTYPE = "unsigned char";
        re2c:yych = "r->yych";
        re2c:yych:emit = 0;
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        {body}
    */
}}
''')
    return '\n'.join(out)


HARNESS_C = r'''#include "common.h"

size_t g_vec_loads = 0;

#define DECL_GRAMMARS(sfx) \
    int lex_g1_##sfx(Rec *r); \
    int lex_g2_##sfx(Rec *r); \
    int lex_g3_##sfx(Rec *r); \
    int lex_g4_##sfx(Rec *r); \
    int lex_g5_##sfx(Rec *r);

DECL_GRAMMARS(scalar)
DECL_GRAMMARS(goto_simple)
DECL_GRAMMARS(goto_record)
DECL_GRAMMARS(goto_generic_fn)
DECL_GRAMMARS(goto_generic_free)
DECL_GRAMMARS(loop_switch)
DECL_GRAMMARS(rec_func)
DECL_GRAMMARS(eager_skip)
DECL_GRAMMARS(storable_goto)
DECL_GRAMMARS(storable_loop_switch)

void lex_uri_scalar(Rec *r, UriResult *out);
void lex_uri_goto_simple(Rec *r, UriResult *out);
void lex_uri_goto_record(Rec *r, UriResult *out);
void lex_uri_goto_generic_fn(Rec *r, UriResult *out);
void lex_uri_goto_generic_free(Rec *r, UriResult *out);
void lex_uri_loop_switch(Rec *r, UriResult *out);
void lex_uri_eager_skip(Rec *r, UriResult *out);

typedef int (*lex_fn_t)(Rec *r);
typedef void (*uri_fn_t)(Rec *r, UriResult *out);

static inline Rec make_rec(const unsigned char *cur, const unsigned char *lim) {
    Rec r;
    r.cur = cur;
    r.lim = lim;
    r.mar = cur;
    r.tok = cur;
    r.yych = 0;
    r.yyaccept = 0;
    r.yystate = -1;
    return r;
}

static uint64_t rng_state = 0x853c49e6748fea9bULL;

static uint32_t xorshift32(void) {
    uint64_t x = rng_state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    rng_state = x;
    return (uint32_t)((x * 0x2545F4914F6CDD1DULL) >> 32);
}

static void check_tokens_oneshot(
    const char *gname,
    lex_fn_t scalar_fn,
    const char *vname,
    lex_fn_t vec_fn,
    const unsigned char *data,
    size_t len
) {
    unsigned char *buf_s = (unsigned char *)malloc(len + 1);
    unsigned char *buf_v = (unsigned char *)malloc(len + 1);
    assert(buf_s && buf_v);
    memcpy(buf_s, data, len);
    buf_s[len] = 0;
    memcpy(buf_v, data, len);
    buf_v[len] = 0;

    Rec rs = make_rec(buf_s, buf_s + len + 1);
    Rec rv = make_rec(buf_v, buf_v + len + 1);

    for (size_t step = 0;; ++step) {
        const unsigned char *s_start = rs.cur;
        const unsigned char *v_start = rv.cur;
        int ks = scalar_fn(&rs);
        int kv = vec_fn(&rv);
        int ls = (int)(rs.cur - s_start);
        int lv = (int)(rv.cur - v_start);
        if (ks != kv || ls != lv) {
            fprintf(stderr, "MISMATCH [%s / %s] len=%zu step=%zu: scalar=(%d,%d) vec=(%d,%d)\n",
                    gname, vname, len, step, ks, ls, kv, lv);
            abort();
        }
        if (ks <= 0 || (size_t)(rs.cur - buf_s) > len) {
            break;
        }
    }

    free(buf_s);
    free(buf_v);
}

static void check_tokens_chunked(
    const char *gname,
    lex_fn_t scalar_fn,
    const char *vname,
    lex_fn_t storable_fn,
    const unsigned char *data,
    size_t len,
    size_t chunk_size,
    unsigned char *buf_s,
    unsigned char *buf_v
) {
    memcpy(buf_s, data, len);
    memset(buf_s + len, 0, MAX_PAD);
    Rec rs = make_rec(buf_s, buf_s + len + MAX_PAD);

    size_t cap = len + MAX_PAD + 64;
    size_t src_pos = 0;
    int eof = 0;
    size_t init_n = chunk_size < len ? chunk_size : len;
    memcpy(buf_v, data, init_n);
    src_pos = init_n;
    Rec rv = make_rec(buf_v, buf_v + init_n);
    if (src_pos == len) {
        memset((unsigned char *)rv.lim, 0, MAX_PAD);
        rv.lim += MAX_PAD;
        eof = 1;
    }

    for (size_t step = 0;; ++step) {
        const unsigned char *s_start = rs.cur;
        int ks = scalar_fn(&rs);
        int ls = (int)(rs.cur - s_start);

        rv.tok = rv.cur;
        int kv;
        for (;;) {
            kv = storable_fn(&rv);
            if (kv != -2) break;
            if (eof) {
                fprintf(stderr, "UNEXPECTED YYFILL at EOF [%s / %s] len=%zu chunk=%zu\n",
                        gname, vname, len, chunk_size);
                abort();
            }
            size_t shift = (size_t)(rv.tok - buf_v);
            size_t rem = (size_t)(rv.lim - rv.tok);
            if (shift > 0) {
                memmove(buf_v, rv.tok, rem);
                rv.cur -= shift;
                rv.mar = (rv.mar && rv.mar >= rv.tok) ? (rv.mar - shift) : buf_v;
                rv.lim -= shift;
                rv.tok -= shift;
            }
            size_t avail = len - src_pos;
            size_t add = chunk_size < avail ? chunk_size : avail;
            assert((size_t)(rv.lim - buf_v) + add + MAX_PAD <= cap);
            memcpy((unsigned char *)rv.lim, data + src_pos, add);
            rv.lim += add;
            src_pos += add;
            if (src_pos == len) {
                memset((unsigned char *)rv.lim, 0, MAX_PAD);
                rv.lim += MAX_PAD;
                eof = 1;
            }
        }
        int lv = (int)(rv.cur - rv.tok);
        if (ks != kv || ls != lv) {
            fprintf(stderr, "STORABLE MISMATCH [%s / %s] len=%zu chunk=%zu step=%zu: scalar=(%d,%d) vec=(%d,%d)\n",
                    gname, vname, len, chunk_size, step, ks, ls, kv, lv);
            abort();
        }
        if (ks <= 0 || (size_t)(rs.cur - buf_s) > len) {
            break;
        }
    }
}

static void check_all_grammars(
    const unsigned char *data,
    size_t len,
    unsigned char *buf1,
    unsigned char *buf2,
    size_t chunk_size
) {
    struct {
        const char *name;
        lex_fn_t scalar;
        lex_fn_t variants[7];
        lex_fn_t storables[2];
    } table[5] = {
        {"g1", lex_g1_scalar,
         {lex_g1_goto_simple, lex_g1_goto_record, lex_g1_goto_generic_fn,
          lex_g1_goto_generic_free, lex_g1_loop_switch, lex_g1_rec_func, lex_g1_eager_skip},
         {lex_g1_storable_goto, lex_g1_storable_loop_switch}},
        {"g2", lex_g2_scalar,
         {lex_g2_goto_simple, lex_g2_goto_record, lex_g2_goto_generic_fn,
          lex_g2_goto_generic_free, lex_g2_loop_switch, lex_g2_rec_func, lex_g2_eager_skip},
         {lex_g2_storable_goto, lex_g2_storable_loop_switch}},
        {"g3", lex_g3_scalar,
         {lex_g3_goto_simple, lex_g3_goto_record, lex_g3_goto_generic_fn,
          lex_g3_goto_generic_free, lex_g3_loop_switch, lex_g3_rec_func, lex_g3_eager_skip},
         {lex_g3_storable_goto, lex_g3_storable_loop_switch}},
        {"g4", lex_g4_scalar,
         {lex_g4_goto_simple, lex_g4_goto_record, lex_g4_goto_generic_fn,
          lex_g4_goto_generic_free, lex_g4_loop_switch, lex_g4_rec_func, lex_g4_eager_skip},
         {lex_g4_storable_goto, lex_g4_storable_loop_switch}},
        {"g5", lex_g5_scalar,
         {lex_g5_goto_simple, lex_g5_goto_record, lex_g5_goto_generic_fn,
          lex_g5_goto_generic_free, lex_g5_loop_switch, lex_g5_rec_func, lex_g5_eager_skip},
         {lex_g5_storable_goto, lex_g5_storable_loop_switch}},
    };
    const char *vnames[7] = {
        "goto_simple", "goto_record", "goto_generic_fn",
        "goto_generic_free", "loop_switch", "rec_func", "eager_skip"
    };
    const char *snames[2] = {"storable_goto", "storable_loop_switch"};

    for (int g = 0; g < 5; ++g) {
        for (int v = 0; v < 7; ++v) {
            check_tokens_oneshot(table[g].name, table[g].scalar, vnames[v], table[g].variants[v], data, len);
        }
        if (chunk_size > 0) {
            for (int s = 0; s < 2; ++s) {
                check_tokens_chunked(table[g].name, table[g].scalar, snames[s], table[g].storables[s],
                                     data, len, chunk_size, buf1, buf2);
            }
        }
    }
}

static void check_uri_parity(const unsigned char *data, size_t len, unsigned char *buf, int check_loads) {
    memcpy(buf, data, len);
    memset(buf + len, 0, MAX_PAD);

    uri_fn_t vfns[6] = {
        lex_uri_goto_simple,
        lex_uri_goto_record,
        lex_uri_goto_generic_fn,
        lex_uri_goto_generic_free,
        lex_uri_loop_switch,
        lex_uri_eager_skip
    };
    const char *vnames[6] = {
        "uri_goto_simple", "uri_goto_record", "uri_goto_generic_fn",
        "uri_goto_generic_free", "uri_loop_switch", "uri_eager_skip"
    };

    for (int v = 0; v < 6; ++v) {
        size_t before = g_vec_loads;
        Rec rs = make_rec(buf, buf + len + MAX_PAD);
        Rec rv = make_rec(buf, buf + len + MAX_PAD);
        for (;;) {
            UriResult os, ov;
            lex_uri_scalar(&rs, &os);
            vfns[v](&rv, &ov);
            if (os.kind != ov.kind || os.len != ov.len || memcmp(os.tags, ov.tags, sizeof(os.tags)) != 0) {
                fprintf(stderr, "URI MISMATCH [%s] kind=(%d,%d) len=(%d,%d)\n",
                        vnames[v], os.kind, ov.kind, os.len, ov.len);
                abort();
            }
            if (os.kind <= 0 || (size_t)(rs.cur - buf) >= len) break;
        }
        if (check_loads) {
            assert(g_vec_loads > before);
        }
    }
}

int main(void) {
    unsigned char *data = (unsigned char *)malloc(1024);
    unsigned char *buf1 = (unsigned char *)malloc(1024);
    unsigned char *buf2 = (unsigned char *)malloc(1024);
    assert(data && buf1 && buf2);

    size_t total_inputs = 0;

    // 1. Verify positive vector load count on long runs (>= 64 bytes) for every grammar and variant
    struct {
        lex_fn_t scalar;
        lex_fn_t fns[9];
        unsigned char fill_byte;
        const char *prefix;
        const char *suffix;
        int want_kind;
        int want_len;
    } load_checks[5] = {
        {lex_g1_scalar,
         {lex_g1_goto_simple, lex_g1_goto_record, lex_g1_goto_generic_fn,
          lex_g1_goto_generic_free, lex_g1_loop_switch, lex_g1_rec_func,
          lex_g1_eager_skip, lex_g1_storable_goto, lex_g1_storable_loop_switch},
         'a', "", "!", 1, 128},
        {lex_g2_scalar,
         {lex_g2_goto_simple, lex_g2_goto_record, lex_g2_goto_generic_fn,
          lex_g2_goto_generic_free, lex_g2_loop_switch, lex_g2_rec_func,
          lex_g2_eager_skip, lex_g2_storable_goto, lex_g2_storable_loop_switch},
         'x', "\"", "\"", 1, 130},
        {lex_g3_scalar,
         {lex_g3_goto_simple, lex_g3_goto_record, lex_g3_goto_generic_fn,
          lex_g3_goto_generic_free, lex_g3_loop_switch, lex_g3_rec_func,
          lex_g3_eager_skip, lex_g3_storable_goto, lex_g3_storable_loop_switch},
         ' ', "", "!", 1, 128},
        {lex_g4_scalar,
         {lex_g4_goto_simple, lex_g4_goto_record, lex_g4_goto_generic_fn,
          lex_g4_goto_generic_free, lex_g4_loop_switch, lex_g4_rec_func,
          lex_g4_eager_skip, lex_g4_storable_goto, lex_g4_storable_loop_switch},
         'c', "//", "\n", 1, 130},
        {lex_g5_scalar,
         {lex_g5_goto_simple, lex_g5_goto_record, lex_g5_goto_generic_fn,
          lex_g5_goto_generic_free, lex_g5_loop_switch, lex_g5_rec_func,
          lex_g5_eager_skip, lex_g5_storable_goto, lex_g5_storable_loop_switch},
         'a', "", "!", 1, 128},
    };
    for (int g = 0; g < 5; ++g) {
        size_t plen = strlen(load_checks[g].prefix);
        size_t slen = strlen(load_checks[g].suffix);
        memcpy(data, load_checks[g].prefix, plen);
        memset(data + plen, load_checks[g].fill_byte, 128);
        memcpy(data + plen + 128, load_checks[g].suffix, slen);
        size_t tot = plen + 128 + slen;
        data[tot] = 0;
        for (int i = 0; i < 9; ++i) {
            memcpy(buf1, data, tot + 1);
            Rec r = make_rec(buf1, buf1 + tot + 1);
            size_t before = g_vec_loads;
            int k = load_checks[g].fns[i](&r);
            assert(k == load_checks[g].want_kind && (r.cur - buf1) == load_checks[g].want_len);
            assert(g_vec_loads > before);
        }
        // Also verify vector loads occur in chunked storable-state mode when chunk_size >= 64
        for (int s = 7; s < 9; ++s) {
            for (size_t ch = 64; ch <= 128; ch += 64) {
                size_t before = g_vec_loads;
                check_tokens_chunked("load_check", load_checks[g].scalar, "storable",
                                     load_checks[g].fns[s], data, tot, ch, buf1, buf2);
                assert(g_vec_loads > before);
            }
        }
    }

    // 2. Boundary lengths 0..200 and every exit position in 16-byte and 32-byte blocks
    const unsigned char classes[5] = {'a', '7', ' ', '\t', 0x90};
    const size_t chunks[7] = {15, 16, 17, 31, 32, 33, 64};
    for (int c = 0; c < 5; ++c) {
        for (size_t n = 0; n <= 200; ++n) {
            memset(data, classes[c], n);
            data[n] = '!';
            data[n + 1] = 0;
            check_all_grammars(data, n + 1, buf1, buf2, chunks[n % 7]);
            ++total_inputs;
        }
    }
    for (size_t n = 0; n <= 200; ++n) {
        data[0] = '"';
        memset(data + 1, 'x', n);
        data[n + 1] = '"';
        data[n + 2] = 0;
        check_all_grammars(data, n + 2, buf1, buf2, chunks[n % 7]);

        data[0] = '/';
        data[1] = '/';
        memset(data + 2, 'c', n);
        data[n + 2] = '\n';
        data[n + 3] = 0;
        check_all_grammars(data, n + 3, buf1, buf2, chunks[(n + 1) % 7]);
        total_inputs += 2;
    }

    // 3. 10,000 deterministic PRNG inputs (lengths 0..500) per width
    const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        "_ \t\r\n\"\\/:@.-~%!$&'()*+,;=?#[]";
    const size_t alpha_len = sizeof(alphabet) - 1;

    for (size_t iter = 0; iter < 10000; ++iter) {
        size_t len = xorshift32() % 501;
        size_t pos = 0;
        while (pos < len) {
            uint32_t mode = xorshift32() % 8;
            size_t run = 1 + (xorshift32() % 96);
            if (pos + run > len) run = len - pos;
            if (mode == 0) {
                for (size_t j = 0; j < run; ++j) data[pos++] = 'a' + (xorshift32() % 26);
            } else if (mode == 1) {
                data[pos++] = '"';
                for (size_t j = 1; j + 1 < run && pos + 1 < len; ++j) {
                    data[pos++] = 'a' + (xorshift32() % 26);
                }
                if (pos < len) data[pos++] = '"';
            } else if (mode == 2) {
                for (size_t j = 0; j < run; ++j) data[pos++] = (xorshift32() & 1) ? ' ' : '\t';
            } else if (mode == 3) {
                if (pos + 2 <= len) {
                    data[pos++] = '/';
                    data[pos++] = '/';
                    for (size_t j = 2; j < run && pos < len; ++j) data[pos++] = 'x';
                    if (pos < len) data[pos++] = '\n';
                } else {
                    data[pos++] = '/';
                }
            } else if (mode == 4) {
                for (size_t j = 0; j < run; ++j) data[pos++] = '0' + (xorshift32() % 10);
            } else if (mode == 5) {
                for (size_t j = 0; j < run; ++j) data[pos++] = (unsigned char)(0x80 + (xorshift32() % 128));
            } else {
                for (size_t j = 0; j < run; ++j) data[pos++] = (unsigned char)alphabet[xorshift32() % alpha_len];
            }
        }
        data[len] = 0;
        size_t chunk = (iter % 10 == 0) ? (15 + (iter % 53)) : 0;
        check_all_grammars(data, len, buf1, buf2, chunk);
        ++total_inputs;
    }

    // 4. URI RFC 3986 grammar parity with tags
    const char *schemes[3] = {"http", "https", "custom+scheme.v1-test"};
    for (size_t n = 1; n <= 160; ++n) {
        const char *sc = schemes[n % 3];
        size_t pos = 0;
        size_t sclen = strlen(sc);
        memcpy(data + pos, sc, sclen); pos += sclen;
        memcpy(data + pos, "://", 3); pos += 3;
        for (size_t j = 0; j < (n % 50) + 1; ++j) data[pos++] = 'u';
        data[pos++] = '@';
        for (size_t j = 0; j < n; ++j) data[pos++] = 'h';
        memcpy(data + pos, ":8080/", 6); pos += 6;
        for (size_t j = 0; j < n; ++j) data[pos++] = (j % 17 == 0) ? '/' : 'p';
        data[pos++] = '?';
        for (size_t j = 0; j < n; ++j) data[pos++] = 'q';
        data[pos++] = '#';
        for (size_t j = 0; j < n; ++j) data[pos++] = 'f';
        data[pos++] = '\n';
        data[pos] = 0;
        check_uri_parity(data, pos, buf1, n >= 40);
        ++total_inputs;
    }

    printf("OK: %zu inputs verified, g_vec_loads=%zu\n", total_inputs, g_vec_loads);
    free(data);
    free(buf1);
    free(buf2);
    return 0;
}
'''


GO_REC_PROBE = r'''package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
	"strings"
)

type Input struct {
	data []byte
	cur  int
	lim  int
	mar  int
}

/*!re2c
	re2c:vectorize:loops = 1;
	re2c:api = simple;
	re2c:api:style = free-form;
	re2c:define:YYFN = ["lexRec;int", "in;*Input"];
	re2c:YYCTYPE = byte;
	re2c:YYINPUT = "in.data";
	re2c:YYCURSOR = "in.cur";
	re2c:YYLIMIT = "in.lim";
	re2c:YYMARKER = "in.mar";
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-zA-Z_][a-zA-Z0-9_]* { return 1 }
	[ \t\r\n]+             { return 2 }
	"\x00"                 { return 0 }
	*                      { return -1 }
*/

func main() {
	for n := 0; n <= 160; n++ {
		raw := []byte(strings.Repeat("x", n) + "!" + strings.Repeat("\x00", 64))
		in := &Input{data: raw, cur: 0, lim: len(raw)}
		got := lexRec(in)
		wantKind, wantCur := 1, n
		if n == 0 {
			wantKind, wantCur = -1, 1
		}
		if got != wantKind || in.cur != wantCur {
			panic(fmt.Sprintf("n=%d: got=(%d,%d) want=(%d,%d)", n, got, in.cur, wantKind, wantCur))
		}
	}
	fmt.Println("OK: Go recursive-functions")
}
'''


def verify_generated_c_invariants(gen_code: str, name: str, vec_size: int, is_generic: bool):
    load_fn = '_mm256_loadu_si256' if vec_size == 32 else '_mm_loadu_si128'
    cmpgt_fn = '_mm256_cmpgt_epi8' if vec_size == 32 else '_mm_cmpgt_epi8'
    peek_macro = 'YYPEEK32' if vec_size == 32 else 'YYPEEK16'

    for forbidden in ('_mm256_zeroupper', 'volatile', 'yysimdzero', '_mm256_subs_epu8', '_mm_subs_epu8'):
        if forbidden in gen_code:
            raise RuntimeError(f'forbidden token `{forbidden}` in generated {name}.c')

    if cmpgt_fn not in gen_code:
        raise RuntimeError(f'missing `{cmpgt_fn}` in generated {name}.c')

    if 'switch (' not in gen_code:
        raise RuntimeError(f'missing scalar `switch` pre-test in generated {name}.c')

    if is_generic:
        if re.search(r'\bYYCURSOR\b', gen_code):
            raise RuntimeError(f'YYCURSOR leaked in --api generic output {name}.c')
        if peek_macro not in gen_code and load_fn not in gen_code:
            raise RuntimeError(f'missing {peek_macro} / {load_fn} in generic output {name}.c')
    else:
        if load_fn not in gen_code:
            raise RuntimeError(f'missing {load_fn} in generated {name}.c')


def run_c_suite_for_width(re2c_bin: Path, directory: Path, compilers: list[str], vec_size: int):
    wdir = directory / f'c_w{vec_size}'
    wdir.mkdir(parents=True, exist_ok=True)
    (wdir / 'common.h').write_text(COMMON_HDR)
    (wdir / 'harness.c').write_text(HARNESS_C)

    vec_flags = ['--arch', 'x86', '--vectorize-size', str(vec_size), '--vectorize-loops']
    specs = [
        ('scalar', [], False, gen_simple_variant('scalar', 0)),
        ('goto_simple', vec_flags, False, gen_simple_variant('goto_simple', 1)),
        ('goto_record', vec_flags, False, gen_record_variant('goto_record')),
        ('goto_generic_fn', vec_flags + ['--api', 'generic'], True, gen_generic_fn_variant('goto_generic_fn')),
        ('goto_generic_free', vec_flags + ['--api', 'generic'], True, gen_generic_free_variant('goto_generic_free')),
        ('loop_switch', vec_flags + ['--loop-switch'], False, gen_simple_variant('loop_switch', 1)),
        ('rec_func', vec_flags + ['--recursive-functions'], False, gen_rec_func_variant('rec_func')),
        ('eager_skip', vec_flags + ['--eager-skip'], False, gen_simple_variant('eager_skip', 1)),
        ('storable_goto', vec_flags + ['-f'], False, gen_storable_variant('storable_goto', use_getstate=True)),
        ('storable_loop_switch', vec_flags + ['--loop-switch', '-f'], False, gen_storable_variant('storable_loop_switch', use_getstate=False)),
    ]

    c_files = [str(wdir / 'harness.c')]
    base_cmd = [str(re2c_bin.resolve()), '--no-generation-date', '-i']

    for name, flags, is_generic, content in specs:
        re_path = wdir / f'{name}.re'
        c_path = wdir / f'{name}.c'
        re_path.write_text(content)
        subprocess.run(base_cmd + flags + [str(re_path), '-o', str(c_path)], check=True)
        if name != 'scalar':
            verify_generated_c_invariants(c_path.read_text(), f'w{vec_size}/{name}', vec_size, is_generic)
        c_files.append(str(c_path))

    isa_flag = '-mavx2' if vec_size == 32 else '-msse2'
    for idx, cc in enumerate(compilers):
        cc_name = os.path.basename(cc)
        for mode_name, mode_flags in [
            ('O2', ['-O2', isa_flag]),
            ('asan-ubsan', ['-O1', isa_flag, '-fsanitize=address,undefined', '-fno-sanitize-recover=all']),
        ]:
            bin_path = wdir / f'parity-w{vec_size}-{idx}-{cc_name}-{mode_name}'
            compile_cmd = [cc, '-std=c11', '-Wall', '-Wextra', '-Wno-unused-label',
                           '-Wno-unused-parameter', '-I', str(wdir)] + mode_flags + c_files + ['-o', str(bin_path)]
            print(f'[C w={vec_size}] compiling with {cc} ({mode_name})...', flush=True)
            subprocess.run(compile_cmd, check=True)
            res = subprocess.run([str(bin_path)], check=True, text=True, capture_output=True)
            print(f'[C w={vec_size}] {cc} ({mode_name}): {res.stdout.strip()}', flush=True)


def run_c_standalone(re2c_bin: Path, directory: Path, compilers: list[str], root: Path):
    base_cmd = [str(re2c_bin.resolve()), '--no-generation-date', '-i']
    standalone_specs = [
        ('vectorize_loops_generic_api', ['--arch', 'x86', '--api', 'generic', '--vectorize-loops'], True),
        ('vectorize_loops_ranges_16_32', ['--arch', 'x86', '--vectorize-loops'], False),
        ('vectorize_loops_code_models', ['--arch', 'x86', '--loop-switch', '--eager-skip', '-f', '--vectorize-loops'], False),
        ('vectorize_loops_recursive_functions', ['--arch', 'x86', '--recursive-functions', '--vectorize-loops'], False),
    ]
    standalone_c_files = []
    for st_stem, st_flags, check_no_yycursor in standalone_specs:
        st_re = root / 'test/codegen/c' / f'{st_stem}.re'
        st_c = directory / f'{st_stem}.c'
        subprocess.run(base_cmd + st_flags + [str(st_re), '-o', str(st_c)], check=True)
        txt = st_c.read_text()
        if check_no_yycursor and re.search(r'\bYYCURSOR\b', txt):
            raise RuntimeError(f'YYCURSOR leaked in {st_stem}.c')
        standalone_c_files.append((st_stem, st_c))

    for idx, cc in enumerate(compilers):
        cc_name = os.path.basename(cc)
        for mode_name, mode_flags in [
            ('O2', ['-O2', '-mavx2']),
            ('asan-ubsan', ['-O1', '-mavx2', '-fsanitize=address,undefined', '-fno-sanitize-recover=all']),
        ]:
            for st_stem, st_c in standalone_c_files:
                st_bin = directory / f'{st_stem}-{idx}-{cc_name}-{mode_name}.out'
                subprocess.run([cc, '-std=c11', '-Wall', '-Wextra', '-Wno-unused-parameter'] + mode_flags + [str(st_c), '-o', str(st_bin)], check=True)
                subprocess.run([str(st_bin)], check=True)


def run_go_suite(re2c_bin: Path, directory: Path, go_bin: str, root: Path):
    env = dict(os.environ, GOEXPERIMENT='simd', GOARCH='amd64', GOOS='linux')
    env.pop('GOWORK', None)

    (directory / 'go.mod').write_text('module vecparity\n\ngo 1.27\n')
    (directory / 'go.work').write_text('go 1.27\n\nuse .\n')

    base_cmd = [str(re2c_bin.resolve()), '--no-generation-date', '-i', '--lang', 'go', '--arch', 'x86', '--vectorize-loops']

    for vec_size in (16, 32):
        size_flags = ['--vectorize-size', str(vec_size)]
        # 1. Run test/codegen/go/004_simd_models.re (--loop-switch -f + record + generic API)
        models_re = root / 'test/codegen/go/004_simd_models.re'
        models_go = directory / f'004_simd_models_w{vec_size}.go'
        subprocess.run(base_cmd + size_flags + ['--loop-switch', '-f', str(models_re), '-o', str(models_go)], check=True)
        mtxt = models_go.read_text()
        if vec_size == 16 and 'ClearAVXUpperBits' in mtxt:
            raise RuntimeError('ClearAVXUpperBits must not be emitted for Go vector width 16')
        if vec_size == 32 and 'ClearAVXUpperBits' not in mtxt:
            raise RuntimeError('ClearAVXUpperBits missing for Go vector width 32')
        res1 = subprocess.run([go_bin, 'run', str(models_go)], cwd=directory, env=env, check=True, text=True, capture_output=True)
        print(f'[Go w={vec_size}] 004_simd_models: {res1.stdout.strip()}', flush=True)

        # 2. Run recursive-functions Go probe
        rec_re = directory / f'go_rec_w{vec_size}.re'
        rec_go = directory / f'go_rec_w{vec_size}.go'
        rec_re.write_text(GO_REC_PROBE)
        subprocess.run(base_cmd + size_flags + ['--recursive-functions', str(rec_re), '-o', str(rec_go)], check=True)
        res2 = subprocess.run([go_bin, 'run', str(rec_go)], cwd=directory, env=env, check=True, text=True, capture_output=True)
        print(f'[Go w={vec_size}] recursive-functions: {res2.stdout.strip()}', flush=True)

        # 3. Run 004_simd.re differential test in Go
        simd_re = root / 'test/codegen/go/004_simd.re'
        simd_go = directory / f'004_simd_w{vec_size}.go'
        subprocess.run(base_cmd + size_flags + [str(simd_re), '-o', str(simd_go)], check=True)
        res3 = subprocess.run([go_bin, 'run', str(simd_go)], cwd=directory, env=env, check=True, text=True, capture_output=True)
        print(f'[Go w={vec_size}] 004_simd: {res3.stdout.strip()}', flush=True)

    # 4. Run 004_simd_ranges_16_32.re (256-byte signed-bias ranges & opaque generic API)
    ranges_re = root / 'test/codegen/go/004_simd_ranges_16_32.re'
    ranges_go = directory / '004_simd_ranges_16_32.go'
    subprocess.run(base_cmd + [str(ranges_re), '-o', str(ranges_go)], check=True)
    res4 = subprocess.run([go_bin, 'run', str(ranges_go)], cwd=directory, env=env, check=True, text=True, capture_output=True)
    print(f'[Go] 004_simd_ranges_16_32: {res4.stdout.strip()}', flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('re2c', type=Path)
    parser.add_argument('--cc', action='append', help='C compiler (default: gcc and clang)')
    parser.add_argument('--go', default='go', help='Go 1.27+ executable')
    parser.add_argument('--language', choices=['all', 'c', 'go'], default='all')
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()

    root = Path(__file__).resolve().parents[3]
    with tempfile.TemporaryDirectory(prefix='re2c-vec-loops-') as temporary:
        directory = (args.output_dir or Path(temporary)).resolve()
        directory.mkdir(parents=True, exist_ok=True)
        if args.language in ('all', 'c'):
            candidates = list(args.cc or []) + ['gcc', 'clang']
            compilers = []
            seen_realpaths = set()
            for c in candidates:
                resolved = shutil.which(c)
                if resolved:
                    real = os.path.realpath(resolved)
                    if real not in seen_realpaths:
                        seen_realpaths.add(real)
                        compilers.append(c)
            if not compilers:
                raise RuntimeError('no C compiler found')
            for vec_size in (16, 32):
                run_c_suite_for_width(args.re2c, directory, compilers, vec_size)
            run_c_standalone(args.re2c, directory, compilers, root)
        if args.language in ('all', 'go'):
            run_go_suite(args.re2c, directory, args.go, root)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
