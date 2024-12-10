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
#include "src/parse/lexer.h"
#include "src/parse/parser.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/check.h"
#include "src/util/forbid_copy.h"

union CONF_STYPE;

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
struct StxCode;
using StxCodes = list_t<StxCode>;

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

    OutAllocator& alc;

  private:
    Msg& msg;
    std::vector<InputFile*> files;
    std::set<std::string> filedeps;
    const conopt_t* globopts;

    // This is needed to save `tok` locaton to be used in `tok_loc()` later.
    // We cannot find it in the same way as for `cur` and `cur_loc()` because line number
    // and line start `pos` are only updated for `cur`.
    loc_t location;

    enum class ConfKind {NONE, STR, NUM, LIST, CODE} conf_kind;
    std::string tmp_str;
    int32_t tmp_num;
    bool tmp_bool;
    std::vector<std::string> tmp_list;
    const StxCodes* tmp_code;

    bool in_syntax_file;

  public:
    Input(OutAllocator& alc, const conopt_t* o, Msg& m);
    ~Input();

    Ret open(const std::string& filename, const std::string* parent) NODISCARD;
    Ret load_syntax_config(Opt& opts, Lang lang);
    Ret include(const std::string& filename, uint8_t* at) NODISCARD;
    Ret gen_dep_file(const std::string& header) const NODISCARD;

    Ret lex_program(Output& out, std::string& block_name, InputBlock& kind) NODISCARD;
    Ret lex_block(RE2C_STYPE* yylval, Ast& ast, int& token) NODISCARD;
    Ret lex_conf(Opt& opts) NODISCARD;
    Ret lex_conf_token(CONF_STYPE* yylval, int& token, Opt& opts);
    Ret lex_syntax_file(Opt& opts);

    const loc_t& tok_loc() const;
    loc_t cur_loc() const;
    void error_at(const loc_t& loc, const char* fmt, ...) const RE2C_ATTR((format(printf, 3, 4)));
    void error_at_cur(const char* fmt, ...) const RE2C_ATTR((format(printf, 2, 3)));
    void error_at_tok(const char* fmt, ...) const RE2C_ATTR((format(printf, 2, 3)));

    void save_conf_num(int32_t num);
    void save_conf_str(const char* str);
    void save_conf_list(std::vector<std::string>* list);
    std::vector<std::string>* get_tmp_list();

  private:
    void reset_lexer();

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

    Ret process_semact(RE2C_STYPE* yylval, Ast& ast, const uint8_t* p, const uint8_t* q) NODISCARD;

    Ret lex_opt_name(std::string& name) NODISCARD;
    Ret lex_name_list(BlockNameList** ptail) NODISCARD;
    Ret lex_special_block(Output& out, CodeKind kind, uint32_t mask) NODISCARD;
    Ret lex_block_end(Output& out, bool allow_garbage = false) NODISCARD;
    Ret lex_code_indented(RE2C_STYPE* yylval, Ast& ast) NODISCARD;
    Ret lex_code_in_braces(RE2C_STYPE* yylval, Ast& ast) NODISCARD;
    Ret lex_dqstring_in_code() NODISCARD;
    Ret lex_sqstring_in_code() NODISCARD;
    Ret lex_bqstring_in_code() NODISCARD;
    Ret lex_sqchar_or_standalone_in_code() NODISCARD;
    Ret lex_bqchar_or_standalone_in_code() NODISCARD;
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

    Ret lex_spaces() NODISCARD;
    Ret lex_conf_assign() NODISCARD;
    Ret lex_conf_semicolon() NODISCARD;
    Ret lex_conf_number(Opt& opts) NODISCARD;
    Ret lex_conf_bool(Opt& opts) NODISCARD;
    Ret lex_conf_string_quoted(uint8_t quote) NODISCARD;
    Ret lex_conf_string_legacy() NODISCARD;
    Ret lex_conf_string(Opt& opts) NODISCARD;
    Ret lex_conf_list(Opt& opts) NODISCARD;
    Ret lex_conf_code(Opt& opts) NODISCARD;
    Ret parse_conf(Opt& opts);

    FORBID_COPY(Input);
};

inline Input::Input(OutAllocator& alc, const conopt_t* o, Msg& m)
    : LexerState(),
      alc(alc),
      msg(m),
      files(),
      filedeps(),
      globopts(o),
      location(ATSTART),
      conf_kind(ConfKind::NONE),
      tmp_str(),
      tmp_num(),
      tmp_bool(),
      tmp_list(),
      tmp_code(),
      in_syntax_file(false) {}

inline loc_t Input::cur_loc() const {
    const uint8_t* p = cur;
    if (is_eof()) { // if this is the end, roll back to the beginning of YYMAXFILL padding
        while (*p == 0) --p;
        ++p; // point at the first null, not at the last valid character
    }
    DCHECK(p >= pos);
    uint32_t c = static_cast<uint32_t>(p - pos);

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

inline void Input::save_conf_num(int32_t num) {
    conf_kind = ConfKind::NUM;
    tmp_num = num;
    tmp_bool = num != 0;
}

inline void Input::save_conf_str(const char* str) {
    conf_kind = ConfKind::STR;
    tmp_str = str;
}

inline void Input::save_conf_list(std::vector<std::string>* list) {
    conf_kind = ConfKind::LIST;
    CHECK(list == &tmp_list); // `tmp_list` already contains list
}

inline std::vector<std::string>* Input::get_tmp_list() {
    tmp_list.clear();
    return &tmp_list;
}

} // namespace re2c

#endif // _RE2C_AST_INPUT_
