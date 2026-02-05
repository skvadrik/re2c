#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using Cat = std::vector<std::pair<uint32_t, uint32_t>>;
using CatMap = std::map<std::string, Cat>;

constexpr uint32_t NONE = ~0u;
constexpr uint32_t MAX = 0x10FFFF;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = uint8_t;
*/

struct Input {
    uint8_t* buffer;

    Input(): buffer(nullptr) {}

    ~Input() { delete(buffer); }

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

static int gen_categories() {
    Input in;
    if (!in.init("UnicodeData.txt")) return 1;

    CatMap categories;

    const uint8_t* YYCURSOR = in.buffer;
    const uint8_t* YYMARKER;
    const uint8_t* token;
    size_t line = 0;
    std::string cat;
    uint32_t first = NONE, last = NONE, prev = 0;

    // Example:
    //   0000;<control>;Cc;0;BN;;;;;N;NULL;;;;
loop:
    token = YYCURSOR;
    uint32_t cp = 0;
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
    /*!re2c
        [0-9] { cp = cp * 16 + (YYCURSOR[-1] - '0');      goto cpoint; }
        [A-F] { cp = cp * 16 + (YYCURSOR[-1] - 'A' + 10); goto cpoint; }
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
    token = YYCURSOR;
    /*!re2c
        [A-Z][a-z]? { cat.assign((const char*)token, YYCURSOR - token); goto rest; }
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
    fprintf(stderr, "parsing UnicodeData.txt: error at line %lu; '%.*s'\n", line, 100, YYCURSOR);
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

    FILE* fcategories = fopen("unicode_categories.re", "wb");
    if (fcategories == nullptr) {
        fprintf(stderr, "cannot open unicode_categories.re\n");
        return 1;
    }

    fprintf(fcategories, "/*!""re2c\n");
    for (const auto& i : categories) {
        fprintf(fcategories, "%s = [", i.first.c_str());
        for (const auto& p : i.second) {
            print_char(fcategories, p.first);
            if (p.second > p.first) {
                fprintf(fcategories, "-");
                print_char(fcategories, p.second);
            }
        }
        fprintf(fcategories, "];\n");
    }
    fprintf(fcategories, "*/\n");

    fclose(fcategories);
    return 0;
}

int main() {
    gen_categories();
}
