/* Overflow-safe math functions
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 */

#if !defined(PSNIP_SAFE_H)
#define PSNIP_SAFE_H

#if defined(HEDLEY_GCC_HAS_BUILTIN)
#  if HEDLEY_GCC_HAS_BUILTIN(__builtin_add_overflow)
#    define PSNIP_SAFE_HAVE_BUILTINS
#  endif
#elif defined(__clang__) && defined(__has_builtin)
#  if __has_builtin(__builtin_add_overflow)
#    define PSNIP_SAFE_HAVE_BUILTINS
#  endif
#elif defined(__GNUC__) && (__GNUC__ >= 5)
#  define PSNIP_SAFE_HAVE_BUILTINS
#endif

#if !defined(PSNIP_SAFE_FORCE_PORTABLE)
#  if defined(__clang__)
#    if __has_builtin(__builtin_add_overflow)
#      define PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW
#    endif
#  elif defined(__GNUC__) && (__GNUC__ >= 5)
#    define PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW
#  endif
#endif /* !defined(PSNIP_SAFE_FORCE_PORTABLE) */

#if defined(__GNUC__)
#  define PSNIP_SAFE_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#  define PSNIP_SAFE_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#  define PSNIP_SAFE_LIKELY(expr) !!(expr)
#  define PSNIP_SAFE_UNLIKELY(expr) !!(expr)
#endif /* defined(__GNUC__) */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  define PSNIP_SAFE_STATIC_INLINE static inline
#elif defined(__GNUC__)
#  define PSNIP_SAFE_STATIC_INLINE static __inline__
#elif defined(_MSC_VER)
#  define PSNIP_SAFE_STATIC_INLINE static __inline
#else
#  define PSNIP_SAFE_STATIC_INLINE static
#endif

#if !defined(PSNIP_SAFE_NO_FIXED)
#  include <stdint.h>
#endif /* !defined(PSNIP_SAFE_NO_FIXED) */
#include <limits.h>
#include <stdlib.h>

/* If there is a type larger than the one we're concerned with it's
 * likely much faster to simply promote the operands, perform the
 * requested operation, verify that the result falls within the
 * original type, then cast the result back to the original type. */

#if !defined(PSNIP_SAFE_NO_PROMOTIONS)

#define PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, op_name, op) \
  PSNIP_SAFE_STATIC_INLINE psnip_safe_##name##_larger \
  psnip_safe_larger_##name##_##op_name (T a, T b) { \
    return ((psnip_safe_##name##_larger) a) op ((psnip_safe_##name##_larger) b); \
  }

#define PSNIP_SAFE_DEFINE_LARGER_UNARY_OP(T, name, op_name, op) \
  PSNIP_SAFE_STATIC_INLINE psnip_safe_##name##_larger \
  psnip_safe_larger_##name##_##op_name (T value) { \
    return (op ((psnip_safe_##name##_larger) value)); \
  }

#define PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(T, name) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, add, +) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, sub, -) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, mul, *) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, div, /) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, mod, %) \
  PSNIP_SAFE_DEFINE_LARGER_UNARY_OP (T, name, neg, -)

#define PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(T, name) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, add, +) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, sub, -) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, mul, *) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, div, /) \
  PSNIP_SAFE_DEFINE_LARGER_BINARY_OP(T, name, mod, %) \
  PSNIP_SAFE_DEFINE_LARGER_UNARY_OP (T, name, neg, -)

#define PSNIP_SAFE_IS_LARGER(ORIG_MAX, DEST_MAX) ((DEST_MAX / ORIG_MAX) >= ORIG_MAX)

#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__SIZEOF_INT128__)
#define PSNIP_SAFE_HAVE_128
typedef __int128  psnip_safe_int128_t;
typedef unsigned __int128 psnip_safe_uint128_t;
#endif /* defined(__GNUC__) */

#if !defined(PSNIP_SAFE_NO_FIXED)
#define PSNIP_SAFE_HAVE_INT8_LARGER
#define PSNIP_SAFE_HAVE_UINT8_LARGER
typedef int16_t  psnip_safe_int8_larger;
typedef uint16_t psnip_safe_uint8_larger;

#define PSNIP_SAFE_HAVE_INT16_LARGER
typedef int32_t  psnip_safe_int16_larger;
typedef uint32_t psnip_safe_uint16_larger;

#define PSNIP_SAFE_HAVE_INT32_LARGER
typedef int64_t  psnip_safe_int32_larger;
typedef uint64_t psnip_safe_uint32_larger;

#if defined(PSNIP_SAFE_HAVE_128)
#define PSNIP_SAFE_HAVE_INT64_LARGER
typedef psnip_safe_int128_t psnip_safe_int64_larger;
typedef psnip_safe_uint128_t psnip_safe_uint64_larger;
#endif /* defined(PSNIP_SAFE_HAVE_128) */
#endif /* !defined(PSNIP_SAFE_NO_FIXED) */

#define PSNIP_SAFE_HAVE_LARGER_CHAR
#if PSNIP_SAFE_IS_LARGER(CHAR_MAX, SHRT_MAX)
typedef short psnip_safe_char_larger;
#elif PSNIP_SAFE_IS_LARGER(CHAR_MAX, INT_MAX)
typedef int psnip_safe_char_larger;
#elif PSNIP_SAFE_IS_LARGER(CHAR_MAX, LONG_MAX)
typedef long psnip_safe_char_larger;
#elif PSNIP_SAFE_IS_LARGER(CHAR_MAX, LLONG_MAX)
typedef long long psnip_safe_char_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(CHAR_MAX, INT16_MAX)
typedef int16_t psnip_safe_char_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(CHAR_MAX, INT32_MAX)
typedef int32_t psnip_safe_char_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(CHAR_MAX, INT64_MAX)
typedef int64_t psnip_safe_char_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (CHAR_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_char_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_CHAR
#endif

#define PSNIP_SAFE_HAVE_LARGER_UCHAR
#if PSNIP_SAFE_IS_LARGER(UCHAR_MAX, USHRT_MAX)
typedef unsigned short psnip_safe_uchar_larger;
#elif PSNIP_SAFE_IS_LARGER(UCHAR_MAX, UINT_MAX)
typedef unsigned int psnip_safe_uchar_larger;
#elif PSNIP_SAFE_IS_LARGER(UCHAR_MAX, ULONG_MAX)
typedef unsigned long psnip_safe_uchar_larger;
#elif PSNIP_SAFE_IS_LARGER(UCHAR_MAX, ULLONG_MAX)
typedef unsigned long long psnip_safe_uchar_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UCHAR_MAX, UINT16_MAX)
typedef uint16_t psnip_safe_uchar_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UCHAR_MAX, UINT32_MAX)
typedef uint32_t psnip_safe_uchar_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UCHAR_MAX, UINT64_MAX)
typedef uint64_t psnip_safe_uchar_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (UCHAR_MAX <= UINT64_MAX)
typedef psnip_safe_uint128_t psnip_safe_uchar_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_UCHAR
#endif

#define PSNIP_SAFE_HAVE_LARGER_SHRT
#if PSNIP_SAFE_IS_LARGER(SHRT_MAX, INT_MAX)
typedef int psnip_safe_short_larger;
#elif PSNIP_SAFE_IS_LARGER(SHRT_MAX, LONG_MAX)
typedef long psnip_safe_short_larger;
#elif PSNIP_SAFE_IS_LARGER(SHRT_MAX, LLONG_MAX)
typedef long long psnip_safe_short_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SHRT_MAX, INT16_MAX)
typedef int16_t psnip_safe_short_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SHRT_MAX, INT32_MAX)
typedef int32_t psnip_safe_short_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SHRT_MAX, INT64_MAX)
typedef int64_t psnip_safe_short_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (SHRT_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_short_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_SHRT
#endif

#define PSNIP_SAFE_HAVE_LARGER_USHRT
#if PSNIP_SAFE_IS_LARGER(USHRT_MAX, UINT_MAX)
typedef unsigned int psnip_safe_ushort_larger;
#elif PSNIP_SAFE_IS_LARGER(USHRT_MAX, ULONG_MAX)
typedef unsigned long psnip_safe_ushort_larger;
#elif PSNIP_SAFE_IS_LARGER(USHRT_MAX, ULLONG_MAX)
typedef unsigned long long psnip_safe_ushort_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(USHRT_MAX, UINT16_MAX)
typedef uint16_t psnip_safe_ushort_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(USHRT_MAX, UINT32_MAX)
typedef uint32_t psnip_safe_ushort_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(USHRT_MAX, UINT64_MAX)
typedef uint64_t psnip_safe_ushort_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (USHRT_MAX <= UINT64_MAX)
typedef psnip_safe_uint128_t psnip_safe_ushort_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_USHRT
#endif

#define PSNIP_SAFE_HAVE_LARGER_INT
#if PSNIP_SAFE_IS_LARGER(INT_MAX, LONG_MAX)
typedef long psnip_safe_int_larger;
#elif PSNIP_SAFE_IS_LARGER(INT_MAX, LLONG_MAX)
typedef long long psnip_safe_int_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(INT_MAX, INT16_MAX)
typedef int16_t psnip_safe_int_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(INT_MAX, INT32_MAX)
typedef int32_t psnip_safe_int_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(INT_MAX, INT64_MAX)
typedef int64_t psnip_safe_int_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (INT_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_int_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_INT
#endif

#define PSNIP_SAFE_HAVE_LARGER_UINT
#if PSNIP_SAFE_IS_LARGER(UINT_MAX, ULONG_MAX)
typedef unsigned long psnip_safe_uint_larger;
#elif PSNIP_SAFE_IS_LARGER(UINT_MAX, ULLONG_MAX)
typedef unsigned long long psnip_safe_uint_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UINT_MAX, UINT16_MAX)
typedef uint16_t psnip_safe_uint_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UINT_MAX, UINT32_MAX)
typedef uint32_t psnip_safe_uint_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(UINT_MAX, UINT64_MAX)
typedef uint64_t psnip_safe_uint_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (UINT_MAX <= UINT64_MAX)
typedef psnip_safe_uint128_t psnip_safe_uint_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_UINT
#endif

#define PSNIP_SAFE_HAVE_LARGER_LONG
#if PSNIP_SAFE_IS_LARGER(LONG_MAX, LLONG_MAX)
typedef long long psnip_safe_long_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LONG_MAX, INT16_MAX)
typedef int16_t psnip_safe_long_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LONG_MAX, INT32_MAX)
typedef int32_t psnip_safe_long_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LONG_MAX, INT64_MAX)
typedef int64_t psnip_safe_long_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (LONG_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_long_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_LONG
#endif

#define PSNIP_SAFE_HAVE_LARGER_ULONG
#if PSNIP_SAFE_IS_LARGER(ULONG_MAX, ULLONG_MAX)
typedef unsigned long long psnip_safe_ulong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULONG_MAX, UINT16_MAX)
typedef uint16_t psnip_safe_ulong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULONG_MAX, UINT32_MAX)
typedef uint32_t psnip_safe_ulong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULONG_MAX, UINT64_MAX)
typedef uint64_t psnip_safe_ulong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (ULONG_MAX <= UINT64_MAX)
typedef psnip_safe_uint128_t psnip_safe_ulong_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_ULONG
#endif

#define PSNIP_SAFE_HAVE_LARGER_LLONG
#if !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LLONG_MAX, INT16_MAX)
typedef int16_t psnip_safe_llong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LLONG_MAX, INT32_MAX)
typedef int32_t psnip_safe_llong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(LLONG_MAX, INT64_MAX)
typedef int64_t psnip_safe_llong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (LLONG_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_llong_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_LLONG
#endif

#define PSNIP_SAFE_HAVE_LARGER_ULLONG
#if !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULLONG_MAX, UINT16_MAX)
typedef uint16_t psnip_safe_ullong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULLONG_MAX, UINT32_MAX)
typedef uint32_t psnip_safe_ullong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(ULLONG_MAX, UINT64_MAX)
typedef uint64_t psnip_safe_ullong_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (ULLONG_MAX <= UINT64_MAX)
typedef psnip_safe_uint128_t psnip_safe_ullong_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_ULLONG
#endif

#define PSNIP_SAFE_HAVE_LARGER_SIZE
#if PSNIP_SAFE_IS_LARGER(SIZE_MAX, SHRT_MAX)
typedef short psnip_safe_size_larger;
#elif PSNIP_SAFE_IS_LARGER(SIZE_MAX, INT_MAX)
typedef int psnip_safe_size_larger;
#elif PSNIP_SAFE_IS_LARGER(SIZE_MAX, LONG_MAX)
typedef long psnip_safe_size_larger;
#elif PSNIP_SAFE_IS_LARGER(SIZE_MAX, LLONG_MAX)
typedef long long psnip_safe_size_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SIZE_MAX, INT16_MAX)
typedef int16_t psnip_safe_size_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SIZE_MAX, INT32_MAX)
typedef int32_t psnip_safe_size_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && PSNIP_SAFE_IS_LARGER(SIZE_MAX, INT64_MAX)
typedef int64_t psnip_safe_size_larger;
#elif !defined(PSNIP_SAFE_NO_FIXED) && defined(PSNIP_SAFE_HAVE_128) && (SIZE_MAX <= INT64_MAX)
typedef psnip_safe_int128_t psnip_safe_size_larger;
#else
#undef PSNIP_SAFE_HAVE_LARGER_SIZE
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_CHAR)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(char, char)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_UCHAR)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(unsigned char, uchar)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_SHORT)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(short, short)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_USHORT)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(unsigned short, ushort)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_INT)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(int, int)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_UINT)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(unsigned int, uint)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_LONG)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(long, long)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_ULONG)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(unsigned long, ulong)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_LLONG)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(long long, llong)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_ULLONG)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(unsigned long long, ullong)
#endif

#if defined(PSNIP_SAFE_HAVE_LARGER_SIZE)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(size_t, size)
#endif

#if !defined(PSNIP_SAFE_NO_FIXED)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(int8_t,   int8)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(uint8_t,  uint8)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(int16_t,  int16)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(uint16_t, uint16)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(int32_t,  int32)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(uint32_t, uint32)
#if defined(PSNIP_SAFE_HAVE_128)
PSNIP_SAFE_DEFINE_LARGER_SIGNED_OPS(int64_t,  int64)
PSNIP_SAFE_DEFINE_LARGER_UNSIGNED_OPS(uint64_t, uint64)
#endif
#endif

#endif /* !defined(PSNIP_SAFE_NO_PROMOTIONS) */

#define PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(T, name, op_name) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_##op_name(T* res, T a, T b) { \
    return !__builtin_##op_name##_overflow(a, b, res); \
  }

#define PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(T, name, op_name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_##op_name(T* res, T a, T b) { \
    const psnip_safe_##name##_larger r = psnip_safe_larger_##name##_##op_name(a, b); \
    *res = (T) r; \
    return (r >= min) && (r <= max); \
  }

#define PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(T, name, op_name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_##op_name(T* res, T a, T b) { \
    const psnip_safe_##name##_larger r = psnip_safe_larger_##name##_##op_name(a, b); \
    *res = (T) r; \
    return (r <= max); \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_ADD(T, name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_add (T* res, T a, T b) { \
    _Bool r = !( ((b > 0) && (a > (max - b))) ||   \
                 ((b < 0) && (a < (max - b))) ); \
    if(PSNIP_SAFE_LIKELY(r)) \
        *res = a + b; \
    return r; \
  }

#define PSNIP_SAFE_DEFINE_UNSIGNED_ADD(T, name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_add (T* res, T a, T b) { \
    *res = (T) (a + b); \
    return !PSNIP_SAFE_UNLIKELY((b > 0) && (a > (max - b))); \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_SUB(T, name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_sub (T* res, T a, T b) { \
      _Bool r = !((b > 0 && a < min + b) || \
                  (b < 0 && a > max + b)); \
      if(PSNIP_SAFE_LIKELY(r)) \
          *res = a - b; \
      return r; \
  }

#define PSNIP_SAFE_DEFINE_UNSIGNED_SUB(T, name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_sub (T* res, T a, T b) { \
      *res = a - b; \
      return !PSNIP_SAFE_UNLIKELY(b > a); \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_MUL(T, name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_mul (T* res, T a, T b) { \
    _Bool r = 1;  \
    if (a > 0) { \
      if (b > 0) { \
        if (a > (max / b)) { \
          r = 0; \
        } \
      } else { \
        if (b < (min / a)) { \
          r = 0; \
        } \
      } \
    } else { \
      if (b > 0) { \
        if (a < (min / b)) { \
          r = 0; \
        } \
      } else { \
        if ( (a != 0) && (b < (max / a))) { \
          r = 0; \
        } \
      } \
    } \
    if(PSNIP_SAFE_LIKELY(r)) \
        *res = a * b; \
    return r; \
  }

#define PSNIP_SAFE_DEFINE_UNSIGNED_MUL(T, name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_mul (T* res, T a, T b) { \
    *res = (T) (a * b); \
    return !PSNIP_SAFE_UNLIKELY((a > 0) && (b > 0) && (a > (max / b))); \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_DIV(T, name, min, max)   \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_div (T* res, T a, T b) { \
    if (PSNIP_SAFE_UNLIKELY(b == 0)) { \
      *res = 0; \
      return 0; \
    } else if (PSNIP_SAFE_UNLIKELY(a == min && b == -1)) {    \
      *res = min; \
      return 0; \
    } else { \
      *res = (T) (a / b); \
      return 1; \
    } \
  }

#define PSNIP_SAFE_DEFINE_UNSIGNED_DIV(T, name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_div (T* res, T a, T b) { \
    if (PSNIP_SAFE_UNLIKELY(b == 0)) { \
      *res = 0; \
      return 0; \
    } else { \
      *res = a / b; \
      return 1; \
    } \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_MOD(T, name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_mod (T* res, T a, T b) { \
    if (PSNIP_SAFE_UNLIKELY(b == 0)) { \
      *res = 0; \
      return 0; \
    } else if (PSNIP_SAFE_UNLIKELY(a == min && b == -1)) { \
      *res = min; \
      return 0; \
    } else { \
      *res = (T) (a % b); \
      return 1; \
    } \
  }

#define PSNIP_SAFE_DEFINE_UNSIGNED_MOD(T, name, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_mod (T* res, T a, T b) { \
    if (PSNIP_SAFE_UNLIKELY(b == 0)) { \
      *res = 0; \
      return 0; \
    } else { \
      *res = a % b; \
      return 1; \
    } \
  }

#define PSNIP_SAFE_DEFINE_SIGNED_NEG(T, name, min, max) \
  PSNIP_SAFE_STATIC_INLINE _Bool \
  psnip_safe_##name##_neg (T* res, T value) { \
    *res = -value; \
    return !PSNIP_SAFE_UNLIKELY(value == min); \
  }

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(char, char, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(char, char, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(char, char, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_CHAR)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(char, char, add, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(char, char, sub, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(char, char, mul, CHAR_MIN, CHAR_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(char, char, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(char, char, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(char, char, CHAR_MIN, CHAR_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(char, char, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(char, char, CHAR_MIN, CHAR_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(char, char, CHAR_MIN, CHAR_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned char, uchar, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned char, uchar, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned char, uchar, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UCHAR)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned char, uchar, add, UCHAR_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned char, uchar, sub, UCHAR_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned char, uchar, mul, UCHAR_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(unsigned char, uchar, UCHAR_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(unsigned char, uchar, UCHAR_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(unsigned char, uchar, UCHAR_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(unsigned char, uchar, UCHAR_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(unsigned char, uchar, UCHAR_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(short, short, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(short, short, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(short, short, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_SHORT)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(short, short, add, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(short, short, sub, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(short, short, mul, SHRT_MIN, SHRT_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(short, short, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(short, short, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(short, short, SHRT_MIN, SHRT_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(short, short, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(short, short, SHRT_MIN, SHRT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(short, short, SHRT_MIN, SHRT_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned short, ushort, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned short, ushort, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned short, ushort, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_USHORT)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned short, ushort, add, USHRT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned short, ushort, sub, USHRT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned short, ushort, mul, USHRT_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(unsigned short, ushort, USHRT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(unsigned short, ushort, USHRT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(unsigned short, ushort, USHRT_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(unsigned short, ushort, USHRT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(unsigned short, ushort, USHRT_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int, int, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int, int, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int, int, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_INT)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int, int, add, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int, int, sub, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int, int, mul, INT_MIN, INT_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(int, int, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(int, int, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(int, int, INT_MIN, INT_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(int, int, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(int, int, INT_MIN, INT_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(int, int, INT_MIN, INT_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned int, uint, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned int, uint, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned int, uint, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UINT)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned int, uint, add, UINT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned int, uint, sub, UINT_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned int, uint, mul, UINT_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(unsigned int, uint, UINT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(unsigned int, uint, UINT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(unsigned int, uint, UINT_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(unsigned int, uint, UINT_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(unsigned int, uint, UINT_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long, long, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long, long, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long, long, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_LONG)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long, long, add, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long, long, sub, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long, long, mul, LONG_MIN, LONG_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(long, long, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(long, long, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(long, long, LONG_MIN, LONG_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(long, long, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(long, long, LONG_MIN, LONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(long, long, LONG_MIN, LONG_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long, ulong, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long, ulong, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long, ulong, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_ULONG)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long, ulong, add, ULONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long, ulong, sub, ULONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long, ulong, mul, ULONG_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(unsigned long, ulong, ULONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(unsigned long, ulong, ULONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(unsigned long, ulong, ULONG_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(unsigned long, ulong, ULONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(unsigned long, ulong, ULONG_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long long, llong, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long long, llong, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(long long, llong, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_LLONG)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long long, llong, add, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long long, llong, sub, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(long long, llong, mul, LLONG_MIN, LLONG_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(long long, llong, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(long long, llong, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(long long, llong, LLONG_MIN, LLONG_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(long long, llong, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(long long, llong, LLONG_MIN, LLONG_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(long long, llong, LLONG_MIN, LLONG_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long long, ullong, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long long, ullong, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(unsigned long long, ullong, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_ULLONG)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long long, ullong, add, ULLONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long long, ullong, sub, ULLONG_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(unsigned long long, ullong, mul, ULLONG_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(unsigned long long, ullong, ULLONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(unsigned long long, ullong, ULLONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(unsigned long long, ullong, ULLONG_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(unsigned long long, ullong, ULLONG_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(unsigned long long, ullong, ULLONG_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(size_t, size, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(size_t, size, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(size_t, size, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_SIZE)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(size_t, size, add, SIZE_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(size_t, size, sub, SIZE_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(size_t, size, mul, SIZE_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(size_t, size, SIZE_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(size_t, size, SIZE_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(size_t, size, SIZE_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(size_t, size, SIZE_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(size_t, size, SIZE_MAX)

#if !defined(PSNIP_SAFE_NO_FIXED)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int8_t, int8, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int8_t, int8, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int8_t, int8, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_INT8)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int8_t, int8, add, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int8_t, int8, sub, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int8_t, int8, mul, INT8_MIN, INT8_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(int8_t, int8, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(int8_t, int8, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(int8_t, int8, INT8_MIN, INT8_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(int8_t, int8, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(int8_t, int8, INT8_MIN, INT8_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(int8_t, int8, INT8_MIN, INT8_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint8_t, uint8, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint8_t, uint8, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint8_t, uint8, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UINT8)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint8_t, uint8, add, UINT8_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint8_t, uint8, sub, UINT8_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint8_t, uint8, mul, UINT8_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(uint8_t, uint8, UINT8_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(uint8_t, uint8, UINT8_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(uint8_t, uint8, UINT8_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(uint8_t, uint8, UINT8_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(uint8_t, uint8, UINT8_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int16_t, int16, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int16_t, int16, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int16_t, int16, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_INT16)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int16_t, int16, add, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int16_t, int16, sub, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int16_t, int16, mul, INT16_MIN, INT16_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(int16_t, int16, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(int16_t, int16, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(int16_t, int16, INT16_MIN, INT16_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(int16_t, int16, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(int16_t, int16, INT16_MIN, INT16_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(int16_t, int16, INT16_MIN, INT16_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint16_t, uint16, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint16_t, uint16, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint16_t, uint16, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UINT16)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint16_t, uint16, add, UINT16_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint16_t, uint16, sub, UINT16_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint16_t, uint16, mul, UINT16_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(uint16_t, uint16, UINT16_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(uint16_t, uint16, UINT16_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(uint16_t, uint16, UINT16_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(uint16_t, uint16, UINT16_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(uint16_t, uint16, UINT16_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int32_t, int32, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int32_t, int32, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int32_t, int32, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_INT32)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int32_t, int32, add, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int32_t, int32, sub, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int32_t, int32, mul, INT32_MIN, INT32_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(int32_t, int32, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(int32_t, int32, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(int32_t, int32, INT32_MIN, INT32_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(int32_t, int32, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(int32_t, int32, INT32_MIN, INT32_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(int32_t, int32, INT32_MIN, INT32_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint32_t, uint32, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint32_t, uint32, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint32_t, uint32, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UINT32)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint32_t, uint32, add, UINT32_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint32_t, uint32, sub, UINT32_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint32_t, uint32, mul, UINT32_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(uint32_t, uint32, UINT32_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(uint32_t, uint32, UINT32_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(uint32_t, uint32, UINT32_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(uint32_t, uint32, UINT32_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(uint32_t, uint32, UINT32_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int64_t, int64, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int64_t, int64, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(int64_t, int64, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_INT64)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int64_t, int64, add, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int64_t, int64, sub, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_SIGNED_BINARY_OP(int64_t, int64, mul, INT64_MIN, INT64_MAX)
#else
PSNIP_SAFE_DEFINE_SIGNED_ADD(int64_t, int64, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_SIGNED_SUB(int64_t, int64, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MUL(int64_t, int64, INT64_MIN, INT64_MAX)
#endif
PSNIP_SAFE_DEFINE_SIGNED_DIV(int64_t, int64, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_SIGNED_MOD(int64_t, int64, INT64_MIN, INT64_MAX)
PSNIP_SAFE_DEFINE_SIGNED_NEG(int64_t, int64, INT64_MIN, INT64_MAX)

#if defined(PSNIP_SAFE_HAVE_BUILTIN_OVERFLOW)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint64_t, uint64, add)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint64_t, uint64, sub)
PSNIP_SAFE_DEFINE_BUILTIN_BINARY_OP(uint64_t, uint64, mul)
#elif defined(PSNIP_SAFE_HAVE_LARGER_UINT64)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint64_t, uint64, add, UINT64_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint64_t, uint64, sub, UINT64_MAX)
PSNIP_SAFE_DEFINE_PROMOTED_UNSIGNED_BINARY_OP(uint64_t, uint64, mul, UINT64_MAX)
#else
PSNIP_SAFE_DEFINE_UNSIGNED_ADD(uint64_t, uint64, UINT64_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_SUB(uint64_t, uint64, UINT64_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MUL(uint64_t, uint64, UINT64_MAX)
#endif
PSNIP_SAFE_DEFINE_UNSIGNED_DIV(uint64_t, uint64, UINT64_MAX)
PSNIP_SAFE_DEFINE_UNSIGNED_MOD(uint64_t, uint64, UINT64_MAX)

#endif /* !defined(PSNIP_SAFE_NO_FIXED) */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/* The are no fixed-length or size selections because they cause an
 * error about _Generic specifying two compatible types.  Hopefully
 * this doesn't cause problems on exotic platforms, but if it does
 * please let me know and I'll try to figure something out. */
#define PSNIP_SAFE_C11_GENERIC_SELECTION(res, op) \
  _Generic((*res), \
	   char: psnip_safe_char_##op, \
	   unsigned char: psnip_safe_uchar_##op, \
	   short: psnip_safe_short_##op, \
	   unsigned short: psnip_safe_ushort_##op, \
	   int: psnip_safe_int_##op, \
	   unsigned int: psnip_safe_uint_##op, \
	   long: psnip_safe_long_##op, \
	   unsigned long: psnip_safe_ulong_##op, \
	   long long: psnip_safe_llong_##op, \
	   unsigned long long: psnip_safe_ullong_##op)

#define PSNIP_SAFE_C11_GENERIC_BINARY_OP(op, res, a, b) \
  PSNIP_SAFE_C11_GENERIC_SELECTION(res, op)(res, a, b)
#define PSNIP_SAFE_C11_GENERIC_UNARY_OP(op, res, v) \
  PSNIP_SAFE_C11_GENERIC_SELECTION(res, op)(res, v)

#define psnip_safe_add(res, a, b) PSNIP_SAFE_C11_GENERIC_BINARY_OP(add, res, a, b)
#define psnip_safe_sub(res, a, b) PSNIP_SAFE_C11_GENERIC_BINARY_OP(sub, res, a, b)
#define psnip_safe_mul(res, a, b) PSNIP_SAFE_C11_GENERIC_BINARY_OP(mul, res, a, b)
#define psnip_safe_div(res, a, b) PSNIP_SAFE_C11_GENERIC_BINARY_OP(div, res, a, b)
#define psnip_safe_mod(res, a, b) PSNIP_SAFE_C11_GENERIC_BINARY_OP(mod, res, a, b)
#define psnip_safe_neg(res, v)    PSNIP_SAFE_C11_GENERIC_UNARY_OP (neg, res, v)
#endif

#if !defined(PSNIP_SAFE_HAVE_BUILTINS) && (defined(PSNIP_SAFE_EMULATE_NATIVE) || defined(PSNIP_BUILTIN_EMULATE_NATIVE))
#  define __builtin_sadd_overflow(a, b, res)   psnip_safe_int_add(res, a, b)
#  define __builtin_saddl_overflow(a, b, res)  psnip_safe_long_add(res, a, b)
#  define __builtin_saddll_overflow(a, b, res) psnip_safe_llong_add(res, a, b)
#  define __builtin_uadd_overflow(a, b, res)   psnip_safe_uint_add(res, a, b)
#  define __builtin_uaddl_overflow(a, b, res)  psnip_safe_ulong_add(res, a, b)
#  define __builtin_uaddll_overflow(a, b, res) psnip_safe_ullong_add(res, a, b)

#  define __builtin_ssub_overflow(a, b, res)   psnip_safe_int_sub(res, a, b)
#  define __builtin_ssubl_overflow(a, b, res)  psnip_safe_long_sub(res, a, b)
#  define __builtin_ssubll_overflow(a, b, res) psnip_safe_llong_sub(res, a, b)
#  define __builtin_usub_overflow(a, b, res)   psnip_safe_uint_sub(res, a, b)
#  define __builtin_usubl_overflow(a, b, res)  psnip_safe_ulong_sub(res, a, b)
#  define __builtin_usubll_overflow(a, b, res) psnip_safe_ullong_sub(res, a, b)

#  define __builtin_smul_overflow(a, b, res)   psnip_safe_int_mul(res, a, b)
#  define __builtin_smull_overflow(a, b, res)  psnip_safe_long_mul(res, a, b)
#  define __builtin_smulll_overflow(a, b, res) psnip_safe_llong_mul(res, a, b)
#  define __builtin_umul_overflow(a, b, res)   psnip_safe_uint_mul(res, a, b)
#  define __builtin_umull_overflow(a, b, res)  psnip_safe_ulong_mul(res, a, b)
#  define __builtin_umulll_overflow(a, b, res) psnip_safe_ullong_mul(res, a, b)
#endif

#endif /* !defined(PSNIP_SAFE_H) */
