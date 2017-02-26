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
test_gnu_clrsb(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v = ~0;
  int expected = (sizeof(v) * 8) - 1;

  do {
    munit_assert_int(psnip_builtin_clrsb(v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsb_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_clrsb(v), ==, __builtin_clrsb(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long v = ~(0L);
  int expected = (sizeof(v) * 8) - 1;

  do {
    munit_assert_int(psnip_builtin_clrsbl(v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_clrsbl(v), ==, __builtin_clrsbl(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long long v = ~(0LL);
  int expected = (sizeof(v) * 8) - 1;

  do {
    munit_assert_int(psnip_builtin_clrsbll(v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long long v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_clrsbll(v), ==, __builtin_clrsbll(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint16_t v = (psnip_uint16_t) 0xAABBULL;

  munit_assert_uint16(psnip_builtin_bswap16(v), ==, ((psnip_uint16_t) 0xBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap16_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bswap16(v), ==, __builtin_bswap16(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint32_t v = (psnip_uint32_t) 0xAABBCCDDULL;

  munit_assert_uint32(psnip_builtin_bswap32(v), ==, ((psnip_uint32_t) 0xDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap32_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bswap32(v), ==, __builtin_bswap32(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint64_t v = (psnip_uint64_t) 0xAABBCCDDEEFF0011ULL;

  munit_assert_uint64(psnip_builtin_bswap64(v), ==, ((psnip_uint64_t) 0x1100FFEEDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bswap64(v), ==, __builtin_bswap64(v));

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

static MunitResult
test_msvc_byteswap_ushort(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint16_t v = (psnip_uint16_t) 0xAABBULL;

  munit_assert_uint16(psnip_intrin_byteswap_ushort(v), ==, ((psnip_uint16_t) 0xBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_ushort_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_intrin_byteswap_ushort(v), ==, _byteswap_ushort(v));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_ulong(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint32_t v = (psnip_uint32_t) 0xAABBCCDDULL;

  munit_assert_uint32(psnip_intrin_byteswap_ulong(v), ==, ((psnip_uint32_t) 0xDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_ulong_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_intrin_byteswap_ulong(v), ==, _byteswap_ulong(v));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_uint64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint64_t v = (psnip_uint64_t) 0xAABBCCDDEEFF0011ULL;

  munit_assert_uint64(psnip_intrin_byteswap_uint64(v), ==, ((psnip_uint64_t) 0x1100FFEEDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_uint64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  int v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_intrin_byteswap_uint64(v), ==, _byteswap_uint64(v));

  return MUNIT_OK;
}

static MunitResult
test_msvc_umul128(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { uint64_t a; uint64_t b; uint64_t h; uint64_t l; } test_vec[] = {
    { UINT64_C(0xC6B6DDC01F733A90), UINT64_C(0xA4C45B9EF559B578),
      UINT64_C(0x7FE5912F3F60B226), UINT64_C(0xDB945346627B4380) },
    { UINT64_C(0x36A8CA1B03821DB8), UINT64_C(0x62A40AA599B7ED91),
      UINT64_C(0x150FA3C5C4278673), UINT64_C(0xA90418EAA8BE2D38) },
    { UINT64_C(0xE81E7C6D89E34775), UINT64_C(0x4F0CE32721B92CCB),
      UINT64_C(0x47AD17CA263D8458), UINT64_C(0x55F711D7200EC5C7) },
    { UINT64_C(0x10937DA4C092E2F3), UINT64_C(0x5F58E0FCBA6AB3C8),
      UINT64_C(0x062C7CE4BF4A9D64), UINT64_C(0x15EAD847AE0F36D8) },
    { UINT64_C(0xE5CC9A7274E29934), UINT64_C(0x7EA66F3C4BCE6796),
      UINT64_C(0x71B01A8A52B75EB8), UINT64_C(0x5DA071812C41B078) },
    { UINT64_C(0xC5A143BD388777F3), UINT64_C(0x7DC4583D50A86925),
      UINT64_C(0x611751AA067404F9), UINT64_C(0xD17DF1D2633F011F) },
    { UINT64_C(0x441DEAF5ECE144D8), UINT64_C(0x47D243590296EFDB),
      UINT64_C(0x131C3EA076043C90), UINT64_C(0x7C6B9E27FA8B8CC8) },
    { UINT64_C(0x8A9A3484A5C686FA), UINT64_C(0x53E028F096743BEA),
      UINT64_C(0x2D695C1F500BAAD1), UINT64_C(0x58419EDFEDDAFE84) },
    { UINT64_C(0xBD5AB164F183D7DE), UINT64_C(0x9FEDEC643D502DB1),
      UINT64_C(0x764B4FFDACC4BE9D), UINT64_C(0xF702439A847A467E) },
    { UINT64_C(0x33B2D543F63838FC), UINT64_C(0xDB499F10330C81C7),
      UINT64_C(0x2C48DA8F4BF50007), UINT64_C(0xF97BD8A39A3B47E4) },
    { UINT64_C(0x36AE1CA1B71F7882), UINT64_C(0x91F3B4A7A1CF61BC),
      UINT64_C(0x1F2CAC13007FD40C), UINT64_C(0x974D2F2F9AE3C178) },
    { UINT64_C(0x966F9286CB83354A), UINT64_C(0x2B9EDBCD2CB756FE),
      UINT64_C(0x19A217A317593508), UINT64_C(0x2F96AC51CFFBBB6C) },
    { UINT64_C(0xD4D8EC9DFD60D07C), UINT64_C(0xA3367BA56A002FB1),
      UINT64_C(0x87B36B38434A7B5D), UINT64_C(0x2A10A5004E36E9BC) },
    { UINT64_C(0x8B6E41935FEA44F7), UINT64_C(0xBA24076A1993732C),
      UINT64_C(0x6561BB3019C9F523), UINT64_C(0xD205BCF27213CF74) },
    { UINT64_C(0x2DB6930675FF6D7D), UINT64_C(0x85DB0F7C6D7A8BAD),
      UINT64_C(0x17E6F8560C6DDBFC), UINT64_C(0x919A3653D4A1DC79) },
    { UINT64_C(0x98150D54B680492B), UINT64_C(0xEF3AAFBC98EF68B9),
      UINT64_C(0x8E1E849D8A008A1F), UINT64_C(0xA40BBA25D7935813) },
    { UINT64_C(0x03631E773C4F414F), UINT64_C(0x6124A42AACDA0DF9),
      UINT64_C(0x01490AA786AF6026), UINT64_C(0x2AF69E5E60AD88D7) },
    { UINT64_C(0x1DF3499565E4BE4B), UINT64_C(0xECB8422823BDB38B),
      UINT64_C(0x1BB1D670087A9420), UINT64_C(0xEE7BFBFA02A0C3B9) },
    { UINT64_C(0x45288C96F038F19C), UINT64_C(0xFD010C977F1CCA5C),
      UINT64_C(0x44595B808BD81C23), UINT64_C(0x95B5F8E6142BEC10) },
    { UINT64_C(0xA6D037A9992FB2B9), UINT64_C(0x87F9C1C01E1C523F),
      UINT64_C(0x589A8C20BD7D9D37), UINT64_C(0xF406E1B734383D87) },
    { UINT64_C(0x175E4B7396E8334C), UINT64_C(0x46BEAFCC7BEEB716),
      UINT64_C(0x067530A9BB15BB42), UINT64_C(0xEF83CDE42947BC88) },
    { UINT64_C(0xDFB44F5A02B80516), UINT64_C(0x9E868828BF70F87C),
      UINT64_C(0x8A86D8567C697632), UINT64_C(0x549699F939AFC6A8) },
    { UINT64_C(0xDAAB24D49C87C73F), UINT64_C(0x3D22AECC3A3662E7),
      UINT64_C(0x343867D052AC3B40), UINT64_C(0x43D4FFC18614E7D9) },
    { UINT64_C(0x3CBE6D4DA6BA5216), UINT64_C(0x79B2016AD4115BB4),
      UINT64_C(0x1CE03E67CB645F13), UINT64_C(0x33BDE65321A58978) },
    { UINT64_C(0x661B70A120207C80), UINT64_C(0x1F6155FEB27FE93E),
      UINT64_C(0x0C842555E2C273DF), UINT64_C(0xF27F7AF21CAEA700) },
    { UINT64_C(0xF7232C6E1CEAD21E), UINT64_C(0xEF8441BAFE88518E),
      UINT64_C(0xE73984122954E017), UINT64_C(0x0D301D3FBAAC0AA4) },
    { UINT64_C(0xC3EF3F18774FDFE6), UINT64_C(0xB6956BDA10E0981C),
      UINT64_C(0x8BBE73A704160913), UINT64_C(0x09F69D42C2ED0D28) },
    { UINT64_C(0xC52C2CA7225C532F), UINT64_C(0xB9BC92BF44A19E5B),
      UINT64_C(0x8F0E29BC14DACCD1), UINT64_C(0x2C5706D7FEB793B5) },
    { UINT64_C(0x62B4AA64745EF71E), UINT64_C(0xC4F5DA4D4EFEF3C2),
      UINT64_C(0x4BF11D87A322388D), UINT64_C(0x4C7CC020A84CBEBC) },
    { UINT64_C(0x6AFFE56DC73EBD39), UINT64_C(0x580525FF389322ED),
      UINT64_C(0x24CA1DBEE0565524), UINT64_C(0x9FF3D649E9F1BFC5) },
    { UINT64_C(0x42415EEBD0DD6589), UINT64_C(0x3F4A24304289BC29),
      UINT64_C(0x1061469F276451B9), UINT64_C(0x929D897FB256DEF1) },
    { UINT64_C(0x37FCA3ED60518911), UINT64_C(0xC999666B8FC452FB),
      UINT64_C(0x2C16E91988D8BD15), UINT64_C(0xEE9C1CAFFDDCD5AB) },
    { UINT64_C(0x05789FF90BC71965), UINT64_C(0x0A5C2A270ADCE1C1),
      UINT64_C(0x0038AE7FD7D0AC26), UINT64_C(0xE0D1D496A337EA25) },
    { UINT64_C(0xB303B26181F2668D), UINT64_C(0x66322B277BD6EAB7),
      UINT64_C(0x47768DF8EBF193D0), UINT64_C(0x08550ADDEEE230CB) },
    { UINT64_C(0xDC7B8B35DF508FBB), UINT64_C(0x306C3C157D61F60B),
      UINT64_C(0x29B461F84B590E63), UINT64_C(0x24B851F3C76EDF09) },
    { UINT64_C(0xD3D20674EA3BD525), UINT64_C(0xA70A2D3E2B07307C),
      UINT64_C(0x8A366DD9E0F885D0), UINT64_C(0x80E2A0F2B7F52DEC) },
    { UINT64_C(0x3E155C0C50D124BC), UINT64_C(0x108977C33005AD74),
      UINT64_C(0x0402AC3A4B588AE8), UINT64_C(0xDC45325EEC43B130) },
    { UINT64_C(0xC2947D35DCBF8249), UINT64_C(0x4927E5D8E84F7F56),
      UINT64_C(0x379AAB0721050F51), UINT64_C(0xB6ECB05E867EFB86) },
    { UINT64_C(0x28568A56C5D22490), UINT64_C(0x62F33098EB184748),
      UINT64_C(0x0F9772C2DA75E56A), UINT64_C(0xA8C0220888BE3880) },
    { UINT64_C(0xCB58C70BFC644D3B), UINT64_C(0xF855B4EDF4DB1A7C),
      UINT64_C(0xC5421505231F5361), UINT64_C(0x32C82079BDE66694) },
    { UINT64_C(0x670213546A9BAEA9), UINT64_C(0x7484F449C410CA29),
      UINT64_C(0x2EE2701FE0BDD45F), UINT64_C(0x657D724939505311) },
    { UINT64_C(0xE1E26DB26992BB7B), UINT64_C(0x21300264DFEA7C63),
      UINT64_C(0x1D488CB557F1187A), UINT64_C(0x1B965A9D69FC1491) },
    { UINT64_C(0x6FA9DCA1BB124EA5), UINT64_C(0x53162B973B7B7C66),
      UINT64_C(0x243DBE24E4BF539C), UINT64_C(0xB88E734C37AA41BE) },
    { UINT64_C(0x4E03889ED999A70C), UINT64_C(0x291DADF4103A7BD3),
      UINT64_C(0x0C879C4AAE7BDDAF), UINT64_C(0xF5D7282AC59F72E4) },
    { UINT64_C(0xC321C2C93EC24448), UINT64_C(0x7E2D63EC5941B4D1),
      UINT64_C(0x602D36F87FBFDCA9), UINT64_C(0xE396C9DD32E45EC8) },
    { UINT64_C(0x4445853927E95D63), UINT64_C(0x293D5C31629B140E),
      UINT64_C(0x0AFF7F7D0D7DE549), UINT64_C(0x51E9B43CDAFFD76A) },
    { UINT64_C(0xC0900683DF0772E1), UINT64_C(0xAA200C4471296168),
      UINT64_C(0x7FF7BF8E9E456FE9), UINT64_C(0x6B08AEBF2496EC68) },
    { UINT64_C(0x964F1A3E7581727E), UINT64_C(0x91FD8DB46FF4A633),
      UINT64_C(0x55B7AD3DD3173EC5), UINT64_C(0xC4DBC1411B1F831A) },
    { UINT64_C(0x511E40050B770F19), UINT64_C(0xFFF1FDEE92EF5977),
      UINT64_C(0x5119CFB5C91EFC3E), UINT64_C(0x4EB5DC5612EEB59F) },
    { UINT64_C(0xF3D6D581DF65EF29), UINT64_C(0xD4C17155027A1D99),
      UINT64_C(0xCAA629B950D90BE0), UINT64_C(0x428B14FC5B8D9481) },
    { UINT64_C(0x1446DA220E144921), UINT64_C(0x58A0F7260BEEDC67),
      UINT64_C(0x07051AD76A0CF928), UINT64_C(0x046CAFB380AFC847) },
    { UINT64_C(0x454AA73F768AF954), UINT64_C(0x2CC65E7C79AC0E96),
      UINT64_C(0x0C1E860F5DF6BDC3), UINT64_C(0xC66469934780AF38) },
    { UINT64_C(0xB9DC42BB2FC15342), UINT64_C(0x9A9A89FA5603663B),
      UINT64_C(0x703EB2D15E96D3F5), UINT64_C(0x24A417DB2E807C36) },
    { UINT64_C(0xB5D9CD4C6DFA2AE0), UINT64_C(0x44669BAB3E240F20),
      UINT64_C(0x3096BDE49D980ACC), UINT64_C(0x62F3752FAF487C00) },
    { UINT64_C(0xF642B9ACABD62CE2), UINT64_C(0x1234639870D43F3F),
      UINT64_C(0x1183166A4D1D58F7), UINT64_C(0x30B73CF809E8A99E) },
    { UINT64_C(0x20AC4837B01A1145), UINT64_C(0xD8264FF40F126D21),
      UINT64_C(0x1B9640B605449922), UINT64_C(0x949BAEC50E909AE5) },
    { UINT64_C(0x737E2B303BF93BEB), UINT64_C(0xAA368C75F13A2563),
      UINT64_C(0x4CCA64A9591C4850), UINT64_C(0x7EAACA99054922E1) },
    { UINT64_C(0xFA8E73893558565E), UINT64_C(0xEFF5127D8B64FEC1),
      UINT64_C(0xEADADA4A8F39C7A2), UINT64_C(0x89C1D2ABA40260DE) },
    { UINT64_C(0x3661CAB97DB87B19), UINT64_C(0x8E7994FD0E17B1B6),
      UINT64_C(0x1E441252003FB819), UINT64_C(0x9587DDCF5B82CCC6) },
    { UINT64_C(0x83665B14E877060F), UINT64_C(0x7A69A18F5A7A6A01),
      UINT64_C(0x3ED4FF504641E9CA), UINT64_C(0xFE4075915A1F3C0F) },
    { UINT64_C(0x8F46C33A075AC5B7), UINT64_C(0x7D79ADD5F7BDBBEB),
      UINT64_C(0x4639A7102E7AE979), UINT64_C(0x9A22C8AE97DB2BFD) },
    { UINT64_C(0xAFD684A04F9292C4), UINT64_C(0xA4BA212965FA0019),
      UINT64_C(0x7125459A25F2F854), UINT64_C(0xC5B242166CB85524) },
    { UINT64_C(0x131C7BFC3BD3E511), UINT64_C(0xB0FAEB1EF2E272E6),
      UINT64_C(0x0D36509BF2BD01D1), UINT64_C(0xA8BE49DA67635F46) },
    { UINT64_C(0x5FEC2901CA08C671), UINT64_C(0x273CFBBD1980F1FC),
      UINT64_C(0x0EB3D3EC49501873), UINT64_C(0xE93A392664F3B83C) }
  };

  uint64_t l, h;
  int i;

  for (i = 0 ; i < 64 ; i++) {
    l = psnip_intrin_umul128(test_vec[i].a, test_vec[i].b, &h);
    munit_assert_uint64(h, ==, test_vec[i].h);
    munit_assert_uint64(l, ==, test_vec[i].l);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_umul128_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t a, b, h1, l1, h2, l2;

  munit_rand_memory(sizeof(a), (uint8_t*) &a);
  munit_rand_memory(sizeof(b), (uint8_t*) &b);

  l1 = psnip_intrin_umul128(a, b, &h1);
  l2 = _umul128(a, b, &h2);

  munit_assert_uint64(h1, ==, h2);
  munit_assert_uint64(l1, ==, l2);

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
  PSNIP_TEST_BUILTIN(clrsb),
  PSNIP_TEST_BUILTIN(clrsbl),
  PSNIP_TEST_BUILTIN(clrsbll),
  PSNIP_TEST_BUILTIN(bswap16),
  PSNIP_TEST_BUILTIN(bswap32),
  PSNIP_TEST_BUILTIN(bswap64),

  PSNIP_TEST_INTRIN(rotl8),
  PSNIP_TEST_INTRIN(rotl16),
  PSNIP_TEST_INTRIN(rotl),
  PSNIP_TEST_INTRIN(rotl64),
  PSNIP_TEST_INTRIN(BitScanForward),
  PSNIP_TEST_INTRIN(BitScanForward64),
  PSNIP_TEST_INTRIN(bittest),
  PSNIP_TEST_INTRIN(bittest64),
  PSNIP_TEST_INTRIN(byteswap_ushort),
  PSNIP_TEST_INTRIN(byteswap_ulong),
  PSNIP_TEST_INTRIN(byteswap_uint64),
  PSNIP_TEST_INTRIN(umul128),

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
