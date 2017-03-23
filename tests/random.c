#include "../random/random.h"
#include "munit/munit.h"

static MunitResult
test_random_secure(const MunitParameter params[], void* data) {
  psnip_uint8_t buf[4096] = { 0, };
  int r;
  size_t p;

  (void) params;
  (void) data;

  r = psnip_random_bytes(PSNIP_RANDOM_SOURCE_SECURE, sizeof(buf), buf);
  munit_assert_int(r, ==, 0);

  /* Make sure we actually read some data. */
  for (p = 0 ; p < sizeof(buf) ; p++)
    if (buf[p] != 0)
      break;

  munit_assert_size(p, <, sizeof(buf));

  return MUNIT_OK;
}

static MunitResult
test_random_reproducible(const MunitParameter params[], void* data) {
  const psnip_uint32_t test_data[] = {
    0x8a4b308cU, 0x15534978U, 0xfec18d9aU, 0x7f345f7dU,
    0x297766eeU, 0x771fb9f4U, 0x31e5a255U, 0xd0c9819dU,
    0xef73a350U, 0xd9d26480U, 0xb5367e1aU, 0xc1a02725U,
    0x8b2a1228U, 0x735c43f6U, 0x63ca3280U, 0x9bcd8362U,
    0xac305d31U, 0x45f16be6U, 0x53247d92U, 0x363d54fbU,
    0xaccbf201U, 0xc5963be4U, 0x646402c1U, 0xcbbf2841U,
    0x16c42c02U, 0xf1b19a74U, 0xe2c78da3U, 0x352ac7a4U,
    0x0e208ef3U, 0x94fec876U, 0x9fd96b4bU, 0x3ed00c53U
  };
  psnip_uint32_t buf[sizeof(test_data) / sizeof(test_data[0])] = { 0, };
  size_t i;
  int r;

  (void) params;
  (void) data;

  psnip_random_set_seed(1729);

  r = psnip_random_bytes(PSNIP_RANDOM_SOURCE_REPRODUCIBLE, sizeof(buf), (psnip_uint8_t*) buf);
  munit_assert_int(r, ==, 0);

  for (i = 0 ; i < sizeof(buf) / sizeof(buf[0]) ; i++) {
    munit_assert_uint32(buf[i], ==, test_data[i]);
  }

  return MUNIT_OK;
}

static MunitResult
test_random_fast(const MunitParameter params[], void* data) {
  psnip_uint8_t buf[4096] = { 0, };
  int r;
  size_t p;

  (void) params;
  (void) data;

  r = psnip_random_bytes(PSNIP_RANDOM_SOURCE_FAST, sizeof(buf), buf);
  munit_assert_int(r, ==, 0);

  /* Make sure we actually read some data. */
  for (p = 0 ; p < sizeof(buf) ; p++)
    if (buf[p] != 0)
      break;

  munit_assert_size(p, <, sizeof(buf));

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/random/secure",       test_random_secure,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/random/reproducible", test_random_reproducible, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/random/fast",         test_random_fast,         NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
