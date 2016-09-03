#include <stdlib.h>
#include <stdint.h>
#include "munit/munit.h"

#if defined(__GNUC__)
#  define PSNIP_BUILTIN_ALWAYS_FALLBACK
#endif
#include "../builtin/builtin-gnu.h"

static MunitResult
test_gnu_ffs(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffs(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ffs_native(const MunitParameter params[], void* data) {
  unsigned int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  const int m = ((int) ~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
  v &= m;

  munit_assert_int(psnip_builtin_ffs(v), ==, __builtin_ffs(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_ffsl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffsl(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ffsl_native(const MunitParameter params[], void* data) {
  unsigned long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  const int m = ((int) ~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
  v &= m;

  munit_assert_int(psnip_builtin_ffsl(v), ==, __builtin_ffsl(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_ffsll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffsll(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ffsll_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  const int m = ((int) ~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
  v &= m;

  munit_assert_int(psnip_builtin_ffsll(v), ==, __builtin_ffsll(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_clz(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clz(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_clz_native(const MunitParameter params[], void* data) {
  unsigned int v;

  /* __builtin_clz(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) >> munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_clz(v), ==, __builtin_clz(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_clzl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clzl(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_clzl_native(const MunitParameter params[], void* data) {
  unsigned long v;

  /* __builtin_clzl(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) >> munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_clzl(v), ==, __builtin_clzl(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_clzll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clzll(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_clzll_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  /* __builtin_clzll(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) >> munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_clzll(v), ==, __builtin_clzll(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_ctz(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctz(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ctz_native(const MunitParameter params[], void* data) {
  unsigned int v;

  /* __builtin_ctz(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_ctz(v), ==, __builtin_ctz(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_ctzl(const MunitParameter params[], void* data) {
  unsigned long v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctzl(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ctzl_native(const MunitParameter params[], void* data) {
  unsigned long v;

  /* __builtin_ctzl(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_ctzl(v), ==, __builtin_ctzl(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_ctzll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctzll(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_ctzll_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  /* __builtin_ctzll(0) is undefined, so make sure we don't test it.
   * That said, here it returns 1 less than the number of bits in the
   * number. */
  do {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);

    /* Unset a random number of the most significant bits, otherwise
       we're heavily biased towards low results. */
    const unsigned int m = (~0U) << munit_rand_int_range(0, (sizeof(v) * 8) - 1);
    v &= m;
  } while (v == 0);

  munit_assert_int(psnip_builtin_ctzll(v), ==, __builtin_ctzll(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_parity(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parity(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_parity_native(const MunitParameter params[], void* data) {
  unsigned int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parity(v), ==, __builtin_parity(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_parityl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parityl(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_parityl_native(const MunitParameter params[], void* data) {
  unsigned long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parityl(v), ==, __builtin_parityl(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_parityll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parityll(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_parityll_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parityll(v), ==, __builtin_parityll(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_popcount(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcount(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_popcount_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcount(v), ==, __builtin_popcount(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_popcountl(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcountl(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_popcountl_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcountl(v), ==, __builtin_popcountl(v));

  return MUNIT_OK;
}
#endif

static MunitResult
test_gnu_popcountll(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcountll(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
static MunitResult
test_gnu_popcountll_native(const MunitParameter params[], void* data) {
  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcountll(v), ==, __builtin_popcountll(v));

  return MUNIT_OK;
}
#endif

static MunitTest test_suite_tests[] = {
#if defined(__GNUC__)
#  if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
  { (char*) "/builtin/ffs/native",   test_gnu_ffs_native,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/ffsl/native",  test_gnu_ffsl_native,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/ffsll/native", test_gnu_ffsll_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
#  endif
#  if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
  { (char*) "/builtin/clz/native",        test_gnu_clz_native,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/clzl/native",       test_gnu_clzl_native,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/clzll/native",      test_gnu_clzll_native,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/ctz/native",        test_gnu_ctz_native,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/ctzl/native",       test_gnu_ctzl_native,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/ctzll/native",      test_gnu_ctzll_native,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/parity/native",     test_gnu_parity_native,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/parityl/native",    test_gnu_parityl_native,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/parityll/native",   test_gnu_parityll_native,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/popcount/native",   test_gnu_popcount_native,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/popcountl/native",  test_gnu_popcountl_native,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/builtin/popcountll/native", test_gnu_popcountll_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
#  endif
#endif
  { (char*) "/builtin/ffs",        test_gnu_ffs,        NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/ffsl",       test_gnu_ffsl,       NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/ffsll",      test_gnu_ffsll,      NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/clz",        test_gnu_clz,        NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/clzl",       test_gnu_clzl,       NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/clzll",      test_gnu_clzll,      NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/ctz",        test_gnu_ctz,        NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/ctzl",       test_gnu_ctzl,       NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/ctzll",      test_gnu_ctzll,      NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/parity",     test_gnu_parity,     NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/parityl",    test_gnu_parityl,    NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/parityll",   test_gnu_parityll,   NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/popcount",   test_gnu_popcount,   NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/popcountl",  test_gnu_popcountl,  NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/popcountll", test_gnu_popcountll, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
