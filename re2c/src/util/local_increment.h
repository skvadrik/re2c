#ifndef __LOCAL_INCREMENT__
#define __LOCAL_INCREMENT__

namespace re2c
{

template <typename counter_t>
struct local_increment_t
{
	counter_t & counter;
	inline explicit local_increment_t (counter_t & c)
		: counter (++c)
	{}
	inline ~local_increment_t ()
	{
		--counter;
	}
};

} // namespace re2c

#endif // __LOCAL_INCREMENT__
