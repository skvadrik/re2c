#ifndef _RE2C_AST_SCANNER_
#define _RE2C_AST_SCANNER_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <sys/types.h>
#include <string>

#include "src/ast/input.h"
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
class OutputFile;
class Range;
struct AST;

struct ScannerState
{
    enum lexer_state_t
    {
        LEX_NORMAL,
        LEX_FLEX_NAME
    };

    // positioning
    char * tok;
    char * ptr;
    char * cur;
    char * mar;
    char * pos;
    char * ctx;

    // buffer
    char * bot;
    char * lim;
    char * top;
    char * eof;

    ptrdiff_t tchar;
    uint32_t cline;

    lexer_state_t lexer_state;

    ScannerState();
    FORBID_COPY(ScannerState);
};

class Scanner: private ScannerState
{
    static const uint32_t BSIZE;
    Input & in;
    Warn &warn;

    void fill(uint32_t need);
    void lex_end_of_comment(OutputFile &out);
    void lex_tags(OutputFile &out, bool mtags);
    void set_sourceline ();
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
    size_t tok_len () const;

public:
    enum ParseMode {Stop, Parse, Reuse, Rules};

    Scanner(Input&, Warn &w);
    ~Scanner();
    ParseMode echo(OutputFile &out);
    int scan(const conopt_t *globopts);
    void lex_conf(Opt &opts);
    uint32_t get_cline() const;
    uint32_t get_column() const;
    const std::string & get_fname () const;
    FORBID_COPY (Scanner);
};

inline size_t Scanner::tok_len () const
{
    // lexing and fill procedures must maintain: token pointer <= cursor pointer
    return static_cast<size_t> (cur - tok);
}

inline const std::string & Scanner::get_fname () const
{
    return in.escaped_file_name;
}

inline uint32_t Scanner::get_cline() const
{
    return cline;
}

inline uint32_t Scanner::get_column() const
{
    return static_cast<uint32_t>(tok - pos);
}

} // end namespace re2c

#endif // _RE2C_AST_SCANNER_
