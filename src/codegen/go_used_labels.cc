#include <stddef.h>
#include "src/util/c99_stdint.h"

#include "src/adfa/adfa.h"
#include "src/codegen/go.h"
#include "src/codegen/label.h"


namespace re2c {

void Cases::used_labels() const
{
    for (uint32_t i = 0; i < cases_size; ++i) {
        cases[i].to->label.used = true;
    }
}

void Binary::used_labels() const
{
    thn->used_labels();
    els->used_labels();
}

void Linear::used_labels() const
{
    for (uint32_t i = 0; i < nbranches; ++i) {
        State *to = branches[i].to;
        if (to) {
            to->label.used = true;
        }
    }
    if (def) {
        def->label.used = true;
    }
}

void If::used_labels() const
{
    switch (type) {
        case BINARY:
            info.binary->used_labels();
            break;
        case LINEAR:
            info.linear->used_labels();
            break;
    }
}

void SwitchIf::used_labels() const
{
    switch (type) {
        case SWITCH:
            info.cases->used_labels();
            break;
        case IF:
            info.ifs->used_labels();
            break;
    }
}

void GoBitmap::used_labels() const
{
    if (hgo != NULL) {
        hgo->used_labels();
    }
    if (lgo != NULL) {
        lgo->used_labels();
    }
    bitmap_state->label.used = true;
}

void CpgotoTable::used_labels() const
{
    for (uint32_t i = 0; i < TABLE_SIZE; ++i) {
        table[i]->label.used = true;
    }
}

void Cpgoto::used_labels() const
{
    if (hgo != NULL) {
        hgo->used_labels();
    }
    table->used_labels();
}

void Go::used_labels() const
{
    switch (type) {
        case EMPTY:
        case DOT:
            break;
        case SWITCH_IF:
            info.switchif->used_labels();
            break;
        case BITMAP:
            info.bitmap->used_labels();
            break;
        case CPGOTO:
            info.cpgoto->used_labels();
            break;
    }
}

} // namespace re2c
