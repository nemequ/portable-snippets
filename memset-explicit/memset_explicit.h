#ifndef PSNIPS_MEMSET_EXPLICIT_H
#define PSNIPS_MEMSET_EXPLICIT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

/**
 * The memset_explicit function copies the value of c (converted to an unsigned
 * char) into each of the first n characters of the object pointed to by s
 *
 * @return The memset_explicit function returns the value of s.
 */
void *psnip_memset_explicit(void *str, int c, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* PSNIPS_MEMSET_EXPLICIT_H */
