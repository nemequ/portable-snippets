#if defined(PSNIP_ENABLE_PTHREADS)
#  include <pthread.h>
#endif
#include "../once/once.h"
#include "munit/munit.h"

static psnip_once test_once_basic_once = PSNIP_ONCE_INIT;
static int test_once_basic_times_called = 0;

static void test_once_basic_init(void) {
  munit_assert_int(test_once_basic_times_called, ==, 0);
  test_once_basic_times_called++;
}

static MunitResult
test_once_basic(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_int(test_once_basic_times_called, ==, 0);
  psnip_once_call(&test_once_basic_once, &test_once_basic_init);
  munit_assert_int(test_once_basic_times_called, ==, 1);
  psnip_once_call(&test_once_basic_once, &test_once_basic_init);
  munit_assert_int(test_once_basic_times_called, ==, 1);
  psnip_once_call(&test_once_basic_once, &test_once_basic_init);
  munit_assert_int(test_once_basic_times_called, ==, 1);

  return MUNIT_OK;
}

/* TODO: thread safety test. */

static MunitTest test_suite_tests[] = {
  { (char*) "/once/basic", test_once_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
