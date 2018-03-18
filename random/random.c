#define _GNU_SOURCE

#include "random.h"

#if !defined(psnip_uint64_t)
#  include "../exact-int/exact-int.h"
#endif

#include "../atomic/atomic.h"
#include "../clock/clock.h"
#include "../once/once.h"
#include "../cpu/cpu.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#if !defined(_WIN32)
#  include <sys/types.h>
#  include <unistd.h>
#endif

#if defined(PSNIP_CPU_ARCH_X86_64) || defined(PSNIP_CPU_ARCH_X86)
#  if defined(__has_builtin)
#    if defined(__clang__) && (__clang_major__ == 3 && __clang_minor__ == 5)
#    elif __has_builtin(__builtin_ia32_rdrand64_step) || __has_builtin(__builtin_ia32_rdrand32_step)
#      define PSNIP_RANDOM__SECURE_ALLOW_RDRAND
#    endif
#  elif (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#    define PSNIP_RANDOM__SECURE_ALLOW_RDRAND
#  endif
#endif

static int (* psnip_random_secure_generate)(size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) = NULL;
static psnip_once psnip_random_secure_once = PSNIP_ONCE_INIT;

#if defined(__linux)
#  include <unistd.h>
#  include <sys/syscall.h>

#  if defined(SYS_getrandom)
#    include <linux/version.h>
#    include <sys/utsname.h>

static int
psnip_random__have_getrandom(void) {
  struct utsname buf;
  int major, minor, revision, r;

  uname(&buf);
  r = sscanf(buf.release, "%d.%d.%d", &major, &minor, &revision);
  if (r != 3)
    return 0;

  return KERNEL_VERSION(major, minor, revision) >= KERNEL_VERSION(3, 17, 0);
}

#    if defined(__GLIBC__) && (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 26))
#      include <sys/random.h>
#      define psnip_random__getrandom(buf, buflen, flags) getrandom(buf, buflen, flags)
#    else
static int
psnip_random__getrandom(void* buf, size_t buflen, unsigned int flags) {
  return (int) syscall(SYS_getrandom, buf, buflen, flags);
}
#    endif

static int
psnip_random_secure_generate_getrandom(size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  size_t bytes_read = 0;
  int r;

  while (bytes_read < length) {
    r = psnip_random__getrandom(&(data[bytes_read]), length - bytes_read, 0);
    if (r == -1)
      return -4;
    bytes_read += r;
  }

  return 0;
}
#  endif
#endif

#if defined(PSNIP_RANDOM__SECURE_ALLOW_RDRAND)
#  if defined(__GNUC__)
#    include <x86intrin.h>
#  else
#    include <immintrin.h>
#  endif

#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
__attribute__((__target__("rdrnd")))
#endif
static int
psnip_random__rdrand (size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  size_t remaining = length;
  unsigned int r;
#if defined(PSNIP_CPU_ARCH_X86_64)
  unsigned long long int v;
#else
  unsigned int v;
#endif

  while (remaining > 0) {
    do {
#if defined(PSNIP_CPU_ARCH_X86_64)
#  if defined(__GNUC__)
      r = __builtin_ia32_rdrand64_step(&v);
#  else
      r = _rdrand64_step(&v);
#  endif
#else
#  if defined(__GNUC__)
      r = __builtin_ia32_rdrand32_step(&v);
#  else
      r = _rdrand32_step(&v);
#  endif
#endif
    } while (r == 0);

    if (remaining >= sizeof(v)) {
      memcpy(&(data[length - remaining]), &v, sizeof(v));
      remaining -= sizeof(v);
    } else {
      memcpy(&(data[length - remaining]), &v, remaining);
      remaining = 0;
    }
  }

  return 0;
}
#endif

#if defined(_WIN32)
static HMODULE psnip_rand_secure__advapi32_dll = NULL;
static BOOLEAN (APIENTRY *psnip_rand_secure__RtlGenRandom)(void*, ULONG);

static int psnip_random_secure_generate_RtlGenRandom(size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  assert(psnip_rand_secure__RtlGenRandom != NULL);

  return psnip_rand_secure__RtlGenRandom(data, (ULONG) length) ? 0 : -3;
}

static void
psnip_random_secure_init(void) {
  psnip_rand_secure__advapi32_dll = LoadLibrary("ADVAPI32.DLL");
  if (psnip_rand_secure__advapi32_dll == NULL)
    return;

  psnip_rand_secure__RtlGenRandom = (BOOLEAN (APIENTRY *)(void*,ULONG))
    GetProcAddress(psnip_rand_secure__advapi32_dll, "SystemFunction036");

  if (psnip_rand_secure__RtlGenRandom == NULL)
    return;

  psnip_random_secure_generate = &psnip_random_secure_generate_RtlGenRandom;
}

#  define PSNIP_RANDOM_SECURE_FOUND
#endif /* defined(_WIN32) */

#if !defined(PSNIP_RANDOM_SECURE_FOUND)
static int
psnip_random_secure_generate_dev_random(size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  static FILE* dev_random = NULL;
  size_t bytes_read = 0;

  if (dev_random == NULL) {
    dev_random = fopen("/dev/random", "rb");
    if (dev_random == NULL)
      return -1;
  }

  if (length > 0) {
    bytes_read = fread(data, 1, length, dev_random);
    if (bytes_read != length)
      return -5;
  }

  return 0;
}

static int
psnip_random_secure_generate_dev_urandom(size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  static FILE* dev_urandom = NULL;
  size_t bytes_read = 0;

  if (dev_urandom == NULL) {
    dev_urandom = fopen("/dev/random", "rb");
    if (dev_urandom == NULL)
      return -1;
  }

  if (length > 0) {
    bytes_read = fread(data, 1, length, dev_urandom);
    if (bytes_read != length)
      return -5;
  }

  return 0;
}

static void
psnip_random_secure_init(void) {
#if defined(__linux) && defined(SYS_getrandom)
  if (psnip_random__have_getrandom()) {
    psnip_random_secure_generate = &psnip_random_secure_generate_getrandom;
    return;
  }
#endif

  if (psnip_random_secure_generate_dev_urandom(0, NULL) == 0) {
    psnip_random_secure_generate = &psnip_random_secure_generate_dev_urandom;
    return;
  }

  if (psnip_random_secure_generate_dev_random(0, NULL) == 0) {
    psnip_random_secure_generate = &psnip_random_secure_generate_dev_random;
    return;
  }

#if defined(PSNIP_RANDOM__SECURE_ALLOW_RDRAND)
  if (psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_RDRND)) {
    psnip_random_secure_generate = &psnip_random__rdrand;
    return;
  }
#endif
}
#endif

/* http://burtleburtle.net/bob/hash/integer.html */
static psnip_uint32_t psnip_random__seed_hash(psnip_uint32_t a) {
  a  = (a ^ 61) ^ (a >> 16);
  a += (a << 3);
  a ^= (a >> 4);
  a *= 0x27d4eb2dU;
  a ^= (a >> 15);

  return a;
}

static psnip_uint32_t
psnip_random__pcg_gen_seed(void) {
  psnip_uint32_t res = 0;
  struct PsnipClockTimespec cur_time = { 0, };
  int precision;

  precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_WALL);
  if (precision != 0) {
    if (psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &cur_time) == 0) {
      goto complete;
    }
  }

  precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_MONOTONIC);
  if (precision != 0) {
    if (psnip_clock_get_time(PSNIP_CLOCK_TYPE_MONOTONIC, &cur_time) == 0) {
      goto complete;
    }
  }

  precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_CPU);
  if (precision != 0) {
    if (psnip_clock_get_time(PSNIP_CLOCK_TYPE_CPU, &cur_time) == 0) {
      goto complete;
    }
  }

 complete:
  res ^= psnip_random__seed_hash((psnip_uint32_t) cur_time.nanoseconds);
  res ^= psnip_random__seed_hash((psnip_uint32_t) cur_time.seconds);
  res ^= psnip_random__seed_hash((psnip_uint32_t) rand());
#if !defined(_WIN32)
  res ^= psnip_random__seed_hash((psnip_uint32_t) getpid());
  res ^= psnip_random__seed_hash((psnip_uint32_t) getppid());
#endif

  return res;
}

/* PCG */

#define PSNIP_RANDOM__PCG_MULTIPLIER (747796405U)
#define PSNIP_RANDOM__PCG_INCREMENT  (1729U)

static psnip_uint32_t
psnip_random__pcg_next_state(psnip_uint32_t state) {
  return state * PSNIP_RANDOM__PCG_MULTIPLIER + PSNIP_RANDOM__PCG_INCREMENT;
}

static psnip_uint32_t
psnip_random__pcg_from_state(psnip_uint32_t state) {
  psnip_uint32_t res = ((state >> ((state >> 28) + 4)) ^ state) * (277803737U);
  res ^= res >> 22;
  return res;
}

static int
psnip_random__pgc_generate(psnip_atomic_int32* state, size_t length, psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  psnip_int32_t old_state;
  psnip_uint32_t new_state, v;
  size_t remaining;

  do {
    old_state = psnip_atomic_int32_load(state);
    new_state = (psnip_uint32_t) old_state;

    remaining = length;
    while (remaining > 0) {
      v = psnip_random__pcg_from_state(new_state);
      new_state = psnip_random__pcg_next_state(new_state);

      if (remaining >= sizeof(psnip_uint32_t)) {
	memcpy(&(data[length - remaining]), &v, sizeof(psnip_uint32_t));
	remaining -= sizeof(psnip_uint32_t);
      } else {
	memcpy(&(data[length - remaining]), &v, remaining);
	remaining = 0;
      }
    }
  } while (!psnip_atomic_int32_compare_exchange(state, &old_state, (psnip_int32_t) new_state));

  return 0;
}

/* Reproducible */

static psnip_atomic_int32 psnip_random__reproducible_seed = 0;
static psnip_atomic_int32 psnip_random__reproducible_state = 0;
static psnip_once psnip_random_reproducible_once = PSNIP_ONCE_INIT;

static void
psnip_random_reproducible_init(void) {
  psnip_int32_t seed = (psnip_uint32_t) psnip_random__pcg_gen_seed();

  psnip_atomic_int32_store(&psnip_random__reproducible_seed, seed);
  psnip_atomic_int32_store(&psnip_random__reproducible_state, seed);
}

void
psnip_random_set_seed (psnip_uint32_t seed) {
  const psnip_int32_t sseed = (psnip_int32_t) seed;
  psnip_once_call(&psnip_random_reproducible_once, &psnip_random_reproducible_init);

  psnip_atomic_int32_store(&psnip_random__reproducible_seed, sseed);
  psnip_atomic_int32_store(&psnip_random__reproducible_state, sseed);
}

psnip_uint32_t
psnip_random_get_seed (void) {
  psnip_once_call(&psnip_random_reproducible_once, &psnip_random_reproducible_init);

  return (psnip_uint32_t) psnip_atomic_int32_load(&psnip_random__reproducible_seed);
}

/* Fast */

static psnip_atomic_int32 psnip_random__fast_state = 0;
static psnip_once psnip_random_fast_once = PSNIP_ONCE_INIT;

static void
psnip_random_fast_init(void) {
  psnip_int32_t seed = (psnip_int32_t) psnip_random__pcg_gen_seed();

  psnip_atomic_int32_store((psnip_atomic_int32*) &psnip_random__fast_state, seed);
}

int
psnip_random_bytes(enum PSnipRandomSource source,
		   size_t length,
		   psnip_uint8_t data[PSNIP_RANDOM_ARRAY_PARAM(length)]) {
  switch (source) {
    case PSNIP_RANDOM_SOURCE_SECURE:
#if !defined(PSNIP_RANDOM_SECURE_NO_INIT)
      psnip_once_call(&psnip_random_secure_once, &psnip_random_secure_init);

      if (psnip_random_secure_generate == NULL)
	return -1;
#endif

      return psnip_random_secure_generate(length, data);

    case PSNIP_RANDOM_SOURCE_REPRODUCIBLE:
#if !defined(PSNIP_RANDOM_REPRODUCIBLE_NO_INIT)
      psnip_once_call(&psnip_random_reproducible_once, &psnip_random_reproducible_init);
#endif

      return psnip_random__pgc_generate(&psnip_random__reproducible_state, length, data);

    case PSNIP_RANDOM_SOURCE_FAST:
#if !defined(PSNIP_RANDOM_FAST_NO_INIT)
      psnip_once_call(&psnip_random_fast_once, &psnip_random_fast_init);
#endif

      return psnip_random__pgc_generate(&psnip_random__fast_state, length, data);
  }

  return -2;
}
