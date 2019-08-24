#ifndef _RE2C_AST_SCANNER_
#define _RE2C_AST_SCANNER_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>
#include <vector>

#include "src/debug/debug.h"
#include "src/msg/location.h"
#include "src/parse/input.h"
#include "src/parse/lex.h"
#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/encoding/utf8/utf8.h"
#include "src/util/forbid_copy.h"


namespace re2c {

class Msg;
class Output;
struct AST;
struct ASTChar;

class Scanner: private ScannerState
{
public:
    enum ParseMode {Stop, Parse, Reuse, Rules};
    static const char *const ENDPOS;

    Msg &msg;

private:
    std::vector<Input*> files;
    const conopt_t *globopts;
    loc_t location;

public:
    Scanner(const conopt_t *o, Msg &m);
    ~Scanner();
    bool open(const std::string &filename, const std::string *parent);
    bool include(const std::string &filename);
    const loc_t &tok_loc() const;
    loc_t cur_loc() const;
    ParseMode echo(Output &out);
    int scan();
    void lex_conf(Opt &opts);

private:
    bool read(size_t want);
    bool fill(size_t need);
    void shift_ptrs_and_fpos(ptrdiff_t offs);
    void pop_finished_files();
    size_t get_input_index() const;
    Input& get_input();
    const Input& get_cinput() const;
    inline void set_line(uint32_t l);
    inline void next_line();
    void set_sourceline ();
    void lex_end_of_comment(Output &out);
    void lex_code_indented();
    void lex_code_in_braces();
    void lex_c_comment();
    void lex_cpp_comment();
    bool lex_namedef_context_re2c();
    bool lex_namedef_context_flex();
    int lex_clist();
    void lex_string(char delim);
    void lex_tags(Output &out, bool mtags);
    uint32_t lex_cls_chr();
    bool lex_str_chr(char quote, ASTChar &ast);
    const AST *lex_cls(bool neg);
    const AST *lex_str(char quote);
    void lex_conf_encoding_policy(Opt &opts);
    void lex_conf_input(Opt &opts);
    void lex_conf_empty_class(Opt &opts);
    void lex_conf_enc(Enc::type_t enc, Opt &opts);
    void lex_conf_assign();
    void lex_conf_semicolon();
    int32_t lex_conf_number();
    bool lex_conf_bool();
    uint32_t lex_conf_eof();
    std::string lex_conf_string();
    bool is_eof() const;
    void fail_if_eof() const;
    uint32_t decode(const char *str) const;

    FORBID_COPY (Scanner);
};

inline Scanner::Scanner(const conopt_t *o, Msg &m)
    : ScannerState()
    , msg(m)
    , files()
    , globopts(o)
    , location(ATSTART)
{}

inline loc_t Scanner::cur_loc() const
{
    const Input &in = get_cinput();
    uint32_t c = static_cast<uint32_t>(cur - pos);
    if (is_eof()) {
         DASSERT(c > 0);
         --c;
    }
    const loc_t loc = {in.line, c, in.fidx};
    return loc;
}

inline const loc_t &Scanner::tok_loc() const
{
    return location;
}

inline void Scanner::set_line(uint32_t l)
{
    get_input().line = l;
}

inline void Scanner::next_line()
{
    pos = cur;
    ++get_input().line;
}

inline bool Scanner::is_eof() const
{
    return eof && cur > eof;
}

inline Input& Scanner::get_input()
{
    return *files[get_input_index()];
}

inline const Input& Scanner::get_cinput() const
{
    return *files[get_input_index()];
}

inline uint32_t Scanner::decode(const char *str) const
{
    return globopts->input_encoding == Enc::ASCII
        ? static_cast<uint8_t>(str[0])
        : utf8::decode_unsafe(str);
}

} // end namespace re2c

#endif // _RE2C_AST_SCANNER_
