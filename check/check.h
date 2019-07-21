/* Check (assertions)
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 */

#if !defined(PSNIP_CHECK_H)
#define PSNIP_CHECK_H

#if !defined(PSNIP_NDEBUG) && defined(NDEBUG) && !defined(PSNIP_DEBUG)
#  define PSNIP_NDEBUG 1
#endif

#if !defined(PSNIP_CHECK_LIKELY)
#  if defined(HEDLEY_LIKELY)
#    define PSNIP_CHECK_LIKELY(expr) HEDLEY_LIKELY(expr)
#  elif defined(__GNUC__)
#    define PSNIP_CHECK_LIKELY(expr) (__builtin_expect(!!(expr), !0))
#  else
#    define PSNIP_CHECK_LIKELY(expr) (!!(expr))
#  endif
#endif

#if !defined(PSNIP_CHECK_UNLIKELY)
#  if defined(PSNIP_CHECK_UNLIKELY)
#    define PSNIP_CHECK_UNLIKELY(expr) PSNIP_CHECK_UNLIKELY(expr)
#  elif defined(__GNUC__)
#    define PSNIP_CHECK_UNLIKELY(expr) (__builtin_expect(!!(expr), !!0))
#  else
#    define PSNIP_CHECK_UNLIKELY(expr) (!!(expr))
#  endif
#endif

/* For maximum portability include the exact-int module from
   portable snippets. */
#if \
  !defined(psnip_uint64_t) || \
  !defined(psnip_uint32_t) || \
  !defined(psnip_uint16_t) || \
  !defined(psnip_uint8_t)  || \
  !defined(psnip_int64_t)  || \
  !defined(psnip_int32_t)  || \
  !defined(psnip_int16_t)  || \
  !defined(psnip_int8_t)
#  include <stdint.h>
#  if !defined(psnip_uint64_t)
#    define psnip_uint64_t uint64_t
#  endif
#  if !defined(psnip_uint32_t)
#    define psnip_uint32_t uint32_t
#  endif
#  if !defined(psnip_uint16_t)
#    define psnip_uint16_t uint16_t
#  endif
#  if !defined(psnip_uint8_t)
#    define psnip_uint8_t uint8_t
#  endif
#  if !defined(psnip_int64_t)
#    define psnip_int64_t int64_t
#  endif
#  if !defined(psnip_int32_t)
#    define psnip_int32_t int32_t
#  endif
#  if !defined(psnip_int16_t)
#    define psnip_int16_t int16_t
#  endif
#  if !defined(psnip_int8_t)
#    define psnip_int8_t int8_t
#  endif
#endif

#if \
  !defined(PRIi8)  || \
  !defined(PRIi16) || \
  !defined(PRIi32) || \
  !defined(PRIi64) || \
  !defined(PRId8)  || \
  !defined(PRId16) || \
  !defined(PRId32) || \
  !defined(PRId64) || \
  !defined(PRIx8)  || \
  !defined(PRIx16) || \
  !defined(PRIx32) || \
  !defined(PRIx64) || \
  !defined(PRIu8)  || \
  !defined(PRIu16) || \
  !defined(PRIu32) || \
  !defined(PRIu64)
#  if defined(_MSC_VER) && (_MSC_VER < 1800)
#    if !defined(PRIi8)
#      define PRIi8 "i"
#    endif
#    if !defined(PRIi16)
#      define PRIi16 "i"
#    endif
#    if !defined(PRIi32)
#      define PRIi32 "i"
#    endif
#    if !defined(PRIi64)
#      define PRIi64 "I64i"
#    endif
#    if !defined(PRId8)
#      define PRId8 "d"
#    endif
#    if !defined(PRId16)
#      define PRId16 "d"
#    endif
#    if !defined(PRId32)
#      define PRId32 "d"
#    endif
#    if !defined(PRId64)
#      define PRId64 "I64d"
#    endif
#    if !defined(PRIx8)
#      define PRIx8 "x"
#    endif
#    if !defined(PRIx16)
#      define PRIx16 "x"
#    endif
#    if !defined(PRIx32)
#      define PRIx32 "x"
#    endif
#    if !defined(PRIx64)
#      define PRIx64 "I64x"
#    endif
#    if !defined(PRIu8)
#      define PRIu8 "u"
#    endif
#    if !defined(PRIu16)
#      define PRIu16 "u"
#    endif
#    if !defined(PRIu32)
#      define PRIu32 "u"
#    endif
#    if !defined(PRIu64)
#      define PRIu64 "I64u"
#    endif
#  else
#    include <inttypes.h>
#  endif
#endif

#if !defined(_WIN32)
#  define PSNIP_SIZE_MODIFIER "z"
#  define PSNIP_CHAR_MODIFIER "hh"
#  define PSNIP_SHORT_MODIFIER "h"
#else
#  if defined(_M_X64) || defined(__amd64__)
#    define PSNIP_SIZE_MODIFIER "I64"
#  else
#    define PSNIP_SIZE_MODIFIER ""
#  endif
#  define PSNIP_CHAR_MODIFIER ""
#  define PSNIP_SHORT_MODIFIER ""
#endif

#if defined(_MSC_VER) &&  (_MSC_VER >= 1500)
#  define PSNIP__PUSH_DISABLE_MSVC_C4127 __pragma(warning(push)) __pragma(warning(disable:4127))
#  define PSNIP__POP_DISABLE_MSVC_C4127 __pragma(warning(pop))
#else
#  define PSNIP__PUSH_DISABLE_MSVC_C4127
#  define PSNIP__POP_DISABLE_MSVC_C4127
#endif

#if !defined(psnip_errorf)
#  include <stdio.h>
#  include <stdlib.h>
#  define psnip_errorf(format, ...) (fprintf(stderr, format, __VA_ARGS__), abort())
#endif

#define psnip_error(msg) psnip_errorf("%s", msg)

#if defined(PSNIP_NDEBUG)
#  if defined(PSNIP_CHECK_FAIL_DEFINED)
#    define psnip_assert(expr)
#  else
#    if defined(HEDLEY_ASSUME)
#      define psnip_assert(expr) HEDLEY_ASSUME(expr)
#    elif defined(__GNUC__)
#      define psnip_assert(expr) ((void) (!!(expr) ? 1 : (__builtin_unreachable(), 1)))
#    elif defined(_MSC_VER)
#      define psnip_assert(expr) __assume(expr)
#    else
#      define psnip_assert(expr)
#    endif
#  endif
#  define psnip_assert_true(expr) psnip_assert(expr)
#  define psnip_assert_false(expr) psnip_assert(!(expr))
#  define psnip_assert_type_full(prefix, suffix, T, fmt, a, op, b) psnip_assert(((a) op (b)))
#  define psnip_assert_double_equal(a, b, precision)
#  define psnip_assert_string_equal(a, b)
#  define psnip_assert_string_not_equal(a, b)
#  define psnip_assert_memory_equal(size, a, b)
#  define psnip_assert_memory_not_equal(size, a, b)
#else
#  define psnip_assert(expr) \
    do { \
      if (!PSNIP_CHECK_LIKELY(expr)) { \
        psnip_error("assertion failed: " #expr "\n"); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_true(expr) \
    do { \
      if (!PSNIP_CHECK_LIKELY(expr)) { \
        psnip_error("assertion failed: " #expr " is not true\n"); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_false(expr) \
    do { \
      if (!PSNIP_CHECK_LIKELY(!(expr))) { \
        psnip_error("assertion failed: " #expr " is not false\n"); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_type_full(prefix, suffix, T, fmt, a, op, b)   \
    do { \
      T psnip_tmp_a_ = (a); \
      T psnip_tmp_b_ = (b); \
      if (!(psnip_tmp_a_ op psnip_tmp_b_)) { \
        psnip_errorf("assertion failed: %s %s %s (" prefix "%" fmt suffix " %s " prefix "%" fmt suffix ")\n", \
                     #a, #op, #b, psnip_tmp_a_, #op, psnip_tmp_b_); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_double_equal(a, b, precision) \
    do { \
      const double psnip_tmp_a_ = (a); \
      const double psnip_tmp_b_ = (b); \
      const double psnip_tmp_diff_ = ((psnip_tmp_a_ - psnip_tmp_b_) < 0) ? \
        -(psnip_tmp_a_ - psnip_tmp_b_) : \
        (psnip_tmp_a_ - psnip_tmp_b_); \
      if (PSNIP_CHECK_UNLIKELY(psnip_tmp_diff_ > 1e-##precision)) { \
        psnip_errorf("assertion failed: %s == %s (%0." #precision "g == %0." #precision "g)\n", \
                     #a, #b, psnip_tmp_a_, psnip_tmp_b_); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  include <string.h>
#  define psnip_assert_string_equal(a, b) \
    do { \
      const char* psnip_tmp_a_ = a; \
      const char* psnip_tmp_b_ = b; \
      if (PSNIP_CHECK_UNLIKELY(strcmp(psnip_tmp_a_, psnip_tmp_b_) != 0)) { \
        psnip_errorf("assertion failed: string %s == %s (\"%s\" == \"%s\")\n", \
                     #a, #b, psnip_tmp_a_, psnip_tmp_b_); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_string_not_equal(a, b) \
    do { \
      const char* psnip_tmp_a_ = a; \
      const char* psnip_tmp_b_ = b; \
      if (PSNIP_CHECK_UNLIKELY(strcmp(psnip_tmp_a_, psnip_tmp_b_) == 0)) { \
        psnip_errorf("assertion failed: string %s != %s (\"%s\" == \"%s\")\n", \
                     #a, #b, psnip_tmp_a_, psnip_tmp_b_); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_memory_equal(size, a, b) \
    do { \
      const unsigned char* psnip_tmp_a_ = (const unsigned char*) (a); \
      const unsigned char* psnip_tmp_b_ = (const unsigned char*) (b); \
      const size_t psnip_tmp_size_ = (size); \
      if (PSNIP_CHECK_UNLIKELY(memcmp(psnip_tmp_a_, psnip_tmp_b_, psnip_tmp_size_)) != 0) { \
        size_t psnip_tmp_pos_; \
        for (psnip_tmp_pos_ = 0 ; psnip_tmp_pos_ < psnip_tmp_size_ ; psnip_tmp_pos_++) { \
          if (psnip_tmp_a_[psnip_tmp_pos_] != psnip_tmp_b_[psnip_tmp_pos_]) { \
            psnip_errorf("assertion failed: memory %s == %s, at offset %" PSNIP_SIZE_MODIFIER "u\n", \
                         #a, #b, psnip_tmp_pos_); \
            break; \
          } \
        } \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127

#  define psnip_assert_memory_not_equal(size, a, b) \
    do { \
      const unsigned char* psnip_tmp_a_ = (const unsigned char*) (a); \
      const unsigned char* psnip_tmp_b_ = (const unsigned char*) (b); \
      const size_t psnip_tmp_size_ = (size); \
      if (PSNIP_CHECK_UNLIKELY(memcmp(psnip_tmp_a_, psnip_tmp_b_, psnip_tmp_size_)) == 0) { \
        psnip_errorf("assertion failed: memory %s != %s (%" PSNIP_SIZE_MODIFIER "u bytes)\n", \
                     #a, #b, psnip_tmp_size_); \
      } \
      PSNIP__PUSH_DISABLE_MSVC_C4127 \
    } while (0) \
    PSNIP__POP_DISABLE_MSVC_C4127
#endif

#define psnip_assert_type(T, fmt, a, op, b) \
  psnip_assert_type_full("", "", T, fmt, a, op, b)

#define psnip_assert_char(a, op, b) \
  psnip_assert_type_full("'\\x", "'", char, "02" PSNIP_CHAR_MODIFIER "x", a, op, b)
#define psnip_assert_uchar(a, op, b) \
  psnip_assert_type_full("'\\x", "'", unsigned char, "02" PSNIP_CHAR_MODIFIER "x", a, op, b)
#define psnip_assert_short(a, op, b) \
  psnip_assert_type(short, PSNIP_SHORT_MODIFIER "d", a, op, b)
#define psnip_assert_ushort(a, op, b) \
  psnip_assert_type(unsigned short, PSNIP_SHORT_MODIFIER "u", a, op, b)
#define psnip_assert_int(a, op, b) \
  psnip_assert_type(int, "d", a, op, b)
#define psnip_assert_uint(a, op, b) \
  psnip_assert_type(unsigned int, "u", a, op, b)
#define psnip_assert_long(a, op, b) \
  psnip_assert_type(long int, "ld", a, op, b)
#define psnip_assert_ulong(a, op, b) \
  psnip_assert_type(unsigned long int, "lu", a, op, b)
#define psnip_assert_llong(a, op, b) \
  psnip_assert_type(long long int, "lld", a, op, b)
#define psnip_assert_ullong(a, op, b) \
  psnip_assert_type(unsigned long long int, "llu", a, op, b)

#define psnip_assert_size(a, op, b) \
  psnip_assert_type(size_t, PSNIP_SIZE_MODIFIER "u", a, op, b)

#define psnip_assert_float(a, op, b) \
  psnip_assert_type(float, "f", a, op, b)
#define psnip_assert_double(a, op, b) \
  psnip_assert_type(double, "g", a, op, b)
#define psnip_assert_ptr(a, op, b) \
  psnip_assert_type(const void*, "p", a, op, b)

#define psnip_assert_int8(a, op, b)             \
  psnip_assert_type(psnip_int8_t, PRIi8, a, op, b)
#define psnip_assert_uint8(a, op, b) \
  psnip_assert_type(psnip_uint8_t, PRIu8, a, op, b)
#define psnip_assert_int16(a, op, b) \
  psnip_assert_type(psnip_int16_t, PRIi16, a, op, b)
#define psnip_assert_uint16(a, op, b) \
  psnip_assert_type(psnip_uint16_t, PRIu16, a, op, b)
#define psnip_assert_int32(a, op, b) \
  psnip_assert_type(psnip_int32_t, PRIi32, a, op, b)
#define psnip_assert_uint32(a, op, b) \
  psnip_assert_type(psnip_uint32_t, PRIu32, a, op, b)
#define psnip_assert_int64(a, op, b) \
  psnip_assert_type(psnip_int64_t, PRIi64, a, op, b)
#define psnip_assert_uint64(a, op, b) \
  psnip_assert_type(psnip_uint64_t, PRIu64, a, op, b)

#define psnip_assert_ptr_equal(a, b) \
  psnip_assert_ptr(a, ==, b)
#define psnip_assert_ptr_not_equal(a, b) \
  psnip_assert_ptr(a, !=, b)
#define psnip_assert_null(ptr) \
  psnip_assert_ptr(ptr, ==, NULL)
#define psnip_assert_not_null(ptr) \
  psnip_assert_ptr(ptr, !=, NULL)
#define psnip_assert_ptr_null(ptr) \
  psnip_assert_ptr(ptr, ==, NULL)
#define psnip_assert_ptr_not_null(ptr) \
  psnip_assert_ptr(ptr, !=, NULL)

#endif /* !defined(PSNIP_CHECK_H) */
