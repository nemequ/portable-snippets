#include "../clock/clock.h"
#include "munit/munit.h"

/* These tests can yield false positives in some situations, but I'm
 * having trouble thinking of better ways to test.  Ideas welcome. */

#if !defined(_WIN32)
#  include <unistd.h>
#  define sleep_seconds(n) sleep(n)
#else
#  include <Windows.h>
#  define sleep_seconds(n) Sleep((n) * 1000)
#endif

static MunitResult
test_clock_wall_time(const MunitParameter params[], void* data) {
#if defined(PSNIP_CLOCK_WALL_METHOD)
  struct PsnipClockTimespec res;
  psnip_uint32_t precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_WALL);
  time_t t;
  int r;

  (void) params;
  (void) data;

  munit_logf(MUNIT_LOG_DEBUG, "Wall clock method: %d", PSNIP_CLOCK_WALL_METHOD);

  munit_assert_uint32(precision, !=, 0);

  t = time(NULL);
  /* This test may fail if more than 1 second passes here, but this
   * thread could conceivably be preempted for longer. */
  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res);
  munit_assert_int(r, ==, 0);

  munit_assert_uint64(t, <=, res.seconds);
  munit_assert_uint64(t, >=, res.seconds - 1);

  return MUNIT_OK;
#else
  (void) params;
  (void) data;

  return MUNIT_SKIP;
#endif
}

static int ts_difference(struct PsnipClockTimespec* earlier, struct PsnipClockTimespec* later) {
  return
    (int) ((later->seconds - earlier->seconds) * 1000) +
    (int) ((((psnip_int64_t) later->nanoseconds) - ((psnip_int64_t) earlier->nanoseconds)) / 1000000);
}

static MunitResult
test_clock_wall_veracity(const MunitParameter params[], void* data) {
#if defined(PSNIP_CLOCK_WALL_METHOD)
  struct PsnipClockTimespec res1, res2;
  int elapsed_ms;
  int r;

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res1);
  munit_assert_int(r, ==, 0);

  /* Assuming we aren't interrupted by a signal, aren't suspended for
   * much more than 1 seconds, etc. */
  sleep_seconds(1);

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res2);
  munit_assert_int(r, ==, 0);

  elapsed_ms = ts_difference(&res1, &res2);

  munit_assert_int(elapsed_ms, >,  950);
  munit_assert_int(elapsed_ms, <, 1050);

  (void) params;
  (void) data;

  return MUNIT_OK;
#else
  (void) params;
  (void) data;

  return MUNIT_SKIP;
#endif
}

static MunitResult
test_clock_cpu(const MunitParameter params[], void* data) {
#if defined(PSNIP_CLOCK_CPU_METHOD)
  struct PsnipClockTimespec res1, res2;
  psnip_uint32_t precision = psnip_clock_get_precision(PSNIP_CLOCK_TYPE_WALL);
  int r;
  int elapsed_ms;

  munit_logf(MUNIT_LOG_DEBUG, "CPU clock method: %d", PSNIP_CLOCK_CPU_METHOD);

  munit_assert_uint32(precision, !=, 0);

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res1);
  munit_assert_int(r, ==, 0);

  sleep_seconds(1);

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_WALL, &res2);
  munit_assert_int(r, ==, 0);

  elapsed_ms = ts_difference(&res1, &res2);

  munit_assert_int(elapsed_ms, >=, 1000);
  if (precision >= 1000)
    munit_assert_int(elapsed_ms, <=, 1010);

  (void) params;
  (void) data;

  return MUNIT_OK;
#else
  (void) params;
  (void) data;

  return MUNIT_SKIP;
#endif
}

static MunitResult
test_clock_monotonic(const MunitParameter params[], void* data) {

#if defined(PSNIP_CLOCK_MONOTONIC_METHOD)
  struct PsnipClockTimespec res1, res2;
  int r;
  int elapsed_ms;

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_MONOTONIC, &res1);
  munit_assert_int(r, ==, 0);

  /* Assuming we aren't interrupted by a signal, aren't suspended for
   * much more than 2 seconds, etc. */
  sleep_seconds(1);

  r = psnip_clock_get_time(PSNIP_CLOCK_TYPE_MONOTONIC, &res2);
  munit_assert_int(r, ==, 0);

  elapsed_ms = ts_difference(&res1, &res2);

  munit_assert_int(elapsed_ms, >,  950);
  munit_assert_int(elapsed_ms, <, 1050);

  (void) params;
  (void) data;

  return MUNIT_OK;
#else
  return MUNIT_SKIP;
#endif
}

static MunitTest test_suite_tests[] = {
  { (char*) "/clock/wall/time",     test_clock_wall_time,     NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/clock/wall/veracity", test_clock_wall_veracity, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/clock/cpu",           test_clock_cpu,           NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/clock/monotonic",     test_clock_monotonic,     NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 16384, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
