#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef __GNUC__
static void *(*const volatile memset_ptr)(void *, int, size_t) = memset;
#endif

void *psnip_memset_explicit(void *str, int c, size_t n) {
#if defined(__NetBSD__)
  return explicit_memset(str, c, n);
#else
  if (c == 0) {
#if defined(_WIN32)
    return SecureZeroMemory(str, n);
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__)
    explicit_bzero(str, n);
    return str;
#endif
  }

#if defined(__GNUC__)
  (void)memset(str, c, n);
  __asm__ volatile("" : : "r"(str) : "memory");

  return str;
#else
  return (memset_ptr)(str, c, n);
#endif

#endif
}
