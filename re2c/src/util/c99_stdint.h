#ifndef _RE2C_UTIL_C99_STDINT_
#define _RE2C_UTIL_C99_STDINT_

#include "config.h"

#if HAVE_STDINT_H
#    include <stdint.h>
#else // HAVE_STDINT_H

// A humble attempt to provide C99 compliant <stdint.h>
// for environments that don't have it (e.g., MSVC 2003).
//
// First, we try to define exact-width integer types. We don't
// rely on any particular environment: instead, we search for
// a type of certain width in the following list:
//     char      (C89)
//     short     (C89)
//     int       (C89)
//     long      (C89)
//     long long (C99)
//     __int64   (MSVC-specific)
// (we consider even insane possibilities for simplicity).
// The size of each type is defined by autoconf in the form
// of a macro SIZEOF_<TYPE> (set to 0 for nonexistent types).
// If we don't find a type with the required width, we typedef
// the corresponding exact-width C99 type to a nonexistent
// type name so that further compilation will fail.
//
// We define other types and constants based on exact-width
// types and C99 standard.
//
// We use SIZEOF_VOID_P to determine size of pointers.
//
// We use SIZEOF_0<SUFFIX> to find suitable 64-bit integer
// constant suffix.

typedef
#if SIZEOF_CHAR == 1
    char
#elif SIZEOF_SHORT == 1
    short
#elif SIZEOF_INT == 1
    int
#elif SIZEOF_LONG == 1
    long
#elif SIZEOF_LONG_LONG == 1
    long long
#elif SIZEOF___INT64 == 1
    __int64
#else
    nonexistent_byte1_type
#endif
byte1_type;

typedef
#if SIZEOF_CHAR == 2
    char
#elif SIZEOF_SHORT == 2
    short
#elif SIZEOF_INT == 2
    int
#elif SIZEOF_LONG == 2
    long
#elif SIZEOF_LONG_LONG == 2
    long long
#elif SIZEOF___INT64 == 2
    __int64
#else
    nonexistent_byte2_type
#endif
byte2_type;

typedef
#if SIZEOF_CHAR == 4
    char
#elif SIZEOF_SHORT == 4
    short
#elif SIZEOF_INT == 4
    int
#elif SIZEOF_LONG == 4
    long
#elif SIZEOF_LONG_LONG == 4
    long long
#elif SIZEOF___INT64 == 4
    __int64
#else
    nonexistent_byte4_type
#endif
byte4_type;

typedef
#if SIZEOF_CHAR == 8
    char
#elif SIZEOF_SHORT == 8
    short
#elif SIZEOF_INT == 8
    int
#elif SIZEOF_LONG == 8
    long
#elif SIZEOF_LONG_LONG == 8
    long long
#elif SIZEOF___INT64 == 8
    __int64
#else
    nonexistent_byte8_type
#endif
byte8_type;

// C99-7.18.1.1 Exact-width integer types
typedef          byte1_type int8_t;
typedef          byte2_type int16_t;
typedef          byte4_type int32_t;
typedef          byte8_type int64_t;
typedef unsigned byte1_type uint8_t;
typedef unsigned byte2_type uint16_t;
typedef unsigned byte4_type uint32_t;
typedef unsigned byte8_type uint64_t;

// C99-7.18.1.2 Minimum-width integer types
typedef int8_t   int_least8_t;
typedef int16_t  int_least16_t;
typedef int32_t  int_least32_t;
typedef int64_t  int_least64_t;
typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

// C99-7.18.1.3 Fastest minimum-width integer types
typedef int8_t   int_fast8_t;
typedef int16_t  int_fast16_t;
typedef int32_t  int_fast32_t;
typedef int64_t  int_fast64_t;
typedef uint8_t  uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

// C99-7.18.1.4 Integer types capable of holding object pointers
#if SIZEOF_VOID_P == 8
   typedef int64_t  intptr_t;
   typedef uint64_t uintptr_t;
#else
   typedef          int intptr_t;
   typedef unsigned int uintptr_t;
#endif

// C99-7.18.1.5 Greatest-width integer types
typedef int64_t  intmax_t;
typedef uint64_t uintmax_t;

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) // See footnote 220 at page 257 and footnote 221 at page 259

// C99-7.18.2.1 Limits of exact-width integer types
#define INT8_MIN   (-128)                 // -2^(8 - 1)
#define INT8_MAX   127                    //  2^(8 - 1) - 1
#define INT16_MIN  (-32768)               // -2^(16 - 1)
#define INT16_MAX  32767                  //  2^(16 - 1) - 1
#define INT32_MIN  (-2147483648)          // -2^(32 - 1)
#define INT32_MAX  2147483647             //  2^(32 - 1) - 1
#define INT64_MIN  (-9223372036854775808) // -2^(64 - 1)
#define INT64_MAX  9223372036854775807    //  2^(64 - 1) - 1
#define UINT8_MAX  0xFF               // 2^8 - 1
#define UINT16_MAX 0xFFFF             // 2^16 - 1
#define UINT32_MAX 0xFFFFffff         // 2^32 - 1
#define UINT64_MAX 0xFFFFffffFFFFffff // 2^64 - 1

// C99-7.18.2.2 Limits of minimum-width integer types
#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MIN  INT64_MIN
#define INT_LEAST64_MAX  INT64_MAX
#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

// C99-7.18.2.3 Limits of fastest minimum-width integer types
#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST8_MAX   INT8_MAX
#define INT_FAST16_MIN  INT16_MIN
#define INT_FAST16_MAX  INT16_MAX
#define INT_FAST32_MIN  INT32_MIN
#define INT_FAST32_MAX  INT32_MAX
#define INT_FAST64_MIN  INT64_MIN
#define INT_FAST64_MAX  INT64_MAX
#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

// C99-7.18.2.4 Limits of integer types capable of holding object pointers
#define INTPTR_MIN  (-32767) // -(2^15 - 1)
#define INTPTR_MAX  32767    // 2^15 - 1
#define UINTPTR_MAX 0xFFFF   // 2^16 - 1

// C99-7.18.2.5 Limits of greatest-width integer types
#define INTMAX_MIN  (-9223372036854775807) // -(2^63 - 1)
#define INTMAX_MAX  9223372036854775807    // 2^63 - 1
#define UINTMAX_MAX 0xFFFFffffFFFFffff     // 2^64 - 1

// C99-7.18.3 Limits of other integer types:
//     "An implementation shall define only the macros
//     corresponding to those typedef names it actually
//     provides"
// and footnote 222 at page 259:
//     "A freestanding implementation need not provide
//     all of these types."
//
// Since we don't define corresponding types, we don't
// define the following limits either:
//     PTRDIFF_MIN
//     PTRDIFF_MAX
//     SIG_ATOMIC_MIN
//     SIG_ATOMIC_MAX
//     SIZE_MAX
//     WCHAR_MIN
//     WCHAR_MAX
//     WINT_MIN
//     WINT_MAX

#endif // __STDC_LIMIT_MACROS

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) // See footnote 224 at page 260

// C99-7.18.4.1 Macros for minimum-width integer constants
#define INT8_C(x)   x
#define UINT8_C(x)  x##u
#define INT16_C(x)  x
#define UINT16_C(x) x##u
#define INT32_C(x)  x
#define UINT32_C(x) x##u
#if SIZEOF_0L == 8
#    define  INT64_C(x) x##l
#    define UINT64_C(x) x##ul
#elif SIZEOF_0LL == 8
#    define  INT64_C(x) x##ll
#    define UINT64_C(x) x##ull
#elif SIZEOF_0I8 == 8
#    define  INT64_C(x) x##i8
#    define UINT64_C(x) x##ui8
#else
#    define  INT64_C(x) x
#    define UINT64_C(x) x##u
#endif

// C99-7.18.4.2 Macros for greatest-width integer constants
#define INTMAX_C  INT64_C
#define UINTMAX_C UINT64_C

#endif // __STDC_CONSTANT_MACROS

#endif // HAVE_STDINT_H

#endif // _RE2C_UTIL_C99_STDINT_
