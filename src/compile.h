#ifndef _RE2C_COMPILE_
#define _RE2C_COMPILE_


namespace re2c {

class Scanner;
struct Opt;
class Output;

void compile(Scanner &input, Output &output, Opt &opts);

} // namespace re2c

#endif // _RE2C_COMPILE_
