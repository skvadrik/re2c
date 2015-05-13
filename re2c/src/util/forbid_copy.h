#ifndef __FORBID_COPY__
#define __FORBID_COPY__

// must be used at the end of class definition
// (since this macro changes scope to private)
#define FORBID_COPY(type) \
	private: \
		type (const type &); \
		type & operator = (const type &)

#endif // __FORBID_COPY__
