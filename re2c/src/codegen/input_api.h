#ifndef _RE2C_CODEGEN_INPUT_API_
#define _RE2C_CODEGEN_INPUT_API_

#include "src/util/c99_stdint.h"
#include <string>

namespace re2c
{

struct Opt;
struct opt_t;

enum input_api_t
{
	INPUT_DEFAULT,
	INPUT_CUSTOM
};

std::string output_expr_peek     (Opt &opts);
std::string output_restore       (uint32_t ind, Opt &opts);
std::string output_expr_lessthan (size_t n, Opt &opts);

void output_peek             (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_skip             (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_backup           (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_skip_peek        (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_peek_skip        (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_skip_backup      (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_backup_skip      (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_backup_peek      (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_skip_backup_peek (std::ostream &o, uint32_t ind, const opt_t *opts);
void output_backup_peek_skip (std::ostream &o, uint32_t ind, const opt_t *opts);

} // end namespace re2c

#endif // _RE2C_CODEGEN_INPUT_API_
