#ifndef _RE2C_AST_INPUT_
#define _RE2C_AST_INPUT_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <set>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/encoding/enc.h"
#include "src/encoding/utf8.h"
#include "src/msg/location.h"
#include "src/parse/lex.h"
#include "src/parse/parser.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/check.h"
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

struct InputFile {
    FILE* file;
    std::string name;
    std::string path;
    std::string escaped_name;
    const uint8_t* so; // start offset in buffer
    const uint8_t* eo; // end offset in buffer
    uint32_t line;
    uint32_t fidx;

    explicit InputFile(size_t fidx);
    ~InputFile();
    Ret open(const std::string& filename,
             const std::string* parent,
             const std::vector<std::string>& include_paths) NODISCARD;

    FORBID_COPY(InputFile);
};

class Input: private LexerState {
  public:
    static const uint8_t* const ENDPOS;

  private:
    Msg& msg;
    std::vector<InputFile*> files;
    std::set<std::string> filedeps;
    const conopt_t* globopts;
    loc_t location;

  public:
    Input(const conopt_t* o, Msg& m);
    ~Input();
    const loc_t& tok_loc() const;
    loc_t cur_loc() const;
    Ret open(const std::string& filename, const std::string* parent) NODISCARD;
    Ret include(const std::string& filename, uint8_t* at) NODISCARD;
    Ret gen_dep_file(const std::string& header) const NODISCARD;
    Ret lex_program(Output& out, std::string& block_name, InputBlock& kind) NODISCARD;
    Ret lex_block(YYSTYPE* yylval, Ast& ast, int& token) NODISCARD;
    Ret lex_conf(Opt& opts) NODISCARD;

    void error_at(const loc_t& loc, const char* fmt, ...) const RE2C_ATTR((format(printf, 3, 4)));
    void error_at_cur(const char* fmt, ...) const RE2C_ATTR((format(printf, 2, 3)));
    void error_at_tok(const char* fmt, ...) const RE2C_ATTR((format(printf, 2, 3)));

  private:
    bool read(size_t want) NODISCARD;
    bool fill(size_t need) NODISCARD;
    void shift_ptrs_and_fpos(ptrdiff_t offs);
    void pop_finished_files();

    size_t get_input_index() const;
    InputFile& get_input();
    const InputFile& get_cinput() const;

    bool is_eof() const;

    uint32_t decode(const uint8_t* str) const;

    inline void set_line(uint32_t l);
    inline void next_line();
    Ret set_sourceline() NODISCARD;

    Ret lex_opt_name(std::string& name) NODISCARD;
    Ret lex_name_list(OutAllocator& alc, BlockNameList** ptail) NODISCARD;
    Ret lex_special_block(Output& out, CodeKind kind, uint32_t mask) NODISCARD;
    Ret lex_block_end(Output& out, bool allow_garbage = false) NODISCARD;
    Ret lex_code_indented(YYSTYPE* yylval, Ast& ast) NODISCARD;
    Ret lex_code_in_braces(YYSTYPE* yylval, Ast& ast) NODISCARD;
    Ret try_lex_literal_in_code(uint8_t quote) NODISCARD;
    Ret lex_c_comment() NODISCARD;
    Ret lex_cpp_comment() NODISCARD;
    Ret lex_namedef_context_re2c(bool& yes) NODISCARD;
    Ret lex_namedef_context_flex(bool& yes) NODISCARD;
    Ret lex_clist(Ast& ast, int& token) NODISCARD;
    Ret lex_cls_chr(uint32_t& c) NODISCARD;
    Ret lex_str_chr(uint8_t quote, AstChar& ast, bool& stop) NODISCARD;
    Ret lex_cls(Ast& ast, bool neg, const AstNode*&) NODISCARD;
    Ret lex_str(Ast& ast, uint8_t quote, const AstNode*&) NODISCARD;

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

    FORBID_COPY(Input);
};

inline Input::Input(const conopt_t* o, Msg& m)
    : LexerState(),
      msg(m),
      files(),
      filedeps(),
      globopts(o),
      location({1, 0, 1}) {} // file index 1 because 0 is reserved for syntax file

inline loc_t Input::cur_loc() const {
    const uint8_t* p = cur;
    ptrdiff_t padding = 0;
    if (is_eof()) { // if this is the end, roll back to the beginning of YYMAXFILL padding
        while (cur[padding] == 0) --padding;
        ++padding; // point at the first null, not at the last valid character
    }
    DCHECK(p >= pos);
    uint32_t c = static_cast<uint32_t>(cur - pos + padding);

    const InputFile& in = get_cinput();
    return {in.line, c, in.fidx};
}

inline const loc_t& Input::tok_loc() const {
    return location;
}

inline void Input::set_line(uint32_t l) {
    get_input().line = l;
}

inline void Input::next_line() {
    pos = cur;
    ++get_input().line;
}

inline bool Input::is_eof() const {
    return eof && cur > eof;
}

inline InputFile& Input::get_input() {
    return *files[get_input_index()];
}

inline const InputFile& Input::get_cinput() const {
    return *files[get_input_index()];
}

} // namespace re2c

#endif // _RE2C_AST_INPUT_
