#include "src/parse/parse.h"


namespace re2c {

RulesBlock::RulesBlock(const std::string &name, const opt_t *opts,
    const specs_t &specs): name(name), opts(opts), specs(specs) {}

RulesBlocks::RulesBlocks(): blocks() {}

RulesBlocks::~RulesBlocks()
{
    for (size_t i = 0; i < blocks.size(); ++i) {
        delete blocks[i];
    }
}

bool RulesBlocks::empty() const { return blocks.empty(); }

void RulesBlocks::add(const std::string &name, const opt_t *opts,
    const specs_t &specs)
{
    blocks.push_back(new RulesBlock(name, opts, specs));
}

const RulesBlock *RulesBlocks::find(const std::string &name) const
{
    if (name.empty()) {
        if (!blocks.empty()) {
            return blocks.back();
        }
        error("cannot find `/*!rules:re2c ... */` block");
    } else {
        for (size_t i = 0; i < blocks.size(); ++i) {
            const RulesBlock *b = blocks[i];
            if (b->name == name) {
                return b;
            }
        }
        error("cannot find `/*!rules:re2c:%s ... */` block", name.c_str());
    }
    return NULL;
}

const opt_t *RulesBlocks::last_opts() const
{
    return blocks.empty() ? NULL : blocks.back()->opts;
}

spec_t &find_or_add_spec(specs_t &specs, const std::string &name)
{
    for (specs_t::iterator i = specs.begin(); i != specs.end(); ++i) {
        if (i->name == name) return *i;
    }
    specs.push_back(spec_t(name));
    return specs.back();
}

void use_block(context_t &context, const std::string &name)
{
    const RulesBlock *rb = context.rblocks.find(name);
    if (rb == NULL) exit(1);

    for (specs_t::const_iterator i = rb->specs.begin(); i != rb->specs.end(); ++i) {
        spec_t &spec = find_or_add_spec(context.specs, i->name);

        // Merge rules.
        spec.rules.insert(spec.rules.end(), i->rules.begin(), i->rules.end());
        spec.defs.insert(spec.defs.end(), i->defs.begin(), i->defs.end());
        spec.eofs.insert(spec.eofs.end(), i->eofs.begin(), i->eofs.end());
        spec.setup.insert(spec.setup.end(), i->setup.begin(), i->setup.end());

        // Merge configurations.
        context.opts.merge(rb->opts);
    }
}

} // namespace re2c
