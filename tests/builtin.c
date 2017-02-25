#include <stdlib.h>
#include <limits.h>

#include "munit/munit.h"

#define PSNIP_BUILTIN_EMULATE_NATIVE
#include "../builtin/builtin.h"

static MunitResult
test_gnu_ffs(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v = (int) (~0U);
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffs(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffs_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  v &= (int) (~0U << munit_rand_int_range(0, (sizeof(v) * 8) - 1));

  munit_assert_int(psnip_builtin_ffs(v), ==, __builtin_ffs(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long v = (long) (~0UL);
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffsl(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  v &= (long) (~0UL << munit_rand_int_range(0, (sizeof(v) * 8) - 1));

  munit_assert_int(psnip_builtin_ffsl(v), ==, __builtin_ffsl(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long long v = (long long) (~0ULL);
  int expected = 1;

  do {
    munit_assert_int(psnip_builtin_ffsll(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  /* Unset a random number of the least significant bits, otherwise
     we're heavily biased towards low results. */
  v &= (long long) (~0ULL << munit_rand_int_range(0, (sizeof(v) * 8) - 1));

  munit_assert_int(psnip_builtin_ffsll(v), ==, __builtin_ffsll(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clz(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_clzl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long v = ~0UL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clzl(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clzl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_clzll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v = ~0ULL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clzll(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clzll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_ctz(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctz(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctz_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_ctzl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctzl(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctzl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_ctzll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_ctzll(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctzll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

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

static MunitResult
test_gnu_parity(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parity(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_parity_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parity(v), ==, __builtin_parity(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long v = ~0UL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parityl(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parityl(v), ==, __builtin_parityl(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v = ~0ULL;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_parityll(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_parityll(v), ==, __builtin_parityll(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcount(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcount(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcount_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcount(v), ==, __builtin_popcount(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcountl(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcountl(v), ==, __builtin_popcountl(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  do {
    munit_assert_int(psnip_builtin_popcountll(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_popcountll(v), ==, __builtin_popcountll(v));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned char v = 'A';

  const unsigned char expected[] = {
    0x41, 0x82, 0x05, 0x0a,
    0x14, 0x28, 0x50, 0xa0
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uchar(psnip_intrin_rotl8(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl8_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned char v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uchar(psnip_intrin_rotl8(v, s), ==, _rotl8(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned short v = 0x12;

  const unsigned short expected[] = {
    0x0012, 0x0024, 0x0048, 0x0090,
    0x0120, 0x0240, 0x0480, 0x0900,
    0x1200, 0x2400, 0x4800, 0x9000,
    0x2001, 0x4002, 0x8004, 0x0009
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_ushort(psnip_intrin_rotl16(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl16_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_ushort(psnip_intrin_rotl16(v, s), ==, _rotl16(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned int v = 0x0fd93;

  const unsigned int expected[] = {
    0x0000fd93, 0x0001fb26, 0x0003f64c, 0x0007ec98,
    0x000fd930, 0x001fb260, 0x003f64c0, 0x007ec980,
    0x00fd9300, 0x01fb2600, 0x03f64c00, 0x07ec9800,
    0x0fd93000, 0x1fb26000, 0x3f64c000, 0x7ec98000,
    0xfd930000, 0xfb260001, 0xf64c0003, 0xec980007,
    0xd930000f, 0xb260001f, 0x64c0003f, 0xc980007e,
    0x930000fd, 0x260001fb, 0x4c0003f6, 0x980007ec,
    0x30000fd9, 0x60001fb2, 0xc0003f64, 0x80007ec9
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uint(psnip_intrin_rotl(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int v;
  const int s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uint(psnip_intrin_rotl(v, s), ==, _rotl(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const uint64_t v = UINT64_C(0x3db5195091e98f9d);

  const uint64_t expected[] = {
    UINT64_C(0x3db5195091e98f9d), UINT64_C(0x7b6a32a123d31f3a), UINT64_C(0xf6d4654247a63e74), UINT64_C(0xeda8ca848f4c7ce9),
    UINT64_C(0xdb5195091e98f9d3), UINT64_C(0xb6a32a123d31f3a7), UINT64_C(0x6d4654247a63e74f), UINT64_C(0xda8ca848f4c7ce9e),
    UINT64_C(0xb5195091e98f9d3d), UINT64_C(0x6a32a123d31f3a7b), UINT64_C(0xd4654247a63e74f6), UINT64_C(0xa8ca848f4c7ce9ed),
    UINT64_C(0x5195091e98f9d3db), UINT64_C(0xa32a123d31f3a7b6), UINT64_C(0x4654247a63e74f6d), UINT64_C(0x8ca848f4c7ce9eda),
    UINT64_C(0x195091e98f9d3db5), UINT64_C(0x32a123d31f3a7b6a), UINT64_C(0x654247a63e74f6d4), UINT64_C(0xca848f4c7ce9eda8),
    UINT64_C(0x95091e98f9d3db51), UINT64_C(0x2a123d31f3a7b6a3), UINT64_C(0x54247a63e74f6d46), UINT64_C(0xa848f4c7ce9eda8c),
    UINT64_C(0x5091e98f9d3db519), UINT64_C(0xa123d31f3a7b6a32), UINT64_C(0x4247a63e74f6d465), UINT64_C(0x848f4c7ce9eda8ca),
    UINT64_C(0x091e98f9d3db5195), UINT64_C(0x123d31f3a7b6a32a), UINT64_C(0x247a63e74f6d4654), UINT64_C(0x48f4c7ce9eda8ca8),
    UINT64_C(0x91e98f9d3db51950), UINT64_C(0x23d31f3a7b6a32a1), UINT64_C(0x47a63e74f6d46542), UINT64_C(0x8f4c7ce9eda8ca84),
    UINT64_C(0x1e98f9d3db519509), UINT64_C(0x3d31f3a7b6a32a12), UINT64_C(0x7a63e74f6d465424), UINT64_C(0xf4c7ce9eda8ca848),
    UINT64_C(0xe98f9d3db5195091), UINT64_C(0xd31f3a7b6a32a123), UINT64_C(0xa63e74f6d4654247), UINT64_C(0x4c7ce9eda8ca848f),
    UINT64_C(0x98f9d3db5195091e), UINT64_C(0x31f3a7b6a32a123d), UINT64_C(0x63e74f6d4654247a), UINT64_C(0xc7ce9eda8ca848f4),
    UINT64_C(0x8f9d3db5195091e9), UINT64_C(0x1f3a7b6a32a123d3), UINT64_C(0x3e74f6d4654247a6), UINT64_C(0x7ce9eda8ca848f4c),
    UINT64_C(0xf9d3db5195091e98), UINT64_C(0xf3a7b6a32a123d31), UINT64_C(0xe74f6d4654247a63), UINT64_C(0xce9eda8ca848f4c7),
    UINT64_C(0x9d3db5195091e98f), UINT64_C(0x3a7b6a32a123d31f), UINT64_C(0x74f6d4654247a63e), UINT64_C(0xe9eda8ca848f4c7c),
    UINT64_C(0xd3db5195091e98f9), UINT64_C(0xa7b6a32a123d31f3), UINT64_C(0x4f6d4654247a63e7), UINT64_C(0x9eda8ca848f4c7ce)
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uint64(psnip_intrin_rotl64(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uint64(psnip_intrin_rotl64(v, s), ==, _rotl64(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned char v = 'A';

  const unsigned char expected[] = {
    0x41, 0xa0, 0x50, 0x28,
    0x14, 0x0a, 0x05, 0x82
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uchar(psnip_intrin_rotr8(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr8_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned char v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uchar(psnip_intrin_rotr8(v, s), ==, _rotr8(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned short v = 0x12;

  const unsigned short expected[] = {
    0x0012, 0x0009, 0x8004, 0x4002,
    0x2001, 0x9000, 0x4800, 0x2400,
    0x1200, 0x0900, 0x0480, 0x0240,
    0x0120, 0x0090, 0x0048, 0x0024
  };

  int i;
  for (i = 0; i < sizeof(unsigned short) * CHAR_BIT; i++)
    munit_assert_ushort(psnip_intrin_rotr16(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr16_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_ushort(psnip_intrin_rotr16(v, s), ==, _rotr16(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const unsigned int v = 0x0fd93;

  const unsigned int expected[] = {
    UINT32_C(0x0000fd93), UINT32_C(0x80007ec9), UINT32_C(0xc0003f64), UINT32_C(0x60001fb2),
    UINT32_C(0x30000fd9), UINT32_C(0x980007ec), UINT32_C(0x4c0003f6), UINT32_C(0x260001fb),
    UINT32_C(0x930000fd), UINT32_C(0xc980007e), UINT32_C(0x64c0003f), UINT32_C(0xb260001f),
    UINT32_C(0xd930000f), UINT32_C(0xec980007), UINT32_C(0xf64c0003), UINT32_C(0xfb260001),
    UINT32_C(0xfd930000), UINT32_C(0x7ec98000), UINT32_C(0x3f64c000), UINT32_C(0x1fb26000),
    UINT32_C(0x0fd93000), UINT32_C(0x07ec9800), UINT32_C(0x03f64c00), UINT32_C(0x01fb2600),
    UINT32_C(0x00fd9300), UINT32_C(0x007ec980), UINT32_C(0x003f64c0), UINT32_C(0x001fb260),
    UINT32_C(0x000fd930), UINT32_C(0x0007ec98), UINT32_C(0x0003f64c), UINT32_C(0x0001fb26)
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uint(psnip_intrin_rotr(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uint(psnip_intrin_rotr(v, s), ==, _rotr(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const uint64_t v = UINT64_C(0x3db5195091e98f9d);

  const uint64_t expected[] = {
    UINT64_C(0x3db5195091e98f9d), UINT64_C(0x9eda8ca848f4c7ce), UINT64_C(0x4f6d4654247a63e7), UINT64_C(0xa7b6a32a123d31f3),
    UINT64_C(0xd3db5195091e98f9), UINT64_C(0xe9eda8ca848f4c7c), UINT64_C(0x74f6d4654247a63e), UINT64_C(0x3a7b6a32a123d31f),
    UINT64_C(0x9d3db5195091e98f), UINT64_C(0xce9eda8ca848f4c7), UINT64_C(0xe74f6d4654247a63), UINT64_C(0xf3a7b6a32a123d31),
    UINT64_C(0xf9d3db5195091e98), UINT64_C(0x7ce9eda8ca848f4c), UINT64_C(0x3e74f6d4654247a6), UINT64_C(0x1f3a7b6a32a123d3),
    UINT64_C(0x8f9d3db5195091e9), UINT64_C(0xc7ce9eda8ca848f4), UINT64_C(0x63e74f6d4654247a), UINT64_C(0x31f3a7b6a32a123d),
    UINT64_C(0x98f9d3db5195091e), UINT64_C(0x4c7ce9eda8ca848f), UINT64_C(0xa63e74f6d4654247), UINT64_C(0xd31f3a7b6a32a123),
    UINT64_C(0xe98f9d3db5195091), UINT64_C(0xf4c7ce9eda8ca848), UINT64_C(0x7a63e74f6d465424), UINT64_C(0x3d31f3a7b6a32a12),
    UINT64_C(0x1e98f9d3db519509), UINT64_C(0x8f4c7ce9eda8ca84), UINT64_C(0x47a63e74f6d46542), UINT64_C(0x23d31f3a7b6a32a1),
    UINT64_C(0x91e98f9d3db51950), UINT64_C(0x48f4c7ce9eda8ca8), UINT64_C(0x247a63e74f6d4654), UINT64_C(0x123d31f3a7b6a32a),
    UINT64_C(0x091e98f9d3db5195), UINT64_C(0x848f4c7ce9eda8ca), UINT64_C(0x4247a63e74f6d465), UINT64_C(0xa123d31f3a7b6a32),
    UINT64_C(0x5091e98f9d3db519), UINT64_C(0xa848f4c7ce9eda8c), UINT64_C(0x54247a63e74f6d46), UINT64_C(0x2a123d31f3a7b6a3),
    UINT64_C(0x95091e98f9d3db51), UINT64_C(0xca848f4c7ce9eda8), UINT64_C(0x654247a63e74f6d4), UINT64_C(0x32a123d31f3a7b6a),
    UINT64_C(0x195091e98f9d3db5), UINT64_C(0x8ca848f4c7ce9eda), UINT64_C(0x4654247a63e74f6d), UINT64_C(0xa32a123d31f3a7b6),
    UINT64_C(0x5195091e98f9d3db), UINT64_C(0xa8ca848f4c7ce9ed), UINT64_C(0xd4654247a63e74f6), UINT64_C(0x6a32a123d31f3a7b),
    UINT64_C(0xb5195091e98f9d3d), UINT64_C(0xda8ca848f4c7ce9e), UINT64_C(0x6d4654247a63e74f), UINT64_C(0xb6a32a123d31f3a7),
    UINT64_C(0xdb5195091e98f9d3), UINT64_C(0xeda8ca848f4c7ce9), UINT64_C(0xf6d4654247a63e74), UINT64_C(0x7b6a32a123d31f3a)
  };

  int i;
  for (i = 0; i < sizeof(v) * CHAR_BIT; i++)
    munit_assert_uint64(psnip_intrin_rotr64(v, i), ==, expected[i]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short v;
  const unsigned char s = munit_rand_int_range(0, (sizeof(v) * CHAR_BIT) - 1);

  munit_rand_memory(sizeof(v), (unsigned char*) &v);

  munit_assert_uint64(psnip_intrin_rotr64(v, s), ==, _rotr64(v, s));

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long index;
  unsigned char isNonzero;

  munit_assert_uint8(psnip_intrin_BitScanForward(&index, 0), ==, 0);

  int i;
  for (i = 0 ; i < 32 ; i++) {
    isNonzero = psnip_intrin_BitScanForward(&index, ULONG_MAX << i);
    munit_assert_uint8(isNonzero, ==, 1);
    munit_assert_ulong(index, ==, i);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask;
  unsigned long i1, i2;
  unsigned char z1, z2;
  munit_rand_memory(sizeof(mask), (unsigned char*) &mask);

  z1 = _BitScanForward(&i1, mask);
  z2 = psnip_intrin_BitScanForward(&i2, mask);
  munit_assert_uint8(z1, ==, z2);
  munit_assert_ulong(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long index;
  unsigned char isNonzero;

  munit_assert_uint8(psnip_intrin_BitScanForward64(&index, 0), ==, 0);

  int i;
  for (i = 0 ; i < 64 ; i++) {
    isNonzero = psnip_intrin_BitScanForward64(&index, ULLONG_MAX << i);
    munit_assert_uint8(isNonzero, ==, 1);
    munit_assert_ulong(index, ==, i);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask;
  unsigned long i1, i2;
  unsigned char z1, z2;
  munit_rand_memory(sizeof(mask), (unsigned char*) &mask);

  z1 = _BitScanForward64(&i1, mask);
  z2 = psnip_intrin_BitScanForward64(&i2, mask);
  munit_assert_uint8(z1, ==, z2);
  munit_assert_ulong(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  /* Yes, I know this only looks at 31 bits.  I'm trying to match
   * Microsoft's example on
   * https://msdn.microsoft.com/en-us/library/h65k4tze.aspx */

  int num = 78002;
  const char bits[] = "0100110100001100100000000000000";

  int nBit;
  for (nBit = 0 ; nBit < 31 ; nBit++)
    munit_assert_uint8(bits[nBit] == '1', ==, psnip_intrin_bittest(&num, nBit));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int nBit;
  long num;
  munit_rand_memory(sizeof(num), (uint8_t*) &num);

  for (nBit = 0 ; nBit < (sizeof(num) * CHAR_BIT) ; nBit++)
    munit_assert_uint8(_bittest(&num, nBit), ==,
		       psnip_intrin_bittest(&num, nBit));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int64_t num = UINT64_C(0x7273c4752334168f);
  const uint8_t bits[] = {
    1, 1, 1, 1, 0, 0, 0, 1,   0, 1, 1, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 1, 1, 0, 0,   1, 1, 0, 0, 0, 1, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0,   0, 0, 1, 0, 0, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 0,   0, 1, 0, 0, 1, 1, 1, 0
  };

  int i;
  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint8(bits[i], ==, psnip_intrin_bittest64(&num, i));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int nBit;
  int64_t num;
  munit_rand_memory(sizeof(num), (uint8_t*) &num);

  for (nBit = 0 ; nBit < (sizeof(num) * CHAR_BIT) ; nBit++)
    munit_assert_uint8(_bittest64(&num, nBit), ==,
		       psnip_intrin_bittest64(&num, nBit));

  return MUNIT_OK;
}

#define PSNIP_TEST_BUILTIN(name) \
  { (char*) "/builtin/"#name, test_gnu_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }, \
  { (char*) "/builtin/"#name"/native", test_gnu_##name##_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
#define PSNIP_TEST_INTRIN(name) \
  { (char*) "/intrin/"#name, test_msvc_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }, \
  { (char*) "/intrin/"#name"/native", test_msvc_##name##_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

static MunitTest test_suite_tests[] = {
  PSNIP_TEST_BUILTIN(ffs),
  PSNIP_TEST_BUILTIN(ffsl),
  PSNIP_TEST_BUILTIN(ffsll),
  PSNIP_TEST_BUILTIN(clz),
  PSNIP_TEST_BUILTIN(clzl),
  PSNIP_TEST_BUILTIN(clzll),
  PSNIP_TEST_BUILTIN(ctz),
  PSNIP_TEST_BUILTIN(ctzl),
  PSNIP_TEST_BUILTIN(ctzll),
  PSNIP_TEST_BUILTIN(parity),
  PSNIP_TEST_BUILTIN(parityl),
  PSNIP_TEST_BUILTIN(parityll),
  PSNIP_TEST_BUILTIN(popcount),
  PSNIP_TEST_BUILTIN(popcountl),
  PSNIP_TEST_BUILTIN(popcountll),

  PSNIP_TEST_INTRIN(rotl8),
  PSNIP_TEST_INTRIN(rotl16),
  PSNIP_TEST_INTRIN(rotl),
  PSNIP_TEST_INTRIN(rotl64),
  PSNIP_TEST_INTRIN(BitScanForward),
  PSNIP_TEST_INTRIN(BitScanForward64),
  PSNIP_TEST_INTRIN(bittest),
  PSNIP_TEST_INTRIN(bittest64),

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
