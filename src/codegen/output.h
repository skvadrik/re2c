#ifndef _RE2C_CODEGEN_OUTPUT_
#define _RE2C_CODEGEN_OUTPUT_

#include <stdint.h>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

#include "src/constants.h"
#include "src/codegen/code.h"
#include "src/dfa/tcmd.h"
#include "src/msg/location.h"
#include "src/options/opt.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"

namespace re2c {

// forward decls
class Msg;
struct Adfa;
struct Opt;
struct opt_t;
struct OutputBlock;
struct State;
using Adfas = std::vector<std::unique_ptr<Adfa>>;

class Scratchbuf {
    OutAllocator& alc;
    std::ostringstream os;

  public:
    explicit Scratchbuf(OutAllocator& alc): alc(alc), os() {}
    bool empty() const { return os.str().empty(); }
    std::ostringstream& stream() { return os; }
    Scratchbuf& i32(int32_t u) { os << u; return *this; }
    Scratchbuf& u32(uint32_t u) { os << u; return *this; }
    Scratchbuf& u64(uint64_t u) { os << u; return *this; }
    Scratchbuf& str(const std::string& s) { os << s; return *this; }
    Scratchbuf& cstr(const char* s) { os << s; return *this; }
    Scratchbuf& exact_uint(size_t width);
    const char* flush();

    Scratchbuf& unchecked_label(const Label& l);
    Scratchbuf& label(const Label& l);
};

using blocks_t = std::vector<OutputBlock*>;
using blocks_citer_t = blocks_t::const_iterator;
using tagnames_t = std::set<std::string>;

struct RenderContext {
    std::ostringstream os;
    const Msg& msg;
    const opt_t* opts;
    const std::string& file;
    uint32_t line;
    uint32_t ind;
    bool oneline_mode;

    RenderContext(const Msg& msg, const std::string& file)
        : os(), msg(msg), opts(nullptr), file(file), line(1), ind(0), oneline_mode(false) {}
    FORBID_COPY(RenderContext);
};

class RenderCallback {
  public:
    virtual void render_var(StxVarId var);
    virtual size_t get_list_size(StxVarId var) const;
    virtual void start_list(StxVarId var, size_t lbound, size_t rbound);
    virtual bool next_in_list(StxVarId var);
    virtual bool eval_cond(StxLOpt opt);
    virtual ~RenderCallback() = default;
};

struct StartCond {
    std::string name;
    uint32_t number;
};
using StartConds = std::vector<StartCond>;

using storable_states_t = std::map<uint32_t, CodeList*>;

struct OutputBlock {
    InputBlock kind;
    std::string name;
    const loc_t loc;
    CodeList* code;
    bool used_yyaccept;
    bool have_user_code;
    StartConds conds;
    tagnames_t stags;
    tagnames_t mtags;
    tagnames_t svars;
    tagnames_t mvars;
    const opt_t* opts;
    Adfas dfas;

    size_t max_fill;   // YYMAXFILL
    size_t max_nmatch; // YYMAXNMATCH

    // Used in the state switch (with `-f --storable-state` option).
    Label* start_label;          // start label of this block
    storable_states_t fill_goto; // transitions to YYFILL states

    // precomputed YYFN parts with block-level options (in rec/func mode)
    CodeFnCommon* fn_common;
    // precomputed relational operators
    const char* binops[OP_COUNT];

    OutputBlock(InputBlock kind, const std::string& name, const loc_t& loc);
    ~OutputBlock();
    FORBID_COPY(OutputBlock);
};

struct Output {
    OutAllocator& allocator;
    Msg& msg;
    blocks_t cblocks;  // .c file
    blocks_t hblocks;  // .h file
    blocks_t* pblocks; // selector
    blocks_t tmpblocks;
    uint32_t label_counter;
    uint32_t fill_label_counter;
    bool state_goto;
    bool cond_enum_autogen; // true unless an explicit `conditions` block is used
    bool warn_condition_order;
    bool need_header;
    bool done_mtag_defs;
    std::set<std::string> skeletons;
    Scratchbuf scratchbuf;
    OutputBlock* current_block;

    // whole-program options accumulated for all non-reuse blocks
    const opt_t* total_opts;

    // precomputed YYFN parts with whole-program options (in rec/func mode)
    CodeFnCommon* fn_common;

    Output(OutAllocator& alc, Msg& msg);
    ~Output();
    OutputBlock& block();
    void set_current_block(OutputBlock* block);
    bool open();
    Ret new_block(Opt& opts, InputBlock kind, std::string name, const loc_t& loc) NODISCARD;
    void header_mode(bool on);
    bool in_header() const;
    void gen_raw(const uint8_t* s, const uint8_t* e, bool newline = false);
    void gen_stmt(Code* stmt);
    Ret gen_prolog(Opt& opts, const loc_t& loc);
    void gen_epilog();
    FORBID_COPY(Output);
};

void init_go(CodeGo* go);
bool endstate(const State* s);
bool consume(const State* s);
State* fallback_state_with_eof_rule(
        const Adfa& dfa, const opt_t* opts, const State* state, tcid_t* ptags);
std::string bitmap_name(const opt_t* opts, const std::string& cond);
CodeList* gen_bitmap(Output& output, const CodeBitmap* bitmap, const std::string& cond);
void gen_tags(Scratchbuf& buf, const opt_t* opts, Code* code, const tagnames_t& tags);
CodeList* gen_goto_after_fill(
        Output& output, const Adfa& dfa, const State* from, const CodeJump* jump);
void gen_dfa_as_blocks_with_labels(Output& output, const Adfa& dfa, CodeList* stmts);
void gen_dfa_as_switch_cases(Output& output, Adfa& dfa, CodeCases* cases);
void wrap_dfas_in_loop_switch(Output& output, CodeList* stmts, CodeCases* cases);
void expand_fintags(Output& output, const Tag& tag, std::vector<const char*>& fintags);
std::string captvar_name(size_t index, const opt_t* opts);
std::string vartag_name(tagver_t ver, const opt_t* opts, bool is_mtag);
std::string vartag_expr(tagver_t ver, const opt_t* opts, bool is_mtag);
void gen_peek_expr(std::ostream& os, const opt_t* opts);

Ret codegen_analyze(Output& output) NODISCARD;
Ret codegen_generate(Output& output) NODISCARD;
void codegen_fixup(Output& output);
Ret codegen_render(Output& outptu) NODISCARD;

} // namespace re2c

#endif // _RE2C_CODEGEN_OUTPUT_
