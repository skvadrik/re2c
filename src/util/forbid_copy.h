#ifndef _RE2C_UTIL_FORBID_COPY_
#define _RE2C_UTIL_FORBID_COPY_

#define FORBID_COPY(type) \
    type(const type &) = delete; \
    type& operator=(const type&) = delete

#endif // _RE2C_UTIL_FORBID_COPY_
