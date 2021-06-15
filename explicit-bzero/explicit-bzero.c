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

#ifndef __STDC_WANT_LIB_EXT1__
/* memset_s() function in C11 Annex K (bound-checking interface) */
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <stdlib.h>
#include <string.h>

#include "explicit-bzero.h"

#if defined(__FreeBSD__) || defined(__OpenBSD__)
#include <sys/param.h>
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif /* _WIN32 */

#ifdef __STDC_LIB_EXT1__
/* memset_s() function in C11 Annex K (bound-checking interface) */
#define HAVE_MEMSET_S 1
#endif /* __STDC_LIB_EXT1__ */

#if (defined(__GLIBC__) && __GLIBC_PREREQ(2, 25)) ||                           \
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

#if defined(__GNUC__) && (defined(__ELF__) || defined(__APPLE_CC__))
#define HAVE_WEAK_LINKING_SUPPORT 1
__attribute__((weak)) void dummy_sym_to_avoid_optimization(void *str, size_t n);
__attribute__((weak)) void dummy_sym_to_avoid_optimization(void *str,
                                                           size_t n) {
  (void)str;
  (void)n;
}
#elif !defined(_WIN32)
static void *(*const volatile memset_ptr)(void *, int, size_t) = memset;
#endif

void psnip_explicit_bzero(void *str, size_t n) {
#if defined(HAVE_EXPLICIT_MEMSET)
  (void)explicit_memset(str, 0, n);
#elif defined(HAVE_MEMSET_S)
  (void)memset_s(str, (rsize_t)n, 0, (rsize_t)n);
#elif defined(_WIN32)
  (void)SecureZeroMemory(str, n);
#elif defined(HAVE_EXPLICIT_BZERO)
  explicit_bzero(str, n);
#else

#if defined(HAVE_WEAK_LINKING_SUPPORT)
  /*
   * Use weak linking if available to prevent compiler from optimizing away
   * memset calls. (Approach used by libsodium[1]).
   *
   * [1]:
   * https://github.com/jedisct1/libsodium/blob/master/src/libsodium/sodium/utils.c#L106
   */
  (void)memset(str, 0, n);
  dummy_sym_to_avoid_optimization(str, n);
#else
  /*
   * Use a volatile pointer to memset as used by OpenSSL[1] for securely
   * clearing memory.
   *
   * [1]:
   * https://github.com/openssl/openssl/blob/f77208693ec3bda99618e6f76c0f8d279c0077bb/crypto/mem_clr.c
   */
  (void)(memset_ptr)(str, 0, n);
#endif /* defined(HAVE_WEAK_LINKING_SUPPORT) */

#ifdef __GNUC__
  /*
   * Use a ASM memory barrier to force GCC to not optimize memset away. (Used by
   * Glibc)
   */
  __asm__ __volatile__("" : : "r"(str) : "memory");
#endif /* __GNUC__ */

#endif
}
