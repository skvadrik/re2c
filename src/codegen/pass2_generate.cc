#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/helpers.h"
#include "src/codegen/output.h"
#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/opt.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/string_utils.h"

namespace re2c {

static CodeList* gen_goswif(
        Output& output, const Adfa& dfa, const CodeGoSwIf* go, const State* from);

namespace {

class GenArrayElem : public RenderCallback {
    std::ostream& os;
    const char* array;
    const char* index;

  public:
    GenArrayElem(std::ostream& os, const char* array, const char* index)
        : os(os), array(array), index(index)  {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::ARRAY: os << array; break;
            case StxVarId::INDEX: os << index; break;
            default: UNREACHABLE(); break;
        }
    }

    FORBID_COPY(GenArrayElem);
};

class GenGetAccept : public RenderCallback {
    std::ostringstream& os;
    const opt_t* opts;

  public:
    GenGetAccept(std::ostringstream& os, const opt_t* opts)
        : os(os), opts(opts) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::GETACCEPT:
            argsubst(os, opts->api_accept_get, opts->api_sigil, "var", true, opts->var_accept);
            break;
        case StxVarId::VAR:
            os << opts->var_accept;
            break;
        case StxVarId::RECORD:
            os << opts->var_record;
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    FORBID_COPY(GenGetAccept);
};

class GenGetCond : public RenderCallback {
    std::ostringstream& os;
    const opt_t* opts;

  public:
    GenGetCond(std::ostringstream& os, const opt_t* opts)
        : os(os), opts(opts) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::GETCOND: os << opts->api_cond_get; break;
            case StxVarId::VAR: os << opts->var_cond; break;
            case StxVarId::RECORD: os << opts->var_record; break;
            default: UNREACHABLE(); break;
        }
    }

    FORBID_COPY(GenGetCond);
};

class GenGetState : public RenderCallback {
    std::ostringstream& os;
    const opt_t* opts;

  public:
    GenGetState(std::ostringstream& os, const opt_t* opts)
        : os(os), opts(opts) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::GETSTATE: os << opts->api_state_get; break;
            case StxVarId::VAR: os << opts->var_state; break;
            case StxVarId::RECORD: os << opts->var_record; break;
            default: UNREACHABLE(); break;
        }
    }

    FORBID_COPY(GenGetState);
};

class GenLessThan : public RenderCallback {
    std::ostringstream& os;
    const opt_t* opts;
    size_t need;

  public:
    GenLessThan(std::ostringstream& os, const opt_t* opts, size_t need)
        : os(os), opts(opts), need(need) {}

    void render_var(StxVarId var) override {
        switch (var) {
        case StxVarId::LESSTHAN:
            argsubst(os, opts->api_less_than, opts->api_sigil, "len", true, need);
            break;
        case StxVarId::CURSOR:
            os << opts->api_cursor;
            break;
        case StxVarId::LIMIT:
            os << opts->api_limit;
            break;
        case StxVarId::NEED:
            os << need;
            break;
        case StxVarId::RECORD:
            os << opts->var_record;
            break;
        default:
            UNREACHABLE();
            break;
        }
    }

    bool eval_cond(StxLOpt opt) override {
        if (opt == StxLOpt::MANY) {
            return need > 1;
        }
        UNREACHABLE();
        return false;
    }

    FORBID_COPY(GenLessThan);
};

class GenEnumElem : public RenderCallback {
    std::ostream& os;
    const std::string& type;
    const std::string& name;

  public:
    GenEnumElem(std::ostream& os, const std::string& type, const std::string& name)
        : os(os), type(type), name(name) {}

    void render_var(StxVarId var) override {
        switch (var) {
            case StxVarId::TYPE: os << type; break;
            case StxVarId::NAME: os << name; break;
            default: UNREACHABLE(); break;
        }
    }

    FORBID_COPY(GenEnumElem);
};

} // anonymous namespace

bool endstate(const State* s) {
    // An 'end' state is a state which has no outgoing transitions on symbols. Usually 'end' states
    // are final states (not all final states are 'end' states), but sometimes it be initial
    // non-accepting state, e.g. in case of rule '[]'.
    DCHECK(s->go.span_count > 0);
    Action::Kind a = s->go.span[0].to->action.kind;
    return s->go.span_count == 1 && (a == Action::Kind::RULE || a == Action::Kind::ACCEPT);
}

static const char* gen_fill_label(Output& output, uint32_t index) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& o = output.scratchbuf;
    DCHECK(o.empty());
    return o.str(opts->label_fill).u32(index).flush();
}

static bool omit_peek(const State* s) {
    // Do not generate YYPEEK statement in case `yych` is overwritten before it is used. This may
    // happen if this is a "move" state (which doesn't have its own YYPEEK and relies on the
    // previous value of `yych`), or if this state has a single transition that goes to a non-"move"
    // state (a single transition does not require matching on `yych`). Such states are added by
    // the tunneling optimisation which attempts to compress DFA by factoring out common parts of
    // similar states.
    return s->action.kind == Action::Kind::MOVE
            || (s->go.span_count == 1 && s->go.span[0].to->action.kind != Action::Kind::MOVE);
}

static void gen_peek(OutAllocator& alc, const State* s, CodeList* stmts) {
    if (!omit_peek(s)) append(stmts, code_peek(alc));
}

static bool need_yych_arg(const State* s) {
    // In rec/func mode `yych` should be passed as an argument only to those state-functions that
    // don't have YYPEEK (otherwise YYPEEK would immediately overwrite the argument).
    return omit_peek(s) && s->go.span_count > 1 && !endstate(s);
}

static const char* fn_name_for_cond(Scratchbuf& buf, const std::string& cond) {
    return buf.cstr("yyfn").str(cond).flush();
}

static CodeList* gen_abort(OutAllocator& alc) {
    CodeList* abort = code_list(alc);
    append(abort, code_abort(alc));
    return abort;
}

static void gen_set_tags(Output& output, CodeList* tag_actions, const Adfa& dfa, tcid_t tcid) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const tcmd_t* cmd = dfa.tcpool[tcid];

    // single tag, backwards compatibility, use context marker
    if (cmd && dfa.oldstyle_ctxmarker) {
        append(tag_actions, code_backupctx(alc));
        return;
    }

    for (const tcmd_t* p = cmd; p; p = p->next) {
        const tagver_t l = p->lhs, r = p->rhs, *h = p->history, *h0;
        bool is_mtag = dfa.mtagvers.find(l) != dfa.mtagvers.end();
        const char* le = buf.str(vartag_expr(l, opts, is_mtag)).flush();
        const char* re = buf.str(vartag_expr(r, opts, is_mtag)).flush();

        if (tcmd_t::iscopy(p)) {
            // "copy" command
            append(tag_actions, code_copy_tag(alc, le, re, is_mtag));
        } else if (tcmd_t::isadd(p)) {
            // "save" command with history
            if (l != r) {
                append(tag_actions, code_copy_tag(alc, le, re, is_mtag));
            }
            // history is reversed, so find its end and iterate back
            for (h0 = h; *h != TAGVER_ZERO; ++h);
            for (; h --> h0; ) {
                bool negative = *h == TAGVER_BOTTOM;
                append(tag_actions, code_set_tag(alc, le, true, negative));
            }
        } else {
            // "save" command
            bool negative = *h == TAGVER_BOTTOM;
            append(tag_actions, code_set_tag(alc, le, false, negative));
        }
    }
}

static const char* fintag_expr(Output& output, const char* name) {
    // Normally final tags are local variables defined by the user in the function that wraps DFA.
    // But in rec/func mode each DFA state is a separate autogenerated function, so final tags must
    // be part of the state that is passed to these functions.
    const opt_t* opts = output.block().opts;
    if (opts->code_model == CodeModel::REC_FUNC) {
        Scratchbuf& buf = output.scratchbuf;
        argsubst(buf.stream(), opts->tags_expression, opts->api_sigil, "tag", true, name);
        return buf.flush();
    } else {
        return name;
    }
}

static void gen_fintags(Output& output, CodeList* stmts, const Adfa& dfa, const Rule& rule) {
    const opt_t* opts = output.block().opts;
    const std::vector<Tag>& tags = dfa.tags;
    const tagver_t* fins = dfa.finvers;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    std::vector<const char*> fintags;

    if (rule.ncap > 0 && opts->captures_array) {
        const char* lhs = fintag_expr(output, opts->var_nmatch.c_str());
        const char* rhs = o.u64(rule.ncap).flush();
        append(stmts, code_assign(alc, lhs, rhs));
    }

    CodeList* varops = code_list(alc);
    CodeList* fixops = code_list(alc);
    CodeList* trailops = code_list(alc);
    CodeList* fixpostops = code_list(alc);
    const char* negtag = nullptr;

    for (size_t t = rule.ltag; t < rule.htag; ++t) {
        const Tag& tag = tags[t];

        // structural tag that is only needed for disambiguation
        if (fictive(tag)) continue;

        bool is_mtag = history(tag);
        bool fixed_on_cursor = fixed(tag) && tag.base == Tag::RIGHTMOST;
        int32_t dist = tag.dist == Tag::VARDIST ? 0 : static_cast<int32_t>(tag.dist);
        const char* base = fixed_on_cursor
                ? opts->api_cursor.c_str()
                : o.str(vartag_expr(fins[fixed(tag) ? tag.base : t], opts, is_mtag)).flush();

        if (trailing(tag)) {
            if (fixed_on_cursor) {
                append(trailops, code_shift(alc, dist));
            } else if (dfa.oldstyle_ctxmarker) {
                append(trailops, code_restore_ctx(alc));
            } else {
                append(trailops, code_restore_tag(alc, o.str(base).flush()));
                if (dist != 0) append(trailops, code_shift(alc, dist));
            }
            continue;
        }

        expand_fintags(output, tag, fintags);

        if (!fixed(tag)) { // variable tag
            for (const char* f : fintags) {
                append(varops, code_copy_tag(alc, f, base, is_mtag));
            }
        } else {
            DCHECK(!is_mtag);
            DCHECK(!fintags.empty());
            auto first = fintags.begin(), second = first + 1, last = fintags.end();

            if (fixed_on_cursor) {
                append(fixops, code_set_tag(alc, *first, false, false));
                if (dist != 0) append(fixops, code_shift_tag(alc, *first, nullptr, dist, false));
                for (auto i = second; i != last; ++i) {
                    append(fixops, code_copy_tag(alc, *i, *first, false));
                }
            } else if (dist == 0) {
                for (auto i = first; i != last; ++i) {
                    append(fixops, code_copy_tag(alc, *i, base, false));
                }
            } else if (tag.toplevel) {
                append(fixops, code_copy_tag(alc, *first, base, false));
                append(fixops, code_shift_tag(alc, *first, nullptr, dist, false));
                for (auto i = second; i != last; ++i) {
                    append(fixops, code_copy_tag(alc, *i, *first, false));
                }
            } else {
                // Pick one of the base tags to store negative value (with generic API we cannot
                // rely on a NULL constant). `code:yyshiftstag` or YYSHIFTSTAG will compare the tag
                // to it before shifting. These operations must go after all uses of the base tag.
                if (negtag == nullptr) negtag = base;
                append(fixops, code_copy_tag(alc, *first, base, false));
                append(fixpostops, code_shift_tag(alc, *first, negtag, dist, false));
                for (auto i = second; i != last; ++i) {
                    append(fixpostops, code_copy_tag(alc, *i, *first, false));
                }
            }
        }
    }

    // Variable tags must be set before fixed tags which depend on them. Trailing context is updated
    // after all tags, because fixed tags may depend on the rightmost position.
    append(stmts, varops);
    append(stmts, fixops);
    append(stmts, trailops);
    // With generic API it's necessary to materialize no-match value in a tag (there's no constant).
    if (opts->api == Api::GENERIC && negtag != nullptr) {
        append(stmts, code_set_tag(alc, negtag, false, true));
    }
    append(stmts, fixpostops);
}

void expand_fintags(Output& output, const Tag& tag, std::vector<const char*>& fintags) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;

    fintags.clear();
    if (trailing(tag)) {
        // empty list
    } else if (!capture(tag)) {
        // named tag
        fintags.push_back(fintag_expr(output, output.scratchbuf.str(tag.name).flush()));
    } else if (opts->captures_array) {
        // capture tag, maps to a range of parentheses, stored in the form of `yypmatch` array
        const char* yypmatch = fintag_expr(output, opts->var_pmatch.c_str());
        for (size_t i = tag.lsub; i <= tag.hsub; i += 2) {
            const char* index = buf.u64(i).flush();
            GenArrayElem callback(buf.stream(), yypmatch, index);
            fintags.push_back(opts->gen_code_array_elem(buf, callback));
        }
    } else {
        // capture tag, maps to a range of parentheses, stored in the form of variables
        for (size_t i = tag.lsub; i <= tag.hsub; i += 2) {
            fintags.push_back(fintag_expr(output, buf.str(captvar_name(i, opts)).flush()));
        }
    }
}

static void gen_continue_yyloop(Output& output, CodeList* stmts, const char* next) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    append(stmts, code_assign(alc, opts->var_state.c_str(), next));

    const char* label = opts->label_loop.empty() ? nullptr : opts->label_loop.c_str();
    append(stmts, code_continue(alc, label));
}

static CodeList* gen_fill_falllback(
        Output& output, const Adfa& dfa, const State* from, const CodeJump* jump) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    DCHECK(opts->fill_eof != NOEOF);

    tcid_t falltags;
    const State* fallback = fallback_state_with_eof_rule(dfa, opts, from, &falltags);

    if (from->go.tags != TCID0) {
        // Tags have been hoisted out of transitions into state (this means that tags on all
        // transitions coincide, including the fallback transition). Do not add duplicate tags to
        // fallback transition.
        DCHECK(from->go.tags == falltags);
        falltags = TCID0;
    }

    CodeList* fallback_trans = code_list(alc);
    if (jump && fallback == jump->to && falltags == jump->tags && !jump->skip &&
            // Fallback transition is part of an IF/THEN/ELSE statement. In rec/func mode both
            // branches must end in a tailcall, therefore elision is forbidden (unless YYFILL is
            // disabled, then the whole IF/THEN/ELSE can be replaced with a tailcall to to-state).
            !(opts->code_model == CodeModel::REC_FUNC && opts->fill_enable)) {
        // Transition can be elided, because control flow falls through to another transition
        // with the same destination state, tags and no YYSKIP.
    } else {
        // tag actions on the fallback transition
        gen_set_tags(output, fallback_trans, dfa, falltags);

        // go to fallback state
        switch (opts->code_model) {
        case CodeModel::GOTO_LABEL:
            buf.str(opts->label_prefix).label(*fallback->label);
            append(fallback_trans, code_goto(alc, buf.flush()));
            break;
        case CodeModel::LOOP_SWITCH:
            buf.label(*fallback->label);
            gen_continue_yyloop(output, fallback_trans, buf.flush());
            break;
        case CodeModel::REC_FUNC: {
            const CodeFnCommon* fn = output.block().fn_common;
            buf.str(opts->label_prefix).u32(fallback->label->index);
            append(fallback_trans, code_tailcall(alc, buf.flush(), fn->args, fn->type != nullptr));
            break;
        }}
    }
    return fallback_trans;
}

static void gen_if(
        OutAllocator& alc,
        const opt_t* opts,
        const char* cond,
        CodeList* trans1,
        CodeList* trans2,
        CodeList* code) {
    if (opts->code_model == CodeModel::REC_FUNC) {
        // In rec/func mode, generate a single IF/ELSE statement.
        // There are valid cases when ELSE is empty, e.g. YYFILL without EOF rule $.
        append(code, code_if_then_else(alc, cond, trans1, trans2));
    } else {
        // In goto/label and loop/switch modes, generte IF followed by the second transition
        // (note that it may be elided, so we don't want an ELSE branch).
        append(code, code_if_then_else(alc, cond, trans1, nullptr));
        append(code, trans2);
    }
}

CodeList* gen_goto_after_fill(
        Output& output, const Adfa& dfa, const State* from, const CodeJump* jump) {
    const opt_t* opts = output.block().opts;
    const bool eof_rule = opts->fill_eof != NOEOF;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    DCHECK(opts->fill_enable);

    // Transition to YYFILL label from the initial state dispatch or after YYFILL on transition.
    CodeList* resume = code_list(alc);
    State* s = from->fill_state;
    switch (opts->code_model) {
    case CodeModel::GOTO_LABEL:
        if (opts->storable_state || eof_rule) {
            append(resume, code_goto(alc, gen_fill_label(output, s->fill_label->index)));
        }
        break;
    case CodeModel::LOOP_SWITCH:
        o.u32(s->label->index);
        gen_continue_yyloop(output, resume, o.flush());
        break;
    case CodeModel::REC_FUNC: {
        const CodeFnCommon* fn = output.block().fn_common;
        o.str(opts->label_prefix).u32(s->label->index);
        append(resume, code_tailcall(alc, o.flush(), fn->args, fn->type != nullptr));
        break;
    }}

    if (opts->storable_state && eof_rule) {
        // With storable state and end-of-input rule $ the initial state dispatch needs to handle
        // YYFILL failure: if there is still not enough input, it must follow the fallback
        // transition for the state that triggered YYFILL. Fallback transition is inlined in the
        // state dispatch (as opposed to jumping to the corresponding DFA transition) because Go
        // backend does not support jumping in the middle of a nested block.
        CodeList* fallback_or_resume = code_list(alc);
        CodeList* fallback = gen_fill_falllback(output, dfa, from, jump);
        GenLessThan callback(o.stream(), opts, 1);
        const char* less_than = opts->gen_code_yylessthan(o, callback);
        gen_if(alc, opts, less_than, fallback, resume, fallback_or_resume);
        return fallback_or_resume;
    } else {
        return resume;
    }
}

static void gen_fill(
        Output& output,
        CodeList* stmts,
        CodeList* tail,
        const Adfa& dfa,
        const State* from,
        const CodeJump* jump) {
    const opt_t* opts = output.block().opts;
    const bool eof_rule = opts->fill_eof != NOEOF;
    const size_t need = eof_rule ? 1 : from->fill;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* fill = code_list(alc);
    if (opts->fill_enable) {
        if (opts->storable_state) {
            append(fill, code_set_state(alc, o.u32(from->fill_state->fill_label->index).flush()));
        }

        // With end-of-input rule $ there is no YYFILL argument and no parameter to replace.
        o.str(opts->api_fill);
        if (!eof_rule) {
            argsubst(o.stream(), opts->fill_param, "len", true, need);
        }
        if (opts->fill_param_enable) {
            o.cstr("(");
            if (!eof_rule) o.u64(need);
            o.cstr(")");
        }
        if (eof_rule && !opts->storable_state) {
            // End-of-input rule $ without a storable state: check YYFILL return value. If it
            // succeeds (returns zero) then go to YYFILL label and rematch.
            if (!opts->fill_naked) o.cstr(" ").cstr(output.block().binops[OP_CMP_EQ]).cstr(" 0");
            const char* call = o.flush();
            if (!opts->var_fill.empty()) {
                append(fill, opts->fill_naked ? code_text(alc, call) : code_stmt(alc, call));
                call = opts->var_fill.c_str(); // replace call with its result
            }
            CodeList* rematch = gen_goto_after_fill(output, dfa, from, jump);
            CodeList* fallback = gen_fill_falllback(output, dfa, from, jump);
            gen_if(alc, opts, call, rematch, fallback, fill);
        } else {
            // Otherwise don't check YYFILL return value: assume that it does not return on failure.
            const char* call = o.flush();
            append(fill, opts->fill_naked ? code_text(alc, call) : code_stmt(alc, call));
        }
    } else if (eof_rule && !opts->storable_state) {
        append(fill, gen_fill_falllback(output, dfa, from, jump));
    }

    if (opts->fill_check && fill->head) {
        GenLessThan callback(o.stream(), opts, need);
        const char* less_than = opts->gen_code_yylessthan(o, callback);
        gen_if(alc, opts, less_than, fill, tail, stmts);
    } else {
        append(stmts, fill);
        append(stmts, tail);
    }
}

static void gen_fill_and_label(Output& output, CodeList* stmts, const Adfa& dfa, const State* s) {
    const opt_t* opts = output.block().opts;

    if (opts->fill_enable && !endstate(s) && opts->fill_eof == NOEOF && s->fill > 0) {
        gen_fill(output, stmts, nullptr, dfa, s, nullptr);
    }

    if (opts->fill_eof != NOEOF) {
        // If the end-of-input rule $ is used, the lexer may jump to the YYFILL label to rescan the
        // current input character. Generate tag operations before the label to avoid applying them
        // multiple times in the above scenario (re-application may produce incorrect results in
        // case of non-idempotent operations).
        gen_set_tags(output, stmts, dfa, s->go.tags);
    }

    if (s->fill_label != nullptr && opts->code_model == CodeModel::GOTO_LABEL) {
        const char* flabel = gen_fill_label(output, s->fill_label->index);
        append(stmts, code_slabel(output.allocator, flabel));
    }
}

static void gen_goto(
        Output& output, const Adfa& dfa, CodeList* stmts, const State* from, const CodeJump& jump) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* transition = code_list(alc);

    gen_set_tags(output, transition, dfa, jump.tags);

    if (jump.skip) {
        append(transition, code_skip(alc));
    }

    if (!jump.elide && jump.to->label->used) {
        switch (opts->code_model) {
        case CodeModel::GOTO_LABEL:
            o.str(opts->label_prefix).label(*jump.to->label);
            append(transition, code_goto(alc, o.flush()));
            break;
        case CodeModel::LOOP_SWITCH:
            o.label(*jump.to->label);
            gen_continue_yyloop(output, transition, o.flush());
            break;
        case CodeModel::REC_FUNC: {
            const CodeFnCommon* fn = output.block().fn_common;
            CodeArgs* args = need_yych_arg(jump.to) ? fn->args_yych : fn->args;
            o.str(opts->label_prefix).u32(jump.to->label->index);
            append(transition, code_tailcall(alc, o.flush(), args, fn->type != nullptr));
            break;
        }}
    } else {
        // Goto can be elided, because control flow "falls through" to the correct DFA state. This
        // usually happens for the last statement in a sequence of "linear if" statements.
        // Elision happens even in rec/func mode due to split states (tunneling optimization).
    }

    if (jump.eof) {
        gen_fill(output, stmts, transition, dfa, from, &jump);
    } else {
        append(stmts, transition);
    }
}

static CodeList* gen_gosw(Output& output, const Adfa& dfa, const CodeGoSw* go, const State* from) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    const char* expr = o.str(opts->var_char).flush();

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

static CodeList* gen_goif(Output& output, const Adfa& dfa, const CodeGoIf* go, const State* from);

static CodeList* gen_goifb(
        Output& output, const Adfa& dfa, const CodeGoIfB* go, const State* from) {
    OutAllocator& alc = output.allocator;
    CodeList* stmts = code_list(alc);
    CodeList* if_then = gen_goif(output, dfa, go->gothen, from);
    CodeList* if_else = gen_goif(output, dfa, go->goelse, from);
    append(stmts, code_if_then_else(alc, go->cond, if_then, if_else));
    return stmts;
}

static CodeList* gen_goifl(
        Output& output, const Adfa& dfa, const CodeGoIfL* go, const State* from) {
    OutAllocator& alc = output.allocator;
    const opt_t* opts = output.block().opts;

    auto transition = [&](const CodeGoBranch* b) {
        if (b->kind == CodeGoBranch::Kind::JUMP) {
            CodeList* code = code_list(alc);
            gen_goto(output, dfa, code, from, b->jump);
            return code;
        } else {
            return gen_goswif(output, dfa, b->swif, from);
        }
    };

    CodeList* stmts = code_list(alc);
    const CodeGoBranch* b = go->branches, *e = b + go->nbranches;

    if (opts->code_model != CodeModel::REC_FUNC) {
        // In goto/label and loop/switch modes generate a sequence of IF statements.
        // It is possible to use IF/ELSE-IF.../ELSE instead, but this would prevent folding YYSKIP
        // in the last unconditional branch with the following YYPEEK, as in `yych = *++YYCURSOR`.
        for (; b != e; ++b) {
            if (b->cond) {
                append(stmts, code_if_then_else(alc, b->cond, transition(b), nullptr));
            } else {
                DCHECK(b + 1 == e); // the last one
                append(stmts, transition(b));
            }
        }
    } else {
        // In rec/func mode generate one IF/ELSE-IF.../ELSE statement.
        // In functional languages IF/ELSE is usually an expression where both branches must
        // have the same type, and early return from an IF is allowed only for void functions.
        if (go->nbranches == 1 && b->cond == nullptr) {
            gen_goto(output, dfa, stmts, from, b->jump);
        } else {
            Code* ifte = code_if_then_else(alc);
            for (; b != e; ++b) {
                append(ifte->ifte, code_branch(alc, b->cond, transition(b)));
            }
            append(stmts, ifte);
        }
    }

    return stmts;
}

static CodeList* gen_goif(Output& output, const Adfa& dfa, const CodeGoIf* go, const State* from) {
    return go->kind == CodeGoIf::Kind::BINARY
           ? gen_goifb(output, dfa, go->goifb, from)
           : gen_goifl(output, dfa, go->goifl, from);
}

static CodeList* gen_goswif(
        Output& output, const Adfa& dfa, const CodeGoSwIf* go, const State* from) {
    return go->kind == CodeGoSwIf::Kind::SWITCH
           ? gen_gosw(output, dfa, go->gosw, from)
           : gen_goif(output, dfa, go->goif, from);
}

static CodeList* gen_gocp_table(Output& output, const CodeGoCpTable* go) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    const char** elems = alc.alloct<const char*>(CodeGoCpTable::TABLE_SIZE);
    for (uint32_t i = 0; i < CodeGoCpTable::TABLE_SIZE; ++i) {
        elems[i] = buf.cstr("&&").str(opts->label_prefix).u32(go->table[i]->label->index).flush();
    }

    const char* name = opts->var_computed_gotos_table.c_str();
    const char* type = opts->gen_code_type_yytarget(buf);
    // In rec/func mode tables are reused across different fnctions, so they must be global.
    bool local = opts->code_model != CodeModel::REC_FUNC;

    CodeList* stmts = code_list(alc);
    append(stmts, code_array(
            alc, name, type, elems, CodeGoCpTable::TABLE_SIZE, local, /*tabulate*/ true));
    return stmts;
}

static CodeList* gen_gocp(Output& output, const Adfa& dfa, const CodeGoCp* go, const State* from) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    CodeList* stmts = code_list(alc);

    CodeList* if_else = gen_gocp_table(output, go->table);
    buf.cstr("*").str(opts->var_computed_gotos_table).cstr("[").str(opts->var_char).cstr("]");
    append(if_else, code_goto(alc, buf.flush()));

    if (go->hgo != nullptr) {
        const char* cond =
                buf.str(opts->var_char).cstr(" & ~0xFF").flush();
        CodeList* if_then = gen_goswif(output, dfa, go->hgo, from);
        append(stmts, code_if_then_else(alc, cond, if_then, if_else));
    } else {
        append(stmts, code_block(alc, if_else, CodeBlock::Kind::WRAPPED));
    }

    return stmts;
}

static void gen_godot(
        Output& output, const Adfa& dfa, const CodeGoSw* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;
    const uint32_t n = go->ncases;
    const char* text;

    if (n == 1) {
        text = o.label(*from->label).cstr(" -> ").label(*go->cases[0].jump.to->label).flush();
        append(stmts, code_text(alc, text));
    } else {
        for (const CodeGoCase* c = go->cases, *e = c + go->ncases; c < e; ++c) {
            o.label(*from->label).cstr(" -> ").label(*c->jump.to->label).cstr(" [label=\"");

            const int64_t* ranges = c->ranges->elems;
            for (uint32_t i = 0; i < c->ranges->size; ++i) {
                print_span(o.stream(),
                           static_cast<uint32_t>(ranges[2 * i]),
                           static_cast<uint32_t>(ranges[2 * i + 1]),
                           opts);
            }

            const tcmd_t* cmd = dfa.tcpool[c->jump.tags];
            for (const tcmd_t* p = cmd; p; p = p->next) {
                bool is_mtag = dfa.mtagvers.find(p->lhs) != dfa.mtagvers.end();
                o.cstr("<").str(vartag_name(p->lhs, opts, is_mtag));
                if (tcmd_t::iscopy(p)) {
                    o.cstr("~").str(vartag_name(p->rhs, opts, is_mtag));
                }
                o.cstr(">");
            }

            text = o.cstr("\"]").flush();
            append(stmts, code_text(alc, text));
        }
    }
}

static void gen_go(Output& output, const Adfa& dfa, const CodeGo* go, const State* from, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    if (go->kind == CodeGo::Kind::DOT) {
        gen_godot(output, dfa, go->godot, from, stmts);
        return;
    }

    DCHECK(consume(from) || go->tags == TCID0);
    if (opts->fill_eof == NOEOF) {
        // With the end-of-input rule $ tag operations *must* be generated before YYFILL label.
        // Without the $ rule the are no strict requirements, but generating them here (after YYFILL
        // label) allows to fuse skip and peek into one statement.
        gen_set_tags(output, stmts, dfa, go->tags);
    }

    if (go->skip) {
        append(stmts, code_skip(alc));
    }

    if (go->kind == CodeGo::Kind::SWITCH_IF) {
        append(stmts, gen_goswif(output, dfa, go->goswif, from));
    } else if (go->kind == CodeGo::Kind::LINEAR_IF) {
        append(stmts, gen_goifl(output, dfa, go->goifl, from));
    } else if (go->kind == CodeGo::Kind::CPGOTO) {
        append(stmts, gen_gocp(output, dfa, go->gocp, from));
    }
}

static CodeList* emit_accept_binary(Output& output,
                                    const Adfa& dfa,
                                    const char* var,
                                    const uniq_vector_t<AcceptTrans>& acc,
                                    size_t l,
                                    size_t r) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    if (l < r) {
        const size_t m = (l + r) >> 1;
        const char* cmp = output.block().binops[r == l + 1 ? OP_CMP_EQ : OP_CMP_LE];
        const char* if_cond = o.cstr(var).cstr(" ").cstr(cmp).cstr(" ").u64(m).flush();
        CodeList* if_then = emit_accept_binary(output, dfa, var, acc, l, m);
        CodeList* if_else = emit_accept_binary(output, dfa, var, acc, m + 1, r);
        append(stmts, code_if_then_else(alc, if_cond, if_then, if_else));
    } else {
        const CodeJump jump = {acc[l].state, acc[l].tags, false, false, false};
        gen_goto(output, dfa, stmts, nullptr, jump);
    }
    return stmts;
}

static void emit_accept(
        Output& output, CodeList* stmts, const Adfa& dfa, const uniq_vector_t<AcceptTrans>& acc) {
    const opt_t* opts = output.block().opts;
    const size_t nacc = acc.size();
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    if (nacc == 0) return;

    append(stmts, code_restore(alc));

    GenGetAccept callback(buf.stream(), opts);
    const char* var = opts->gen_code_yygetaccept(buf, callback);

    // only one possible 'yyaccept' value: unconditional jump
    if (nacc == 1) {
        const CodeJump jump = {acc[0].state, acc[0].tags, false, false, false};
        gen_goto(output, dfa, stmts, nullptr, jump);
        return;
    }

    bool have_tags = acc.end() != std::find_if(
            acc.begin(), acc.end(), [](const AcceptTrans& a) { return a.tags != TCID0; });

    // jump table
    if (opts->computed_gotos && nacc >= opts->computed_gotos_threshold && !have_tags) {
        CodeList* block = code_list(alc);

        const char** elems = alc.alloct<const char*>(nacc);
        for (uint32_t i = 0; i < nacc; ++i) {
            buf.cstr("&&").str(opts->label_prefix).u32(acc[i].state->label->index);
            elems[i] = buf.flush();
        }
        const char* name = opts->var_computed_gotos_table.c_str();
        const char* type = opts->gen_code_type_yytarget(buf);

        // In rec/func mode the table can be local, as it's used in the same function.
        append(block, code_array(alc, name, type, elems, nacc, /*local*/ true));

        buf.cstr("*").str(opts->var_computed_gotos_table).cstr("[").cstr(var).cstr("]");
        append(block, code_goto(alc, buf.flush()));

        append(stmts, code_block(alc, block, CodeBlock::Kind::WRAPPED));
        return;
    }

    // nested ifs
    if (opts->nested_ifs || nacc == 2) {
        append(stmts, emit_accept_binary(output, dfa, var, acc, 0, nacc - 1));
        return;
    }

    // switch
    CodeCases* cases = code_cases(alc);
    for (uint32_t i = 0; i < nacc; ++i) {
        CodeList* case_body = code_list(alc);
        const CodeJump jump = {acc[i].state, acc[i].tags, false, false, false};
        gen_goto(output, dfa, case_body, nullptr, jump);
        if (i == nacc - 1) {
            append(cases, code_case_default(alc, case_body));
        } else {
            append(cases, code_case_number(alc, case_body, static_cast<int32_t>(i)));
        }
    }
    append(stmts, code_switch(alc, var, cases));
}

static const char* gen_cond_enum_elem(Scratchbuf& buf, const opt_t* opts, const std::string& name) {
    const std::string& cond = opts->cond_enum_prefix + name;
    GenEnumElem callback(buf.stream(), opts->api_cond_type, cond);
    return opts->gen_code_enum_elem(buf, callback);
}

static void emit_rule(Output& output, CodeList* stmts, const Adfa& dfa, size_t rule_idx) {
    const opt_t* opts = output.block().opts;
    const Rule& rule = dfa.rules[rule_idx];
    const SemAct* semact = rule.semact;
    OutAllocator& alc = output.allocator;
    Scratchbuf& o = output.scratchbuf;

    gen_fintags(output, stmts, dfa, rule);

    if (opts->target == Target::SKELETON) {
        emit_skeleton_action(output, stmts, dfa, rule_idx);
        return;
    }

    // Condition in the semantic action is the one set with => or :=> rule.
    const char* cond = semact->cond == nullptr ? dfa.cond.c_str() : semact->cond;
    // Next condition is either the one specified in semantic action, or the current one.
    const char* next_cond = gen_cond_enum_elem(o, opts, cond);

    if (opts->storable_state) {
        // Next state is normally -1 (the initial storable state corresponding to no YYFILL
        // invocation), but in the loop/switch and rec/func mode conditions and storable states are
        // both implemented via `yystate`, so the next state is the next condition.
        const char* next_state = (dfa.cond.empty() || opts->code_model != CodeModel::LOOP_SWITCH)
                ? "-1" : next_cond;
        // Generate YYSETSTATE in the final state. This is needed because the user may enclose the
        // lexer in an outer loop that goes via YYGETSTATE switch (it may happen if `getstate` is
        // not used, which is the case in the loop/switch mode). The user would expect the next
        // iteration of the loop to start in the initial DFA state, so YYGETSTATE should return the
        // corresponding value.
        append(stmts, code_set_state(alc, next_state));
    }

    if (cond != dfa.cond && !(opts->code_model == CodeModel::LOOP_SWITCH && opts->storable_state)) {
        // Omit YYSETCONDITION if the current condition is the same as the new one. Also omit it if
        // both storable state and conditions are used in loop/switch or func/rec mode: only one of
        // YYGETSTATE and YYGETCONDITION can be used to initialize `yystate`, and it must be
        // YYGETSTATE because the lexer may be reentered after an YYFILL invocation. Therefore we
        // use YYSETSTATE instead of YYSETCONDITION in the final states in order to match YYGETSTATE
        // in `yystate` initialization.
        append(stmts, code_set_cond(alc, next_cond));
    }

    if (!semact->autogen) {
        // User-defined semantic action.
        if (!dfa.setup.empty()) append(stmts, code_text(alc, o.str(dfa.setup).flush()));
        if (opts->line_dirs) append(stmts, code_line_info_input(alc, semact->loc));
        if (opts->indentation_sensitive) {
            for (const char* p = semact->text, *q; *p; ++p) {
                for (q = p; *p && *p != '\n'; ++p);
                append(stmts, code_text(alc, newcstr(q, p, alc)));
            }
        } else {
            append(stmts, code_text(alc, o.cstr(semact->text).flush()));
        }
        if (opts->line_dirs) append(stmts, code_line_info_output(alc));
    } else {
        // Autogenerated action for the :=> rule.
        switch (opts->code_model) {
        case CodeModel::GOTO_LABEL:
            // goto/label mode: emit `cond:goto` configuration with `cond:goto@cond` replaced by
            // the next condition label
            o.str(opts->cond_goto);
            argsubst(
                o.stream(), opts->cond_goto_param, "cond", true, opts->cond_label_prefix + cond);
            append(stmts, code_text(alc, o.flush()));
            break;
        case CodeModel::LOOP_SWITCH:
            // loop/switch mode: set `yystate` to the initial state of the next condition and
            // continue to the head of the loop.
            gen_continue_yyloop(output, stmts, next_cond);
            break;
        case CodeModel::REC_FUNC: {
            // func/rec mode: emit function call to the start of the next condition
            const CodeFnCommon* fn = output.block().fn_common;
            append(stmts, code_tailcall(
                    alc, fn_name_for_cond(o, cond), fn->args, fn->type != nullptr));
            break;
        }}
    }
}

static void emit_action(Output& output, const Adfa& dfa, const State* s, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    switch (s->action.kind) {
    case Action::Kind::MATCH:
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        gen_fill_and_label(output, stmts, dfa, s);
        gen_peek(alc, s, stmts);
        break;
    case Action::Kind::INITIAL: {
        const size_t save = s->action.info.save;
        const bool backup = save != NOSAVE;
        const bool ul1 = s->label->used;

        if (ul1 && dfa.accepts.size() > 1 && backup) {
            append(stmts, code_set_accept(alc, save));
        }
        if (ul1 && !opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_nlabel(alc, dfa.initial_label));
        gen_fill_and_label(output, stmts, dfa, s);
        if (backup) {
            append(stmts, code_backup(alc));
        }
        gen_peek(alc, s, stmts);
        if (opts->debug) {
            append(stmts, code_debug(alc, dfa.initial_label->index));
        }
        break;
    }
    case Action::Kind::SAVE:
        if (dfa.accepts.size() > 1) {
            append(stmts, code_set_accept(alc, s->action.info.save));
        }
        if (!opts->eager_skip) {
            append(stmts, code_skip(alc));
        }
        append(stmts, code_backup(alc));
        gen_fill_and_label(output, stmts, dfa, s);
        gen_peek(alc, s, stmts);
        break;
    case Action::Kind::MOVE:
        break;
    case Action::Kind::ACCEPT:
        emit_accept(output, stmts, dfa, *s->action.info.accepts);
        break;
    case Action::Kind::RULE:
        emit_rule(output, stmts, dfa, s->action.info.rule);
        break;
    }
}

static void emit_state(Output& output, const State* state, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    // If state label is unused, we should not generate it.
    // Nor can we emit an YYDEBUG statement, as there is no state number to pass to it.
    if (!state->label->used) return;

    if (opts->code_model == CodeModel::GOTO_LABEL) {
        append(stmts, code_nlabel(output.allocator, state->label));
    }
    if (opts->debug && state->action.kind != Action::Kind::INITIAL) {
        append(stmts, code_debug(alc, state->label->index));
    }
}

static void gen_storable_state_cases(Output& output, CodeCases* cases) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;

    if (!opts->storable_state || opts->code_model == CodeModel::GOTO_LABEL) return;

    // TODO: If `re2c:eof` is not used, some of these cases are redundant (they contain
    // a single transition to the DFA state that has the corresponding YYFILL invocation).
    for (const auto& i : block.fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }

    // Prepare a single range [-1, 1) covering cases `yystate = -1` and `yystate = 0`.
    int64_t* ranges = alc.alloct<int64_t>(2), *ranges_end = ranges;
    *ranges_end++ = -1;
    *ranges_end++ = 1;

    // Replace the first case 0 with a case that covers both -1 and 0.
    CodeCase* first = cases->head;
    DCHECK(first->kind == CodeCase::Kind::NUMBER && first->number == 0);
    first->kind = CodeCase::Kind::RANGES;
    first->ranges = code_ranges(alc, VarType::INT, ranges, ranges_end);
}

static OutputBlock* find_block_with_name(Output& output, const char* name) {
    for (OutputBlock* b : output.cblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    for (OutputBlock* b : output.hblocks) {
        if (b->name.compare(name) == 0) return b;
    }
    return nullptr;
}

static Ret find_blocks(
        Output& output, const BlockNameList* names, blocks_t& blocks, const char* block) {
    blocks.clear();
    for (const BlockNameList* p = names; p; p = p->next) {
        OutputBlock* b = find_block_with_name(output, p->name);
        if (b) {
            blocks.push_back(b);
        } else {
            RET_FAIL(error(
                "cannot find block named `%s` referenced by `%s` block", p->name, block));
        }
    }
    return Ret::OK;
}

static void gen_state_goto_cases(Output& output, CodeCases* cases, const OutputBlock* block) {
    OutAllocator& alc = output.allocator;
    for (const auto& i : block->fill_goto) {
        append(cases, code_case_number(alc, i.second, static_cast<int32_t>(i.first)));
    }
}

LOCAL_NODISCARD(Ret gen_state_goto(Output& output, Code* code)) {
    // Target and code model are constant options, so it doesn't matter which block they come from.
    // Block-level options should wait until we find the first block of `getstate` block.
    Target target = output.total_opts->target;
    CodeModel code_model = output.total_opts->code_model;

    if (target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    Scratchbuf& o = output.scratchbuf;
    OutAllocator& alc = output.allocator;

    // There are two possibilities:
    //
    // 1. A state switch with an explicit list of block names. This is the case of a user-defined
    //    `getstate:<name1>[:<name2>...]` block or a `use` block (use blocks have a block-local
    //    state switch that is automatically generated at the beginning of the block, and they have
    //    a special autogenerated name, as they cannot have a user-defined one).
    //
    // 2. A global state switch without a list of block names. This is the case of a user-defined
    //    `getstate` without a name list, or a global state switch that is generated automatically
    //    if the user did not specify any explicit `getstate` blocks. The global switch includes
    //    all blocks except `use` (if a block generates no code it does not contribute any cases to
    //    the state switch).
    //
    bool global = (code->fmt.block_names == nullptr);

    CodeCases* cases = code_cases(alc);
    const OutputBlock* bstart = nullptr;

    if (global) {
        // No block names are specified: generate a global switch. It includes all blocks except for
        // the `use` ones which have a local switch.
        for (const OutputBlock* b : *output.pblocks) {
            if (b->kind != InputBlock::USE) {
                gen_state_goto_cases(output, cases, b);

                // Use start label of the first non-use block that generates code.
                if (!bstart && b->start_label) bstart = b;
            }
        }
        if (!bstart || !bstart->start_label) {
            // This must be a user-defined `getstate` block: the automatic state switch is generated
            // only when processing the first block that has code.
            RET_FAIL(error("none of the blocks in `getstate` generate any code"));
        }
    } else {
        // Generate a switch for all specified named blocks.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "getstate"));
        for (const OutputBlock* b : output.tmpblocks) {
            if (!b->start_label) {
                RET_FAIL(error("block `%s` does not generate code, so it should not be listed"
                        " in `getstate` block", b->name.c_str()));
            }
            // Use start label of the first block on the list.
            if (!bstart) bstart = b;
            gen_state_goto_cases(output, cases, b);
        }
    }

    // For a global `getstate` block use options accumulated from the whole program.
    // For `getstate` with an explicit list of blocks use options of the first block
    // (this covers `use` blocks that have an autogenerated block list with a single block).
    const opt_t* opts = global ? output.total_opts : bstart->opts;

    // This is the use that makes 2nd codegen pass for labels necessary.
    Label* lstart = bstart->start_label;
    lstart->used = true;

    // We need a special case for the initial transition: start state number can be any number,
    // depending on where the start block is located in the source file, and the user should not
    // depend on this autogenerated number in order to initialize the state variable.
    CodeList* goto_start = code_list(alc);
    switch (code_model) {
    case CodeModel::GOTO_LABEL:
        // always use first block options here as this is a block-level label
        o.str(bstart->opts->label_prefix).u32(lstart->index);
        append(goto_start, code_goto(alc, o.flush()));
        break;
    case CodeModel::REC_FUNC:
        // always use first block options here as this is a block-level function
        o.str(bstart->opts->label_prefix).u32(lstart->index);
        append(goto_start, code_tailcall(
                alc, o.flush(), bstart->fn_common->args, bstart->fn_common->type != nullptr));
        break;
    case CodeModel::LOOP_SWITCH:
        // Loop/switch mode is handled differently (special cases go in the `yystate` switch).
        break;
    }

    if (opts->state_abort) {
        // case -1: goto <start label>;
        prepend(cases, code_case_number(alc, goto_start, -1));
        // default: abort
        append(cases, code_case_default(alc, gen_abort(alc)));
    } else {
        // default: goto <start label>;
        append(cases, code_case_default(alc, goto_start));
    }

    CodeList* stmts = code_list(alc);

    GenGetState callback(o.stream(), opts);
    const char* getstate = opts->gen_code_yygetstate(o, callback);
    append(stmts, code_switch(alc, getstate, cases));

    if (opts->state_next) {
        append(stmts, code_textraw(alc, o.str(opts->label_next).cstr(":").flush()));
    }

    if (code_model == CodeModel::REC_FUNC) {
        // In rec/func mode this should be a function that tail-calls state functions.
        CodeFnCommon* fn = global ? output.fn_common : bstart->fn_common;
        init_code_fndef(code, fn->name, fn->type, fn->params, stmts);
    } else {
        // In goto/label and loop/switch mode state dispatch is block of code.
        code->kind = CodeKind::BLOCK;
        code->block.kind = CodeBlock::Kind::RAW;
        code->block.stmts = stmts;
    }

    return Ret::OK;
}

LOCAL_NODISCARD(Ret gen_state_goto_implicit(Output& output, CodeList* code)) {
    OutputBlock& block = output.block();
    OutAllocator& alc = output.allocator;

    BlockNameList* block_list = nullptr;
    if (block.kind == InputBlock::USE) {
        // For a use block, always generate a local state switch. Link the block to the state
        // switch by the autogenerated block name. Note that it is impossible for the user to do so
        // with a `getstate` block, as use blocks do not have a user-defined name and cannot be
        //referenced.
        block_list = alc.alloct<BlockNameList>(1);
        block_list->name = copystr(block.name, alc);
        block_list->next = nullptr;
    } else if (!output.state_goto) {
        // For a non-use block, generate a state switch only if it wasn't generated before.
        // Null block list means that the autogenerated state switch should include all non-use
        // blocks in the file.
        output.state_goto = true;
    } else {
        // don't generate anything, there is an explicit `getstate` block
        return Ret::OK;
    }

    Code* state_goto = code_state_goto(alc, block_list);
    CHECK_RET(gen_state_goto(output, state_goto));
    append(code, state_goto);
    return Ret::OK;
}

void gen_tags(Scratchbuf& buf, const opt_t* opts, Code* code, const tagnames_t& tags) {
    DCHECK(code->kind == CodeKind::STAGS
        || code->kind == CodeKind::MTAGS
        || code->kind == CodeKind::SVARS
        || code->kind == CodeKind::MVARS);

    const char* fmt = code->fmt.format;
    const char* sep = code->fmt.separator;
    bool first = true;
    for (const std::string& tag : tags) {
        if (first) {
            first = false;
        } else if (sep != nullptr) {
            buf.cstr(sep);
        }
        if (fmt != nullptr) {
            std::ostringstream s(fmt);
            argsubst(s, opts->api_sigil, "tag", true, tag);
            buf.str(s.str());
        }
    }
    if (opts->line_dirs) {
        const std::string& s = buf.stream().str();
        if (!s.empty() && *s.rbegin() != '\n') buf.cstr("\n");
    }

    code->kind = CodeKind::RAW;
    code->raw.size = buf.stream().str().length();
    code->raw.data = buf.flush();
}

static void add_tags_from_blocks(const blocks_t& blocks, tagnames_t& tags, CodeKind kind) {
    for (OutputBlock* b : blocks) {
        switch (kind) {
            case CodeKind::STAGS: tags.insert(b->stags.begin(), b->stags.end()); break;
            case CodeKind::MTAGS: tags.insert(b->mtags.begin(), b->mtags.end()); break;
            case CodeKind::SVARS: tags.insert(b->svars.begin(), b->svars.end()); break;
            case CodeKind::MVARS: tags.insert(b->mvars.begin(), b->mvars.end()); break;
            default: UNREACHABLE(); break;
        }
    }
}

LOCAL_NODISCARD(Ret expand_tags_directive(Output& output, Code* code)) {
    DCHECK(code->kind == CodeKind::STAGS
        || code->kind == CodeKind::MTAGS
        || code->kind == CodeKind::SVARS
        || code->kind == CodeKind::MVARS);

    OutputBlock& block = output.block();
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = block.opts;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    tagnames_t tags;
    if (code->fmt.block_names == nullptr) {
        // Gather tags from all blocks in the output and header files.
        add_tags_from_blocks(output.cblocks, tags, code->kind);
        add_tags_from_blocks(output.hblocks, tags, code->kind);
    } else {
        // Gather tags from the blocks on the list.
        const char* directive = nullptr;
        switch (code->kind) {
            case CodeKind::STAGS: directive = "stags"; break;
            case CodeKind::MTAGS: directive = "mtags"; break;
            case CodeKind::SVARS: directive = "svars"; break;
            case CodeKind::MVARS: directive = "mvars"; break;
            default: UNREACHABLE(); break;
        }
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, directive));
        add_tags_from_blocks(output.tmpblocks, tags, code->kind);
    }
    gen_tags(buf, opts, code, tags);
    return Ret::OK;
}

static void gen_cond_enum(
        Scratchbuf& buf,
        OutAllocator& alc,
        Code* code,
        const opt_t* opts,
        const StartConds& conds) {
    DCHECK(opts->target == Target::CODE);

    if (conds.empty()) return;
    const StartCond* first_cond = &conds.front();

    if (code->fmt.format) {
        const char* fmt = code->fmt.format;
        const char* sep = code->fmt.separator;
        uint32_t cond_number = 0;
        for (const StartCond& cond : conds) {
            if (sep != nullptr && &cond != first_cond) {
                buf.cstr(sep);
            }
            std::ostringstream s(fmt);
            // The main substitution (the one allowing unnamed sigil) must go last, or else it will
            // erroneously substitute all the named ones.
            size_t cid = opts->code_model == CodeModel::GOTO_LABEL ? cond_number : cond.number;
            argsubst(s, opts->api_sigil, "num", false, cid);
            argsubst(s, opts->api_sigil, "cond", true, cond.name);
            buf.str(s.str());
            ++cond_number;
        }
        buf.cstr("\n");

        code->kind = CodeKind::RAW;
        code->raw.size = buf.stream().str().length();
        code->raw.data = buf.flush();
    } else {
        // prepare an array of enum member names
        const char** ids = alc.alloct<const char*>(conds.size()), **i = ids;
        for (const StartCond& cond : conds) *i++ = buf.str(cond.name).flush();
        // prepare an array of enum member numbers (only needed in loop/switch or rec/func mode)
        uint32_t* nums = nullptr;
        if (opts->code_model != CodeModel::GOTO_LABEL) {
            uint32_t* j = nums = alc.alloct<uint32_t>(conds.size());
            for (const StartCond& cond : conds) *j++ = cond.number;
        }
        // construct enum code item in place of the old code item
        init_code_enum(code, opts->api_cond_type.c_str(), conds.size(), ids, nums);
    }
}

LOCAL_NODISCARD(Ret add_condition_from_block(
        const OutputBlock& block, StartConds& conds, StartCond cond)) {
    // Condition prefix is specific to the block that defines it. If a few blocks define conditions
    // with the same name, but a different prefix, they should have different enum entries.
    cond.name = block.opts->cond_enum_prefix + cond.name;

    for (const StartCond& c : conds) {
        if (c.name == cond.name) {
            if (c.number == cond.number) {
                // A duplicate condition, it's not an error but don't add it.
                return Ret::OK;
            } else {
                // An error: conditions with idetical names but different numbers.
                RET_FAIL(error("cannot generate condition enumeration: condition `%s` has "
                               "different numbers in different blocks (use `re2c:condenumprefix` "
                               "configuration to set per-block prefix)",
                               cond.name.c_str()));
            }
        }
    }

    conds.push_back(cond);
    return Ret::OK;
}

LOCAL_NODISCARD(Ret add_conditions_from_blocks(const blocks_t& blocks, StartConds& conds)) {
    for (const OutputBlock* block : blocks) {
        for (const StartCond& cond : block->conds) {
            CHECK_RET(add_condition_from_block(*block, conds, cond));
        }
    }
    return Ret::OK;
}

LOCAL_NODISCARD(Ret expand_cond_enum(Output& output, Code* code)) {
    Scratchbuf& buf = output.scratchbuf;
    OutAllocator& alc = output.allocator;

    // Use global options accumulated across the whole file, as `conditions` may include conditions
    // from a few different blocks, and it is not clear which block's options it should inherit.
    const opt_t* globopts = output.total_opts;

    if (globopts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    StartConds conds;
    if (code->fmt.block_names == nullptr) {
        // Gather conditions from all blocks in the output and header files.
        CHECK_RET(add_conditions_from_blocks(output.cblocks, conds));
        CHECK_RET(add_conditions_from_blocks(output.hblocks, conds));
    } else {
        // Gather conditions from the blocks on the list.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, "conditions"));
        CHECK_RET(add_conditions_from_blocks(output.tmpblocks, conds));
    }

    // Do not generate empty condition enum. Some compilers or language standards allow it, but
    // generally it's more likely to indicate an error in user code.
    if (conds.empty()) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    gen_cond_enum(buf, alc, code, globopts, conds);
    return Ret::OK;
}

// note [condition order]
//
// In theory re2c makes no guarantee about the order of conditions in the generated lexer. Users
// should define condition type YYCONDTYPE and use values of this type with YYGETCONDITION and
// YYSETCONDITION. This way code is independent of internal re2c condition numbering.
//
// However, it is possible to manually hardcode condition numbers and make re2c generate condition
// dispatch without explicit use of condition names (nested `if` statements with `-b` or computed
// `goto` table with `-g`). This code is syntactically valid (compiles), but unsafe:
//     - change of re2c options may break compilation
//     - change of internal re2c condition numbering may break runtime
//
// re2c has to preserve the existing numbering scheme.
//
// re2c warns about implicit assumptions about condition order, unless:
//     - condition type is defined with `conditions` or `--header`
//     - dispatch is independent of condition order: either it uses explicit condition names or
//       there's only one condition and dispatch shrinks to unconditional jump

static CodeList* gen_cond_goto_binary(
        Output& output, const char* getcond, size_t lower, size_t upper) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    CodeList* stmts = code_list(alc);
    if (lower == upper) {
        buf.str(opts->cond_label_prefix).str(block.conds[lower].name);
        append(stmts, code_goto(alc, buf.flush()));
    } else {
        const size_t middle = lower + (upper - lower + 1) / 2;
        CodeList* if_then = gen_cond_goto_binary(output, getcond, lower, middle - 1);
        CodeList* if_else = gen_cond_goto_binary(output, getcond, middle, upper);
        const char* cond =
            buf.cstr(getcond).cstr(" ").cstr(block.binops[OP_CMP_LT]).cstr(" ").u64(middle).flush();
        append(stmts, code_if_then_else(alc, cond, if_then, if_else));
    }
    return stmts;
}

static CodeList* gen_cond_goto(Output& output) {
    OutputBlock& block = output.block();
    const opt_t* opts = block.opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const StartConds& conds = block.conds;
    bool warn_cond_ord = output.warn_condition_order;

    DCHECK(opts->code_model == CodeModel::GOTO_LABEL);
    DCHECK(opts->target != Target::DOT);

    const size_t ncond = conds.size();
    CodeList* stmts = code_list(alc);

    GenGetCond callback(buf.stream(), opts);
    const char* getcond = opts->gen_code_yygetcond(buf, callback);

    if (opts->computed_gotos) {
        buf.cstr("*").str(opts->var_cond_table).cstr("[").cstr(getcond).cstr("]");
        append(stmts, code_goto(alc, buf.flush()));
    } else if (opts->nested_ifs) {
        warn_cond_ord &= ncond > 1;
        append(stmts, gen_cond_goto_binary(output, getcond, 0, ncond - 1));
    } else {
        warn_cond_ord = false;

        CodeCases* ccases = code_cases(alc);
        for (const StartCond& cond : conds) {
            CodeList* body = code_list(alc);
            buf.str(opts->cond_label_prefix).str(cond.name);
            append(body, code_goto(alc, buf.flush()));

            append(ccases, code_case_string(alc, body,
                    gen_cond_enum_elem(buf, opts, cond.name)));
        }
        if (opts->cond_abort) {
            append(ccases, code_case_default(alc, gen_abort(alc)));
        }
        append(stmts, code_switch(alc, getcond, ccases));
    }

    // see note [condition order]
    warn_cond_ord &= opts->header_file.empty();
    if (warn_cond_ord) {
        output.msg.warn.condition_order(block.loc);
    }

    return stmts;
}
static CodeList* gen_cond_table(Output& output) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const StartConds& conds = output.block().conds;

    CodeList* code = code_list(alc);

    const char** elems = alc.alloct<const char*>(conds.size());
    for (size_t i = 0; i < conds.size(); ++i) {
        elems[i] = buf.cstr("&&").str(opts->cond_label_prefix).str(conds[i].name).flush();
    }
    const char* name = opts->var_cond_table.c_str();
    const char* type = opts->gen_code_type_yytarget(buf);

    // In rec/func mode the table can be local, as it's used in the same function.
    append(code, code_array(alc, name, type, elems, conds.size(), /*local*/ true));
    return code;
}

static Code* gen_yystate_def(Output& output) {
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = output.block().opts;

    CHECK(opts->code_model == CodeModel::LOOP_SWITCH);

    VarType type;
    const char* init;
    if (opts->storable_state) {
        // With storable state `yystate` should be initialized to YYGETSTATE. Since there is a
        // -1 case, `yystate` should have a signed type. If conditions are also used, YYGETSTATE
        // takes priority over YYGETCONDITION, because the lexer may be reentered after an YYFILL
        // invocation. In that case we use YYSETSTATE instead of YYSETCONDITION in the final states.
        type = VarType::INT;
        GenGetState callback(buf.stream(), opts);
        init = opts->gen_code_yygetstate(buf, callback);
    } else if (opts->start_conditions) {
        // Else with start conditions yystate should be initialized to YYGETCONDITION.
        type = VarType::UINT;
        GenGetCond callback(buf.stream(), opts);
        init = opts->gen_code_yygetcond(buf, callback);
    } else {
        // Else it should be the start DFA state (always case 0 with --loop-switch).
        type = VarType::UINT;
        init = "0";
    }
    return code_var(output.allocator, type, false, opts->var_state.c_str(), init);
}

static size_t max_among_blocks(const blocks_t& blocks, size_t max, CodeKind kind) {
    for (const OutputBlock* b : blocks) {
        max = std::max(max, kind == CodeKind::MAXFILL ? b->max_fill : b->max_nmatch);
    }
    return max;
}

LOCAL_NODISCARD(Ret gen_yymax(Output& output, Code* code)) {
    const opt_t* opts = output.block().opts;
    Scratchbuf& buf = output.scratchbuf;

    if (opts->target != Target::CODE) {
        code->kind = CodeKind::EMPTY;
        return Ret::OK;
    }

    CodeKind kind = code->kind;
    const char* dirname = kind == CodeKind::MAXFILL ? "max" : "maxnmatch";
    const char* varname = kind == CodeKind::MAXFILL
            ? opts->api_maxfill.c_str() : opts->api_maxnmatch.c_str();

    size_t max = 1;
    if (code->fmt.block_names == nullptr) {
        // Gather max value from all blocks in the output and header files.
        max = max_among_blocks(output.cblocks, max, kind);
        max = max_among_blocks(output.hblocks, max, kind);
    } else {
        // Maximum among the blocks listed in the directive.
        CHECK_RET(find_blocks(output, code->fmt.block_names, output.tmpblocks, dirname));
        max = max_among_blocks(output.tmpblocks, max, kind);
    }

    if (code->fmt.format) {
        buf.cstr(code->fmt.format);
        argsubst(buf.stream(), opts->api_sigil, "max", true, max);
        code->text = buf.flush();
        code->kind = CodeKind::TEXT;
    } else {
        init_code_const(code, VarType::UINT, varname, buf.u64(max).flush());
    }
    return Ret::OK;
}

std::string bitmap_name(const opt_t* opts, const std::string& cond) {
    return cond.empty()
            ? opts->var_bitmaps
            : opts->var_bitmaps + "_" + cond;
}

CodeList* gen_bitmap(Output& output, const CodeBitmap* bitmap, const std::string& cond) {
    if (!bitmap->states->head || !bitmap->used) return nullptr;

    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    const char* name = buf.str(bitmap_name(opts, cond)).flush();
    const char* type = opts->gen_code_type_yybm(buf);
    // In rec/func mode tables are reused across different fnctions, so they must be global.
    bool local = opts->code_model != CodeModel::REC_FUNC;

    CodeList* stmts = code_list(alc);
    append(stmts, code_array(
            alc, name, type, bitmap->elems, bitmap->nelems, local, /*tabulate*/ true));
    return stmts;
}

static bool gen_bitmaps(Output& output, CodeList* code) {
    OutputBlock& b = output.block();

    if (!b.opts->bitmaps) return false;

    bool have_bitmaps = false;
    for (const std::unique_ptr<Adfa>& dfa : b.dfas) {
        CodeList* bitmap = gen_bitmap(output, dfa->bitmap, dfa->cond);
        if (bitmap) {
            have_bitmaps = true;
            append(code, bitmap);
        }
    }
    return have_bitmaps;
}

void gen_dfa_as_blocks_with_labels(Output& output, const Adfa& dfa, CodeList* stmts) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    // If DFA has transitions into the initial state and --eager-skip option is not used, then the
    // initial state must have a YYSKIP statement that must be bypassed when first entering the DFA.
    // In loop/switch or func/rec mode that would be impossible, because there can be no transitions
    // to the middle of a state.
    DCHECK(opts->code_model == CodeModel::GOTO_LABEL);
    if (dfa.initial_label->used) {
        buf.str(opts->label_prefix).label(*dfa.initial_label);
        append(stmts, code_goto(alc, buf.flush()));
    }

    for (State* s = dfa.head; s; s = s->next) {
        emit_state(output, s, stmts);
        emit_action(output, dfa, s, stmts);
        gen_go(output, dfa, &s->go, s, stmts);
    }
}

void gen_dfa_as_switch_cases(Output& output, Adfa& dfa, CodeCases* cases) {
    OutAllocator& alc = output.allocator;

    DCHECK(output.block().opts->code_model != CodeModel::GOTO_LABEL);

    for (State* s = dfa.head; s; s = s->next) {
        CodeList* body = code_list(alc);

        // Emit current state.
        emit_state(output, s, body);
        emit_action(output, dfa, s, body);
        gen_go(output, dfa, &s->go, s, body);
        uint32_t label = s->label->index;
        DCHECK(label != Label::NONE);

        // As long as the following state has no incoming transitions (its label is unused),
        // generate it as a continuation of the current state. This avoids looping through the
        // `yystate` switch only to return to the next case.
        while (s->next && !s->next->label->used) {
            s = s->next;
            emit_state(output, s, body);
            emit_action(output, dfa, s, body);
            gen_go(output, dfa, &s->go, s, body);
        }

        append(cases, code_case_number(alc, body, static_cast<int32_t>(label)));
    }
}

void wrap_dfas_in_loop_switch(Output& output, CodeList* stmts, CodeCases* cases) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;

    DCHECK(opts->code_model != CodeModel::GOTO_LABEL);

    CodeList* loop = code_list(alc);
    gen_storable_state_cases(output, cases);
    if (opts->state_abort) {
        append(cases, code_case_default(alc, gen_abort(alc)));
    }
    append(loop, code_switch(alc, opts->var_state.c_str(), cases));
    append(stmts, code_loop(alc, loop));
}

static void gen_dfa_as_recursive_functions(Output& output, const Adfa& dfa, CodeList* code) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    CodeFnCommon* fn = output.block().fn_common;

    for (State* s = dfa.head; s;) {
        DCHECK(s->label->index != Label::NONE);
        const char* f = buf.str(opts->label_prefix).u32(s->label->index).flush();

        CodeParams* params = need_yych_arg(s) ? fn->params_yych : fn->params;

        // Emit this state and the following state(s) that don't have transitions into them
        // (such states may be added by the tunneling pass).
        CodeList* body = code_list(alc);
        do {
            emit_state(output, s, body);
            emit_action(output, dfa, s, body);
            gen_go(output, dfa, &s->go, s, body);
            s = s->next;
        } while (s && !s->label->used);

        append(code, code_fndef(alc, f, fn->type, params, body));
    }

    if (!dfa.cond.empty()) {
        const char* name = fn_name_for_cond(buf, dfa.cond);

        CodeList* body = code_list(alc);
        const char* f0 = buf.str(opts->label_prefix).u32(dfa.head->label->index).flush();
        append(body, code_tailcall(alc, f0, fn->args, fn->type != nullptr));

        append(code, code_fndef(alc, name, fn->type, fn->params, body));
    }
}

LOCAL_NODISCARD(Code* gen_cond_func(Output& output)) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    CodeFnCommon* fn = output.block().fn_common;

    DCHECK(opts->code_model == CodeModel::REC_FUNC);

    // emit a switch on conditions with a function call to the start state of each condition
    CodeCases* cases = code_cases(alc);
    for (const StartCond& cond : output.block().conds) {
        CodeList* body = code_list(alc);
        const char* name = fn_name_for_cond(buf, cond.name);
        append(body, code_tailcall(alc, name, fn->args, fn->type != nullptr));
        append(cases, code_case_string(alc, body, gen_cond_enum_elem(buf, opts, cond.name)));
    }
    if (opts->cond_abort) {
        append(cases, code_case_default(alc, gen_abort(alc)));
    }

    CodeList* body = code_list(alc);

    GenGetCond callback(buf.stream(), opts);
    const char* getcond = opts->gen_code_yygetcond(buf, callback);
    append(body, code_switch(alc, getcond, cases));

    const char* name = buf.str(opts->label_prefix).u32(output.block().start_label->index).flush();

    return code_fndef(alc, name, fn->type, fn->params, body);
}

LOCAL_NODISCARD(Ret gen_start_function(Output& output, const Adfa& dfa, CodeList* code)) {
    const opt_t* opts = output.block().opts;
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    CodeFnCommon* fn = output.block().fn_common;
    bool is_cond_block = !dfa.cond.empty();

    if (is_cond_block) {
        append(code, gen_cond_func(output));
    }

    if (opts->storable_state) {
        return gen_state_goto_implicit(output, code);
    } else{
        CodeList* body = code_list(alc);
        const Label* l = is_cond_block ? output.block().start_label : dfa.head->label;
        const char* name = buf.str(opts->label_prefix).u32(l->index).flush();
        append(body, code_tailcall(alc, name, fn->args, fn->type != nullptr));

        append(code, code_fndef(alc, fn->name, fn->type, fn->params, body));
        return Ret::OK;
    }
}

LOCAL_NODISCARD(Ret gen_block_code(Output& output, const Adfas& dfas, CodeList* program)) {
    OutputBlock& oblock = output.block();
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;
    const opt_t* opts = oblock.opts;

    // All conditions are named, so it suffices to check the first DFA.
    DCHECK(!dfas.empty());
    const bool is_cond_block = !dfas.front()->cond.empty();

    append(program, code_newline(alc)); // the following #line info must start at zero indent
    if (opts->line_dirs) append(program, code_line_info_output(alc));

    CodeList* code = code_list(alc);
    bool local_decls = false;

    if (!opts->storable_state && opts->char_emit && opts->code_model != CodeModel::REC_FUNC) {
        local_decls = true;
        const char* default_char = sprint_null(opts);
        append(code, code_var(alc, VarType::YYCTYPE, true, opts->var_char.c_str(), default_char));
    }

    if (!opts->storable_state && oblock.used_yyaccept && opts->code_model != CodeModel::REC_FUNC) {
        local_decls = true;
        append(code, code_var(alc, VarType::UINT, false, opts->var_accept.c_str(), "0"));
    }

    if (opts->code_model == CodeModel::GOTO_LABEL) {
        // In the goto/label mode, generate DFA states as blocks of code preceded with labels,
        // and `goto` transitions between states.
        if (opts->computed_gotos && is_cond_block) {
            local_decls = true;
            append(code, gen_cond_table(output));
        }

        local_decls |= gen_bitmaps(output, code);

        if (opts->storable_state) {
            CHECK_RET(gen_state_goto_implicit(output, code));
        }

        if (!opts->label_start.empty()) {
            // User-defined start label that should be used by user-defined code.
            append(code, code_slabel(alc, buf.str(opts->label_start).flush()));
        }

        if (oblock.start_label) {
            // Numeric start label used by the generated code (user-defined one may not exist).
            append(code, code_nlabel(alc, oblock.start_label));
        }

        if (is_cond_block) {
            append(code, gen_cond_goto(output));
        }

        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            if (is_cond_block) {
                if (opts->cond_div.length()) {
                    buf.str(opts->cond_div);
                    argsubst(buf.stream(), opts->cond_div_param, "cond", true, dfa->cond);
                    append(code, code_textraw(alc, buf.flush()));
                }
                buf.str(opts->cond_label_prefix).str(dfa->cond);
                append(code, code_slabel(alc, buf.flush()));
            }
            gen_dfa_as_blocks_with_labels(output, *dfa, code);
        }
    } else if (opts->code_model == CodeModel::LOOP_SWITCH) {
        // In the loop/switch mode append all DFA states as cases of the `yystate` switch.
        // Merge DFAs for different conditions together in one switch.
        local_decls = true;
        append(code, gen_yystate_def(output));

        local_decls |= gen_bitmaps(output, code);

        CodeCases* cases = code_cases(alc);
        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            gen_dfa_as_switch_cases(output, *dfa, cases);
        }

        wrap_dfas_in_loop_switch(output, code, cases);
    } else {
        DCHECK(opts->code_model == CodeModel::REC_FUNC);
        // In the rec/func mode DFA states are separate co-recursive functions that tail-call
        // other state functions or themselves.

        CodeList* funcs = code_list(alc);
        for (const std::unique_ptr<Adfa>& dfa : dfas) {
            gen_dfa_as_recursive_functions(output, *dfa, funcs);
        }

        CHECK_RET(gen_start_function(output, *dfas[0], funcs));

        append(code, code_recursive_functions(alc, funcs));

        gen_bitmaps(output, code); // no local declarations in rec/func mode => ignore return value
    }

    // If needed, wrap the block in braces, so that variable declarations have local scope.
    CHECK(!local_decls || opts->code_model != CodeModel::REC_FUNC);
    CodeBlock::Kind k = local_decls && opts->wrap_blocks_in_braces
            ? CodeBlock::Kind::WRAPPED
            : opts->indent_top > 0 || opts->code_model == CodeModel::REC_FUNC
                    ? CodeBlock::Kind::RAW : CodeBlock::Kind::INDENTED;
    append(program, code_block(alc, code, k));

    return Ret::OK;
}

static void gen_block_dot(Output& output, const Adfas& dfas, CodeList* code) {
    OutAllocator& alc = output.allocator;
    Scratchbuf& buf = output.scratchbuf;

    append(code, code_text(alc, "digraph re2c {"));

    for (const StartCond& cond : output.block().conds) {
        buf.cstr("0 -> ").str(cond.name).cstr(" [label=\"state=").str(cond.name).cstr("\"]");
        append(code, code_text(alc, buf.flush()));
    }

    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        if (!dfa->cond.empty()) {
            buf.str(dfa->cond).cstr(" -> ").label(*dfa->head->label);
            append(code, code_text(alc, buf.flush()));
        }

        for (State* s = dfa->head; s; s = s->next) {
            if (s->action.kind == Action::Kind::ACCEPT) {
                uint32_t i = 0;
                for (const AcceptTrans& a: *s->action.info.accepts) {
                    buf.label(*s->label).cstr(" -> ").label(*a.state->label)
                            .cstr(" [label=\"yyaccept=").u32(i).cstr("\"]");
                    append(code, code_text(alc, buf.flush()));
                    ++i;
                }
            } else if (s->action.kind == Action::Kind::RULE) {
                const SemAct* semact = dfa->rules[s->action.info.rule].semact;
                if (!semact->autogen) {
                    buf.label(*s->label).cstr(" [label=\"")
                            .str(output.msg.filenames[semact->loc.file])
                            .cstr(":").u32(semact->loc.line).cstr("\"]");
                    append(code, code_text(alc, buf.flush()));
                }
            }
            gen_go(output, *dfa, &s->go, s, code);
        }
    }

    append(code, code_text(alc, "}"));
}

static void gen_block_skeleton(Output& output, const Adfas& dfas, CodeList* code) {
    for (const std::unique_ptr<Adfa>& dfa : dfas) {
        emit_skeleton(output, code, *dfa);
    }
}

LOCAL_NODISCARD(Ret codegen_generate_block(Output& output)) {
    OutputBlock& block = output.block();
    Adfas& dfas = block.dfas;
    const opt_t* opts = block.opts;

    for (Code* code = block.code->head; code != nullptr; code = code->next) {
        switch (code->kind) {
        case CodeKind::DFAS: {
            CodeList* program = code_list(output.allocator);
            if (opts->target == Target::DOT) {
                gen_block_dot(output, dfas, program);
            } else if (opts->target == Target::SKELETON) {
                gen_block_skeleton(output, dfas, program);
            } else {
                CHECK_RET(gen_block_code(output, dfas, program));
            }
            code->kind = CodeKind::BLOCK;
            code->block.kind = CodeBlock::Kind::RAW;
            code->block.stmts = program;
            break;
        }
        case CodeKind::STATE_GOTO:
            CHECK_RET(gen_state_goto(output, code));
            break;
        case CodeKind::STAGS:
        case CodeKind::MTAGS:
        case CodeKind::SVARS:
        case CodeKind::MVARS:
            CHECK_RET(expand_tags_directive(output, code));
            break;
        case CodeKind::COND_ENUM:
            CHECK_RET(expand_cond_enum(output, code));
            break;
        case CodeKind::MAXFILL:
        case CodeKind::MAXNMATCH:
            CHECK_RET(gen_yymax(output, code));
            break;
        default:
            // skip for now, leave the rest for the render phase
            break;
        }
    }

    return Ret::OK;
}

Ret codegen_generate(Output& output) {
    for (const blocks_t& bs : {output.cblocks, output.hblocks}) {
        for (OutputBlock* b : bs) {
            output.set_current_block(b);
            CHECK_RET(codegen_generate_block(output));
            b->dfas.clear(); // DFAs are no longer used after this phase
        }
    }
    output.set_current_block(nullptr);
    return Ret::OK;
}

std::string captvar_name(size_t index, const opt_t* opts) {
    std::ostringstream os;
    // Add suffix "l" for the left parenthesis and "r" for the right one.
    os << opts->tags_prefix << (index % 2 == 0 ? "l" : "r") << index / 2;
    return os.str();
}

std::string vartag_name(tagver_t ver, const opt_t* opts, bool is_mtag) {
    std::ostringstream os;
    // S-tags and m-tags should not overlap, so m-tags have an additional "m" prefix (note that tag
    // variables in different conditions may have identical numbers).
    os << opts->tags_prefix << (is_mtag ? "m" : "") << ver;
    return os.str();
}

std::string vartag_expr(tagver_t ver, const opt_t* opts, bool is_mtag) {
    std::ostringstream os(opts->tags_expression);
    std::string name = vartag_name(ver, opts, is_mtag);
    argsubst(os, opts->api_sigil, "tag", true, name);
    return os.str();
}

} // end namespace re2c
