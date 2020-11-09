#ifndef _RE2C_SKELETON_SKELETON_
#define _RE2C_SKELETON_SKELETON_

#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <valarray>
#include <vector>

#include "src/codegen/code.h"
#include "src/msg/location.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/skeleton/mtag_trie.h"
#include "src/util/allocate.h"
#include "src/util/forbid_copy.h"
#include "src/util/local_increment.h"
#include "src/util/fixed_allocator.h"


namespace re2c {

class path_t;
struct DFA;
struct dfa_state_t;
struct dfa_t;
class Msg;
class bitmaps_t;
struct opt_t;
struct tcmd_t;

struct OutBuf {
    FILE *file;
    size_t size;
    union {
        membuf_t<uint8_t>  buf8;
        membuf_t<uint16_t> buf16;
        membuf_t<uint32_t> buf32;
        membuf_t<uint64_t> buf64;
    };

    void init(size_t selector);
    void free(size_t selector);
    template<typename T> membuf_t<T>& select();
    template<typename T> T* alloc(size_t n);
    template<typename T> void flush();
};

template<> inline membuf_t<uint8_t>&  OutBuf::select() { return buf8;  }
template<> inline membuf_t<uint16_t>& OutBuf::select() { return buf16; }
template<> inline membuf_t<uint32_t>& OutBuf::select() { return buf32; }
template<> inline membuf_t<uint64_t>& OutBuf::select() { return buf64; }

inline void OutBuf::init(size_t selector)
{
    static const size_t KB = 1024 * 1024;
    switch (selector) {
        case 1: init_membuf(buf8, KB);  break;
        case 2: init_membuf(buf16, KB); break;
        case 4: init_membuf(buf32, KB); break;
        case 8: init_membuf(buf64, KB); break;
        default: DASSERT(false);
    }
    size = 0;
    file = NULL;
}

inline void OutBuf::free(size_t selector)
{
    switch (selector) {
        case 1: free_membuf(buf8);  break;
        case 2: free_membuf(buf16); break;
        case 4: free_membuf(buf32); break;
        case 8: free_membuf(buf64); break;
        default: DASSERT(false);
    }
    size = 0;
}

template<typename T> inline void OutBuf::flush()
{
    membuf_t<T> &buf = select<T>();
    fwrite(buf.ptr, sizeof(T), size, file);
    size = 0;
}

template<typename T> inline T* OutBuf::alloc(size_t n)
{
    membuf_t<T> &buf = select<T>();

    if (size + n >= buf.size) {
        flush<T>();
        grow_membuf(buf, n);
        size = 0;
    }

    T *ptr = buf.ptr + size;
    size += n;

    return ptr;
}

typedef local_increment_t<uint8_t> local_inc;

struct Node
{
    struct range_t {
        uint32_t lower;
        uint32_t upper;
        const tcmd_t *cmd;
        range_t *next;
    };

    typedef std::map<size_t, range_t*> arcs_t;
    typedef fixed_allocator_t<Node::range_t> range_allocator_t;

    arcs_t arcs;
    size_t rule;
    const tcmd_t *cmd;
    const tcmd_t *stacmd;

    Node();
    void init(const dfa_state_t *s, const std::vector<uint32_t> &charset,
        size_t nil, range_allocator_t &allocator);
    bool end() const;

    FORBID_COPY(Node);
};

struct Skeleton
{
    static const uint32_t DEFTAG;

    const opt_t *opts;
    const std::string name;
    const std::string cond;
    const loc_t loc;
    Msg &msg;

    Node::range_allocator_t range_allocator;

    const size_t nodes_count;
    Node *nodes;
    const tcmd_t *cmd0;

    size_t sizeof_key;
    size_t def_rule;
    size_t eof_rule;
    size_t ntagver;
    const std::vector<uint32_t> &charset;
    const std::valarray<Rule> &rules;
    const std::vector<Tag> &tags;
    const tagver_t *finvers;

    uint32_t *tagvals;
    mtag_trie_t tagtrie;
    std::vector<uint32_t> mtagval;
    membuf_t<const Node::range_t*> arc_iters;
    membuf_t<size_t> char_iters;
    OutBuf buf_data;
    OutBuf buf_keys;

    Skeleton(const dfa_t &dfa, const opt_t *opts, const std::string &name,
        const std::string &cond, const loc_t &loc, Msg &msg);
    ~Skeleton ();
    FORBID_COPY(Skeleton);
};

template<typename key_t> key_t rule2key(size_t r, size_t def)
{
    if (r == Rule::NONE) {
        return std::numeric_limits<key_t>::max();
    } else if (r == def) {
        key_t k = std::numeric_limits<key_t>::max();
        return --k;
    } else {
        return static_cast<key_t>(r);
    }
}

uint64_t rule2key(size_t rule, size_t key, size_t def);
uint32_t maxpath(const Skeleton &skel);
void warn_undefined_control_flow(const Skeleton &skel);
void fprint_default_path(FILE *f, const Skeleton &skel, const path_t &p);
void emit_data(Skeleton &skel);
Code *emit_skeleton_prolog(Output &output);
Code *emit_skeleton_epilog(Output &output);
void emit_skeleton(Output &output, CodeList *code, DFA &dfa);
void emit_skeleton_action(Output &output, CodeList *code, const DFA &dfa, size_t rid);

} // namespace re2c

#endif // _RE2C_SKELETON_SKELETON_
