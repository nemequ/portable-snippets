#include "../clock/clock.h"
#include "munit/munit.h"

static MunitResult
test_clock_wall(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

#if defined(PSNIP_CLOCK_WALL_METHOD)
  struct PsnipClockTimespec res;
  psnip_uint32_t precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_WALL);

  munit_logf(MUNIT_LOG_DEBUG, "Wall clock method: %d", PSNIP_CLOCK_WALL_METHOD);

  munit_assert_uint32(precision, !=, 0);

  int r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res);
  munit_assert_int(r, ==, 0);
#else
  return MUNIT_SKIP;
#endif

  return MUNIT_OK;
}

static MunitResult
test_clock_cpu(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

#if defined(PSNIP_CLOCK_CPU_METHOD)
  struct PsnipClockTimespec res;
  psnip_uint32_t precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_CPU);

  munit_logf(MUNIT_LOG_DEBUG, "CPU clock method: %d", PSNIP_CLOCK_CPU_METHOD);

  munit_assert_uint32(precision, !=, 0);

  int r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res);
  munit_assert_int(r, ==, 0);
#else
  return MUNIT_SKIP;
#endif

  return MUNIT_OK;
}

static MunitResult
test_clock_monotonic(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

#if defined(PSNIP_CLOCK_MONOTONIC_METHOD)
  struct PsnipClockTimespec res;
  psnip_uint32_t precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_MONOTONIC);

  munit_logf(MUNIT_LOG_DEBUG, "Monotonic clock method: %d", PSNIP_CLOCK_MONOTONIC_METHOD);

  munit_assert_uint32(precision, !=, 0);

  int r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res);
  munit_assert_int(r, ==, 0);
#else
  return MUNIT_SKIP;
#endif

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/clock/wall",      test_clock_wall,      NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/clock/cpu",       test_clock_cpu,       NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/clock/monotonic", test_clock_monotonic, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 16384, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
