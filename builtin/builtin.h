/* Builtins and Intrinsics
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Some of these implementations are based on code from
 * https://graphics.stanford.edu/~seander/bithacks.html which is also
 * public domain (and a fantastic web site).
 */

#if !defined(PSNIP_BUILTIN_H)
#define PSNIP_BUILTIN_H

#if defined(HEDLEY_GCC_HAS_BUILTIN)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) HEDLEY_GCC_HAS_BUILTIN(builtin,major,minor,0)
#elif defined(__clang__) && defined(__has_builtin)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) __has_builtin(builtin)
#elif defined(__GNUC__)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (__GNUC__ > major || (major == __GNUC__ && __GNUC_MINOR__ >= minor))
#else
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (0)
#endif

#if defined(HEDLEY_CLANG_HAS_BUILTIN)
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) HEDLEY_CLANG_HAS_BUILTIN(builtin)
#elif defined(__has_builtin)
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define PSNIP_BUILTIN_CLANG_HAS_BUILTIN(builtin) (0)
#endif

#if defined(HEDLEY_MSVC_VERSION_CHECK)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) HEDLEY_MSVC_VERSION_CHECK(major,minor,0)
#elif !defined(_MSC_VER)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 100000) + (minor * 1000)))
#else
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(_MSC_VER)
#  include <intrin.h>
#endif

#if defined(__i386) || defined(_M_IX86) || \
  defined(__amd64) || defined(_M_AMD64) || defined(__x86_64)
#  if defined(_MSC_VER)
#    define PSNIP_BUILTIN__ENABLE_X86
#  elif defined(__GNUC__)
#    define PSNIP_BUILTIN__ENABLE_X86
#    include <x86intrin.h>
#  endif
#endif

#if defined(__amd64) || defined(_M_AMD64) || defined(__x86_64)
#  if defined(_MSC_VER)
#    define PSNIP_BUILTIN__ENABLE_AMD64
#  elif defined(__GNUC__)
#    define PSNIP_BUILTIN__ENABLE_AMD64
#    include <x86intrin.h>
#  endif
#endif

#if \
  !defined(psnip_int64_t) || !defined(psnip_uint64_t) || \
  !defined(psnip_int32_t) || !defined(psnip_uint32_t) || \
  !defined(psnip_int16_t) || !defined(psnip_uint16_t)
#  include "../exact-int/exact-int.h"
#endif

#if defined(HEDLEY_LIKELY) && defined(HEDLEY_UNLIKELY)
#  define PSNIP_BUILTIN_LIKELY(expr) HEDLEY_LIKELY(expr)
#  define PSNIP_BUILTIN_UNLIKELY(expr) HEDLEY_UNLIKELY(expr)
#elif PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_expect,3,0)
#  define PSNIP_BUILTIN_LIKELY(expr) __builtin_expect(!!(expr), 1)
#  define PSNIP_BUILTIN_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#  define PSNIP_BUILTIN_LIKELY(expr) (!!(expr))
#  define PSNIP_BUILTIN_UNLIKELY(expr) (!!(expr))
#endif

#if !defined(PSNIP_BUILTIN_STATIC_INLINE)
#  if defined(HEDLEY_INLINE)
#    define PSNIP_BUILTIN_STATIC_INLINE static HEDLEY_INLINE
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define PSNIP_BUILTIN_STATIC_INLINE static inline
#  elif defined(__GNUC_STDC_INLINE__)
#    define PSNIP_BUILTIN_STATIC_INLINE static __inline__
#  elif defined(_MSC_VER) && _MSC_VER >= 1200
#    define PSNIP_BUILTIN_STATIC_INLINE static __inline
#  else
#    define PSNIP_BUILTIN_STATIC_INLINE static
#  endif
#endif

/* Many GCC-style builtins exist for int, long, and long long
   variants, but *not* for exact sizes.  This tries to determine the
   connect mapping of exact-width sizes to builtin suffixes ("", "l",
   "ll") so we can provide 32- and 64-bit variants. */

#include <limits.h>

#define PSNIP_BUILTIN__CONCAT(a,b) a##b
#define PSNIP_BUILTIN__GEN_NAME(name,suffix) psnip_builtin_##name##suffix

/* Clang has some builtins that have "s" and "b" suffixes for short
   and byte (?). */

#if CHAR_MIN == (-127-1) && INT_MAX == 127
#  define PSNIP_BUILTIN__CHAR_SIZE 8
#  define PSNIP_BUILTIN__VARIANT2_8(name) PSNIP_BUILTIN__GEN_NAME(name,b)
#elif SHRT_MIN == (-127-1) && INT_MAX == 127
#  define PSNIP_BUILTIN__SHORT_SIZE 8
#  define PSNIP_BUILTIN__VARIANT2_8(name) PSNIP_BUILTIN__GEN_NAME(name,s)
#elif INT_MIN == (-127-1) && INT_MAX == 127
#  define PSNIP_BUILTIN__INT_SIZE 8
#  define PSNIP_BUILTIN__VARIANT2_8(name) PSNIP_BUILTIN__GEN_NAME(name,)
#elif LONG_MIN == (-127-1) && LONG_MAX == 127
#  define PSNIP_BUILTIN__LONG_SIZE 8
#  define PSNIP_BUILTIN__VARIANT2_8(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#elif LLONG_MIN == (-127-1) && LLONG_MAX == 127
#  define PSNIP_BUILTIN__LLONG_SIZE 8
#  define PSNIP_BUILTIN__VARIANT2_8(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#endif

#if CHAR_MIN == (-32767-1) && INT_MAX == 32767
#  define PSNIP_BUILTIN__CHAR_SIZE 16
#  define PSNIP_BUILTIN__VARIANT2_16(name) PSNIP_BUILTIN__GEN_NAME(name,b)
#elif SHRT_MIN == (-32767-1) && INT_MAX == 32767
#  define PSNIP_BUILTIN__SHORT_SIZE 16
#  define PSNIP_BUILTIN__VARIANT2_16(name) PSNIP_BUILTIN__GEN_NAME(name,s)
#elif INT_MIN == (-32767-1) && INT_MAX == 32767
#  define PSNIP_BUILTIN__INT_SIZE 16
#  define PSNIP_BUILTIN__VARIANT2_16(name) PSNIP_BUILTIN__GEN_NAME(name,)
#elif LONG_MIN == (-32767-1) && LONG_MAX == 32767
#  define PSNIP_BUILTIN__LONG_SIZE 16
#  define PSNIP_BUILTIN__VARIANT2_16(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#elif LLONG_MIN == (-32767-1) && LLONG_MAX == 32767
#  define PSNIP_BUILTIN__LLONG_SIZE 16
#  define PSNIP_BUILTIN__VARIANT2_16(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#endif

#if CHAR_MIN == (-2147483647-1) && INT_MAX == 2147483647
#  define PSNIP_BUILTIN__CHAR_SIZE 32
#  define PSNIP_BUILTIN__VARIANT2_32(name) PSNIP_BUILTIN__GEN_NAME(name,b)
#elif SHRT_MIN == (-2147483647-1) && INT_MAX == 2147483647
#  define PSNIP_BUILTIN__SHORT_SIZE 32
#  define PSNIP_BUILTIN__VARIANT2_32(name) PSNIP_BUILTIN__GEN_NAME(name,s)
#elif INT_MIN == (-2147483647-1) && INT_MAX == 2147483647
#  define PSNIP_BUILTIN__INT_SIZE 32
#  define PSNIP_BUILTIN__VARIANT_32(name) PSNIP_BUILTIN__GEN_NAME(name,)
#  define PSNIP_BUILTIN__VARIANT2_32(name) PSNIP_BUILTIN__GEN_NAME(name,)
#elif LONG_MIN == (-2147483647-1) && LONG_MAX == 2147483647
#  define PSNIP_BUILTIN__LONG_SIZE 32
#  define PSNIP_BUILTIN__VARIANT_32(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#  define PSNIP_BUILTIN__VARIANT2_32(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#elif LLONG_MIN == (-2147483647-1) && LLONG_MAX == 2147483647
#  define PSNIP_BUILTIN__LLONG_SIZE 32
#  define PSNIP_BUILTIN__VARIANT_32(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#  define PSNIP_BUILTIN__VARIANT2_32(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#endif

#if CHAR_MIN == (-9223372036854775807LL-1) && INT_MAX == 9223372036854775807LL
#  define PSNIP_BUILTIN_CHAR__SIZE 64
#  define PSNIP_BUILTIN__VARIANT2_64(name) PSNIP_BUILTIN__GEN_NAME(name,b)
#elif SHRT_MIN == (-9223372036854775807LL-1) && INT_MAX == 9223372036854775807LL
#  define PSNIP_BUILTIN__SHORT_SIZE 64
#  define PSNIP_BUILTIN__VARIANT2_64(name) PSNIP_BUILTIN__GEN_NAME(name,s)
#elif INT_MIN == (-9223372036854775807LL-1) && INT_MAX == 9223372036854775807LL
#  define PSNIP_BUILTIN__INT_SIZE 64
#  define PSNIP_BUILTIN__VARIANT_64(name) PSNIP_BUILTIN__GEN_NAME(name,)
#  define PSNIP_BUILTIN__VARIANT2_64(name) PSNIP_BUILTIN__GEN_NAME(name,)
#elif LONG_MIN == (-9223372036854775807LL-1) && LONG_MAX == 9223372036854775807LL
#  define PSNIP_BUILTIN__LONG_SIZE 64
#  define PSNIP_BUILTIN__VARIANT_64(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#  define PSNIP_BUILTIN__VARIANT2_64(name) PSNIP_BUILTIN__GEN_NAME(name,l)
#elif LLONG_MIN == (-9223372036854775807LL-1) && LLONG_MAX == 9223372036854775807LL
#  define PSNIP_BUILTIN__LLONG_SIZE 64
#  define PSNIP_BUILTIN__VARIANT_64(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#  define PSNIP_BUILTIN__VARIANT2_64(name) PSNIP_BUILTIN__GEN_NAME(name,ll)
#endif

/******
 *** GCC-style built-ins
 ******/

/*** __builtin_ffs ***/

#define PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  int psnip_builtin_##f_n(T x) {			\
    static const char psnip_builtin_ffs_lookup[256] = { \
      0, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      8, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,	\
      5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1	\
    };							\
							\
    unsigned char t;					\
    size_t s = 0;					\
							\
    while (s < (sizeof(T) * 8)) {			\
      t = (unsigned char) ((x >> s) & 0xff);		\
      if (t)						\
        return psnip_builtin_ffs_lookup[t] + s;		\
							\
      s += 8;						\
    }							\
							\
    return 0;						\
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ffs, 3, 3)
#  define psnip_builtin_ffs(x)   __builtin_ffs(x)
#  define psnip_builtin_ffsl(x)  __builtin_ffsl(x)
#  define psnip_builtin_ffsll(x) __builtin_ffsll(x)
#else
#  if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanForward, 14, 0)
PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffsll(long long v) {
  unsigned long r;
#    if defined(_M_AMD64) || defined(_M_ARM)
  if (_BitScanForward64(&r, (unsigned long long) v)) {
    return (int) (r + 1);
  }
#    else
  if (_BitScanForward(&r, (unsigned long) (v))) {
    return (int) (r + 1);
  } else if (_BitScanForward(&r, (unsigned long) (v >> 32))) {
    return (int) (r + 33);
  }
#    endif
  return 0;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffsl(long v) {
  unsigned long r;
  if (_BitScanForward(&r, (unsigned long) v)) {
    return (int) (r + 1);
  }
  return 0;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffs(int v) {
  return psnip_builtin_ffsl(v);
}
#  else
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffs, int)
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffsl, long)
PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffsll, long long)
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_ffsll(v) psnip_builtin_ffsll(v)
#    define __builtin_ffsl(v)  psnip_builtin_ffsl(v)
#    define __builtin_ffs(v)   psnip_builtin_ffs(v)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_ffs32(x) (PSNIP_BUILTIN__VARIANT_32(ffs)(x))
#else
  PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffs32, psnip_int32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_ffs64(x) (PSNIP_BUILTIN__VARIANT_64(ffs)(x))
#else
  PSNIP_BUILTIN__FFS_DEFINE_PORTABLE(ffs64, psnip_int64_t)
#endif

/*** __builtin_clz ***/

#define PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  int psnip_builtin_##f_n(T x) {			\
    static const char psnip_builtin_clz_lookup[256] = {	\
      7, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,	\
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,	\
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	\
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	\
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	\
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	\
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	\
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	\
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	\
    };							\
    size_t s = sizeof(T) * 8;				\
    T r;						\
							\
    while ((s -= 8) != 0) {				\
      r = x >> s;					\
      if (r != 0)					\
        return psnip_builtin_clz_lookup[r] +		\
          (((sizeof(T) - 1) * 8) - s);			\
    }							\
							\
    if (x == 0)						\
      return (int) ((sizeof(T) * 8) - 1);		\
    else						\
      return psnip_builtin_clz_lookup[x] +		\
        ((sizeof(T) - 1) * 8);				\
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_clz, 3, 4)
#  define psnip_builtin_clz(x)   __builtin_clz(x)
#  define psnip_builtin_clzl(x)  __builtin_clzl(x)
#  define psnip_builtin_clzll(x) __builtin_clzll(x)
#else
#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanReverse,14,0)
PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_clzll(unsigned long long v) {
  unsigned long r = 0;
#if defined(_M_AMD64) || defined(_M_ARM)
  if (_BitScanReverse64(&r, v)) {
    return 63 - r;
  }
#else
  if (_BitScanReverse(&r, (unsigned long) (v >> 32))) {
    return 31 - r;
  } else if (_BitScanReverse(&r, (unsigned long) v)) {
    return 63 - r;
  }
#endif
  return 63;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_clzl(unsigned long v) {
  unsigned long r = 0;
  if (_BitScanReverse(&r, v)) {
    return 31 - r;
  }
  return 31;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_clz(unsigned int v) {
  return psnip_builtin_clzl(v);
}
#else
PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(clz, unsigned int)
PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(clzl, unsigned long)
PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(clzll, unsigned long long)
#endif

#if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#  define __builtin_clz(x)   psnip_builtin_clz(x)
#  define __builtin_clzl(x)  psnip_builtin_clzl(x)
#  define __builtin_clzll(x) psnip_builtin_clzll(x)
#endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_clz32(x) (PSNIP_BUILTIN__VARIANT_32(clz)(x))
#else
  PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(clz32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_clz64(x) (PSNIP_BUILTIN__VARIANT_64(clz)(x))
#else
  PSNIP_BUILTIN__CLZ_DEFINE_PORTABLE(clz64, psnip_uint64_t)
#endif

/*** __builtin_ctz ***/

#define PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  int psnip_builtin_##f_n(T x) {			\
    static const char psnip_builtin_ctz_lookup[256] = {	\
      0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	\
      4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0	\
    };							\
    size_t s = 0;					\
    T r;						\
							\
    do {						\
      r = (x >> s) & 0xff;				\
      if (r != 0)					\
        return psnip_builtin_ctz_lookup[r] + (char) s;	\
    } while ((s += 8) < (sizeof(T) * 8));		\
							\
    return (int) sizeof(T) - 1;				\
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ctz, 3, 4)
#  define psnip_builtin_ctz(x)   __builtin_ctz(x)
#  define psnip_builtin_ctzl(x)  __builtin_ctzl(x)
#  define psnip_builtin_ctzll(x) __builtin_ctzll(x)
#else
PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(ctz, unsigned int)
PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(ctzl, unsigned long)
PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(ctzll, unsigned long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_ctz(x)   psnip_builtin_ctz(x)
#    define __builtin_ctzl(x)  psnip_builtin_ctzl(x)
#    define __builtin_ctzll(x) psnip_builtin_ctzll(x)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_ctz32(x) (PSNIP_BUILTIN__VARIANT_32(ctz)(x))
#else
  PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(ctz32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_ctz64(x) (PSNIP_BUILTIN__VARIANT_64(ctz)(x))
#else
  PSNIP_BUILTIN__CTZ_DEFINE_PORTABLE(ctz64, psnip_uint64_t)
#endif

/*** __builtin_parity ***/

#define PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(f_n, T)		\
  PSNIP_BUILTIN_STATIC_INLINE					\
  int psnip_builtin_##f_n(T x) {				\
    static const char psnip_builtin_parity_lookup[256] = {	\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,		\
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0		\
    };								\
    int s;							\
								\
    for (s = (sizeof(T) / 2) * 8 ; s != 4 ; s /= 2) {		\
      x ^= x >> s;						\
    }								\
    return psnip_builtin_parity_lookup[x & 0xff];		\
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_parity, 3, 4)
#  define psnip_builtin_parity(x)   __builtin_parity(x)
#  define psnip_builtin_parityl(x)  __builtin_parityl(x)
#  define psnip_builtin_parityll(x) __builtin_parityll(x)
#else
PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(parity, unsigned int)
PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(parityl, unsigned long)
PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(parityll, unsigned long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_parity(x)   psnip_builtin_parity(x)
#    define __builtin_parityl(x)  psnip_builtin_parityl(x)
#    define __builtin_parityll(x) psnip_builtin_parityll(x)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_parity32(x) (PSNIP_BUILTIN__VARIANT_32(parity)(x))
#else
  PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(parity32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_parity64(x) (PSNIP_BUILTIN__VARIANT_64(parity)(x))
#else
  PSNIP_BUILTIN__PARITY_DEFINE_PORTABLE(parity64, psnip_uint64_t)
#endif

/*** __builtin_popcount ***/

#define PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(f_n, T)	    \
  PSNIP_BUILTIN_STATIC_INLINE                               \
  int psnip_builtin_##f_n(T x) {                            \
    x = x - ((x >> 1) & (T)~(T)0/3);                        \
    x = (x & (T)~(T)0/15*3) + ((x >> 2) & (T)~(T)0/15*3);   \
    x = (x + (x >> 4)) & (T)~(T)0/255*15;                   \
    return (T)(x * ((T)~(T)0/255)) >> (sizeof(T) - 1) * 8;  \
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_popcount, 3, 4)
#  define psnip_builtin_popcount(x)   __builtin_popcount(x)
#  define psnip_builtin_popcountl(x)  __builtin_popcountl(x)
#  define psnip_builtin_popcountll(x) __builtin_popcountll(x)
#else
PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(popcount, unsigned int)
PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(popcountl, unsigned long)
PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(popcountll, unsigned long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_popcount(x)   psnip_builtin_popcount(x)
#    define __builtin_popcountl(x)  psnip_builtin_popcountl(x)
#    define __builtin_popcountll(x) psnip_builtin_popcountll(x)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_popcount32(x) (PSNIP_BUILTIN__VARIANT_32(popcount)(x))
#else
  PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(popcount32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_popcount64(x) (PSNIP_BUILTIN__VARIANT_64(popcount)(x))
#else
  PSNIP_BUILTIN__POPCOUNT_DEFINE_PORTABLE(popcount64, psnip_uint64_t)
#endif

/*** __builtin_clrsb ***/

#define PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(f_n, clzfn, T) \
  PSNIP_BUILTIN_STATIC_INLINE                               \
  int psnip_builtin_##f_n(T x) {                            \
    return (PSNIP_BUILTIN_UNLIKELY(x == -1) ?		    \
	    (sizeof(x) * 8) :				    \
	    psnip_builtin_##clzfn((x < 0) ? ~x : x)) - 1;   \
  }

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_clrsb, 4, 7)
#  define psnip_builtin_clrsb(x)   __builtin_clrsb(x)
#  define psnip_builtin_clrsbl(x)  __builtin_clrsbl(x)
#  define psnip_builtin_clrsbll(x) __builtin_clrsbll(x)
#else
PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(clrsb, clz, int)
PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(clrsbl, clzl, long)
PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(clrsbll, clzll, long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_clrsb(x)   psnip_builtin_clrsb(x)
#    define __builtin_clrsbl(x)  psnip_builtin_clrsbl(x)
#    define __builtin_clrsbll(x) psnip_builtin_clrsbll(x)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT_32)
#  define psnip_builtin_clrsb32(x) (PSNIP_BUILTIN__VARIANT_32(clrsb)(x))
#else
  PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(clrsb32, clz32, psnip_int32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT_64)
#  define psnip_builtin_clrsb64(x) (PSNIP_BUILTIN__VARIANT_64(clrsb)(x))
#else
  PSNIP_BUILTIN__CLRSB_DEFINE_PORTABLE(clrsb64, clz64, psnip_int64_t)
#endif

/*** __builtin_bitreverse ***/

#define PSNIP_BUILTIN__BITREVERSE_DEFINE_PORTABLE(f_n, T, UT)	\
  PSNIP_BUILTIN_STATIC_INLINE					\
  T psnip_builtin_##f_n(T x) {					\
    UT v = (UT) x;						\
    size_t s = sizeof(x) * CHAR_BIT;				\
    UT mask = (UT) ~((UT) 0U);					\
    while ((s >>= 1) > 0) {					\
      mask ^= (mask << s);					\
      v = ((v >> s) & mask) | ((v << s) & ~mask);		\
    }								\
    return (T) v;						\
  }

#if PSNIP_BUILTIN_CLANG_HAS_BUILTIN(__builtin_bitreverse64)
#  define psnip_builtin_bitreverse8(x)  __builtin_bitreverse8(x)
#  define psnip_builtin_bitreverse16(x) __builtin_bitreverse16(x)
#  define psnip_builtin_bitreverse32(x) __builtin_bitreverse32(x)
#  define psnip_builtin_bitreverse64(x) __builtin_bitreverse64(x)
#else
PSNIP_BUILTIN__BITREVERSE_DEFINE_PORTABLE(bitreverse8,  psnip_int8_t,  psnip_uint8_t)
PSNIP_BUILTIN__BITREVERSE_DEFINE_PORTABLE(bitreverse16, psnip_int16_t, psnip_uint16_t)
PSNIP_BUILTIN__BITREVERSE_DEFINE_PORTABLE(bitreverse32, psnip_int32_t, psnip_uint32_t)
PSNIP_BUILTIN__BITREVERSE_DEFINE_PORTABLE(bitreverse64, psnip_int64_t, psnip_uint64_t)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_bitreverse8(x)  psnip_builtin_bitreverse8(x)
#    define __builtin_bitreverse16(x) psnip_builtin_bitreverse16(x)
#    define __builtin_bitreverse32(x) psnip_builtin_bitreverse32(x)
#    define __builtin_bitreverse64(x) psnip_builtin_bitreverse64(x)
#  endif
#endif

/*** __builtin_addc ***/

#define PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_builtin_##f_n(T x, T y, T ci, T* co) {	\
    const T max = (T) (((T) 0) - 1);			\
    T r = (T) x + y;					\
    *co = (T) (x > (max - y));				\
    if (ci) {						\
      if (r == max)					\
	*co = 1;					\
      r += ci;						\
    }							\
    return r;						\
  }

#if PSNIP_BUILTIN_CLANG_HAS_BUILTIN(__builtin_addc)
#  define psnip_builtin_addcb(x, y, ci, co)  __builtin_addcb(x, y, ci, co)
#  define psnip_builtin_addcs(x, y, ci, co)  __builtin_addcs(x, y, ci, co)
#  define psnip_builtin_addc(x, y, ci, co)   __builtin_addc(x, y, ci, co)
#  define psnip_builtin_addcl(x, y, ci, co)  __builtin_addcl(x, y, ci, co)
#  define psnip_builtin_addcll(x, y, ci, co) __builtin_addcll(x, y, ci, co)
#else
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addcb,  unsigned char)
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addcs,  unsigned short)
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addc,   unsigned int)
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addcl,  unsigned long)
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addcll, unsigned long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_addcb(x, y, ci, co)  psnip_builtin_addcb(x, y, ci, co)
#    define __builtin_addcs(x, y, ci, co)  psnip_builtin_addcs(x, y, ci, co)
#    define __builtin_addc(x, y, ci, co)   psnip_builtin_addc(x, y, ci, co)
#    define __builtin_addcl(x, y, ci, co)  psnip_builtin_addcl(x, y, ci, co)
#    define __builtin_addcll(x, y, ci, co) psnip_builtin_addcll(x, y, ci, co)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_8)
#  define psnip_builtin_addc8(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_8(addc)(x, y, ci, co))
#else
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addc8, psnip_uint8_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_16)
#  define psnip_builtin_addc16(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_16(addc)(x, y, ci, co))
#else
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addc16, psnip_uint16_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_32)
#  define psnip_builtin_addc32(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_32(addc)(x, y, ci, co))
#else
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addc32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_64)
#  define psnip_builtin_addc64(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_64(addc)(x, y, ci, co))
#else
PSNIP_BUILTIN__ADDC_DEFINE_PORTABLE(addc64, psnip_uint64_t)
#endif

/*** __builtin_subc ***/

#define PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(f_n, T)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_builtin_##f_n(T x, T y, T ci, T* co) {	\
    T r = x - y;					\
    *co = x < y;					\
    if (ci) {						\
      r--;						\
      if (r == 0)					\
	*co = 1;					\
    }							\
    return r;						\
  }

#if PSNIP_BUILTIN_CLANG_HAS_BUILTIN(__builtin_subc)
#  define psnip_builtin_subcb(x, y, ci, co)  __builtin_subcb(x, y, ci, co)
#  define psnip_builtin_subcs(x, y, ci, co)  __builtin_subcs(x, y, ci, co)
#  define psnip_builtin_subc(x, y, ci, co)   __builtin_subc(x, y, ci, co)
#  define psnip_builtin_subcl(x, y, ci, co)  __builtin_subcl(x, y, ci, co)
#  define psnip_builtin_subcll(x, y, ci, co) __builtin_subcll(x, y, ci, co)
#else
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subcb,  unsigned char)
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subcs,  unsigned short)
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subc,   unsigned int)
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subcl,  unsigned long)
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subcll, unsigned long long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_subcb(x, y, ci, co)  psnip_builtin_subcb(x, y, ci, co)
#    define __builtin_subcs(x, y, ci, co)  psnip_builtin_subcs(x, y, ci, co)
#    define __builtin_subc(x, y, ci, co)   psnip_builtin_subc(x, y, ci, co)
#    define __builtin_subcl(x, y, ci, co)  psnip_builtin_subcl(x, y, ci, co)
#    define __builtin_subcll(x, y, ci, co) psnip_builtin_subcll(x, y, ci, co)
#  endif
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_8)
#  define psnip_builtin_subc8(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_8(subc)(x, y, ci, co))
#else
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subc8, psnip_uint8_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_16)
#  define psnip_builtin_subc16(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_16(subc)(x, y, ci, co))
#else
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subc16, psnip_uint16_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_32)
#  define psnip_builtin_subc32(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_32(subc)(x, y, ci, co))
#else
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subc32, psnip_uint32_t)
#endif

#if defined(PSNIP_BUILTIN__VARIANT2_64)
#  define psnip_builtin_subc64(x, y, ci, co) (PSNIP_BUILTIN__VARIANT2_64(subc)(x, y, ci, co))
#else
PSNIP_BUILTIN__SUBC_DEFINE_PORTABLE(subc64, psnip_uint64_t)
#endif

/*** __builtin_bswap ***/

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_bswap16, 4, 8)
#  define psnip_builtin_bswap16(x) __builtin_bswap16(x)
#else
#  if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_byteswap_ushort,13,10)
#    define psnip_builtin_bswap16(x) _byteswap_ushort(x)
#  else
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint16_t
psnip_builtin_bswap16(psnip_uint16_t v) {
  return
    ((v & (((psnip_uint16_t) 0xff) << 8)) >> 8) |
    ((v & (((psnip_uint16_t) 0xff)     )) << 8);
}
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_bswap16(x) psnip_builtin_bswap16(x)
#  endif
#endif

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_bswap16, 4, 3)
#  define psnip_builtin_bswap32(x) __builtin_bswap32(x)
#  define psnip_builtin_bswap64(x) __builtin_bswap64(x)
#else
#  if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_byteswap_ushort,13,10)
#    define psnip_builtin_bswap32(x) _byteswap_ulong(x)
#    define psnip_builtin_bswap64(x) _byteswap_uint64(x)
#  else
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint32_t
psnip_builtin_bswap32(psnip_uint32_t v) {
  return
    ((v & (((psnip_uint32_t) 0xff) << 24)) >> 24) |
    ((v & (((psnip_uint32_t) 0xff) << 16)) >>  8) |
    ((v & (((psnip_uint32_t) 0xff) <<  8)) <<  8) |
    ((v & (((psnip_uint32_t) 0xff)      )) << 24);
}

PSNIP_BUILTIN_STATIC_INLINE
psnip_uint64_t
psnip_builtin_bswap64(psnip_uint64_t v) {
  return
    ((v & (((psnip_uint64_t) 0xff) << 56)) >> 56) |
    ((v & (((psnip_uint64_t) 0xff) << 48)) >> 40) |
    ((v & (((psnip_uint64_t) 0xff) << 40)) >> 24) |
    ((v & (((psnip_uint64_t) 0xff) << 32)) >>  8) |
    ((v & (((psnip_uint64_t) 0xff) << 24)) <<  8) |
    ((v & (((psnip_uint64_t) 0xff) << 16)) << 24) |
    ((v & (((psnip_uint64_t) 0xff) <<  8)) << 40) |
    ((v & (((psnip_uint64_t) 0xff)      )) << 56);
}
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_bswap32(x) psnip_builtin_bswap32(x)
#    define __builtin_bswap64(x) psnip_builtin_bswap64(x)
#  endif
#endif

/******
 *** MSVC-style intrinsics
 ******/

/*** _rotl ***/

#define PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(f_n, T, ST)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, ST shift) {		\
    return						\
      (value >> ((sizeof(T) * 8) - shift)) |		\
      (value << shift);					\
  }

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotl8, 14, 0)
#  define psnip_intrin_rotl8(value, shift) _rotl8(value, shift)
#  define psnip_intrin_rotl16(value, shift) _rotl16(value, shift)
#else
  PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(rotl8, unsigned char, unsigned char)
  PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(rotl16, unsigned short, unsigned char)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    if !defined(_rotl8)
#      define _rotl8(value, shift)  psnip_intrin_rotl8(value, shift)
#    endif
#    if !defined(_rotl16)
#      define _rotl16(value, shift) psnip_intrin_rotl16(value, shift)
#    endif
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotl8, 13, 10)
#  define psnip_intrin_rotl(value, shift) _rotl(value, shift)
#  define psnip_intrin_rotl64(value, shift) _rotl64(value, shift)
#else
  PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(rotl, unsigned int, int)
#if defined(_MSC_VER)
  PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(rotl64, unsigned __int64, int)
#else
  PSNIP_BUILTIN_ROTL_DEFINE_PORTABLE(rotl64, psnip_uint64_t, int)
#endif

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    if !defined(_rotl)
#      define _rotl(value, shift)   psnip_intrin_rotl(value, shift)
#    endif
#    if !defined(_rotl64)
#      define _rotl64(value, shift) psnip_intrin_rotl64(value, shift)
#    endif
#  endif
#endif

/*** _rotr ***/

#define PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(f_n, T, ST)	\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, ST shift) {		\
    return						\
      (value << ((sizeof(T) * 8) - shift)) |		\
      (value >> shift);					\
  }

PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(rotr8, unsigned char, unsigned char)
PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(rotr16, unsigned short, unsigned char)

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotr8, 14, 0)
#  define psnip_intrin_rotr8(value, shift) _rotr8(value, shift)
#  define psnip_intrin_rotr16(value, shift) _rotr16(value, shift)
#else
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _rotr8(value, shift)  psnip_intrin_rotr8(value, shift)
#    define _rotr16(value, shift) psnip_intrin_rotr16(value, shift)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotr8, 13, 10)
#  define psnip_intrin_rotr(value, shift) _rotr(value, shift)
#  define psnip_intrin_rotr64(value, shift) _rotr64(value, shift)
#else
PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(rotr, unsigned int, int)
#if defined(_MSC_VER)
PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(rotr64, unsigned __int64, int)
#else
PSNIP_BUILTIN_ROTR_DEFINE_PORTABLE(rotr64, psnip_uint64_t, int)
#endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    if !defined(_rotr)
#      define _rotr(value, shift)   psnip_intrin_rotr(value, shift)
#    endif
#    if !defined(_rotr64)
#      define _rotr64(value, shift) psnip_intrin_rotr64(value, shift)
#    endif
#  endif
#endif

/*** _BitScanForward ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanForward, 14, 0)
#  define psnip_intrin_BitScanForward(Index, Mask) _BitScanForward(Index, Mask)
#else
PSNIP_BUILTIN_STATIC_INLINE
unsigned char psnip_intrin_BitScanForward(unsigned long* Index, unsigned long Mask) {
  return PSNIP_BUILTIN_UNLIKELY(Mask == 0) ? 0 : ((*Index = psnip_builtin_ctzl (Mask)), 1);
}

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _BitScanForward(Index, Mask) psnip_intrin_BitScanForward(Index, Mask)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanForward64, 14, 0) && (defined(_M_AMD64) || defined(_M_ARM))
#  define psnip_intrin_BitScanForward64(Index, Mask) _BitScanForward64(Index, Mask)
#else
PSNIP_BUILTIN_STATIC_INLINE
unsigned char psnip_intrin_BitScanForward64(unsigned long* Index, psnip_uint64_t Mask) {
  return PSNIP_BUILTIN_UNLIKELY(Mask == 0) ? 0 : ((*Index = psnip_builtin_ctzll (Mask)), 1);
}

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _BitScanForward64(Index, Mask) psnip_intrin_BitScanForward64(Index, Mask)
#  endif
#endif

/*** _BitScanReverse ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanReverse, 14, 0)
#  define psnip_intrin_BitScanReverse(Index, Mask) _BitScanReverse(Index, Mask)
#else
PSNIP_BUILTIN_STATIC_INLINE
unsigned char psnip_intrin_BitScanReverse(unsigned long* Index, unsigned long Mask) {
  return (PSNIP_BUILTIN_UNLIKELY(Mask == 0)) ? 0 : ((*Index = ((sizeof(Mask) * CHAR_BIT) - 1) - psnip_builtin_clzl (Mask)), 1);
}

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _BitScanReverse(Index, Mask) psnip_intrin_BitScanReverse(Index, Mask)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanReverse64, 14, 0) && (defined(_M_AMD64) || defined(_M_ARM))
#  define psnip_intrin_BitScanReverse64(Index, Mask) _BitScanReverse64(Index, Mask)
#else
PSNIP_BUILTIN_STATIC_INLINE
unsigned char psnip_intrin_BitScanReverse64(unsigned long* Index, psnip_uint64_t Mask) {
  return (PSNIP_BUILTIN_UNLIKELY(Mask == 0)) ? 0 : ((*Index = ((sizeof(Mask) * CHAR_BIT) - 1) - psnip_builtin_clzll (Mask)), 1);
}

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _BitScanReverse64(Index, Mask) psnip_intrin_BitScanReverse64(Index, Mask)
#  endif
#endif

/*** bittest ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittest, 14, 0)
#  define psnip_intrin_bittest(a, b) _bittest(a, b)
#else
#  define psnip_intrin_bittest(a, b) (((*(a)) >> (b)) & 1)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittest(a, b) psnip_intrin_bittest(a, b)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittest64, 14, 0) && (defined(_M_AMD64) || defined(_M_ARM))
#  define psnip_intrin_bittest64(a, b) _bittest64(a, b)
#else
#  define psnip_intrin_bittest64(a, b) (((*(a)) >> (b)) & 1)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittest64(a, b) psnip_intrin_bittest64(a, b)
#  endif
#endif

/*** bittestandcomplement ***/

#define PSNIP_BUILTIN__BITTESTANDCOMPLEMENT_DEFINE_PORTABLE(f_n, T, UT)	\
  PSNIP_BUILTIN_STATIC_INLINE						\
  unsigned char psnip_intrin_##f_n(T* a, T b) {				\
    const char r = (*a >> b) & 1;					\
    *a ^= ((UT) 1) << b;						\
    return r;								\
  }

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandcomplement, 14, 0)
#  define psnip_intrin_bittestandcomplement(a, b) _bittestandcomplement(a, b)
#else
PSNIP_BUILTIN__BITTESTANDCOMPLEMENT_DEFINE_PORTABLE(bittestandcomplement, long, unsigned long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandcomplement(a, b) psnip_intrin_bittestandcomplement(a, b)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandcomplement64, 14, 0) && defined(_M_AMD64)
#  define psnip_intrin_bittestandcomplement64(a, b) _bittestandcomplement64(a, b)
#else
PSNIP_BUILTIN__BITTESTANDCOMPLEMENT_DEFINE_PORTABLE(bittestandcomplement64, psnip_int64_t, psnip_uint64_t)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandcomplement64(a, b) psnip_intrin_bittestandcomplement64(a, b)
#  endif
#endif

/*** bittestandreset ***/

#define PSNIP_BUILTIN__BITTESTANDRESET_DEFINE_PORTABLE(f_n, T, UT)	\
  PSNIP_BUILTIN_STATIC_INLINE						\
  unsigned char psnip_intrin_##f_n(T* a, T b) {				\
    const char r = (*a >> b) & 1;					\
    *a &= ~(((UT) 1) << b);						\
    return r;								\
  }

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandreset, 14, 0)
#  define psnip_intrin_bittestandreset(a, b) _bittestandreset(a, b)
#else
PSNIP_BUILTIN__BITTESTANDRESET_DEFINE_PORTABLE(bittestandreset, long, unsigned long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandreset(a, b) psnip_intrin_bittestandreset(a, b)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandreset64, 14, 0) && (defined(_M_AMD64) || defined(_M_IA64))
#  define psnip_intrin_bittestandreset64(a, b) _bittestandreset64(a, b)
#else
PSNIP_BUILTIN__BITTESTANDRESET_DEFINE_PORTABLE(bittestandreset64, psnip_int64_t, psnip_uint64_t)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandreset64(a, b) psnip_intrin_bittestandreset64(a, b)
#  endif
#endif

/*** bittestandset ***/

#define PSNIP_BUILTIN__BITTESTANDSET_DEFINE_PORTABLE(f_n, T, UT)	\
  PSNIP_BUILTIN_STATIC_INLINE						\
  unsigned char psnip_intrin_##f_n(T* a, T b) {				\
    const char r = (*a >> b) & 1;					\
    *a |= ((UT) 1) << b;						\
    return r;								\
  }

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandset, 14, 0)
#  define psnip_intrin_bittestandset(a, b) _bittestandset(a, b)
#else
PSNIP_BUILTIN__BITTESTANDSET_DEFINE_PORTABLE(bittestandset, long, unsigned long)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandset(a, b) psnip_intrin_bittestandset(a, b)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittestandset64, 14, 0) && defined(_M_AMD64)
#  define psnip_intrin_bittestandset64(a, b) _bittestandset64(a, b)
#else
PSNIP_BUILTIN__BITTESTANDSET_DEFINE_PORTABLE(bittestandset64, psnip_int64_t, psnip_uint64_t)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittestandset64(a, b) psnip_intrin_bittestandset64(a, b)
#  endif
#endif

/*** shiftleft128 ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(__shiftleft128, 14, 0) && defined(_M_AMD64)
#  define psnip_intrin_shiftleft128(LowPart, HighPart, Shift) __shiftleft128(LowPart, HighPart, Shift)
#else
#  if defined(__SIZEOF_INT128__)
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint64_t psnip_intrin_shiftleft128(psnip_uint64_t LowPart, psnip_uint64_t HighPart, unsigned char Shift) {
  unsigned __int128 r = HighPart;
  r <<= 64;
  r |= LowPart;
  r <<= Shift % 64;
  return (psnip_uint64_t) (r >> 64);
}
#  else
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint64_t psnip_intrin_shiftleft128(psnip_uint64_t LowPart, psnip_uint64_t HighPart, unsigned char Shift) {
  Shift %= 64;
  return PSNIP_BUILTIN_UNLIKELY(Shift == 0) ? HighPart : ((HighPart << Shift) | (LowPart >> (64 - Shift)));
}
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __shiftleft128(LowPart, HighPart, Shift) psnip_intrin_shiftleft128(LowPart, HighPart, Shift)
#  endif
#endif

/*** shiftright128 ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(__shiftright128, 14, 0) && defined(_M_AMD64)
#  define psnip_intrin_shiftright128(LowPart, HighPart, Shift) __shiftright128(LowPart, HighPart, Shift)
#else
#  if defined(__SIZEOF_INT128__)
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint64_t psnip_intrin_shiftright128(psnip_uint64_t LowPart, psnip_uint64_t HighPart, unsigned char Shift) {
  unsigned __int128 r = HighPart;
  r <<= 64;
  r |= LowPart;
  r >>= Shift % 64;
  return (psnip_uint64_t) r;
}
#  else
PSNIP_BUILTIN_STATIC_INLINE
psnip_uint64_t psnip_intrin_shiftright128(psnip_uint64_t LowPart, psnip_uint64_t HighPart, unsigned char Shift) {
  Shift %= 64;

  if (PSNIP_BUILTIN_UNLIKELY(Shift == 0))
    return LowPart;

  return
    (HighPart << (64 - Shift)) |
    (LowPart >> Shift);
}
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __shiftright128(LowPart, HighPart, Shift) psnip_intrin_shiftright128(LowPart, HighPart, Shift)
#  endif
#endif

/*** byteswap ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_byteswap_ushort,13,10)
#  define psnip_intrin_byteswap_ushort(v) _byteswap_ushort(v)
#  define psnip_intrin_byteswap_ulong(v)  _byteswap_ulong(v)
#  define psnip_intrin_byteswap_uint64(v) _byteswap_uint64(v)
#else
#  define psnip_intrin_byteswap_ushort(v) psnip_builtin_bswap16(v)
#  define psnip_intrin_byteswap_ulong(v)  psnip_builtin_bswap32(v)
#  define psnip_intrin_byteswap_uint64(v) psnip_builtin_bswap64(v)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _byteswap_ushort(v) psnip_intrin_byteswap_ushort(v)
#    define _byteswap_ulong(v)  psnip_intrin_byteswap_ulong(v)
#    define _byteswap_uint64(v) psnip_intrin_byteswap_uint64(v)
#  endif
#endif

#endif /* defined(PSNIP_BUILTIN_H) */
