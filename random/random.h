#if !defined(PSNIP_RANDOM__H)
#define PSNIP_RANDOM__H

#include <stdlib.h>

#if !defined(psnip_uint8_t)
#  include "../exact-int/exact-int.h"
#endif

#if defined(HEDLEY_ARRAY_PARAM)
#  define PSNIP_RANDOM_ARRAY_PARAM(expr) HEDLEY_ARRAY_PARAM(expr)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && (!defined(__STDC_NO_VLA__) || !__STDC_NO_VLA__) && !defined(__cplusplus) && !defined(__PGI)
#  define PSNIP_RANDOM_ARRAY_PARAM(expr) (expr)
#else
#  define PSNIP_RANDOM_ARRAY_PARAM(expr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

enum PSnipRandomSource {
  PSNIP_RANDOM_SOURCE_SECURE,
  PSNIP_RANDOM_SOURCE_REPRODUCIBLE,
  PSNIP_RANDOM_SOURCE_FAST,
};

int            psnip_random_bytes    (enum PSnipRandomSource source,
				      size_t length,
				      psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]);
psnip_uint32_t psnip_random_get_seed (void);
void           psnip_random_set_seed (psnip_uint32_t seed);

#if defined(__cplusplus)
}
#endif

#endif /* defined(PSNIP_RANDOM__H) */
