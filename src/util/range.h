#ifndef _RE2C_UTIL_RANGE_
#define _RE2C_UTIL_RANGE_

#include <stddef.h>
#include <stdint.h>

#include "src/test/range/test.h"
#include "src/util/allocator.h"
#include "src/util/forbid_copy.h"

namespace re2c {

class Range {
  private:
    Range* nx;
    // [lb,ub)
    uint32_t lb;
    uint32_t ub;

  public:
    Range* next() const { return nx; }
    uint32_t lower() const { return lb; }
    uint32_t upper() const { return ub; }

  private:
    friend class RangeMgr;

    // not default-cconstructible or copy-constructible
    Range();
    FORBID_COPY(Range);
};

class RangeMgr {
  private:
    IrAllocator& alc;

  public:
    explicit RangeMgr(IrAllocator& alc): alc(alc) {}
    Range* sym(uint32_t c);
    Range* ran(uint32_t l, uint32_t u);
    Range* add(const Range* r1, const Range* r2);
    Range* sub(const Range* r1, const Range* r2);

  private:
    Range* make(Range* n, uint32_t l, uint32_t u);
    void append_overlapping(Range*& head, Range*& tail, const Range* r);
    void append(Range**& ptail, uint32_t l, uint32_t u);

    template<uint8_t> friend Range* re2c_test::range(RangeMgr& rm, uint32_t n);
};

inline Range* RangeMgr::make(Range* n, uint32_t l, uint32_t u) {
    Range* r = alc.alloct<Range>(1);
    r->nx = n;
    r->lb = l;
    r->ub = u;
    return r;
}

inline Range* RangeMgr::sym(uint32_t c) {
    return make(nullptr, c, c + 1);
}

inline Range* RangeMgr::ran(uint32_t l, uint32_t u) {
    return make(nullptr, l, u);
}

} // namespace re2c

#endif // _RE2C_UTIL_RANGE_
