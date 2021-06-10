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

#ifndef PSNIPS_EXPLICIT_BZERO_H
#define PSNIPS_EXPLICIT_BZERO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

/**
 * The psnip_explicit_bzero() function writes `n` zero bytes to the string
 * `str`. If `n` is zero, psnip_explicit_bzero() does nothing.
 */
void psnip_explicit_bzero(void *str, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* PSNIPS_EXPLICIT_BZERO_H */
