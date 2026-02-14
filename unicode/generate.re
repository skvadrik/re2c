#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

struct Block {
    std::string name;
    uint32_t first;
    uint32_t last;
};

using Cat = std::vector<std::pair<uint32_t, uint32_t>>;
using CatMap = std::map<std::string, Cat>;
using Blocks = std::vector<Block>;

constexpr uint32_t NONE = ~0u;
constexpr uint32_t MAX = 0x10FFFF;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = uint8_t;
    re2c:YYCURSOR = in.cursor;
    re2c:YYMARKER = in.marker;
*/

struct Input {
    uint8_t* buffer;
    uint8_t* cursor;
    uint8_t* marker;

    Input(): buffer(nullptr), cursor(nullptr), marker(nullptr) {}

    ~Input() { free(buffer); }

    bool init(const char* fname) {
        FILE* fdata = fopen(fname, "rb");
        if (fdata == nullptr) {
            fprintf(stderr, "cannot open %s\n", fname);
            return false;
        }

        fseek(fdata, 0, SEEK_END);
        size_t fdata_size = ftell(fdata);
        fseek(fdata, 0, SEEK_SET);

        buffer = static_cast<uint8_t*>(malloc(fdata_size + 1));
        fread(buffer, fdata_size, 1, fdata);
        buffer[fdata_size] = 0;

        fclose(fdata);

        cursor = buffer;
        return true;
    }
};

static void print_char(FILE* file, uint32_t chr) {
    if (chr <= 0xFF) {
        fprintf(file, "\\x%02x", chr);
    } else if (chr <= 0xFFFF) {
        fprintf(file, "\\u%04x", chr);
    } else {
        fprintf(file, "\\U%08x", chr);
    }
}

static void add(Cat& cat, uint32_t first, uint32_t last) {
    if (cat.empty() || cat.back().second + 1 != first) { 
        cat.push_back(std::make_pair(first, last));
    } else {
        cat.back().second = last;
    }
}

static uint32_t parse_hex(Input& in) {
    uint32_t cp = 0;
    in.marker = in.cursor;
loop:
    /*!re2c
        [0-9] { cp = cp * 16 + (in.cursor[-1] - '0');      goto loop; }
        [A-F] { cp = cp * 16 + (in.cursor[-1] - 'A' + 10); goto loop; }
        "" { return in.cursor > in.marker ? cp : NONE; }
    */
}

static int gen_categories() {
    Input in;
    if (!in.init("UnicodeData.txt")) return 1;

    CatMap categories;

    const uint8_t* token;
    size_t line = 0;
    std::string cat;
    uint32_t first = NONE, last = NONE, prev = 0, cp;

    // Example:
    //   0000;<control>;Cc;0;BN;;;;;N;NULL;;;;
loop:
    token = in.cursor;
    /*!re2c
        [\x00] {
            if (prev <= MAX) {
                add(categories["Cn"], prev, 0x10FFFF);
            }
            goto end;
        }
        "" { goto cpoint; }
    */
cpoint:
    cp = parse_hex(in);
    if (cp == NONE) goto error;
    /*!re2c
        [;] { goto desc; }
        * { goto error; }
    */
desc:
    /*!re2c
        "<" [A-Za-z0-9 -]+ ", First>;" { first = cp; assert(last == NONE);  goto cat; }
        "<" [A-Za-z0-9 -]+ ", Last>;"  { last = cp;  assert(first != NONE); goto cat; }
        [^;\n\x00]+ [;] { first = last = cp; goto cat; }
        * { goto error; }
    */
cat:
    token = in.cursor;
    /*!re2c
        [A-Z][a-z]? { cat.assign((const char*)token, in.cursor - token); goto rest; }
        * { goto error; }
    */
rest:
    /*!re2c
        [;] [^;\n\x00]* { goto rest; }
        * { goto error; }
        [\n] {
            ++line;
            if (last != NONE) {
                if (first > prev) {
                    add(categories["Cn"], prev, first - 1);
                }
                add(categories[cat], first, last);
                prev = last + 1;
                first = last = NONE;
            }
            goto loop;
        }
    */

error:
    fprintf(stderr, "parsing UnicodeData.txt: error at line %lu; '%.*s'\n", line, 100, in.cursor);
    return 1;

end:
    std::map<std::string, std::vector<std::string>> derived_categories;
    derived_categories["L_"] = {"Lu", "Ll", "Lt"};
    derived_categories["L"] = {"Lu", "Ll", "Lt", "Lm", "Lo"};
    derived_categories["M"] = {"Mn", "Mc", "Me"};
    derived_categories["N"] = {"Nd", "Nl", "No"};
    derived_categories["P"] = {"Pc", "Pd", "Ps", "Pe", "Pi", "Pf", "Po"};
    derived_categories["S"] = {"Sm", "Sc", "Sk", "So"};
    derived_categories["Z"] = {"Zs", "Zl", "Zp"};
    derived_categories["C"] = {"Cc", "Cf", "Cs", "Co", "Cn"};

    Cat tmp;
    for (const auto& i : derived_categories) {
        for (const std::string& s : i.second) {
            Cat& c = categories[s];
            tmp.insert(tmp.end(), c.begin(), c.end());
        }
        std::sort(tmp.begin(), tmp.end());

        Cat& c = categories[i.first];
        c.push_back(tmp[0]);
        for (size_t j = 1; j < tmp.size(); ++j) {
            if (tmp[j].first == tmp[j - 1].second + 1) {
                c.back().second = tmp[j].second;
            } else {
                c.push_back(tmp[j]);
            }
        }
        tmp.clear();
    }

    FILE* f = fopen("unicode_categories.re", "wb");
    if (f == nullptr) {
        fprintf(stderr, "cannot open unicode_categories.re\n");
        return 1;
    }
    fprintf(f, "/*!""re2c\n");
    for (const auto& i : categories) {
        fprintf(f, "%s = [", i.first.c_str());
        for (const auto& p : i.second) {
            print_char(f, p.first);
            if (p.second > p.first) {
                fprintf(f, "-");
                print_char(f, p.second);
            }
        }
        fprintf(f, "];\n");
    }
    fprintf(f, "*/\n");
    fclose(f);

    return 0;
}

static int gen_blocks() {
    Input in;
    if (!in.init("Blocks.txt")) return 1;

    Blocks blocks;

    const uint8_t* token;
    size_t line = 0;
    std::string block;
    uint32_t first = NONE, last = NONE;

    // Example:
    //   # comments
    //   0000..007F; Basic Latin
loop:
    /*!re2c
        "# EOF\n" { goto end; }
        ([#] [^\x00\n]*)? [\n] { ++line; goto loop; }
        "" { goto first; }
    */
first:
    first = parse_hex(in);
    /*!re2c
        ".." { goto last; }
        * { goto error; }
    */
last:
    last = parse_hex(in);
    /*!re2c
        "; " { goto block; }
        * { goto error; }
    */
block:
    token = in.cursor;
    /*!re2c
        [A-Z][A-Za-z0-9_ -]* [\n] {
            if (first == NONE || last == NONE) goto error;

            ++line;
            block.assign((const char*)token, in.cursor - token - 1);
            for (size_t i = 0; i < block.size(); ++i) {
                if (!isdigit(block[i]) && !isalpha(block[i])) {
                    block[i] = '_';
                }
            }
            blocks.push_back({block, first, last});
            goto loop;
        }
        * { goto error; }
    */
error:
    fprintf(stderr, "parsing Blocks.txt: error at line %lu; '%.*s'\n", line, 100, in.cursor);
    return 1;
end:
    FILE* f = fopen("unicode_blocks.re", "wb");
    if (f == nullptr) {
        fprintf(stderr, "cannot open unicode_blocks.re\n");
        return 1;
    }
    fprintf(f, "/*!""re2c\n");
    for (const Block& b : blocks) {
        fprintf(f, "%s = [", b.name.c_str());
        print_char(f, b.first);
        fprintf(f, "-");
        print_char(f, b.last);
        fprintf(f, "];\n");
    }
    fprintf(f, "*/\n");
    fclose(f);
    return 0;
}

int main() {
    gen_categories();
    gen_blocks();
}
