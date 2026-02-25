#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <array>
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

static bool parse_categories(CatMap& categories) {
    Input in;
    if (!in.init("UnicodeData.txt")) return false;

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
    return false;

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

    return true;
}

static bool gen_include_file_categories(const CatMap& categories) {
    FILE* f = fopen("unicode_categories.re", "wb");
    if (f == nullptr) {
        fprintf(stderr, "cannot open unicode_categories.re\n");
        return false;
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
    return true;
}

static bool gen_tests_categories(const CatMap& categories) {
    const std::array<std::string, 3> encodings = {"8", "x", "u"};
    const std::array<std::string, 3> policies = {"ignore", "substitute", "fail"};
    for (const std::string& encoding : encodings) {
        uint32_t max_cunits_per_cpoint = encoding == "8" ? 6 : encoding == "x" ? 2 : 1;
        uint32_t bits = encoding == "8" ? 8 : encoding == "x" ? 16 : 32;
        for (const std::string& policy : policies) {
            for (const auto& i: categories) {
                const char* cat = i.first.c_str();
                std::string fname = "unicode_group_" + i.first + "_" + encoding + "_encoding_policy_" + policy + ".re";
                FILE* f = fopen(fname.c_str(), "wb");
                if (f == nullptr) {
                    fprintf(stderr, "cannot open %s\n", fname.c_str());
                    return false;
                }
                fprintf(f, "// re2c $INPUT -o $OUTPUT -%s --encoding-policy %s\n", encoding.c_str(), policy.c_str());
                fprintf(f, "#include <stdint.h>\n");
                fprintf(f, "#include <stdio.h>\n");
                if (encoding == "8") {
                    fprintf(f, "#include \"utf8.h\"\n");
                    fprintf(f, "#define YYCTYPE uint8_t\n");
                } else if (encoding == "x") {
                    fprintf(f, "#include \"utf16.h\"\n");
                    fprintf(f, "#define YYCTYPE uint16_t\n");
                } else if (encoding == "u") {
                    fprintf(f, "#define YYCTYPE uint32_t\n");
                }
                fprintf(f, "\n");
                fprintf(f, "bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {\n");
                fprintf(f, "\t__attribute__((unused)) const YYCTYPE* YYMARKER;\n");
                fprintf(f, "#define YYCURSOR start\n");
                fprintf(f, "%s:\n", cat);
                fprintf(f, "/*""!re2c\n");
                fprintf(f, "\tre2c:yyfill:enable = 0;\n");
                fprintf(f, "\t%s = [", cat);
                for (const auto& p : i.second) {
                    print_char(f, p.first);
                    if (p.second > p.first) {
                        fprintf(f, "-");
                        print_char(f, p.second);
                    }
                }
                fprintf(f, "];\n");
                fprintf(f, "\t\t%s { goto %s; }\n", cat, cat);
                fprintf(f, "\t\t* { return YYCURSOR - 1 == limit; }\n");
                fprintf(f, "\t*/\n");
                fprintf(f, "}\n");
                fprintf(f, "\n");
                fprintf(f, "static const uint32_t chars_%s[] = {", cat);
                for (const auto& p : i.second) {
                    fprintf(f, "0x%x,0x%x,", p.first, p.second);
                }
                fprintf(f, "};\n");
                fprintf(f, "\n");

                uint32_t cat_size = 0;
                for (const auto& p : i.second) cat_size += p.second - p.first + 1;

                uint32_t outer = 0;
                for (const auto& p : i.second) {
                    if (outer < p.first) break;
                    outer = p.second + 1;
                }

                if (encoding == "8") {
                    fprintf(f, "static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {\n");
                    fprintf(f, "\tuint8_t* const s0 = s;\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < ranges_count; i += 2)\n");
                    fprintf(f, "\t\tfor (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) s[i] = %u;\n", max_cunits_per_cpoint, outer);
                    fprintf(f, "\treturn s - s0;\n");
                    fprintf(f, "}\n");
                } else if (encoding == "x") {
                    fprintf(f, "static uint32_t encode_utf16(const uint32_t* ranges, uint32_t ranges_count, uint16_t* s) {\n");
                    fprintf(f, "\tuint16_t* const s0 = s;\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < ranges_count; i += 2)\n");
                    fprintf(f, "\t\tfor (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j)\n");
                    fprintf(f, "\t\t\tif (j <= re2c::utf16::MAX_1WORD_RUNE) {\n");
                    fprintf(f, "\t\t\t\t*s++ = j;\n");
                    fprintf(f, "\t\t\t} else {\n");
                    fprintf(f, "\t\t\t\t*s++ = re2c::utf16::lead_surr(j);\n");
                    fprintf(f, "\t\t\t\t*s++ = re2c::utf16::trail_surr(j);\n");
                    fprintf(f, "\t\t\t}\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) s[i] = %u;\n", max_cunits_per_cpoint, outer);
                    fprintf(f, "\treturn s - s0;\n");
                    fprintf(f, "}\n");
                } else if (encoding == "u") {
                    fprintf(f, "static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {\n");
                    fprintf(f, "\tuint32_t* const s0 = s;\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < ranges_count; i += 2)\n");
                    fprintf(f, "\t\tfor (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;\n");
                    fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) s[i] = %u;\n", max_cunits_per_cpoint, outer);
                    fprintf(f, "\treturn s - s0;\n");
                    fprintf(f, "}\n");
                }
                fprintf(f, "\n");
                fprintf(f, "int main() {\n");
                fprintf(f, "\tYYCTYPE* buffer_%s = new YYCTYPE[%u];\n", cat, (cat_size + 1) * max_cunits_per_cpoint);
                fprintf(f, "\tuint32_t buffer_%s_len = encode_utf%d(chars_%s, sizeof(chars_%s) / sizeof(uint32_t), buffer_%s);\n", cat, bits, cat, cat, cat);
                fprintf(f, "\tif (!scan(buffer_%s, buffer_%s + buffer_%s_len)) printf(\"test '%s' failed\\n\");\n", cat, cat, cat, cat);
                fprintf(f, "\tdelete[] buffer_%s;\n", cat);
                fprintf(f, "\treturn 0;\n");
                fprintf(f, "}\n");

                fclose(f);
            }
        }
    }
    return true;
}

static bool parse_blocks(Blocks& blocks) {
    Input in;
    if (!in.init("Blocks.txt")) return false;

    const uint8_t* token;
    size_t line = 0;
    std::string block;
    uint32_t first = NONE, last = NONE;

    // Example:
    //   # comments
    //   0000..007F; Basic Latin
loop:
    /*!re2c
        "# EOF\n" [\x00] { goto end; }
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
    return false;
end:
    return true;
}

static void print_block_defs(FILE* f, const Blocks& blocks) {
    fprintf(f, "/*!""re2c\n");
    for (const Block& b : blocks) {
        fprintf(f, "%s = [", b.name.c_str());
        print_char(f, b.first);
        fprintf(f, "-");
        print_char(f, b.last);
        fprintf(f, "];\n");
    }
    fprintf(f, "*/\n");
}

static bool gen_include_file_blocks(const Blocks& blocks) {
    FILE* f = fopen("unicode_blocks.re", "wb");
    if (f == nullptr) {
        fprintf(stderr, "cannot open unicode_blocks.re\n");
        return false;
    }
    print_block_defs(f, blocks);
    fclose(f);
    return true;
}

static bool gen_tests_blocks(const Blocks& blocks) {
    const std::array<std::string, 3> encodings = {"8", "x", "u"};
    const std::array<std::string, 3> policies = {"ignore", "substitute", "fail"};
    for (const std::string& encoding : encodings) {
        uint32_t max_cunits_per_cpoint = encoding == "8" ? 6 : encoding == "x" ? 2 : 1;
        uint32_t bits = encoding == "8" ? 8 : encoding == "x" ? 16 : 32;
        for (const std::string& policy : policies) {
            std::string fname = "unicode_blocks_" + encoding + "_encoding_policy_" + policy + ".re";
            FILE* f = fopen(fname.c_str(), "wb");
            if (f == nullptr) {
                fprintf(stderr, "cannot open %s\n", fname.c_str());
                return false;
            }
            fprintf(f, "// re2c $INPUT -o $OUTPUT -%s --encoding-policy %s\n", encoding.c_str(), policy.c_str());
            fprintf(f, "#include <stdint.h>\n");
            fprintf(f, "#include <stdio.h>\n");
            if (encoding == "8") {
                fprintf(f, "#include \"utf8.h\"\n");
                fprintf(f, "#define YYCTYPE uint8_t\n");
            } else if (encoding == "x") {
                fprintf(f, "#include \"utf16.h\"\n");
                fprintf(f, "#define YYCTYPE uint16_t\n");
            } else if (encoding == "u") {
                fprintf(f, "#define YYCTYPE uint32_t\n");
            }
            fprintf(f, "\n");
            fprintf(f, "enum Block {\n");
            for (const Block& b : blocks) {
                fprintf(f, "\t%s,\n", b.name.c_str());
            }
            fprintf(f, "\tError\n");
            fprintf(f, "};\n");
            fprintf(f, "\n");
            fprintf(f, "Block scan(const YYCTYPE* start, const YYCTYPE* const limit, Block blk) {\n");
            fprintf(f, "\t__attribute__((unused)) const YYCTYPE* YYMARKER;\n");
            fprintf(f, "#define YYCURSOR start\n");
            fprintf(f, "\tswitch (blk) {\n");
            for (const Block& b : blocks) {
                fprintf(f, "\t\tcase %s: goto %s;\n", b.name.c_str(), b.name.c_str());
            }
            fprintf(f, "\t\tdefault: return Error;\n");
            fprintf(f, "\t}\n");
            print_block_defs(f, blocks);
            for (const Block& b : blocks) {
                const char *s = b.name.c_str();
                fprintf(f, "%s:\n", s);
                fprintf(f, "\t/*""!re2c\n");
                fprintf(f, "\t\tre2c:yyfill:enable = 0;\n");
                fprintf(f, "\t\t%s { goto %s; }\n", s, s);
                fprintf(f, "\t\t* { if (YYCURSOR - 1 == limit) return %s; else return Error; }\n", s);
                fprintf(f, "\t*/\n");
            }
            fprintf(f, "}\n");
            fprintf(f, "\n");
            for (const Block& b : blocks) {
                fprintf(f, "static const uint32_t chars_%s[] = {0x%x,0x%x};\n", b.name.c_str(), b.first, b.last);
            }
            fprintf(f, "\n");
            if (encoding == "8") {
                fprintf(f, "static uint32_t encode_utf8(uint32_t first, uint32_t last, uint8_t* s) {\n");
                fprintf(f, "\tuint8_t* const s0 = s;\n");
                fprintf(f, "\tfor (uint32_t i = first; i <= last; ++i) s += re2c::utf8::rune_to_bytes(s, i);\n");
                fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) *s++ = (first == 0) ? 0xFF : 0;\n", max_cunits_per_cpoint);
                fprintf(f, "\treturn s - s0;\n");
                fprintf(f, "}\n");
            } else if (encoding == "x") {
                fprintf(f, "static uint32_t encode_utf16(uint32_t first, uint32_t last, uint16_t* s) {\n");
                fprintf(f, "\tuint16_t* const s0 = s;\n");
                fprintf(f, "\tfor (uint32_t i = first; i <= last; ++i) {\n");
                fprintf(f, "\t\tif (i <= re2c::utf16::MAX_1WORD_RUNE) {\n");
                fprintf(f, "\t\t\t*s++ = i;\n");
                fprintf(f, "\t\t} else {\n");
                fprintf(f, "\t\t\t*s++ = re2c::utf16::lead_surr(i);\n");
                fprintf(f, "\t\t\t*s++ = re2c::utf16::trail_surr(i);\n");
                fprintf(f, "\t\t}\n");
                fprintf(f, "\t}\n");
                fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) *s++ = (first == 0) ? 0xFFFF : 0;\n", max_cunits_per_cpoint);
                fprintf(f, "\treturn s - s0;\n");
                fprintf(f, "}\n");
            } else if (encoding == "u") {
                fprintf(f, "static uint32_t encode_utf32(uint32_t first, uint32_t last, uint32_t* s) {\n");
                fprintf(f, "\tuint32_t* const s0 = s;\n");
                fprintf(f, "\tfor (uint32_t i = first; i <= last; ++i) *s++ = i;\n");
                fprintf(f, "\tfor (uint32_t i = 0; i < %u; ++i) *s++ = (first == 0) ? 0xFFFFffff : 0;\n", max_cunits_per_cpoint);
                fprintf(f, "\treturn s - s0;\n");
                fprintf(f, "}\n");
            }
            fprintf(f, "\n");
            fprintf(f, "int main() {\n");
            for (const Block& b : blocks) {
                const char *s = b.name.c_str();
                fprintf(f, "\tYYCTYPE *buffer_%s = new YYCTYPE[%u];\n", s, (b.last - b.first + 1) * max_cunits_per_cpoint + max_cunits_per_cpoint);
                fprintf(f, "\tuint32_t buffer_%s_len = encode_utf%d(chars_%s[0], chars_%s[1], buffer_%s) - %u;\n", s, bits, s, s, s, max_cunits_per_cpoint);
                fprintf(f, "\tif (scan(buffer_%s, buffer_%s + buffer_%s_len, %s) != %s)\n", s, s, s, s, s);
                fprintf(f, "\t\tprintf(\"test '%s' failed\\n\");\n", s);
                fprintf(f, "\tdelete[] buffer_%s;\n", s);
                fprintf(f, "\n");
            }
            fprintf(f, "\treturn 0;\n");
            fprintf(f, "}\n");
            fclose(f);
        }
    }
    return true;
}

int main() {
    CatMap categories;
    if (!parse_categories(categories)) return 1;
    if (!gen_include_file_categories(categories)) return 1;
    if (!gen_tests_categories(categories)) return 1;

    Blocks blocks;
    if (!parse_blocks(blocks)) return 1;
    if (!gen_include_file_blocks(blocks)) return 1;
    if (!gen_tests_blocks(blocks)) return 1;
}
