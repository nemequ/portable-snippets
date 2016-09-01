#include <stdlib.h>
#include <stdint.h>
#include "munit/munit.h"

#define PSNIP_BUILTIN_ALWAYS_FALLBACK
#include "../builtin/builtin-gnu.h"
#undef PSNIP_BUILTIN_ALWAYS_FALLBACK

static MunitResult
test_gnu_ffs(const MunitParameter params[], void* data) {
	int v = (int)(~0U);
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
	int v;

	munit_rand_memory(sizeof(int), (uint8_t*) &v);

	/* Unset a random number of the least significant bits, otherwise
		 we're heavily biased towards low results. */
	const int m = ((int) ~0U) << munit_rand_int_range(0, (sizeof(int) * 8) - 1);
	v &= m;

	munit_assert_int(psnip_builtin_ffs(v), ==, __builtin_ffs(v));

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

#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
static MunitResult
test_gnu_clz_native(const MunitParameter params[], void* data) {
	unsigned int v;

	/* __builtin_clz(0) is undefined, so make sure we don't test it.
	 * That said, here it returns 1 less than the number of bits in the
	 * number. */
	do {
		munit_rand_memory(sizeof(unsigned int), (uint8_t*) &v);

		/* Unset a random number of the most significant bits, otherwise
			 we're heavily biased towards low results. */
		const unsigned int m = (~0U) >> munit_rand_int_range(0, (sizeof(unsigned int) * 8) - 1);
		v &= m;
	} while (v == 0);

	munit_assert_int(psnip_builtin_clz(v), ==, __builtin_clz(v));

  return MUNIT_OK;
}
#endif

static MunitTest test_suite_tests[] = {
#if defined(__GNUC__)
#  if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
  { (char*) "/builtin/ffs/native", test_gnu_ffs_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
#  endif
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
  { (char*) "/builtin/clz/native", test_gnu_clz_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
#  endif
#endif
  { (char*) "/builtin/ffs", test_gnu_ffs, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/builtin/clz", test_gnu_clz, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
