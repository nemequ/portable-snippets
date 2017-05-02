#include <stdlib.h>
#include "../endian/endian.h"
#include "munit/munit.h"

const union {
  unsigned char bytes[2];
  psnip_uint16_t value;
} test_data_16 = {
  { 1, 2 }
};

const union {
  unsigned char bytes[4];
  psnip_uint32_t value;
} test_data_32 = {
  { 1, 2, 3, 4 }
};

const union {
  unsigned char bytes[8];
  psnip_uint64_t value;
} test_data_64 = {
  { 1, 2, 3, 4, 5, 6, 7, 8 }
};

#if !defined(UINT8_C)
#  define UINT8_C(c) ((psnip_uint8_t) (c ## U))
#endif
#if !defined(UINT16_C)
#  define UINT16_C(c) ((psnip_uint16_t) (c ## U))
#endif
#if !defined(UINT32_C)
#  define UINT32_C(c) c ## U
#endif
#if !defined(UINT64_C)
#  define UINT64_C(c) c ## ULL
#endif

static MunitResult
test_endian_swap_known(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(psnip_builtin_bswap16(UINT16_C(0xefbe)), ==, UINT16_C(0xbeef));
  munit_assert_uint32(psnip_builtin_bswap32(UINT32_C(0xefbeadde)), ==, UINT32_C(0xdeadbeef));
  munit_assert_uint64(psnip_builtin_bswap64(UINT64_C(0x0df0dde0fe0fdcba)), ==, UINT64_C(0xbadc0ffee0ddf00d));

  return MUNIT_OK;
}

static MunitResult
test_endian_swap_random(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(psnip_builtin_bswap16(UINT16_C(0xefbe)), ==, UINT16_C(0xbeef));
  {
    const psnip_uint16_t input = (psnip_uint16_t) munit_rand_uint32();
    const psnip_uint16_t swapped = psnip_builtin_bswap16(input);
    const psnip_uint16_t double_swapped = psnip_builtin_bswap16(swapped);

    munit_assert_uint16(input, ==, double_swapped);
  }

  munit_assert_uint32(psnip_builtin_bswap32(UINT32_C(0xefbeadde)), ==, UINT32_C(0xdeadbeef));
  {
    const psnip_uint32_t input = munit_rand_uint32();
    const psnip_uint32_t swapped = psnip_builtin_bswap32(input);
    const psnip_uint32_t double_swapped = psnip_builtin_bswap32(swapped);

    munit_assert_uint32(input, ==, double_swapped);
  }

  munit_assert_uint64(psnip_builtin_bswap64(UINT64_C(0xdf0dde0fe0fdcba)), ==, UINT64_C(0xbadc0ffee0ddf00d));
  {
    const psnip_uint64_t input = (((psnip_uint64_t) munit_rand_uint32()) << 32) | munit_rand_uint32();
    const psnip_uint64_t swapped = psnip_builtin_bswap64(input);
    const psnip_uint64_t double_swapped = psnip_builtin_bswap64(swapped);

    munit_assert_uint64(input, ==, double_swapped);
  }

  return MUNIT_OK;
}

static MunitResult
test_endian_from_be(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(psnip_endian_be16(test_data_16.value), ==, UINT16_C(0x0102));
  munit_assert_uint32(psnip_endian_be32(test_data_32.value), ==, UINT32_C(0x01020304));
  munit_assert_uint64(psnip_endian_be64(test_data_64.value), ==, UINT64_C(0x0102030405060708));

  return MUNIT_OK;
}

static MunitResult
test_endian_from_le(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  munit_assert_uint16(psnip_endian_le16(test_data_16.value), ==, UINT16_C(0x0201));
  munit_assert_uint32(psnip_endian_le32(test_data_32.value), ==, UINT32_C(0x04030201));
  munit_assert_uint64(psnip_endian_le64(test_data_64.value), ==, UINT64_C(0x0807060504030201));

  return MUNIT_OK;
}

static MunitResult
test_endian_match_rt(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

#if defined(PSNIP_ENDIAN_ORDER)
  munit_assert_uint32(PSNIP_ENDIAN_ORDER, ==, PSNIP_ENDIAN_ORDER_RT);
#endif

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/endian/swap/known", test_endian_swap_known, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/endian/swap/random", test_endian_swap_random, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/endian/from-be", test_endian_from_be, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/endian/from-le", test_endian_from_le, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { (char*) "/endian/match-rt", test_endian_match_rt, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 16384, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
