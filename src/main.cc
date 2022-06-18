#include <stdio.h>

#include "src/codegen/code.h"
#include "src/compile.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/parse/input.h"
#include "src/parse/scanner.h"

using namespace re2c;

int main(int, char* argv[]) {
    conopt_t globopts;
    Msg msg;
    Opt opts(globopts, msg);

    switch (parse_opts(argv, globopts, opts, msg)) {
    case ParseOpts::OK:
        break;
    case ParseOpts::EXIT_OK:
        return 0;
    case ParseOpts::EXIT_FAIL:
        return 1;
    }

    Scanner scanner(&globopts, msg);
    if (!scanner.open(globopts.source_file, nullptr)) {
        return 1;
    }

    Output output(msg);

    compile(scanner, output, opts);

    if (!output.emit()) {
        return 1;
    }

    if (msg.warn.error()) {
        return 1;
    }

    if (!scanner.gen_dep_file()) {
        return 1;
    }

    if (globopts.verbose) {
        fprintf(stderr, "re2c: success\n");
    }
    return 0;
}
