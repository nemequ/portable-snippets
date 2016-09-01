/* Endianness detection and swapping (v1)
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * This is probably a bit overkill; you may want to simplify things a
 * bit (i.e., remove unused macros) if you copy this into your
 * project.  If you just grab a small section, we would still
 * appreciate a link back to the project if only so people know where
 * they can contribute any enhancements to or import big fixes from.
 *
 * Scroll down to the "Swapping" section for an explanation of the
 * macros you'll probably want to use.
 *
 * Support for PDP endian is incomplete.  Patches are welcome, but I
 * don't think anyone actually uses PDP endian anymore…
 *
 * If you improve this, *please* contribute your change back to us.
 */

#if !defined(PSNIP_ENDIAN_H)
#define PSNIP_ENDIAN_H

#if !defined(PSNIP_LITTLE_ENDIAN)
#  define PSNIP_LITTLE_ENDIAN 1234
#endif
#if !defined(PSNIP_BIG_ENDIAN)
#  define PSNIP_BIG_ENDIAN 4321
#endif
#if !defined(PSNIP_PDP_ENDIAN)
#  define PSNIP_PDP_ENDIAN 3412
#endif

/* Detection
 *
 * Detecting endianness can be a bit tricky.  There isn't really a
 * good standard way of determining endianness, and it's actually
 * possible to mix endianness within a single program.  This is
 * currently pretty rare, though.
 *
 * We define PSNIP_BYTE_ORDER to PSNIP_LITTLE_ENDIAN,
 * PSNIP_BIG_ENDIAN, or PSNIP_PDP_ENDIAN.  Additionally, you can use
 * the PSNIP_RT_BYTE_ORDER to check the runtime byte order, which is a
 * bit more reliable (though it does introduce some runtime overhead.
 *
 * In the event we are unable to determine endianness at compile-time,
 * PSNIP_BYTE_ORDER is left undefined and you will be forced to rely
 * on PSNIP_RT_BYTE_ORDER. */

#if !defined(PSNIP_BYTE_ORDER)
/* GCC (and compilers masquerading as GCC) define  __BYTE_ORDER__. */
#  if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#    define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#  elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#    define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
#  elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_PDP_ENDIAN__)
#    define PSNIP_BYTE_ORDER PSNIP_PDP_ENDIAN
/* We know the endianness of some common architectures.  Common
 * architectures not listed (ARM, POWER, MIPS, etc.) here are
 * bi-endian. */
#  elif defined(__amd64) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
#    define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#  elif defined(__s390x__) || defined(__zarch__)
#    define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
/* Looks like we'll have to rely on the platform.  If we're missing a
 * platform, please let us know. */
#  elif defined(_WIN32)
#    define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#  elif defined(sun) || defined(__sun) /* Solaris */
#    include <sys/byteorder.h>
#    if defined(_LITTLE_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#    elif defined(_BIG_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
#    endif
#  elif defined(__APPLE__)
#    include <libkern/OSByteOrder.h>
#    if defined(__LITTLE_ENDIAN__)
#      define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#    elif defined(__BIG_ENDIAN__)
#      define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
#    endif
#  elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(BSD)
#    include <machine/endian.h>
#    if defined(__BYTE_ORDER) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#    elif defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
#    elif defined(__BYTE_ORDER) && (__BYTE_ORDER == __PDP_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_PDP_ENDIAN
#    endif
#  else
#    include <endian.h>
#    if defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && (__BYTE_ORDER == __LITTLE_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_LITTLE_ENDIAN
#    elif defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && (__BYTE_ORDER == __BIG_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_BIG_ENDIAN
#    elif defined(__BYTE_ORDER) && defined(__PDP_ENDIAN) && (__BYTE_ORDER == __PDP_ENDIAN)
#      define PSNIP_BYTE_ORDER PSNIP_PDP_ENDIAN
#    endif
#  endif
#endif

/* PDP endian not yet supported.  Patches welcome. */
#if defined(PSNIP_BYTE_ORDER) && (PSNIP_BYTE_ORDER == PSNIP_PDP_ENDIAN)
#  undef PSNIP_PDP_ENDIAN
#endif

/* We need fixed-length types for some stuff. */
#if defined(_WIN32)
#  define PSNIP_ENDIAN_UINT16_T unsigned short
#  define PSNIP_ENDIAN_UINT32_T unsigned long
#  define PSNIP_ENDIAN_UINT64_T unsigned __int64
#else
#  include <stdint.h>
#  define PSNIP_ENDIAN_UINT16_T uint16_t
#  define PSNIP_ENDIAN_UINT32_T uint32_t
#  define PSNIP_ENDIAN_UINT64_T uint64_t
#endif

/* Runtime detection. */

static const union {
	unsigned char bytes[4];
	PSNIP_ENDIAN_UINT32_T value;
} psnip_endian_rt_data = {
	{ 1, 2, 3, 4 }
};

#define PSNIP_RT_BYTE_ORDER_IS_LE (psnip_endian_rt_data.value == 0x04030201)
#define PSNIP_RT_BYTE_ORDER_IS_BE (psnip_endian_rt_data.value == 0x01020304)
#define PSNIP_RT_BYTE_ORDER \
  (PSNIP_RT_BYTE_ORDER_IS_LE ? PSNIP_LITTLE_ENDIAN : (PSNIP_RT_BYTE_ORDER_IS_BE ? PSNIP_BIG_ENDIAN : PSNIP_PDP_ENDIAN))

/* Swapping
 *
 * We define PSNIP_BSWAP16, PSNIP_BSWAP32, and PSNIP_BSWAP64 to
 * unconditionally swap byte orders between big-endian and
 * little-endian.
 *
 * We also define macros for reading and writing values with different
 * endiannesses which will be preprocessed to either a swap operation
 * or identity, depending on the system's endianness as determined at
 * compile time or, if none could be determined, we fall back on
 * runtime detection.  These are probably the macros you want to use.
 * They are:
 *
 *   PSNIP_READ_LE16, PSNIP_READ_LE32, PSNIP_READ_LE64,
 *   PSNIP_READ_BE16, PSNIP_READ_BE32, PSNIP_READ_BE64,
 *   PSNIP_WRITE_LE16, PSNIP_WRITE_LE32, PSNIP_WRITE_LE64,
 *   PSNIP_WRITE_BE16, PSNIP_WRITE_BE32, PSNIP_WRITE_BE64,
 *
 * Finally, there are runtime-only version of those macros which
 * ignore the compile-time endianness and always check at runtime:
 *
 *   PSNIP_READ_RT_LE16, PSNIP_READ_RT_LE32, PSNIP_READ_RT_LE64,
 *   PSNIP_READ_RT_BE16, PSNIP_READ_RT_BE32, PSNIP_READ_RT_BE64,
 *   PSNIP_WRITE_RT_LE16, PSNIP_WRITE_RT_LE32, PSNIP_WRITE_RT_LE64,
 *   PSNIP_WRITE_RT_BE16, PSNIP_WRITE_RT_BE32, PSNIP_WRITE_RT_BE64
 *
 * Interestingly, GCC and clang will detect that these are for
 * swapping endianness and optimize them into an unconditional bswap,
 * at least when endianness is known at compile time.  Intel, OTOH,
 * keeps the runtime checks.
 */

#if defined(__clang__) && defined(__has_builtin)
#  if !defined(PSNIP_BSWAP16) && __has_builtin(__builtin_bswap16)
#    define PSNIP_BSWAP16(v) __builtin_bswap16((int16_t) (v))
#  endif
#  if !defined(PSNIP_BSWAP32) && __has_builtin(__builtin_bswap32)
#    define PSNIP_BSWAP32(v) __builtin_bswap32((int32_t) (v))
#  endif
#  if !defined(PSNIP_BSWAP64) && __has_builtin(__builtin_bswap64)
#    define PSNIP_BSWAP64(v) __builtin_bswap64((int64_t) (v))
#  endif
#endif

#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#  if !defined(PSNIP_BSWAP16) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
#    define PSNIP_BSWAP16(v) __builtin_bswap16((int16_t) (v))
#  endif
#  if !defined(PSNIP_BSWAP32)
#    define PSNIP_BSWAP32(v) __builtin_bswap32((int32_t) (v))
#  endif
#  if !defined(PSNIP_BSWAP64)
#    define PSNIP_BSWAP64(v) __builtin_bswap64((int64_t) (v))
#  endif
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1310
#  include <stdlib.h>
#  if !defined(PSNIP_BSWAP16)
#    define PSNIP_BSWAP16(v) _byteswap_ushort((unsigned short) (v))
#  endif
#  if !defined(PSNIP_BSWAP16)
#    define PSNIP_BSWAP32(v) _byteswap_ulong((unsigned long) (v))
#  endif
#  if !defined(PSNIP_BSWAP16)
#    define PSNIP_BSWAP64(v) _byteswap_uint64((unsigned __int64) (v))
#  endif
#endif

#if !defined(PSNIP_BSWAP16)
#  define PSNIP_BSWAP16(v) \
  (((((PSNIP_ENDIAN_UINT16_T) (v)) & UINT16_C(0xff00)) >>  8) |	\
   ((((PSNIP_ENDIAN_UINT16_T) (v)) & UINT16_C(0x00ff)) <<  8))
#endif
#if !defined(PSNIP_BSWAP32)
#  define PSNIP_BSWAP32(v) \
  (((((PSNIP_ENDIAN_UINT32_T) (v)) & UINT32_C(0xff000000)) >> 24) |	\
   ((((PSNIP_ENDIAN_UINT32_T) (v)) & UINT32_C(0x00ff0000)) >>  8) | \
   ((((PSNIP_ENDIAN_UINT32_T) (v)) & UINT32_C(0x0000ff00)) <<  8) | \
   ((((PSNIP_ENDIAN_UINT32_T) (v)) & UINT32_C(0x000000ff)) << 24))
#endif
#if !defined(PSNIP_BSWAP64)
#  define PSNIP_BSWAP64(v) \
  (((((PSNIP_ENDIAN_UINT64_T) (v)) & (0xff00000000000000ULL)) >> 56) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x00ff000000000000ULL)) >> 40) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x0000ff0000000000ULL)) >> 24) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x000000ff00000000ULL)) >>  8) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x00000000ff000000ULL)) <<  8) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x0000000000ff0000ULL)) << 24) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x000000000000ff00ULL)) << 40) | \
   ((((PSNIP_ENDIAN_UINT64_T) (v)) & (0x00000000000000ffULL)) << 56))
#endif

#if defined(HEDLEY_INLINE)
#  define PSNIP_ENDIAN_INLINE HEDLEY_INLINE
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define PSNIP_ENDIAN_INLINE inline
#elif defined(__GNUC__) || defined(_MSC_VER)
#  define PSNIP_ENDIAN_INLINE __inline
#else
#  define PSNIP_ENDIAN_INLINE
#endif

static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT16_T psnip_io_le16(PSNIP_ENDIAN_UINT16_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_LITTLE_ENDIAN ? (v) : PSNIP_BSWAP16(v)); }
static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT32_T psnip_io_le32(PSNIP_ENDIAN_UINT32_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_LITTLE_ENDIAN ? (v) : PSNIP_BSWAP32(v)); }
static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT64_T psnip_io_le64(PSNIP_ENDIAN_UINT64_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_LITTLE_ENDIAN ? (v) : PSNIP_BSWAP64(v)); }
static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT16_T psnip_io_be16(PSNIP_ENDIAN_UINT16_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_BIG_ENDIAN    ? (v) : PSNIP_BSWAP16(v)); }
static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT32_T psnip_io_be32(PSNIP_ENDIAN_UINT32_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_BIG_ENDIAN    ? (v) : PSNIP_BSWAP32(v)); }
static PSNIP_ENDIAN_INLINE PSNIP_ENDIAN_UINT64_T psnip_io_be64(PSNIP_ENDIAN_UINT64_T v) { return (PSNIP_RT_BYTE_ORDER == PSNIP_BIG_ENDIAN    ? (v) : PSNIP_BSWAP64(v)); }

#define PSNIP_READ_RT_LE16(v) psnip_io_le16(v)
#define PSNIP_READ_RT_LE32(v) psnip_io_le32(v)
#define PSNIP_READ_RT_LE64(v) psnip_io_le64(v)
#define PSNIP_READ_RT_BE16(v) psnip_io_be16(v)
#define PSNIP_READ_RT_BE32(v) psnip_io_be32(v)
#define PSNIP_READ_RT_BE64(v) psnip_io_be64(v)

#if defined(PSNIP_BYTE_ORDER)
#  if PSNIP_BYTE_ORDER == PSNIP_LITTLE_ENDIAN
#    define PSNIP_READ_LE16(v) (v)
#    define PSNIP_READ_LE32(v) (v)
#    define PSNIP_READ_LE64(v) (v)
#    define PSNIP_READ_BE16(v) PSNIP_BSWAP16(v)
#    define PSNIP_READ_BE32(v) PSNIP_BSWAP32(v)
#    define PSNIP_READ_BE64(v) PSNIP_BSWAP64(v)
#  elif PSNIP_BYTE_ORDER == PSNIP_BIG_ENDIAN
#    define PSNIP_READ_LE16(v) PSNIP_BSWAP16(v)
#    define PSNIP_READ_LE32(v) PSNIP_BSWAP32(v)
#    define PSNIP_READ_LE64(v) PSNIP_BSWAP64(v)
#    define PSNIP_READ_BE16(v) (v)
#    define PSNIP_READ_BE32(v) (v)
#    define PSNIP_READ_BE64(v) (v)
#  endif
#else
#  define PSNIP_READ_LE16(v) PSNIP_READ_RT_LE16(v)
#  define PSNIP_READ_LE32(v) PSNIP_READ_RT_LE32(v)
#  define PSNIP_READ_LE64(v) PSNIP_READ_RT_LE64(v)
#  define PSNIP_READ_BE16(v) PSNIP_READ_RT_BE16(v)
#  define PSNIP_READ_BE32(v) PSNIP_READ_RT_BE32(v)
#  define PSNIP_READ_BE64(v) PSNIP_READ_RT_BE64(v)
#endif

#define PSNIP_WRITE_LE16(v)    PSNIP_READ_LE16(v)
#define PSNIP_WRITE_LE32(v)    PSNIP_READ_LE32(v)
#define PSNIP_WRITE_LE64(v)    PSNIP_READ_LE64(v)
#define PSNIP_WRITE_BE16(v)    PSNIP_READ_BE16(v)
#define PSNIP_WRITE_BE32(v)    PSNIP_READ_BE32(v)
#define PSNIP_WRITE_BE64(v)    PSNIP_READ_BE64(v)
#define PSNIP_WRITE_RT_LE16(v) PSNIP_READ_RT_LE16(v)
#define PSNIP_WRITE_RT_LE32(v) PSNIP_READ_RT_LE32(v)
#define PSNIP_WRITE_RT_LE64(v) PSNIP_READ_RT_LE64(v)
#define PSNIP_WRITE_RT_BE16(v) PSNIP_READ_RT_BE16(v)
#define PSNIP_WRITE_RT_BE32(v) PSNIP_READ_RT_BE32(v)
#define PSNIP_WRITE_RT_BE64(v) PSNIP_READ_RT_BE64(v)

#endif /* !defined(PSNIP_ENDIAN_H) */
