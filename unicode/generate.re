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
using Blocks = std::vector<Block>;

using Charset = std::vector<std::pair<uint32_t, uint32_t>>;
using CharsetMap = std::map<std::string, Charset>;

constexpr uint32_t NONE = ~0u;
constexpr uint32_t MAX = 0x10FFFF;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = uint8_t;
    re2c:YYCURSOR = in.cursor;
    re2c:YYMARKER = in.marker;
    re2c:tags = 1;
    re2c:tags:expression = "in.@@";

    hex = [0-9A-F]+;
    name = [A-Z][A-Za-z0-9_]*;
    comment = ([#] [^\x00\n]*)? [\n];
*/

struct Input {
    uint8_t* buffer;
    uint8_t* cursor;
    uint8_t* marker;
    /*!stags:re2c format="const uint8_t* @@;"; */

    Input()
        : buffer(nullptr)
        , cursor(nullptr)
        , marker(nullptr)
        /*!stags:re2c format=", @@(nullptr)"; */
    {}

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

static void add(Charset& cat, uint32_t first, uint32_t last) {
    if (cat.empty() || cat.back().second + 1 != first) { 
        cat.push_back(std::make_pair(first, last));
    } else {
        cat.back().second = last;
    }
}

static uint32_t parse_hex(const uint8_t* x, const uint8_t* y) {
    constexpr uint32_t translate[] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,10,11,12,13,14,15};
    uint32_t cp = 0;
    for (; x < y; ++x) cp = cp * 16 + translate[*x - '0'];
    return cp;
}

static uint32_t parse_dec(const uint8_t* x, const uint8_t* y) {
    uint32_t cp = 0;
    for (; x < y; ++x) cp = cp * 10 + (*x - '0');
    return cp;
}

static bool parse_categories(CharsetMap& categories) {
    Input in;
    if (!in.init("UnicodeData.txt")) return false;

    const uint8_t* p1, *p2, *p3, *p4, *p5, *p6;
    size_t line = 1;
    std::string cat;
    uint32_t prev = 0;

    // Format:
    //   <hex>;...;<category>;...
    //   ...
    //   <hex>;\<..., First\>;<category>;...
    //   ...
    //   <hex>;\<..., Last\>;<category>;...
    //   ...
loop:
    /*!re2c
        tail = ([;] [^;\n\x00]*)* [\n];
        cat = [A-Z][a-z]?;

        [\x00] {
            if (prev <= MAX) {
                add(categories["Cn"], prev, 0x10FFFF);
            }
            goto end;
        }
        @p1 hex @p2 ";" [^;\n\x00]+ ";" @p3 cat @p4 tail {
            uint32_t cp = parse_hex(p1, p2);
            cat.assign((const char*)p3, (const char*)p4);
            if (cp > prev) {
                add(categories["Cn"], prev, cp - 1);
            }
            add(categories[cat], cp, cp);
            prev = cp + 1;
            ++line;
            goto loop;
        }
        @p1 hex @p2 ";<" [A-Za-z0-9 -]+ ", First>;" @p3 cat @p4 tail
        @p5 hex @p6 ";<" [A-Za-z0-9 -]+ ", Last>;"      cat     tail {
            uint32_t first = parse_hex(p1, p2);
            uint32_t last = parse_hex(p5, p6);
            cat.assign((const char*)p3, (const char*)p4);
            if (first > prev) {
                add(categories["Cn"], prev, first - 1);
            }
            add(categories[cat], first, last);
            prev = last + 1;
            line += 2;
            goto loop;
        }
        * {
            fprintf(stderr, "parsing UnicodeData.txt: error at line %lu; '%.*s'\n",
                line, 100, in.cursor);
            return false;
        }
    */
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

    Charset tmp;
    for (const auto& i : derived_categories) {
        for (const std::string& s : i.second) {
            Charset& c = categories[s];
            tmp.insert(tmp.end(), c.begin(), c.end());
        }
        std::sort(tmp.begin(), tmp.end());

        Charset& c = categories[i.first];
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

static bool gen_include_file_charsets(const CharsetMap& charsets, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (f == nullptr) {
        fprintf(stderr, "cannot open %s\n", filename);
        return false;
    }

    fprintf(f, "/*!""re2c\n");
    for (const auto& i : charsets) {
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

static bool gen_tests_categories(const CharsetMap& categories) {
    const std::array<std::string, 3> encodings = {"8", "x", "u"};
    for (const std::string& encoding : encodings) {
        uint32_t max_cunits_per_cpoint = encoding == "8" ? 6 : encoding == "x" ? 2 : 1;
        uint32_t bits = encoding == "8" ? 8 : encoding == "x" ? 16 : 32;
        for (const auto& i: categories) {
            const char* cat = i.first.c_str();
            std::string fname = "unicode_group_" + i.first + "_" + encoding + ".re";
            FILE* f = fopen(fname.c_str(), "wb");
            if (f == nullptr) {
                fprintf(stderr, "cannot open %s\n", fname.c_str());
                return false;
            }
            fprintf(f, "// re2c $INPUT -o $OUTPUT -%s\n", encoding.c_str());
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
    return true;
}

static bool parse_blocks(Blocks& blocks) {
    Input in;
    if (!in.init("Blocks.txt")) return false;

    const uint8_t* p1, *p2, *p3, *p4, *p5, *p6;
    size_t line = 1;
    std::string block;

    // Format:
    //   # ...
    //   <hex>..<hex>; <name>
    //   ...
loop:
    /*!re2c
        "# EOF\n" [\x00] {
            return true;
        }
        comment {
            ++line;
            goto loop;
        }
        @p1 hex @p2 ".." @p3 hex @p4 "; " @p5 [A-Z][A-Za-z0-9_ -]* @p6 [\n] {
            uint32_t first = parse_hex(p1, p2);
            uint32_t last = parse_hex(p3, p4);
            block.assign((const char*)p5, (const char*)p6);
            for (size_t i = 0; i < block.size(); ++i) {
                if (!isdigit(block[i]) && !isalpha(block[i])) {
                    block[i] = '_';
                }
            }
            blocks.push_back({block, first, last});
            ++line;
            goto loop;
        }
        * {
            fprintf(stderr, "parsing Blocks.txt: error at line %lu; '%.*s'\n",
                line, 100, in.cursor);
            return false;
        }
    */
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

static bool parse_properties(CharsetMap& properties, std::map<std::string, uint32_t>& counts) {
    Input in;
    if (!in.init("PropList.txt")) return false;

    const uint8_t* p1, *p2, *p3, *p4, *p5, *p6;
    size_t line = 1;
    std::string name;

    // Format:
    //   # ...
    //   <hex>[..<hex>] ; <name> [# ... ]
    //   ...
    //   # Total code points: <decimal>
    //   ...
loop:
    /*!re2c
        "# EOF\n" [\x00] {
            return true;
        }
        "# Total code points: " @p1 [0-9]+ @p2 [\n] {
            counts[name] += parse_dec(p1, p2);
            ++line;
            goto loop;
        }
        comment {
            ++line;
            goto loop;
        }
        @p1 hex @p2 (".." @p3 hex @p4)? [ ]* "; " @p5 name @p6 [ ]? comment {
            uint32_t first = parse_hex(p1, p2);
            uint32_t last = p3 ? parse_hex(p3, p4) : first;
            name.assign((const char*)p5, (const char*)p6);
            add(properties[name], first, last);
            ++line;
            goto loop;
        }
        * {
            fprintf(stderr, "parsing PropList.txt: error at line %lu; '%.*s'\n", line, 100,
                in.cursor);
            return false;
        }
    */
}

static bool parse_derived_properties(
        CharsetMap& properties, std::map<std::string, uint32_t>& counts) {
    Input in;
    if (!in.init("DerivedCoreProperties.txt")) return false;

    const uint8_t* p1, *p2, *p3, *p4;
    size_t line = 1;
    std::string name;

    // Format:
    //   # ...
    //   # Derived Property: <name>
    //   <hex>[..<hex]] ; ...
    //   ...
    //   # Total code points: <decimal>
    //   ...
loop:
    /*!re2c
        "# EOF\n" [\x00] {
            goto end;
        }
        "# Derived Property:" [ ]+ @p1 name @p2 ([ ]+ [(][A-Za-z0-9_]+[)])? [\n] {
            ++line;
            name.assign((const char*)p1, (const char*)p2);
            goto loop;
        }
        "# Total code points: " @p1 [0-9]+ @p2 [\n] {
            counts[name] += parse_dec(p1, p2);
            ++line;
            goto loop;
        }
        comment {
            ++line;
            goto loop;
        }
        @p1 hex @p2 (".." @p3 hex @p4)? [ ]* [;] [^\x00\n]* [\n] {
            uint32_t first = parse_hex(p1, p2);
            uint32_t last = p3 ? parse_hex(p3, p4) : first;
            add(properties[name], first, last);
            ++line;
            goto loop;
        }
        * {
            fprintf(stderr, "parsing DerivedCoreProperties.txt: error at line %lu; '%.*s'\n",
                line, 100, in.cursor);
            return false;
        }
    */
end:
    if (properties.size() != counts.size()) {
        fprintf(stderr, "properties and count maps have different size: %lu vs %lu\n",
            properties.size(), counts.size());
        return false;
    }
    for (const auto& i: properties) {
        uint32_t count = 0;
        for (const auto& p: i.second) {
            count += p.second - p.first + 1;
        }
        auto j = counts.find(i.first);
        if (j == counts.end() || j->second != count) {
            fprintf(stderr, "wrong code point count for property '%s': expected %u, have %u\n",
                name.c_str(), j->second, count);
            return false;
        }
    }
    return true;
}

int main() {
    CharsetMap categories;
    if (!parse_categories(categories)) return 1;
    if (!gen_include_file_charsets(categories, "unicode_categories.re")) return 1;
    if (!gen_tests_categories(categories)) return 1;

    Blocks blocks;
    if (!parse_blocks(blocks)) return 1;
    if (!gen_include_file_blocks(blocks)) return 1;
    if (!gen_tests_blocks(blocks)) return 1;

    CharsetMap properties;
    std::map<std::string, uint32_t> counts;
    if (!parse_properties(properties, counts)) return 1;
    if (!parse_derived_properties(properties, counts)) return 1;
    if (!gen_include_file_charsets(properties, "unicode_properties.re")) return 1;
}
