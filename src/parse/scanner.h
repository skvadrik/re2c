#ifndef _RE2C_AST_SCANNER_
#define _RE2C_AST_SCANNER_

#include <stddef.h>
#include <stdint.h>
#include <set>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/debug/debug.h"
#include "src/msg/location.h"
#include "src/parse/input.h"
#include "src/parse/lex.h"
#include "src/encoding/enc.h"
#include "src/encoding/utf8.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class Ast;
class Msg;
struct Output;
struct AstNode;
struct AstChar;
struct BlockNameList;
struct conopt_t;
struct opt_t;
struct Opt;

// Must be defined exacly as in codegen.
using code_alc_t = slab_allocator_t<1024 * 1024, 8>;

class Scanner: private ScannerState {
  public:
    static const char* const ENDPOS;

    Msg& msg;

  private:
    std::vector<Input*> files;
    std::set<std::string> filedeps;
    const conopt_t* globopts;
    loc_t location;

  public:
    Scanner(const conopt_t* o, Msg& m);
    ~Scanner();
    const loc_t& tok_loc() const;
    loc_t cur_loc() const;
    Ret open(const std::string& filename, const std::string* parent) NODISCARD;
    Ret include(const std::string& filename, char* at) NODISCARD;
    Ret gen_dep_file() const NODISCARD;
    Ret echo(Output& out, std::string& block_name, InputBlock& kind) NODISCARD;
    Ret scan(Ast& ast, int& token) NODISCARD;
    Ret lex_conf(Opt& opts) NODISCARD;

  private:
    bool read(size_t want) NODISCARD;
    bool fill(size_t need) NODISCARD;
    void shift_ptrs_and_fpos(ptrdiff_t offs);
    void pop_finished_files();
    size_t get_input_index() const;
    Input& get_input();
    const Input& get_cinput() const;
    inline void set_line(uint32_t l);
    inline void next_line();

    bool is_eof() const;
    Ret set_sourceline() NODISCARD;
    Ret lex_opt_name(std::string& name) NODISCARD;
    Ret lex_name_list(code_alc_t& alc, BlockNameList** ptail) NODISCARD;
    Ret lex_block(Output& out, CodeKind kind, uint32_t indent, uint32_t mask) NODISCARD;
    Ret lex_block_end(Output& out, bool allow_garbage = false) NODISCARD;
    Ret lex_code_indented(Ast& ast) NODISCARD;
    Ret lex_code_in_braces(Ast& ast) NODISCARD;
    Ret try_lex_string_in_code(char quote) NODISCARD;
    Ret lex_c_comment() NODISCARD;
    Ret lex_cpp_comment() NODISCARD;
    Ret lex_namedef_context_re2c(bool& yes) NODISCARD;
    Ret lex_namedef_context_flex(bool& yes) NODISCARD;
    Ret lex_clist(Ast& ast, int& token) NODISCARD;
    Ret lex_string(char delim) NODISCARD;
    Ret lex_cls_chr(uint32_t& c) NODISCARD;
    Ret lex_str_chr(char quote, AstChar& ast, bool& stop) NODISCARD;
    Ret lex_cls(Ast& ast, bool neg, const AstNode*&) NODISCARD;
    Ret lex_str(Ast& ast, char quote, const AstNode*&) NODISCARD;

    Ret lex_conf_encoding_policy(Opt& opts) NODISCARD;
    Ret lex_conf_input(Opt& opts) NODISCARD;
    Ret lex_conf_empty_class(Opt& opts) NODISCARD;
    Ret lex_conf_api_style(Opt& opts) NODISCARD;
    Ret lex_conf_assign() NODISCARD;
    Ret lex_conf_semicolon() NODISCARD;
    Ret lex_conf_number(int32_t& n) NODISCARD;
    Ret lex_conf_bool(bool& b) NODISCARD;
    Ret lex_conf_eof(uint32_t& u) NODISCARD;
    Ret lex_conf_string(std::string& s) NODISCARD;

    uint32_t decode(const char* str) const;

    FORBID_COPY (Scanner);
};

inline Scanner::Scanner(const conopt_t* o, Msg& m)
    : ScannerState(),
      msg(m),
      files(),
      filedeps(),
      globopts(o),
      location(ATSTART) {}

inline loc_t Scanner::cur_loc() const {
    const Input& in = get_cinput();
    uint32_t c = static_cast<uint32_t>(cur - pos);
    if (is_eof()) {
        DASSERT(c > 0);
        --c;
    }
    return {in.line, c, in.fidx};
}

inline const loc_t& Scanner::tok_loc() const {
    return location;
}

inline void Scanner::set_line(uint32_t l) {
    get_input().line = l;
}

inline void Scanner::next_line() {
    pos = cur;
    ++get_input().line;
}

inline bool Scanner::is_eof() const {
    return eof && cur > eof;
}

inline Input& Scanner::get_input() {
    return *files[get_input_index()];
}

inline const Input& Scanner::get_cinput() const {
    return *files[get_input_index()];
}

} // namespace re2c

#endif // _RE2C_AST_SCANNER_
