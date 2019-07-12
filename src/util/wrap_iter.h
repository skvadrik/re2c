#ifndef _RE2C_UTIL_WRAP_ITER_
#define _RE2C_UTIL_WRAP_ITER_


namespace re2c {

// immutable containter
template<typename container_t>
class wrap_citer_t
{
    typedef typename container_t::const_iterator citer_t;
    typedef const typename container_t::value_type* cpval_t;

    const citer_t beg;
    const citer_t end;
    citer_t cur;

public:
    explicit wrap_citer_t(const container_t &c): beg(c.begin()), end(c.end()), cur(beg) {}
    wrap_citer_t& operator++() { if (++cur == end) cur = beg; return *this; }
    cpval_t operator->() const { return cur.operator->(); }
};

} // namespace re2c

#endif // _RE2C_UTIL_WRAP_ITER_
