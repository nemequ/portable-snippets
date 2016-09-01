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

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_ffs, 3, 4)
#  define psnip_builtin_ffs(x) __builtin_ffs(x)
#  define psnip_builtin_ffsl(x) __builtin_ffsl(x)
#  define psnip_builtin_ffsll(x) __builtin_ffsll(x)
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
    unsigned T t = x;                           \
    unsigned int s = 0;                         \
                                                \
    while (s < (sizeof(T) * 8)) {               \
      t = (x >> s) & 0xff;                      \
      if (t)                                    \
        return psnip_builtin_ffs_lookup[t] + s;  \
                                                \
      s += 8;                                   \
    }                                           \
                                                \
    return 0;                                   \
  }

PSNIP_BUILTIN_FFS_DEFINE(ffs, int)
PSNIP_BUILTIN_FFS_DEFINE(ffsl, long int)
PSNIP_BUILTIN_FFS_DEFINE(ffsll, long long int)
#endif

#if PSNIP_BUILTIN_GNU_HAS_BUILTIN(__builtin_clz, 4, 7)
#  define psnip_builtin_clz(x) __builtin_clz(x)
#  define psnip_builtin_clzl(x) __builtin_clzl(x)
#  define psnip_builtin_clzll(x) __builtin_clzll(x)
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

#define PSNIP_BUILTIN_CLZ_DEFINE(f_n, T)         \
  PSNIP_BUILTIN_STATIC_INLINE                    \
  int psnip_builtin_##f_n(T x) {                 \
    size_t s = sizeof(T) * 8;                   \
    T r;                                        \
                                                \
    while ((s -= 8) != 0) {                     \
      r = x >> s;                               \
      if (r != 0)                               \
        return psnip_builtin_clz_lookup[r] +     \
          (((sizeof(T) - 1) * 8) - s);          \
    }                                           \
                                                \
    if (x == 0)                                 \
      return (int) ((sizeof(T) * 8) - 1);       \
    else                                        \
      return psnip_builtin_clz_lookup[x] +       \
        ((sizeof(T) - 1) * 8);                  \
  }

PSNIP_BUILTIN_CLZ_DEFINE(clz, unsigned int)
PSNIP_BUILTIN_CLZ_DEFINE(clzl, unsigned long int)
PSNIP_BUILTIN_CLZ_DEFINE(clzll, unsigned long int)
#endif

#endif /* defined(PSNIP_BUILTIN_GNU_H) */
