#include <stdlib.h>
#include <stdint.h>
#include "../endian/endian.h"
#include "munit/munit.h"

const union {
  unsigned char bytes[2];
  PSNIP_ENDIAN_UINT16_T value;
} test_data_16 = {
  { 1, 2 }
};

const union {
  unsigned char bytes[4];
  PSNIP_ENDIAN_UINT32_T value;
} test_data_32 = {
  { 1, 2, 3, 4 }
};

const union {
  unsigned char bytes[8];
  PSNIP_ENDIAN_UINT64_T value;
} test_data_64 = {
  { 1, 2, 3, 4, 5, 6, 7, 8 }
};

static MunitResult
test_endian_swap_known(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(PSNIP_BSWAP16(UINT16_C(0xefbe)), ==, UINT16_C(0xbeef));
  munit_assert_uint32(PSNIP_BSWAP32(UINT32_C(0xefbeadde)), ==, UINT32_C(0xdeadbeef));
  munit_assert_uint64(PSNIP_BSWAP64(UINT64_C(0x0df0dde0fe0fdcba)), ==, UINT64_C(0xbadc0ffee0ddf00d));

  return MUNIT_OK;
}

static MunitResult
test_endian_swap_random(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(PSNIP_BSWAP16(UINT16_C(0xefbe)), ==, UINT16_C(0xbeef));
  {
    const uint16_t input = (uint16_t) munit_rand_uint32();
    const uint16_t swapped = PSNIP_BSWAP16(input);
    const uint16_t double_swapped = PSNIP_BSWAP16(swapped);

    munit_assert_uint16(input, ==, double_swapped);
  }

  munit_assert_uint32(PSNIP_BSWAP32(UINT32_C(0xefbeadde)), ==, UINT32_C(0xdeadbeef));
  {
    const uint32_t input = munit_rand_uint32();
    const uint32_t swapped = PSNIP_BSWAP32(input);
    const uint32_t double_swapped = PSNIP_BSWAP32(swapped);

    munit_assert_uint32(input, ==, double_swapped);
  }

  munit_assert_uint64(PSNIP_BSWAP64(UINT64_C(0xdf0dde0fe0fdcba)), ==, UINT64_C(0xbadc0ffee0ddf00d));
  {
    const uint64_t input = (((uint64_t) munit_rand_uint32()) << 8) | munit_rand_uint32();
    const uint64_t swapped = PSNIP_BSWAP64(input);
    const uint64_t double_swapped = PSNIP_BSWAP64(swapped);

    munit_assert_uint64(input, ==, double_swapped);
  }

  return MUNIT_OK;
}

static MunitResult
test_endian_from_be(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(PSNIP_READ_BE16(test_data_16.value), ==, UINT16_C(0x0102));
  munit_assert_uint32(PSNIP_READ_BE32(test_data_32.value), ==, UINT32_C(0x01020304));
  munit_assert_uint64(PSNIP_READ_BE64(test_data_64.value), ==, UINT64_C(0x0102030405060708));

  return MUNIT_OK;
}

static MunitResult
test_endian_from_le(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(PSNIP_READ_LE16(test_data_16.value), ==, UINT16_C(0x0201));
  munit_assert_uint32(PSNIP_READ_LE32(test_data_32.value), ==, UINT32_C(0x04030201));
  munit_assert_uint64(PSNIP_READ_LE64(test_data_64.value), ==, UINT64_C(0x0807060504030201));

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/endian/swap/known", test_endian_swap_known, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/endian/swap/random", test_endian_swap_random, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/endian/from-be", test_endian_from_be, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/endian/from-le", test_endian_from_le, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 16384, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
