#include <stdlib.h>
#include "../atomic/atomic.h"
#include "munit/munit.h"

#if !defined(PSNIP_ATOMIC_NOT_FOUND)
static psnip_atomic_int64 value64 = PSNIP_ATOMIC_VAR_INIT(9);
static psnip_atomic_int32 value32 = PSNIP_ATOMIC_VAR_INIT(9);
#endif

static MunitResult
test_atomic_int64(const MunitParameter params[], void* data) {
#if !defined(PSNIP_ATOMIC_NOT_FOUND)
  psnip_int64_t v, expected;
#endif

  (void) params;
  (void) data;

#if !defined(PSNIP_ATOMIC_NOT_FOUND)
  v = psnip_atomic_int64_load(&value64);
  munit_assert_int64(v, ==, 9);

  v = v * v * v;
  psnip_atomic_int64_store(&value64, v);
  v = psnip_atomic_int64_load(&value64);
  munit_assert_int64(v, ==, 729);

  psnip_atomic_int64_add(&value64, 1000);
  v = psnip_atomic_int64_load(&value64);
  munit_assert_int64(v, ==, 1729);

  psnip_atomic_int64_sub(&value64, 729);
  v = psnip_atomic_int64_load(&value64);
  munit_assert_int64(v, ==, 1000);

  do {
    expected = psnip_atomic_int64_load(&value64);
    v = expected * expected;
  } while (!psnip_atomic_int64_compare_exchange(&value64, &expected, v));
  v = psnip_atomic_int64_load(&value64);
  munit_assert_int64(v, ==, 1000 * 1000);

  return MUNIT_OK;
#else
  return MUNIT_SKIP;
#endif
}

static MunitResult
test_atomic_int32(const MunitParameter params[], void* data) {
#if !defined(PSNIP_ATOMIC_NOT_FOUND)
  psnip_int32_t v, expected;
#endif

  (void) params;
  (void) data;

#if !defined(PSNIP_ATOMIC_NOT_FOUND)
  v = psnip_atomic_int32_load(&value32);
  munit_assert_int32(v, ==, 9);

  v = v * v * v;
  psnip_atomic_int32_store(&value32, v);
  v = psnip_atomic_int32_load(&value32);
  munit_assert_int32(v, ==, 729);

  psnip_atomic_int32_add(&value32, 1000);
  v = psnip_atomic_int32_load(&value32);
  munit_assert_int32(v, ==, 1729);

  psnip_atomic_int32_sub(&value32, 729);
  v = psnip_atomic_int32_load(&value32);
  munit_assert_int32(v, ==, 1000);

  do {
    expected = psnip_atomic_int32_load(&value32);
    v = expected * expected;
  } while (!psnip_atomic_int32_compare_exchange(&value32, &expected, v));
  v = psnip_atomic_int32_load(&value32);
  munit_assert_int32(v, ==, 1000 * 1000);

  return MUNIT_OK;
#else
  return MUNIT_SKIP;
#endif
}

static MunitTest test_suite_tests[] = {
  { (char*) "/atomic/int64", test_atomic_int64, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/atomic/int32", test_atomic_int32, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
