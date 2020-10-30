#ifndef _RE2C_UTIL_WRAP_ITER_
#define _RE2C_UTIL_WRAP_ITER_


namespace re2c {

// immutable containter
template<typename container_t>
class wrap_citer_t
{
    typedef typename container_t::const_iterator citer_t;
    typedef const typename container_t::value_type* cpval_t;

    citer_t beg;
    citer_t end;
    citer_t cur;

public:
    wrap_citer_t(): beg(), end(), cur() {}

    explicit wrap_citer_t(const container_t &c)
        : beg(c.begin())
        , end(c.end())
        , cur(beg)
    {}

    wrap_citer_t(const wrap_citer_t &w)
        : beg(w.beg)
        , end(w.end)
        , cur(w.cur)
    {}

    wrap_citer_t& operator=(const wrap_citer_t &w)
    {
        new (this) wrap_citer_t<container_t>(w);
        return *this;
    }

    wrap_citer_t& operator++()
    {
        if (++cur == end) cur = beg;
        return *this;
    }

    cpval_t operator->() const
    {
        return cur.operator->();
    }
};

} // namespace re2c

#endif // _RE2C_UTIL_WRAP_ITER_
