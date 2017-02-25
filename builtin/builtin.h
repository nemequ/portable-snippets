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

#if defined(HEDLEY_MSVC_VERSION_CHECK)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) HEDLEY_MSVC_VERSION_CHECK(major,minor,0)
#elif !defined(_MSC_VER)
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (0)
#elif _MSC_VER >= 1400
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000)))
#elif _MSC_VER >= 1200
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_FULL_VER >= ((major * 100000) + (minor * 1000)))
#else
#  define PSNIP_BUILTIN_MSVC_HAS_INTRIN(intrin,major,minor) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(_MSC_VER)
#  include <intrin.h>
#endif

#if !defined(psnip_int64_t) || !defined(psnip_uint64_t)
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

/******
 *** GCC-style built-ins
 ******/

/*** __builtin_ffs ***/

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
static const char psnip_builtin_ffs_lookup[256] = {
  0, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  8, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  7, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  6, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
  5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1
};

#define PSNIP_BUILTIN_FFS_DEFINE(f_n, T)        \
  PSNIP_BUILTIN_STATIC_INLINE                   \
  int psnip_builtin_##f_n(T x) {                \
    unsigned T t = (unsigned T) x;              \
    size_t s = 0;                               \
                                                \
    while (s < (sizeof(T) * 8)) {               \
      t = (x >> s) & 0xff;                      \
      if (t)                                    \
        return psnip_builtin_ffs_lookup[t] + s; \
                                                \
      s += 8;                                   \
    }                                           \
                                                \
    return 0;                                   \
  }

PSNIP_BUILTIN_FFS_DEFINE(ffs, int)
PSNIP_BUILTIN_FFS_DEFINE(ffsl, long)
PSNIP_BUILTIN_FFS_DEFINE(ffsll, long long)
#  endif
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_ffsll(v) psnip_builtin_ffsll(v)
#    define __builtin_ffsl(v)  psnip_builtin_ffsl(v)
#    define __builtin_ffs(v)   psnip_builtin_ffs(v)
#  endif
#endif

/*** __builtin_clz ***/

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_clz, 3, 4)
#  define psnip_builtin_clz(x)   __builtin_clz(x)
#  define psnip_builtin_clzl(x)  __builtin_clzl(x)
#  define psnip_builtin_clzll(x) __builtin_clzll(x)
#else
#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanReverse64,14,0)
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
static const char psnip_builtin_clz_lookup[256] = {
  7, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define PSNIP_BUILTIN_CLZ_DEFINE(f_n, T)        \
  PSNIP_BUILTIN_STATIC_INLINE                   \
  int psnip_builtin_##f_n(T x) {                \
    size_t s = sizeof(T) * 8;                   \
    T r;                                        \
                                                \
    while ((s -= 8) != 0) {                     \
      r = x >> s;                               \
      if (r != 0)                               \
        return psnip_builtin_clz_lookup[r] +    \
          (((sizeof(T) - 1) * 8) - s);          \
    }                                           \
                                                \
    if (x == 0)                                 \
      return (int) ((sizeof(T) * 8) - 1);       \
    else                                        \
      return psnip_builtin_clz_lookup[x] +      \
        ((sizeof(T) - 1) * 8);                  \
  }

PSNIP_BUILTIN_CLZ_DEFINE(clz, unsigned int)
PSNIP_BUILTIN_CLZ_DEFINE(clzl, unsigned long)
PSNIP_BUILTIN_CLZ_DEFINE(clzll, unsigned long long)
#endif
#if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#  define __builtin_clz(x)   psnip_builtin_clz(x)
#  define __builtin_clzl(x)  psnip_builtin_clzl(x)
#  define __builtin_clzll(x) psnip_builtin_clzll(x)
#endif
#endif

/*** __builtin_ctz ***/

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ctz, 3, 4)
#  define psnip_builtin_ctz(x)   __builtin_ctz(x)
#  define psnip_builtin_ctzl(x)  __builtin_ctzl(x)
#  define psnip_builtin_ctzll(x) __builtin_ctzll(x)
#else
static const char psnip_builtin_ctz_lookup[256] = {
  0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
  4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

#define PSNIP_BUILTIN_CTZ_DEFINE(f_n, T)        \
  PSNIP_BUILTIN_STATIC_INLINE                   \
  int psnip_builtin_##f_n(T x) {                \
    size_t s = 0;                               \
    T r;                                        \
                                                \
    do {                                        \
      r = (x >> s) & 0xff;                      \
      if (r != 0)                               \
        return psnip_builtin_ctz_lookup[r] + s; \
    } while ((s += 8) < (sizeof(T) * 8));       \
                                                \
    return sizeof(T) - 1;                       \
  }

PSNIP_BUILTIN_CTZ_DEFINE(ctz, unsigned int)
PSNIP_BUILTIN_CTZ_DEFINE(ctzl, unsigned long)
PSNIP_BUILTIN_CTZ_DEFINE(ctzll, unsigned long long)

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_ctz(x)   psnip_builtin_ctz(x)
#    define __builtin_ctzl(x)  psnip_builtin_ctzl(x)
#    define __builtin_ctzll(x) psnip_builtin_ctzll(x)
#  endif
#endif

/*** __builtin_parity ***/

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_parity, 3, 4)
#  define psnip_builtin_parity(x)   __builtin_parity(x)
#  define psnip_builtin_parityl(x)  __builtin_parityl(x)
#  define psnip_builtin_parityll(x) __builtin_parityll(x)
#else
static const char psnip_builtin_parity_lookup[256] = {
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
};

#define PSNIP_BUILTIN_PARITY_DEFINE(f_n, T)           \
  PSNIP_BUILTIN_STATIC_INLINE                         \
  int psnip_builtin_##f_n(T x) {                      \
    int s;                                            \
                                                      \
    for (s = (sizeof(T) / 2) * 8 ; s != 4 ; s /= 2) { \
      x ^= x >> s;                                    \
    }                                                 \
    return psnip_builtin_parity_lookup[x & 0xff];     \
  }

PSNIP_BUILTIN_PARITY_DEFINE(parity, unsigned int)
PSNIP_BUILTIN_PARITY_DEFINE(parityl, unsigned long)
PSNIP_BUILTIN_PARITY_DEFINE(parityll, unsigned long long)

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_parity(x)   psnip_builtin_parity(x)
#    define __builtin_parityl(x)  psnip_builtin_parityl(x)
#    define __builtin_parityll(x) psnip_builtin_parityll(x)
#  endif
#endif

/*** __builtin_popcount ***/

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_popcount, 3, 4)
#  define psnip_builtin_popcount(x)   __builtin_popcount(x)
#  define psnip_builtin_popcountl(x)  __builtin_popcountl(x)
#  define psnip_builtin_popcountll(x) __builtin_popcountll(x)
#else
#define PSNIP_BUILTIN_POPCOUNT_DEFINE(f_n, T)               \
  PSNIP_BUILTIN_STATIC_INLINE                               \
  int psnip_builtin_##f_n(T x) {                            \
    x = x - ((x >> 1) & (T)~(T)0/3);                        \
    x = (x & (T)~(T)0/15*3) + ((x >> 2) & (T)~(T)0/15*3);   \
    x = (x + (x >> 4)) & (T)~(T)0/255*15;                   \
    return (T)(x * ((T)~(T)0/255)) >> (sizeof(T) - 1) * 8;  \
  }

PSNIP_BUILTIN_POPCOUNT_DEFINE(popcount, unsigned int)
PSNIP_BUILTIN_POPCOUNT_DEFINE(popcountl, unsigned long)
PSNIP_BUILTIN_POPCOUNT_DEFINE(popcountll, unsigned long long)

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define __builtin_popcount(x)   psnip_builtin_popcount(x)
#    define __builtin_popcountl(x)  psnip_builtin_popcountl(x)
#    define __builtin_popcountll(x) psnip_builtin_popcountll(x)
#  endif
#endif

/******
 *** MSVC-style intrinsics
 ******/

/*** _rotl ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotl8, 14, 0)
#  define psnip_intrin_rotl8(value, shift) _rotl8(value, shift)
#  define psnip_intrin_rotl16(value, shift) _rotl16(value, shift)
#else
#define PSNIP_BUILTIN_ROTL_DEFINE(f_n, T)               \
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, unsigned char shift) {	\
    return						\
      (value >> ((sizeof(T) * 8) - shift)) |		\
      (value << shift);					\
  }

PSNIP_BUILTIN_ROTL_DEFINE(rotl8, unsigned char)
PSNIP_BUILTIN_ROTL_DEFINE(rotl16, unsigned short)

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _rotl8(value, shift)  psnip_intrin_rotl8(value, shift)
#    define _rotl16(value, shift) psnip_intrin_rotl16(value, shift)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotl8, 13, 10)
#  define psnip_intrin_rotl(value, shift) _rotl(value, shift)
#  define psnip_intrin_rotl64(value, shift) _rotl64(value, shift)
#else
#define PSNIP_BUILTIN_ROTL_LARGE_DEFINE(f_n, T)		\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, int shift) {		\
    return						\
      (value >> ((sizeof(T) * 8) - shift)) |		\
      (value << shift);					\
  }

PSNIP_BUILTIN_ROTL_DEFINE(rotl, unsigned int)
#if defined(_MSC_VER)
PSNIP_BUILTIN_ROTL_DEFINE(rotl64, unsigned __int64)
#else
PSNIP_BUILTIN_ROTL_DEFINE(rotl64, uint64_t)
#endif

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _rotl(value, shift)   psnip_intrin_rotl(value, shift)
#    define _rotl64(value, shift) psnip_intrin_rotl64(value, shift)
#  endif
#endif

/*** _rotr ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotr8, 14, 0)
#  define psnip_intrin_rotr8(value, shift) _rotr8(value, shift)
#  define psnip_intrin_rotr16(value, shift) _rotr16(value, shift)
#else
#define PSNIP_BUILTIN_ROTR_DEFINE(f_n, T)               \
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, unsigned char shift) {	\
    return						\
      (value << ((sizeof(T) * 8) - shift)) |		\
      (value >> shift);					\
  }

PSNIP_BUILTIN_ROTR_DEFINE(rotr8, unsigned char)
PSNIP_BUILTIN_ROTR_DEFINE(rotr16, unsigned short)

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _rotr8(value, shift)  psnip_intrin_rotr8(value, shift)
#    define _rotr16(value, shift) psnip_intrin_rotr16(value, shift)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_rotr8, 13, 10)
#  define psnip_intrin_rotr(value, shift) _rotr(value, shift)
#  define psnip_intrin_rotr64(value, shift) _rotr64(value, shift)
#else
#define PSNIP_BUILTIN_ROTR_LARGE_DEFINE(f_n, T)		\
  PSNIP_BUILTIN_STATIC_INLINE				\
  T psnip_intrin_##f_n(T value, int shift) {		\
    return						\
      (value << ((sizeof(T) * 8) - shift)) |		\
      (value >> shift);					\
  }

PSNIP_BUILTIN_ROTR_DEFINE(rotr, unsigned int)
#if defined(_MSC_VER)
PSNIP_BUILTIN_ROTR_DEFINE(rotr64, unsigned __int64)
#else
PSNIP_BUILTIN_ROTR_DEFINE(rotr64, uint64_t)
#endif

#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _rotr(value, shift)   psnip_intrin_rotr(value, shift)
#    define _rotr64(value, shift) psnip_intrin_rotr64(value, shift)
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

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_BitScanForward, 14, 0) && (defined(_M_AMD64) || defined(_M_AMD64))
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

/*** bittest ***/

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittest, 14, 0)
#  define psnip_intrin_bittest(a, b) _bittest(a, b)
#else
#  define psnip_intrin_bittest(a, b) (((*(a)) >> (b)) & 1)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittest(a, b) psnip_intrin_bittest(a, b)
#  endif
#endif

#if PSNIP_BUILTIN_MSVC_HAS_INTRIN(_bittest64, 14, 0) && (defined(_M_AMD64) || defined(_M_AMD64))
#  define psnip_intrin_bittest64(a, b) _bittest64(a, b)
#else
#  define psnip_intrin_bittest64(a, b) (((*(a)) >> (b)) & 1)
#  if defined(PSNIP_BUILTIN_EMULATE_NATIVE)
#    define _bittest64(a, b) psnip_intrin_bittest64(a, b)
#  endif
#endif

#endif /* defined(PSNIP_BUILTIN_H) */
