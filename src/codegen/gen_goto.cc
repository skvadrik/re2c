#include <stddef.h>
#include <stdint.h>
#include <string>

#include "src/adfa/adfa.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/encoding/enc.h"

namespace re2c {

static CodeList* gen_goif(Output& output, const DFA& dfa, const CodeGoIf* go, const State* from);

static const char* gen_cond(Output& output, const CodeCmp* cond) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;
    buf.str(opts->yych).cstr(" ").str(cond->cmp).cstr(" ");
    prtChOrHex(buf.stream(),
               cond->val,
               opts->encoding.szCodeUnit(),
               opts->lang == Lang::RUST || opts->encoding.type() == Enc::Type::EBCDIC,
               opts->target == Target::DOT);
    return buf.flush();
}

static CodeList* gen_gosw(Output& output, const DFA& dfa, const CodeGoSw* go, const State* from) {
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    const char* expr = o.str(opts->yych).flush();

    CodeCases* cases = code_cases(alc);
    CodeCase* defcase = nullptr;
    for (const CodeGoCase* c = go->cases, *e = c + go->ncases; c < e; ++c) {
        CodeList* body = code_list(alc);
        gen_goto(output, dfa, body, from, c->jump);
        if (c == go->defcase) {
            defcase = code_case_default(alc, body);
        } else {
            append(cases, code_case_ranges(alc, body, c->ranges));
        }
    }
    append(cases, defcase);

    CodeList* stmts = code_list(alc);
    append(stmts, code_switch(alc, expr, cases));

    return stmts;
}

static CodeList* gen_goifb(Output& output, const DFA& dfa, const CodeGoIfB* go, const State* from) {
    code_alc_t& alc = output.allocator;
    CodeList* stmts = code_list(alc);
    const char* if_cond = gen_cond(output, go->cond);
    CodeList* if_then = gen_goif(output, dfa, go->gothen, from);
    CodeList* if_else = gen_goif(output, dfa, go->goelse, from);
    append(stmts, code_if_then_else(alc, if_cond, if_then, if_else));
    return stmts;
}

static CodeList* gen_goifl(Output& output, const DFA& dfa, const CodeGoIfL* go, const State* from) {
    code_alc_t& alc = output.allocator;
    CodeList* stmts = code_list(alc);
    for (uint32_t i = 0; i < go->nbranches; ++i) {
        const CodeGoIfL::Branch& b = go->branches[i];
        const CodeCmp* cond = b.cond;
        if (cond) {
            const char* if_cond = gen_cond(output, cond);
            CodeList* if_then = code_list(alc);
            gen_goto(output, dfa, if_then, from, b.jump);
            append(stmts, code_if_then_else(alc, if_cond, if_then, nullptr));
        } else {
            gen_goto(output, dfa, stmts, from, b.jump);
        }
    }
    return stmts;
}

static CodeList* gen_goif(Output& output, const DFA& dfa, const CodeGoIf* go, const State* from) {
    return go->kind == CodeGoIf::Kind::BINARY
           ? gen_goifb(output, dfa, go->goifb, from)
           : gen_goifl(output, dfa, go->goifl, from);
}

static CodeList* gen_goswif(
        Output& output, const DFA& dfa, const CodeGoSwIf* go, const State* from) {
    return go->kind == CodeGoSwIf::Kind::SWITCH
           ? gen_gosw(output, dfa, go->gosw, from)
           : gen_goif(output, dfa, go->goif, from);
}

static CodeList* gen_gobm(Output& output, const DFA& dfa, const CodeGoBm* go, const State* from) {
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    const char* nonzero = opts->lang == Lang::C ? "" : " != 0";

    const char* elif_cond = o.str(opts->yybm).cstr("[").u32(go->bitmap->offset).cstr("+")
            .str(opts->yych).cstr("]").cstr(" & ").yybm_char(go->bitmap->mask, opts, 1)
            .cstr(nonzero).flush();

    CodeList* if_else = code_list(alc);
    const CodeJump jump = {go->bitmap->state, TCID0, false, false, false};
    gen_goto(output, dfa, if_else, from, jump);

    CodeList* stmts = code_list(alc);
    if (go->hgo != nullptr) {
        const char* if_cond = o.str(opts->yych).cstr(" & ~0xFF").cstr(nonzero).flush();
        CodeList* if_then = gen_goswif(output, dfa, go->hgo, from);
        append(stmts, code_if_then_elif(alc, if_cond, if_then, elif_cond, if_else));
    } else {
        append(stmts, code_if_then_else(alc, elif_cond, if_else, nullptr, false));
    }
    if (go->lgo != nullptr) {
        append(stmts, gen_goswif(output, dfa, go->lgo, from));
    }

    return stmts;
}

static uint32_t label_width(uint32_t label) {
    uint32_t n = 0;
    while (label /= 10) ++n;
    return n;
}

static CodeList* gen_gocp_table(Output& output, const CodeGoCpTable* go) {
    static const size_t TABLE_WIDTH = 8;
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    uint32_t maxlabel = 0;
    for (uint32_t i = 0; i < CodeGoCpTable::TABLE_SIZE; ++i) {
        maxlabel = std::max(maxlabel, go->table[i]->label->index);
    }
    const uint32_t max_digits = label_width(maxlabel);

    CodeList* stmts = code_list(alc);

    text = o.cstr("static void *").str(opts->yytarget).cstr("[256] = {").flush();
    append(stmts, code_text(alc, text));

    CodeList* block = code_list(alc);
    for (uint32_t i = 0; i < CodeGoCpTable::TABLE_SIZE / TABLE_WIDTH; ++i) {
        for (uint32_t j = 0; j < TABLE_WIDTH; ++j) {
            const Label& l = *go->table[i * TABLE_WIDTH + j]->label;

            o.cstr("&&").str(opts->labelPrefix).label(l);
            if (j < TABLE_WIDTH - 1) {
                const std::string padding(max_digits - label_width(l.index) + 1, ' ');
                o.cstr(",").str(padding);
            } else if (i < CodeGoCpTable::TABLE_SIZE / TABLE_WIDTH - 1) {
                o.cstr(",");
            }
        }
        text = o.flush();
        append(block, code_text(alc, text));
    }
    append(stmts, code_block(alc, block, CodeBlock::Kind::INDENTED));

    append(stmts, code_stmt(alc, "}"));

    return stmts;
}

static CodeList* gen_gocp(Output& output, const DFA& dfa, const CodeGoCp* go, const State* from) {
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const char* text;

    CodeList* stmts = code_list(alc);

    CodeList* if_else = gen_gocp_table(output, go->table);
    text = o.cstr("goto *").str(opts->yytarget).cstr("[").str(opts->yych).cstr("]").flush();
    append(if_else, code_stmt(alc, text));

    if (go->hgo != nullptr) {
        text = o.str(opts->yych).cstr(" & ~0xFF").flush();
        CodeList* if_then = gen_goswif(output, dfa, go->hgo, from);
        append(stmts, code_if_then_else(alc, text, if_then, if_else, false));
    } else {
        append(stmts, code_block(alc, if_else, CodeBlock::Kind::WRAPPED));
    }

    return stmts;
}

static void gen_godot(
        Output& output, const DFA& dfa, const CodeGoSw* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const std::string& prefix = opts->tags_prefix;
    const uint32_t n = go->ncases;
    const char* text;

    if (n == 1) {
        text = o.label(*from->label).cstr(" -> ").label(*go->cases[0].jump.to->label).flush();
        append(stmts, code_text(alc, text));
    } else {
        for (const CodeGoCase* c = go->cases, *e = c + go->ncases; c < e; ++c) {
            o.label(*from->label).cstr(" -> ").label(*c->jump.to->label).cstr(" [label=\"");

            const Enc& enc = opts->encoding;
            const int64_t* ranges = c->ranges->elems;
            for (uint32_t i = 0; i < c->ranges->size; ++i) {
                printSpan(o.stream(),
                          static_cast<uint32_t>(ranges[2 * i]),
                          static_cast<uint32_t>(ranges[2 * i + 1]),
                          enc.szCodeUnit(),
                          enc.type() == Enc::Type::EBCDIC,
                          true);
            }

            const tcmd_t* cmd = dfa.tcpool[c->jump.tags];
            for (const tcmd_t* p = cmd; p; p = p->next) {
                o.cstr("<").str(vartag_name(p->lhs, prefix, dfa.mtagvers));
                if (tcmd_t::iscopy(p)) {
                    o.cstr("~").str(vartag_name(p->rhs, prefix, dfa.mtagvers));
                }
                o.cstr(">");
            }

            text = o.cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    }
}

void gen_go(Output& output, const DFA& dfa, const CodeGo* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    code_alc_t& alc = output.allocator;

    if (go->kind == CodeGo::Kind::DOT) {
        gen_godot(output, dfa, go->godot, from, stmts);
        return;
    }

    DASSERT(consume(from) || go->tags == TCID0);
    if (opts->eof == NOEOF) {
        // With the end-of-input rule $ tag operations *must* be generated before YYFILL label.
        // Without the $ rule the are no strict requirements, but generating them here (after YYFILL
        // label) allows to fuse skip and peek into one statement.
        gen_settags(output, stmts, dfa, go->tags);
    }

    if (go->skip) {
        append(stmts, code_skip(alc));
    }

    if (go->kind == CodeGo::Kind::SWITCH_IF) {
        append(stmts, gen_goswif(output, dfa, go->goswif, from));
    } else if (go->kind == CodeGo::Kind::BITMAP) {
        append(stmts, gen_gobm(output, dfa, go->gobm, from));
    } else if (go->kind == CodeGo::Kind::CPGOTO) {
        append(stmts, gen_gocp(output, dfa, go->gocp, from));
    }
}

} // namespace re2c
