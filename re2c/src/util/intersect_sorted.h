#ifndef _RE2C_UTIL_INTERSECT_SORTED_
#define _RE2C_UTIL_INTERSECT_SORTED_

namespace re2c {

// test intersection of two sorted ranges
template<class InputIterator1, class InputIterator2>
bool intersect_sorted(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	for (;first1 != last1 && first2 != last2;) {
		if (*first2 < *first1) {
			++first2;
		} else if (*first1 < *first2) {
			++first1;
		} else {
			return true;
		}
	}
	return false;
}

} // namespace re2c

#endif // _RE2C_UTIL_INTERSECT_

