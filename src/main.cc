#include <stdio.h>

#include "src/codegen/code.h"
#include "src/compile.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/input.h"

namespace re2c {

static Ret main(int, char* argv[]) {
    Msg msg;
    conopt_t globopts;
    Opt opts(globopts, msg);
    CHECK_RET(parse_opts(argv, globopts, opts, msg));

    Scanner scanner(&globopts, msg);
    CHECK_RET(scanner.open(globopts.source_file, nullptr));

    Output output(msg);
    CHECK_RET(compile(scanner, output, opts));

    CHECK_RET(output.emit());

    CHECK_RET(msg.warn.check());

    CHECK_RET(scanner.gen_dep_file());

    if (globopts.verbose) fprintf(stderr, "re2c: success\n");
    return Ret::OK;
}

} // namespace re2c

int main(int argc, char* argv[]) {
    return re2c::main(argc, argv) == re2c::Ret::FAIL ? 1 : 0;
}
