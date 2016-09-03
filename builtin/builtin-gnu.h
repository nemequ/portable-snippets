/* Atomic operations (v1)
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

#if !defined(PSNIP_BUILTIN_GNU_H)
#define PSNIP_BUILTIN_GNU_H

#if defined(PSNIP_BUILTIN_ALWAYS_FALLBACK)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (0)
#elif defined(__clang__) && defined(__has_builtin)
#  define PSNIP_INTIRN_GNU_HAS_BUILTIN(builtin,major,minor) __has_builtin(builtin)
#elif defined(__GNUC__)
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (__GNUC__ > major || (major == __GNUC__ && __GNUC_MINOR__ >= minor))
#else
#  define PSNIP_BUILTIN_GNU_HAS_BUILTIN(builtin,major,minor) (0)
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

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ffs, 3, 3)
#  define psnip_builtin_ffs(x) __builtin_ffs(x)
#  define psnip_builtin_ffsl(x) __builtin_ffsl(x)
#  define psnip_builtin_ffsll(x) __builtin_ffsll(x)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#include <intrin.h>

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffsll(unsigned long long v) {
	unsigned long r;
#if defined(_M_AMD64) || defined(_M_ARM)
	if (_BitScanForward64(&r, (unsigned long long) v)) {
		return (int) (r + 1);
	}
#else
	if (_BitScanForward(&r, (unsigned long)(v))) {
		return (int) (r + 1);
	} else if (_BitScanForward(&r, (unsigned long) (v >> 32))) {
		return (int) (r + 33);
	}
#endif
	return 0;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffsl(unsigned long v) {
	unsigned long r;
	if (_BitScanForward(&r, (unsigned long) v)) {
		return (int) (r + 1);
	}
	return 0;
}

PSNIP_BUILTIN_STATIC_INLINE
int psnip_builtin_ffs(unsigned int v) {
	return psnip_builtin_ffsl(v);
}
#else
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

#define PSNIP_BUILTIN_FFS_DEFINE(f_n, T)         \
  PSNIP_BUILTIN_STATIC_INLINE                    \
  int psnip_builtin_##f_n(T x) {                 \
    T t = x;                                     \
    int s = 0;                                   \
                                                 \
    while (s < (sizeof(T) * 8)) {                \
      t = (x >> s) & 0xff;                       \
      if (t)                                     \
        return psnip_builtin_ffs_lookup[t] + s;  \
                                                 \
      s += 8;                                    \
    }                                            \
                                                 \
    return 0;                                    \
  }

PSNIP_BUILTIN_FFS_DEFINE(ffs, unsigned int)
PSNIP_BUILTIN_FFS_DEFINE(ffsl, unsigned long)
PSNIP_BUILTIN_FFS_DEFINE(ffsll, unsigned long long)
#endif

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_clz, 3, 4)
#  define psnip_builtin_clz(x) __builtin_clz(x)
#  define psnip_builtin_clzl(x) __builtin_clzl(x)
#  define psnip_builtin_clzll(x) __builtin_clzll(x)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#include <intrin.h>

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

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ctz, 3, 4)
#  define psnip_builtin_ctz(x) __builtin_ctz(x)
#  define psnip_builtin_ctzl(x) __builtin_ctzl(x)
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

#define PSNIP_BUILTIN_CTZ_DEFINE(f_n, T)				\
  PSNIP_BUILTIN_STATIC_INLINE										\
  int psnip_builtin_##f_n(T x) {								\
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
#endif

#endif /* defined(PSNIP_BUILTIN_GNU_H) */
