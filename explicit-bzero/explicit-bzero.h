/*
 * Portable Snippets - https://github.com/nemequ/portable-snippets
 * Created by arnavyc <arnavyc@outlook.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 */

#ifndef PSNIP_EXPLICIT_BZERO_H
#define PSNIP_EXPLICIT_BZERO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __STDC_WANT_LIB_EXT1__
/* memset_s() function in C11 Annex K (bound-checking interface) */
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#if defined(__FreeBSD__) || defined(__OpenBSD__)
#include <sys/param.h>
#endif

#if defined(_WIN32) && !defined(SecureZeroMemory)
#include <Wdm.h>
#endif

#if !defined(PSNIP_EXPLICIT_BZERO_STATIC_INLINE)
#if defined(__GNUC__)
#define PSNIP_EXPLICIT_BZERO__COMPILER_ATTRIBUTES __attribute__((__unused__))
#else
#define PSNIP_EXPLICIT_BZERO__COMPILER_ATTRIBUTES
#endif

#if defined(HEDLEY_INLINE)
#define PSNIP_EXPLICIT_BZERO__INLINE HEDLEY_INLINE
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define PSNIP_EXPLICIT_BZERO__INLINE inline
#elif defined(__GNUC_STDC_INLINE__)
#define PSNIP_EXPLICIT_BZERO__INLINE __inline__
#elif defined(_MSC_VER) && _MSC_VER >= 1200
#define PSNIP_EXPLICIT_BZERO__INLINE __inline
#else
#define PSNIP_EXPLICIT_BZERO__INLINE
#endif

#define PSNIP_EXPLICIT_BZERO__FUNCTION                                         \
  PSNIP_EXPLICIT_BZERO__COMPILER_ATTRIBUTES static PSNIP_EXPLICIT_BZERO__INLINE
#endif

#if (defined(__GLIBC__) &&                                                     \
     (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 25))) ||          \
    (defined(__FreeBSD__) && __FreeBSD_version >= 1100037) ||                  \
    (defined(__OpenBSD__) && OpenBSD >= 201405)
/*
 * explicit_bzero was added in
 * - glibc 2.25
 * - FreeBSD 11.0 (__FreeBSD_version == 1100037). From:
 *   https://docs.freebsd.org/en/books/porters-handbook/versions/#versions-11
 * - OpenBSD 5.5 (OpenBSD >= 201405)
 */
#define HAVE_EXPLICIT_BZERO 1
#endif

#if defined(__NetBSD__) && __NetBSD_Version__ >= 702000000
#define HAVE_EXPLICIT_MEMSET 1
#endif

#if !defined(HAVE_EXPLICIT_MEMSET) && !defined(HAVE_EXPLICIT_BZERO) &&         \
    !defined(__STDC_LIB_EXT1__) && !defined(_WIN32)
static void *(*const volatile memset_ptr)(void *, int, size_t) = memset;
#endif

/**
 * The psnip_explicit_bzero() function writes `n` zero bytes to the string
 * `str`. If `n` is zero, psnip_explicit_bzero() does nothing.
 */
PSNIP_EXPLICIT_BZERO__FUNCTION void psnip_explicit_bzero(void *str, size_t n) {
#if defined(HAVE_EXPLICIT_MEMSET)
  (void)explicit_memset(str, 0, n);
#elif defined(__STDC_LIB_EXT1__)
  /* memset_s() function in C11 Annex K (bound-checking interface) */
  (void)memset_s(str, (rsize_t)n, 0, (rsize_t)n);
#elif defined(_WIN32)

#if defined(SecureZeroMemory)
  SecureZeroMemory(str, n);
#else
  RtlSecureZeroMemory(str, n);
#endif

#elif defined(HAVE_EXPLICIT_BZERO)
  explicit_bzero(str, n);
#else
  /*
   * Use a volatile pointer to memset as used by OpenSSL[1] for securely
   * clearing memory.
   *
   * [1]:
   * https://github.com/openssl/openssl/blob/f77208693ec3bda99618e6f76c0f8d279c0077bb/crypto/mem_clr.c
   */
  (void)(memset_ptr)(str, 0, n);

#ifdef __GNUC__
  /*
   * Use a ASM memory barrier to force GCC to not optimize memset away. (Used by
   * Glibc)
   */
  __asm__ __volatile__("" : : "r"(str) : "memory");
#endif /* __GNUC__ */

#endif
}

#ifdef __cplusplus
}
#endif

#endif /* PSNIP_EXPLICIT_BZERO_H */
