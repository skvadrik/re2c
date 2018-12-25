#ifndef _RE2C_AST_SCANNER_
#define _RE2C_AST_SCANNER_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <sys/types.h>
#include <string>
#include <vector>

#include "src/ast/input.h"
#include "src/ast/lex.h"
#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/re/encoding/enc.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

class Warn;
struct Opt;
struct conopt_t;
class Output;
class Range;
struct AST;

class Scanner: private ScannerState
{
public:
    enum ParseMode {Stop, Parse, Reuse, Rules};
    static const char *const ENDPOS;

private:
    std::vector<Input*> files;
    Warn &warn;

public:
    explicit Scanner(Warn &w);
    ~Scanner();
    bool push_file(const std::string &filename);
    uint32_t get_cline() const;
    uint32_t get_column() const;
    const std::string & get_fname() const;
    ParseMode echo(Output &out);
    int scan(const conopt_t *globopts);
    void lex_conf(Opt &opts);

private:
    bool read(size_t want);
    bool fill(size_t need);
    void shift_ptrs_and_fpos(ptrdiff_t offs);
    void pop_finished_files();
    size_t get_input_index() const;
    Input& get_input();
    const Input& get_cinput() const;
    size_t tok_len() const;
    void set_sourceline ();
    void lex_end_of_comment(Output &out);
    void lex_include();
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
    uint32_t lex_str_chr(char quote, bool &end);
    const AST *lex_cls(bool neg);
    const AST *lex_str(char quote);
    void lex_conf_encoding_policy(Opt &opts);
    void lex_conf_input(Opt &opts);
    void lex_conf_empty_class(Opt &opts);
    void lex_conf_dfa_minimization(Opt &opts);
    void lex_conf_enc(Enc::type_t enc, Opt &opts);
    void lex_conf_assign();
    void lex_conf_semicolon();
    int32_t lex_conf_number();
    bool lex_conf_bool();
    std::string lex_conf_string();
    bool is_eof() const;
    void fail_if_eof() const;

    FORBID_COPY (Scanner);
};

inline Scanner::Scanner(Warn &w)
    : ScannerState()
    , files()
    , warn(w)
{}

inline size_t Scanner::tok_len() const
{
    return static_cast<size_t>(cur - tok);
}

inline const std::string & Scanner::get_fname() const
{
    return get_cinput().escaped_name;
}

inline uint32_t Scanner::get_cline() const
{
    return cline;
}

inline uint32_t Scanner::get_column() const
{
    return static_cast<uint32_t>(tok - pos);
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

} // end namespace re2c

#endif // _RE2C_AST_SCANNER_
