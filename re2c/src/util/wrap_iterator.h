#ifndef __WRAP_ITERATOR__
#define __WRAP_ITERATOR__

namespace re2c
{

template <typename container_t>
class wrap_iterator_t
{
	container_t & cont;
	typename container_t::iterator iter;
	bool wrapped;

public:
	wrap_iterator_t (container_t & c)
		: cont (c)
		, iter (cont.begin ())
		, wrapped (false)
	{}
	bool end () const
	{
		return wrapped;
	}
	wrap_iterator_t & operator ++ ()
	{
		if (++iter == cont.end ())
		{
			iter = cont.begin ();
			wrapped = true;
		}
		return * this;
	}
	typename container_t::value_type * operator -> ()
	{
		return iter.operator -> ();
	}
};

} // namespace re2c

#endif // __WRAP_ITERATOR__
