#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <utility>
#include <vector>

#include "src/adfa/adfa.h"
#include "src/codegen/bitmap.h"
#include "src/codegen/emit.h"
#include "src/codegen/go.h"
#include "src/codegen/label.h"
#include "src/codegen/output.h"
#include "src/codegen/print.h"
#include "src/options/opt.h"
#include "src/dfa/tcmd.h"
#include "src/encoding/enc.h"


namespace re2c {

static void output_if (Output & o, uint32_t ind, const std::string & compare, uint32_t value);
static std::string output_hgo (Output & o, uint32_t ind, const DFA &dfa, SwitchIf * hgo, const State *from);

void output_if (Output & o, uint32_t ind, const std::string & compare, uint32_t value)
{
    o.wind(ind).ws("if (").wstring(o.block().opts->yych).ws(" ").wstring(compare).ws(" ").wc_hex (value).ws(") ");
}

std::string output_hgo (Output & o, uint32_t ind, const DFA &dfa, SwitchIf * hgo, const State *from)
{
    const opt_t *opts = o.block().opts;
    std::string yych = opts->yych;
    if (hgo != NULL)
    {
        o.wind(ind).ws("if (").wstring(yych).ws(" & ~0xFF) {\n");
        hgo->emit (o, ind + 1, dfa, from);
        o.wind(ind).ws("} else ");
        yych = opts->yych;
    }
    else
    {
        o.wind(ind);
    }
    return yych;
}

void Case::emit (Output & o, uint32_t ind) const
{
    const opt_t *opts = o.block().opts;
    for (uint32_t i = 0; i < ranges.size (); ++i)
    {
        for (uint32_t b = ranges[i].first; b < ranges[i].second; ++b)
        {
            o.wind(ind).ws("case ").wc_hex (b).ws(":");
            if (opts->dFlag && opts->encoding.type () == Enc::EBCDIC)
            {
                const uint32_t c = opts->encoding.decodeUnsafe (b);
                if (is_print (c))
                    o.ws(" /* ").wc(static_cast<char> (c)).ws(" */");
            }
            bool last_case = i == ranges.size () - 1 && b == ranges[i].second - 1;
            if (!last_case)
            {
                o.ws("\n");
            }
        }
    }
}

void Cases::emit(Output &o, uint32_t ind, const DFA &dfa, const State *from) const
{
    o.wind(ind).ws("switch (").wstring(o.block().opts->yych).ws(") {\n");

    for (uint32_t i = 1; i < cases_size; ++i) {
        const Case &c = cases[i];
        c.emit(o, ind);
        gen_goto_case(o, ind, from, c.to, dfa, c.tags, c.skip, c.eof);
    }

    // default case must be the last one
    const Case &c = cases[0];
    o.wind(ind).ws("default:");
    gen_goto_case(o, ind, from, c.to, dfa, c.tags, c.skip, c.eof);

    o.wind(ind).ws("}\n");
}

void Binary::emit(Output &o, uint32_t ind, const DFA &dfa, const State *from) const
{
    output_if(o, ind, cond->compare, cond->value);
    o.ws("{\n");
    thn->emit(o, ind + 1, dfa, from);
    o.wind(ind).ws("} else {\n");
    els->emit(o, ind + 1, dfa, from);
    o.wind(ind).ws("}\n");
}

void Linear::emit(Output &o, uint32_t ind, const DFA &dfa, const State *from) const
{
    for (uint32_t i = 0; i < nbranches; ++i) {
        const Branch &b = branches[i];
        const Cond *cond = b.cond;
        if (cond) {
            output_if(o, ind, cond->compare, cond->value);
            gen_goto_if(o, ind, from, b.to, dfa, b.tags, b.skip, b.eof);
        } else {
            gen_goto_plain(o, ind, from, b.to, dfa, b.tags, b.skip, b.eof);
        }
    }
}

void If::emit(Output &o, uint32_t ind, const DFA &dfa, const State *from) const
{
    switch (type) {
        case BINARY: info.binary->emit(o, ind, dfa, from); break;
        case LINEAR: info.linear->emit(o, ind, dfa, from); break;
    }
}

void SwitchIf::emit(Output &o, uint32_t ind, const DFA &dfa, const State *from) const
{
    switch (type) {
        case SWITCH: info.cases->emit(o, ind, dfa, from); break;
        case IF:     info.ifs->emit(o, ind, dfa, from); break;
    }
}

void GoBitmap::emit (Output & o, uint32_t ind, const DFA &dfa, const State *from) const
{
    const opt_t *opts = o.block().opts;
    std::string yych = output_hgo (o, ind, dfa, hgo, from);
    o.ws("if (").wstring(opts->yybm).ws("[").wu32(bitmap->i).ws("+").wstring(yych).ws("] & ");
    if (opts->yybmHexTable)
    {
        o.wu32_hex(bitmap->m);
    }
    else
    {
        o.wu32(bitmap->m);
    }
    o.ws(") {\n");
    gen_goto_plain(o, ind + 1, from, bitmap_state, dfa, TCID0, false, false);
    o.wind(ind).ws("}\n");
    if (lgo != NULL)
    {
        lgo->emit (o, ind, dfa, from);
    }
}

label_t CpgotoTable::max_label () const
{
    label_t max = label_t::first ();
    for (uint32_t i = 0; i < TABLE_SIZE; ++i)
    {
        if (max < table[i]->label)
        {
            max = table[i]->label;
        }
    }
    return max;
}

void CpgotoTable::emit (Output & o, uint32_t ind) const
{
    const opt_t *opts = o.block().opts;
    o.wind(ind).ws("static void *").wstring(opts->yytarget).ws("[256] = {\n");
    o.wind(++ind);
    const uint32_t max_digits = max_label ().width ();
    for (uint32_t i = 0; i < TABLE_SIZE; ++i)
    {
        o.ws("&&").wstring(opts->labelPrefix).wlabel(table[i]->label);
        if (i == TABLE_SIZE - 1)
        {
            o.ws("\n");
        }
        else if (i % 8 == 7)
        {
            o.ws(",\n").wind(ind);
        }
        else
        {
            const uint32_t padding = max_digits - table[i]->label.width () + 1;
            o.ws(",").wstring(std::string (padding, ' '));
        }
    }
    o.wind(--ind).ws("};\n");
}

void Cpgoto::emit (Output & o, uint32_t ind, const DFA &dfa, const State *from) const
{
    std::string yych = output_hgo (o, ind, dfa, hgo, from);
    o.ws("{\n");
    table->emit (o, ++ind);
    o.wind(ind).ws("goto *").wstring(o.block().opts->yytarget).ws("[").wstring(yych).ws("];\n");
    o.wind(--ind).ws("}\n");
}

void Dot::emit(Output &o, const DFA &dfa, const State *from) const
{
    const std::string &prefix = o.block().opts->tags_prefix;
    const uint32_t n = cases->cases_size;
    if (n == 1) {
        o.wlabel(from->label).ws(" -> ").wlabel(cases->cases[0].to->label).ws("\n");
    } else {
        for (uint32_t i = 0; i < n; ++i) {
            const Case &c = cases->cases[i];
            o.wlabel(from->label).ws(" -> ").wlabel(c.to->label).ws(" [label=\"");
            for (uint32_t j = 0; j < c.ranges.size(); ++j) {
                o.wrange(c.ranges[j].first, c.ranges[j].second);
            }
            const tcmd_t *cmd = dfa.tcpool[c.tags];
            for (const tcmd_t *p = cmd; p; p = p->next) {
                o.ws("<").wstring(vartag_name(p->lhs, prefix));
                if (tcmd_t::iscopy(p)) {
                    o.ws("~").wstring(vartag_name(p->rhs, prefix));
                }
                o.ws(">");
            }
            o.ws("\"]\n");
        }
    }
}

void Go::emit (Output & o, uint32_t ind, const DFA &dfa, const State *from) const
{
    if (type == DOT) {
        info.dot->emit (o, dfa, from);
        return;
    }

    const opt_t *opts = o.block().opts;
    o.wdelay_skip(ind, skip && !opts->lookahead);
    code_lines_t code;
    gen_settags(code, dfa, tags, opts, opts->stadfa /* delayed */);
    for (size_t i = 0; i < code.size(); ++i) {
        o.wind(ind).wstring(code[i]);
    }
    o.wdelay_skip(ind, skip && opts->lookahead);

    if (type == SWITCH_IF) {
        info.switchif->emit (o, ind, dfa, from);
    } else if (type == BITMAP) {
        info.bitmap->emit (o, ind, dfa, from);
    } else if (type == CPGOTO) {
        info.cpgoto->emit (o, ind, dfa, from);
    }
}

} // namespace re2c
