#ifndef __ALLOCATE__
#define __ALLOCATE__

namespace re2c {

// useful fof allocation of arrays of POD objects
// 'new []' invokes default constructor for each object
// this can be unacceptable for performance reasons
template <typename T> T * allocate (size_t n)
{
	void * p = operator new (n * sizeof (T));
	return static_cast<T *> (p);
}

} // namespace re2c

#endif // __ALLOCATE__
