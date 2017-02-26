/* Unaligned operations (v1)
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Most architectures allow unaligned access to some degree, but
 * according to the C specification unaligned accesses are undefined
 * behavior.  The portable thing to do is use memcpy(), but depending
 * on the architecture and compiler that may be slower than either
 * dereferencing a pointer or using a union.
 *
 * If you define PSNIP_UNALIGNED_ALLOW_UNDEFINED prior to including
 * this header, it will try to implement the fastest method which is
 * known to work given the architecture and compiler.
 *
 * Some of the tests are taken from zstd; Yann Collet has done some
 * great work benchmarking different methods on different
 * architectures.
 */

#if !defined(PSNIP_UNALIGNED_H)
#define PSNIP_UNALIGNED_H

#define PSNIP_UNALIGNED_IMPL_MEMCPY 1
#define PSNIP_UNALIGNED_IMPL_DEREF  2
#define PSNIP_UNALIGNED_IMPL_UNION  3

#if defined(PSNIP_UNALIGNED_IMPL)
#  if (PSNIP_UNALIGNED_IMPL < 1) || (PSNIP_UNALIGNED_IMPL > 3)
#    error Unsupported unaligned access method requested.
#  endif
#elif !defined(PSNIP_UNALIGNED_ALLOW_UNDEFINED)
#  define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_MEMCPY
#elif defined(__INTEL_COMPILER)
#  define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_UNION
#elif defined(__PGI)
#  define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_DEREF
#elif defined(__GNUC__)
#  if (__GNUC__ >= 6)
#    define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_MEMCPY
#  elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)
#    define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_UNION
#  elif (defined(__amd64) || defined(__i386))
#    if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
#      define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_MEMCPY
#    else
#      define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_DEREF
#    endif
#  elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#    define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_DEREF
#  else
#    define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_MEMCPY
#  endif
#endif

#if !defined(PSNIP_UNALIGNED_IMPL)
#  define PSNIP_UNALIGNED_IMPL PSNIP_UNALIGNED_IMPL_MEMCPY
#endif

#if !defined(PSNIP_UNALIGNED_STATIC_INLINE)
#  if defined(HEDLEY_INLINE)
#    define PSNIP_UNALIGNED_STATIC_INLINE static HEDLEY_INLINE
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define PSNIP_UNALIGNED_STATIC_INLINE static inline
#  elif defined(__GNUC_STDC_INLINE__)
#    define PSNIP_UNALIGNED_STATIC_INLINE static __inline__
#  elif defined(_MSC_VER) && _MSC_VER >= 1200
#    define PSNIP_UNALIGNED_STATIC_INLINE static __inline
#  else
#    define PSNIP_UNALIGNED_STATIC_INLINE static
#  endif
#endif

/* http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/4972.html */
#if defined(__CC_ARM)
#  define PSNIP_UNALIGNED__PACKED __packed
#else
#  define PSNIP_UNALIGNED__PACKED
#endif

#if PSNIP_UNALIGNED_IMPL == PSNIP_UNALIGNED_IMPL_MEMCPY
#  include <string.h>
#  define PSNIP_UNALIGNED_LOAD_DEFINE(name, T)				\
  PSNIP_UNALIGNED_STATIC_INLINE						\
  T name(const void* src) {						\
    T r;								\
    memcpy(&r, (PSNIP_UNALIGNED__PACKED const void*) src, sizeof(T));	\
    return r;								\
  }
#  define PSNIP_UNALIGNED_STORE_DEFINE(name, T)				\
  PSNIP_UNALIGNED_STATIC_INLINE						\
  void name(void* dest, T src) {					\
    memcpy((PSNIP_UNALIGNED__PACKED void*) &dest, &src, sizeof(T));	\
  }
#elif PSNIP_UNALIGNED_IMPL == PSNIP_UNALIGNED_IMPL_DEREF
#  if defined(__cplusplus)
#    define PSNIP_UNALIGNED_LOAD_DEFINE(name, T)		\
  PSNIP_UNALIGNED_STATIC_INLINE					\
  T name(const void* src) {					\
    return *static_cast<PSNIP_UNALIGNED__PACKED T*>(src);	\
  }
#    define PSNIP_UNALIGNED_STORE_DEFINE(name, T)	\
  PSNIP_UNALIGNED_STATIC_INLINE				\
  void name(void* dest, T src) {			\
    *static_cast<PSNIP_UNALIGNED__PACKED T*> = src;	\
  }
#  else
#    define PSNIP_UNALIGNED_LOAD_DEFINE(name, T)	\
  PSNIP_UNALIGNED_STATIC_INLINE				\
  T name(const void* src) {				\
    return *((PSNIP_UNALIGNED__PACKED T*) src);		\
  }
#    define PSNIP_UNALIGNED_STORE_DEFINE(name, T)	\
  PSNIP_UNALIGNED_STATIC_INLINE				\
  void name(void* dest, T src) {			\
    *((PSNIP_UNALIGNED__PACKED T*) dest) = src;		\
  }
#  endif
#elif PSNIP_UNALIGNED_IMPL == PSNIP_UNALIGNED_IMPL_UNION
#  if defined(_MSC_VER) || (defined(__INTEL_COMPILER) && defined(WIN32))
#    define PSNIP_UNALIGNED__UNION_T(T)		\
  __pragma(pack(push, 1))			\
  union { int64_t v; char a[sizeof(int64_t)]; } \
  __pragma(pack(pop))
#  else
#    define PSNIP_UNALIGNED__UNION_T(T)		\
  union { int64_t v; char a[sizeof(int64_t)]; } \
  __attribute__((packed))
#  endif
#  define PSNIP_UNALIGNED_LOAD_DEFINE(name, T)		\
  PSNIP_UNALIGNED_STATIC_INLINE				\
  T name(const void* src) {				\
    return ((PSNIP_UNALIGNED__UNION_T(T) *) src)->v;	\
  }
#  define PSNIP_UNALIGNED_STORE_DEFINE(name, T)	\
  PSNIP_UNALIGNED_STATIC_INLINE				\
  void name(void* dest, T src) {			\
    ((PSNIP_UNALIGNED__UNION_T(T) *) dest)->v = src;	\
  }
#endif

/* If we've already included exact-int.h (or defined the relevant
   types), we'll set up functions for those types */

#if defined(psnip_int16_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_int16, psnip_int16_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_int16, psnip_int16_t)
#endif
#if defined(psnip_uint16_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_uint16, psnip_uint16_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_uint16, psnip_uint16_t)
#endif
#if defined(psnip_int32_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_int32, psnip_int32_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_int32, psnip_int32_t)
#endif
#if defined(psnip_uint32_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_uint32, psnip_uint32_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_uint32, psnip_uint32_t)
#endif
#if defined(psnip_int64_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_int64, psnip_int64_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_int64, psnip_int64_t)
#endif
#if defined(psnip_uint64_t)
PSNIP_UNALIGNED_LOAD_DEFINE(psnip_unaligned_load_uint64, psnip_uint64_t)
PSNIP_UNALIGNED_STORE_DEFINE(psnip_unaligned_store_uint64, psnip_uint64_t)
#endif

/* And, if endian.h has been included, we can also define functions to
   load different-endian data from unaligned addresses… */

#if defined(PSNIP_ENDIAN_H)
#  psnip_unaligned_load_int16le(src)  psnip_endian_le16(psnip_unaligned_load_int16(src))
#  psnip_unaligned_load_int32le(src)  psnip_endian_le32(psnip_unaligned_load_int32(src))
#  psnip_unaligned_load_int64le(src)  psnip_endian_le64(psnip_unaligned_load_int64(src))
#  psnip_unaligned_load_int16be(src)  psnip_endian_be16(psnip_unaligned_load_int16(src))
#  psnip_unaligned_load_int32be(src)  psnip_endian_be32(psnip_unaligned_load_int32(src))
#  psnip_unaligned_load_int64be(src)  psnip_endian_be64(psnip_unaligned_load_int64(src))
#  psnip_unaligned_load_uint16le(src) psnip_endian_le16(psnip_unaligned_load_uint16(src))
#  psnip_unaligned_load_uint32le(src) psnip_endian_le32(psnip_unaligned_load_uint32(src))
#  psnip_unaligned_load_uint64le(src) psnip_endian_le64(psnip_unaligned_load_uint64(src))
#  psnip_unaligned_load_uint16be(src) psnip_endian_be16(psnip_unaligned_load_uint16(src))
#  psnip_unaligned_load_uint32be(src) psnip_endian_be32(psnip_unaligned_load_uint32(src))
#  psnip_unaligned_load_uint64be(src) psnip_endian_be64(psnip_unaligned_load_uint64(src))
#  psnip_unaligned_store_int16le(dest, src)  psnip_unaligned_store_int16(dest,  (psnip_int16_t)  psnip_endian_le16(src))
#  psnip_unaligned_store_int32le(dest, src)  psnip_unaligned_store_int32(dest,  (psnip_int32_t)  psnip_endian_le32(src))
#  psnip_unaligned_store_int64le(dest, src)  psnip_unaligned_store_int64(dest,  (psnip_int64_t)  psnip_endian_le64(src))
#  psnip_unaligned_store_int16be(dest, src)  psnip_unaligned_store_int16(dest,  (psnip_int16_t)  psnip_endian_be16(src))
#  psnip_unaligned_store_int32be(dest, src)  psnip_unaligned_store_int32(dest,  (psnip_int32_t)  psnip_endian_be32(src))
#  psnip_unaligned_store_int64be(dest, src)  psnip_unaligned_store_int64(dest,  (psnip_int64_t)  psnip_endian_be64(src))
#  psnip_unaligned_store_uint16le(dest, src) psnip_unaligned_store_uint16(dest, (psnip_uint16_t) psnip_endian_le16(src))
#  psnip_unaligned_store_uint32le(dest, src) psnip_unaligned_store_uint32(dest, (psnip_uint32_t) psnip_endian_le32(src))
#  psnip_unaligned_store_uint64le(dest, src) psnip_unaligned_store_uint64(dest, (psnip_uint64_t) psnip_endian_le64(src))
#  psnip_unaligned_store_uint16be(dest, src) psnip_unaligned_store_uint16(dest, (psnip_uint16_t) psnip_endian_be16(src))
#  psnip_unaligned_store_uint32be(dest, src) psnip_unaligned_store_uint32(dest, (psnip_uint32_t) psnip_endian_be32(src))
#  psnip_unaligned_store_uint64be(dest, src) psnip_unaligned_store_uint64(dest, (psnip_uint64_t) psnip_endian_be64(src))
#endif

#endif /* PSNIP_UNALIGNED_H */
