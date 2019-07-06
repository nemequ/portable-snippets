#include "../exact-int/exact-int.h"
#include "../cpu/cpu.h"
#include "munit/munit.h"

static MunitResult
test_cpu_info(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

#if defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ > 7))
#  if defined(PSNIP_CPU_ARCH_X86_64) || defined(PSNIP_CPU_ARCH_X86)
  __builtin_cpu_init();

  munit_assert_int(__builtin_cpu_supports("cmov")    != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_CMOV));
  munit_assert_int(__builtin_cpu_supports("mmx")     != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_MMX));
  munit_assert_int(__builtin_cpu_supports("popcnt")  != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_POPCNT));
  munit_assert_int(__builtin_cpu_supports("sse")     != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_SSE));
  munit_assert_int(__builtin_cpu_supports("sse2")    != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_SSE2));
  munit_assert_int(__builtin_cpu_supports("sse3")    != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_SSE3));
  munit_assert_int(__builtin_cpu_supports("sse4.1")  != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_SSE4_1));
  munit_assert_int(__builtin_cpu_supports("sse4.2")  != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_SSE4_2));
  munit_assert_int(__builtin_cpu_supports("avx")     != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_AVX));
  munit_assert_int(__builtin_cpu_supports("avx2")    != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_AVX2));
#if __GNUC__ >= 5
  munit_assert_int(__builtin_cpu_supports("avx512f") != 0, ==, psnip_cpu_feature_check(PSNIP_CPU_FEATURE_X86_AVX512F));
#endif

  return MUNIT_OK;
#  endif
#endif

  return MUNIT_SKIP;
}

static MunitResult
test_cpu_count(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_int(psnip_cpu_count(), >, 0);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/cpu/info",  test_cpu_info,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/cpu/count", test_cpu_count, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
