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
test_gnu_clz32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint32_t v = UINT32_MAX;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clz32(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint64_t v = UINT64_MAX;
  int expected = 0;

  do {
    munit_assert_int(psnip_builtin_clz64(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

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

  uint16_t v;

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

  uint32_t v;

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

  uint64_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bswap64(v), ==, __builtin_bswap64(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_uint8_t v = 182;

  munit_assert_uint16(psnip_builtin_bitreverse8(v), ==, 109);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse8_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint16_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bitreverse8(v), ==, __builtin_bitreverse8(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { uint16_t v; uint16_t r; } tests[] = {
    { 0x920b, 0xd049 }, { 0x4a43, 0xc252 }, { 0x29d4, 0x2b94 }, { 0xed1a, 0x58b7 },
    { 0x8bc2, 0x43d1 }, { 0xcf7b, 0xdef3 }, { 0x0c60, 0x0630 }, { 0x39a3, 0xc59c },
    { 0xee8a, 0x5177 }, { 0xe48c, 0x3127 }, { 0x4152, 0x4a82 }, { 0xd163, 0xc68b },
    { 0x2359, 0x9ac4 }, { 0x1f01, 0x80f8 }, { 0x2383, 0xc1c4 }, { 0x9ae7, 0xe759 },
    { 0x7c9f, 0xf93e }, { 0xf33f, 0xfccf }, { 0x6f37, 0xecf6 }, { 0x0291, 0x8940 },
    { 0x31fc, 0x3f8c }, { 0xec7e, 0x7e37 }, { 0x4da5, 0xa5b2 }, { 0xd025, 0xa40b },
    { 0x8f99, 0x99f1 }, { 0x934f, 0xf2c9 }, { 0xfbe4, 0x27df }, { 0x7846, 0x621e },
    { 0xbb48, 0x12dd }, { 0x8dcf, 0xf3b1 }, { 0x1a42, 0x4258 }, { 0xbc00, 0x003d },
    { 0xace9, 0x9735 }, { 0x7f13, 0xc8fe }, { 0xb872, 0x4e1d }, { 0x8d27, 0xe4b1 },
    { 0xebb6, 0x6dd7 }, { 0x9a87, 0xe159 }, { 0xe4ba, 0x5d27 }, { 0x9050, 0x0a09 },
    { 0xf9c7, 0xe39f }, { 0xec24, 0x2437 }, { 0x1913, 0xc898 }, { 0x2b7d, 0xbed4 },
    { 0x563a, 0x5c6a }, { 0x914a, 0x5289 }, { 0x7bfa, 0x5fde }, { 0xf426, 0x642f },
    { 0x648f, 0xf126 }, { 0x4e4f, 0xf272 }, { 0xc0ff, 0xff03 }, { 0xc0f2, 0x4f03 },
    { 0xbe3f, 0xfc7d }, { 0x4f99, 0x99f2 }, { 0x4062, 0x4602 }, { 0x877f, 0xfee1 },
    { 0x68a5, 0xa516 }, { 0x548d, 0xb12a }, { 0x999e, 0x7999 }, { 0x8545, 0xa2a1 },
    { 0x9184, 0x2189 }, { 0xaf0c, 0x30f5 }, { 0xe091, 0x8907 }, { 0x86d7, 0xeb61 }
  };

  int i;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint16(psnip_builtin_bitreverse16(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse16_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint16_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bitreverse16(v), ==, __builtin_bitreverse16(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { uint32_t v; uint32_t r; } tests[] = {
    { UINT32_C(0x78418ca2), UINT32_C(0x4531821e) }, { UINT32_C(0x48ec7114), UINT32_C(0x288e3712) },
    { UINT32_C(0x667103a9), UINT32_C(0x95c08e66) }, { UINT32_C(0xb02d55bb), UINT32_C(0xddaab40d) },
    { UINT32_C(0x88833921), UINT32_C(0x849cc111) }, { UINT32_C(0x3df3e00c), UINT32_C(0x3007cfbc) },
    { UINT32_C(0x08227fd5), UINT32_C(0xabfe4410) }, { UINT32_C(0xd42cf07c), UINT32_C(0x3e0f342b) },
    { UINT32_C(0x1120bbf6), UINT32_C(0x6fdd0488) }, { UINT32_C(0xf61a587f), UINT32_C(0xfe1a586f) },
    { UINT32_C(0x524ff49d), UINT32_C(0xb92ff24a) }, { UINT32_C(0xcbff97a6), UINT32_C(0x65e9ffd3) },
    { UINT32_C(0xe0ab8ead), UINT32_C(0xb571d507) }, { UINT32_C(0x1a383b2f), UINT32_C(0xf4dc1c58) },
    { UINT32_C(0x4a5f651d), UINT32_C(0xb8a6fa52) }, { UINT32_C(0x7383307b), UINT32_C(0xde0cc1ce) },
    { UINT32_C(0xec924426), UINT32_C(0x64224937) }, { UINT32_C(0xddeb26b7), UINT32_C(0xed64d7bb) },
    { UINT32_C(0x4f3bc252), UINT32_C(0x4a43dcf2) }, { UINT32_C(0x92b4672e), UINT32_C(0x74e62d49) },
    { UINT32_C(0xb09869a1), UINT32_C(0x8596190d) }, { UINT32_C(0xdf6cd3cc), UINT32_C(0x33cb36fb) },
    { UINT32_C(0xfa53dbab), UINT32_C(0xd5dbca5f) }, { UINT32_C(0x30e333e6), UINT32_C(0x67ccc70c) },
    { UINT32_C(0x263d5be4), UINT32_C(0x27dabc64) }, { UINT32_C(0x8532fe3b), UINT32_C(0xdc7f4ca1) },
    { UINT32_C(0xdd4808d5), UINT32_C(0xab1012bb) }, { UINT32_C(0x29a8c6f9), UINT32_C(0x9f631594) },
    { UINT32_C(0x8ae2c92c), UINT32_C(0x34934751) }, { UINT32_C(0x16ec5edd), UINT32_C(0xbb7a3768) },
    { UINT32_C(0x1cf346b2), UINT32_C(0x4d62cf38) }, { UINT32_C(0x11f83e34), UINT32_C(0x2c7c1f88) },
    { UINT32_C(0xf417bf41), UINT32_C(0x82fde82f) }, { UINT32_C(0xb1e77384), UINT32_C(0x21cee78d) },
    { UINT32_C(0x258785fa), UINT32_C(0x5fa1e1a4) }, { UINT32_C(0xd5c19754), UINT32_C(0x2ae983ab) },
    { UINT32_C(0xf457c146), UINT32_C(0x6283ea2f) }, { UINT32_C(0xce8a83ee), UINT32_C(0x77c15173) },
    { UINT32_C(0x1402b002), UINT32_C(0x400d4028) }, { UINT32_C(0x91a1c97b), UINT32_C(0xde938589) },
    { UINT32_C(0x448b4a5e), UINT32_C(0x7a52d122) }, { UINT32_C(0x4dbb4e40), UINT32_C(0x0272ddb2) },
    { UINT32_C(0xfda65f65), UINT32_C(0xa6fa65bf) }, { UINT32_C(0xdb9d9403), UINT32_C(0xc029b9db) },
    { UINT32_C(0xb0fa7da3), UINT32_C(0xc5be5f0d) }, { UINT32_C(0xdd70807c), UINT32_C(0x3e010ebb) },
    { UINT32_C(0xce442cf7), UINT32_C(0xef342273) }, { UINT32_C(0x0e3e8338), UINT32_C(0x1cc17c70) },
    { UINT32_C(0xb8c3a83d), UINT32_C(0xbc15c31d) }, { UINT32_C(0x551c1e45), UINT32_C(0xa27838aa) },
    { UINT32_C(0x5b3d5709), UINT32_C(0x90eabcda) }, { UINT32_C(0x3c5852b2), UINT32_C(0x4d4a1a3c) },
    { UINT32_C(0x7937208b), UINT32_C(0xd104ec9e) }, { UINT32_C(0x5d5e32a8), UINT32_C(0x154c7aba) },
    { UINT32_C(0x2c5ff965), UINT32_C(0xa69ffa34) }, { UINT32_C(0x9bbcb24f), UINT32_C(0xf24d3dd9) },
    { UINT32_C(0x56e99d80), UINT32_C(0x01b9976a) }, { UINT32_C(0xc3a399a2), UINT32_C(0x4599c5c3) },
    { UINT32_C(0x24a2f605), UINT32_C(0xa06f4524) }, { UINT32_C(0xaed4d60f), UINT32_C(0xf06b2b75) },
    { UINT32_C(0x5dc9a4e2), UINT32_C(0x472593ba) }, { UINT32_C(0x971aecda), UINT32_C(0x5b3758e9) },
    { UINT32_C(0x96fe63cb), UINT32_C(0xd3c67f69) }, { UINT32_C(0x4230d35a), UINT32_C(0x5acb0c42) }
  };

  int i;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint32(psnip_builtin_bitreverse32(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse32_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint32_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bitreverse32(v), ==, __builtin_bitreverse32(v));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { uint64_t v; uint64_t r; } tests[] = {
    { UINT64_C(0x308afbc73f0862a5), UINT64_C(0xa54610fce3df510c) },
    { UINT64_C(0x8027240b84a64cea), UINT64_C(0x57326521d024e401) },
    { UINT64_C(0xf1b95731ec6d1043), UINT64_C(0xc208b6378cea9d8f) },
    { UINT64_C(0x7e2bb385fc0e5836), UINT64_C(0x6c1a703fa1cdd47e) },
    { UINT64_C(0x6068df7a47c08742), UINT64_C(0x42e103e25efb1606) },
    { UINT64_C(0x1aa3bb17aef98aa3), UINT64_C(0xc5519f75e8ddc558) },
    { UINT64_C(0xa287d99ee0d8d530), UINT64_C(0x0cab1b07799be145) },
    { UINT64_C(0x894664ca4368366d), UINT64_C(0xb66c16c253266291) },
    { UINT64_C(0xf31cbf8b8c8dc3a9), UINT64_C(0x95c3b131d1fd38cf) },
    { UINT64_C(0xce9eb8b1edd43676), UINT64_C(0x6e6c2bb78d1d7973) },
    { UINT64_C(0x2b7a9cd63e189b23), UINT64_C(0xc4d9187c6b395ed4) },
    { UINT64_C(0x3c609212b194765d), UINT64_C(0xba6e298d4849063c) },
    { UINT64_C(0x010dcc4b51092c07), UINT64_C(0xe034908ad233b080) },
    { UINT64_C(0x95d2165dea68f546), UINT64_C(0x62af1657ba684ba9) },
    { UINT64_C(0x8fdecebd117b1521), UINT64_C(0x84a8de88bd737bf1) },
    { UINT64_C(0x85190c2e60338cfb), UINT64_C(0xdf31cc06743098a1) },
    { UINT64_C(0xd7df3e6407cc6b19), UINT64_C(0x98d633e0267cfbeb) },
    { UINT64_C(0x0bf04a03c1552a7c), UINT64_C(0x3e54aa83c0520fd0) },
    { UINT64_C(0xaca884f577678a08), UINT64_C(0x1051e6eeaf211535) },
    { UINT64_C(0xb74e69e1dae1f05e), UINT64_C(0x7a0f875b879672ed) },
    { UINT64_C(0x37e8fd8735fafcf8), UINT64_C(0x1f3f5face1bf17ec) },
    { UINT64_C(0xd07db647a43055ed), UINT64_C(0xb7aa0c25e26dbe0b) },
    { UINT64_C(0x5d387a2eb8d11faf), UINT64_C(0xf5f88b1d745e1cba) },
    { UINT64_C(0xa0fb85d86c4114f4), UINT64_C(0x2f2882361ba1df05) },
    { UINT64_C(0x32be7eadf096f2fa), UINT64_C(0x5f4f690fb57e7d4c) },
    { UINT64_C(0x240bff8fcb507716), UINT64_C(0x68ee0ad3f1ffd024) },
    { UINT64_C(0xa5a88b2b85f8f224), UINT64_C(0x244f1fa1d4d115a5) },
    { UINT64_C(0x51b3172c5ac49ee9), UINT64_C(0x9779235a34e8cd8a) },
    { UINT64_C(0x9e7a27dffce5ecd8), UINT64_C(0x1b37a73ffbe45e79) },
    { UINT64_C(0xba503e01c99ef696), UINT64_C(0x696f7993807c0a5d) },
    { UINT64_C(0xf84b0454161168ae), UINT64_C(0x751688682a20d21f) },
    { UINT64_C(0x435cf21f723b74d2), UINT64_C(0x4b2edc4ef84f3ac2) },
    { UINT64_C(0x3b0345cbbfd8967c), UINT64_C(0x3e691bfdd3a2c0dc) },
    { UINT64_C(0xe4f997187c1e80ae), UINT64_C(0x7501783e18e99f27) },
    { UINT64_C(0x961c103a57a55c4a), UINT64_C(0x523aa5ea5c083869) },
    { UINT64_C(0x47ce8b971fb05608), UINT64_C(0x106a0df8e9d173e2) },
    { UINT64_C(0x6d1f9852530fcdbd), UINT64_C(0xbdb3f0ca4a19f8b6) },
    { UINT64_C(0x20158c5c1762f3ec), UINT64_C(0x37cf46e83a31a804) },
    { UINT64_C(0xb16d44a688e35217), UINT64_C(0xe84ac7116522b68d) },
    { UINT64_C(0x94ef5dc2f8734883), UINT64_C(0xc112ce1f43baf729) },
    { UINT64_C(0x5a6dec6caca2c4e9), UINT64_C(0x972345353637b65a) },
    { UINT64_C(0x21d06b5e5a3cc478), UINT64_C(0x1e233c5a7ad60b84) },
    { UINT64_C(0x6d45e19bcfe1774c), UINT64_C(0x32ee87f3d987a2b6) },
    { UINT64_C(0x39cf8cca2068fe45), UINT64_C(0xa27f16045331f39c) },
    { UINT64_C(0x00de013799794c2a), UINT64_C(0x54329e99ec807b00) },
    { UINT64_C(0x1693d09f77270c94), UINT64_C(0x2930e4eef90bc968) },
    { UINT64_C(0xac6daa88cffc8dd4), UINT64_C(0x2bb13ff31155b635) },
    { UINT64_C(0x29ae817961f92b21), UINT64_C(0x84d49f869e817594) },
    { UINT64_C(0xce0a37e3cd164d9c), UINT64_C(0x39b268b3c7ec5073) },
    { UINT64_C(0xf1202fe6eb2964b2), UINT64_C(0x4d2694d767f4048f) },
    { UINT64_C(0xcac56f531b8bb9be), UINT64_C(0x7d9dd1d8caf6a353) },
    { UINT64_C(0xd25bbd455f887443), UINT64_C(0xc22e11faa2bdda4b) },
    { UINT64_C(0xc03db58e58cce928), UINT64_C(0x1497331a71adbc03) },
    { UINT64_C(0x2a80fe8c4e6192ed), UINT64_C(0xb7498672317f0154) },
    { UINT64_C(0x8403247899351df8), UINT64_C(0x1fb8ac991e24c021) },
    { UINT64_C(0xf31cbc4658899c0f), UINT64_C(0xf039911a623d38cf) },
    { UINT64_C(0x2a02081ee53b8021), UINT64_C(0x8401dca778104054) },
    { UINT64_C(0xc6e4aa7ea41ee3e5), UINT64_C(0xa7c778257e552763) },
    { UINT64_C(0x5feda4f6f75e73bf), UINT64_C(0xfdce7aef6f25b7fa) },
    { UINT64_C(0x6645644da160119c), UINT64_C(0x39880685b226a266) },
    { UINT64_C(0xeccbc95517b603dc), UINT64_C(0x3bc06de8aa93d337) },
    { UINT64_C(0x83f45e1182739325), UINT64_C(0xa4c9ce41887a2fc1) },
    { UINT64_C(0xea285d2fd31ed5fc), UINT64_C(0x3fab78cbf4ba1457) },
    { UINT64_C(0x4873eb126c124c55), UINT64_C(0xaa32483648d7ce12) }
  };

  int i;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint64(psnip_builtin_bitreverse64(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_builtin_bitreverse64(v), ==, __builtin_bitreverse64(v));

  return MUNIT_OK;
}

#if defined(__SIZEOF_INT128__)
typedef unsigned __int128 psnip_uint_big;
#else
typedef psnip_uint64_t psnip_uint_big;
#endif

static MunitResult
test_gnu_addcb(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  if (sizeof(unsigned char) < sizeof(psnip_uint_big)) {
    unsigned char r, x, y, ci, co;
    psnip_uint_big R, X, Y, Rp;

    munit_rand_memory(sizeof(x), (uint8_t*) &x);
    munit_rand_memory(sizeof(y), (uint8_t*) &y);
    ci = 0;

    r = psnip_builtin_addcb(x, y, ci, &co);
    Rp = co;
    Rp <<= sizeof(r) * CHAR_BIT;
    Rp |= r;

    X = x;
    Y = y;
    R = X + Y;

    munit_assert_uint64(R, ==, Rp);
  } else {
    return MUNIT_SKIP;
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcb_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned char x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned char) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_addcb(x, y, ci, &co1);
  r2 = __builtin_addcb(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcs(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  if (sizeof(unsigned short) < sizeof(psnip_uint_big)) {
    unsigned short r, x, y, ci, co;
    psnip_uint_big R, X, Y, Rp;

    munit_rand_memory(sizeof(x), (uint8_t*) &x);
    munit_rand_memory(sizeof(y), (uint8_t*) &y);
    ci = 0;

    r = psnip_builtin_addcs(x, y, ci, &co);
    Rp = co;
    Rp <<= sizeof(r) * CHAR_BIT;
    Rp |= r;

    X = x;
    Y = y;
    R = X + Y;

    munit_assert_uint64(R, ==, Rp);
  } else {
    return MUNIT_SKIP;
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcs_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned short) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_addcs(x, y, ci, &co1);
  r2 = __builtin_addcs(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  if (sizeof(unsigned int) < sizeof(psnip_uint_big)) {
    unsigned int r, x, y, ci, co;
    psnip_uint_big R, X, Y, Rp;

    munit_rand_memory(sizeof(x), (uint8_t*) &x);
    munit_rand_memory(sizeof(y), (uint8_t*) &y);
    ci = 0;

    r = psnip_builtin_addc(x, y, ci, &co);
    Rp = co;
    Rp <<= sizeof(r) * CHAR_BIT;
    Rp |= r;

    X = x;
    Y = y;
    R = X + Y;

    munit_assert_uint64(R, ==, Rp);
  } else {
    return MUNIT_SKIP;
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned int) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_addc(x, y, ci, &co1);
  r2 = __builtin_addc(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  if (sizeof(unsigned long) < sizeof(psnip_uint_big)) {
    unsigned long r, x, y, ci, co;
    psnip_uint_big R, X, Y, Rp;

    munit_rand_memory(sizeof(x), (uint8_t*) &x);
    munit_rand_memory(sizeof(y), (uint8_t*) &y);
    ci = 0;

    r = psnip_builtin_addcl(x, y, ci, &co);
    Rp = co;
    Rp <<= sizeof(r) * CHAR_BIT;
    Rp |= r;

    X = x;
    Y = y;
    R = X + Y;

    munit_assert_uint64(R, ==, Rp);
  } else {
    return MUNIT_SKIP;
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned long) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_addcl(x, y, ci, &co1);
  r2 = __builtin_addcl(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  if (sizeof(unsigned long long) < sizeof(psnip_uint_big)) {
    unsigned long long r, x, y, ci, co;
    psnip_uint_big R, X, Y, Rp;

    munit_rand_memory(sizeof(x), (uint8_t*) &x);
    munit_rand_memory(sizeof(y), (uint8_t*) &y);
    ci = 0;

    r = psnip_builtin_addcll(x, y, ci, &co);
    Rp = co;
    Rp <<= sizeof(r) * CHAR_BIT;
    Rp |= r;

    X = x;
    Y = y;
    R = X + Y;

    munit_assert_uint64(R, ==, Rp);
  } else {
    return MUNIT_SKIP;
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addcll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned long long) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_addcll(x, y, ci, &co1);
  r2 = __builtin_addcll(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcb(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { unsigned char x; unsigned char y; unsigned char ci; unsigned char r; unsigned char co; } test_vec[] = {
    { 0xe7, 0xf8, 1, 0xee, 1 }, { 0x2d, 0x13, 1, 0x19, 0 },
    { 0x11, 0xbc, 1, 0x54, 1 }, { 0x96, 0xb5, 1, 0xe0, 1 },
    { 0xc7, 0xf2, 1, 0xd4, 1 }, { 0x16, 0xe4, 0, 0x32, 1 },
    { 0x9b, 0x2b, 0, 0x70, 0 }, { 0xdf, 0xa5, 0, 0x3a, 0 },
    { 0x03, 0xc0, 0, 0x43, 1 }, { 0x91, 0xd7, 1, 0xb9, 1 },
    { 0x35, 0xbd, 0, 0x78, 1 }, { 0x4a, 0x42, 1, 0x07, 0 },
    { 0xa5, 0xde, 0, 0xc7, 1 }, { 0x33, 0xbf, 0, 0x74, 1 },
    { 0x12, 0x32, 0, 0xe0, 1 }, { 0x74, 0xfe, 1, 0x75, 1 },
    { 0x0f, 0x54, 1, 0xba, 1 }, { 0xe1, 0xcd, 1, 0x13, 0 },
    { 0x6a, 0x5d, 0, 0x0d, 0 }, { 0x0e, 0x12, 1, 0xfb, 1 },
    { 0xb1, 0xea, 0, 0xc7, 1 }, { 0x43, 0x4b, 1, 0xf7, 1 },
    { 0xb3, 0x43, 1, 0x6f, 0 }, { 0x83, 0xa4, 1, 0xde, 1 },
    { 0x5a, 0x09, 1, 0x50, 0 }, { 0x92, 0x0c, 1, 0x85, 0 },
    { 0xc5, 0x87, 1, 0x3d, 0 }, { 0x9a, 0xda, 1, 0xbf, 1 },
    { 0x28, 0xe5, 1, 0x42, 1 }, { 0x13, 0xcd, 0, 0x46, 1 },
    { 0x7f, 0x40, 1, 0x3e, 0 }, { 0xc3, 0x58, 0, 0x6b, 0 },
  };

  size_t i;
  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    unsigned char r, co;
    r = psnip_builtin_subcb(test_vec[0].x, test_vec[0].y, test_vec[0].ci, &co);
    munit_assert_uint8(r,  ==, test_vec[0].r);
    munit_assert_uint8(co, ==, test_vec[0].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcb_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned char x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned char) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_subcb(x, y, ci, &co1);
  r2 = __builtin_subcb(x, y, ci, &co2);

  munit_assert_uint8(r1, ==, r2);
  munit_assert_uint8(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcs(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short co, r;

  r = psnip_builtin_subcs(USHRT_MAX - 1, USHRT_MAX, 0, &co);
  munit_assert_ushort(r,  ==, USHRT_MAX);
  munit_assert_ushort(co, ==, 1);
  r = psnip_builtin_subcs(USHRT_MAX, USHRT_MAX - 1, 0, &co);
  munit_assert_ushort(r,  ==, 1);
  munit_assert_ushort(co, ==, 0);
  r = psnip_builtin_subcs(USHRT_MAX, USHRT_MAX, 0, &co);
  munit_assert_ushort(r,  ==, 0);
  munit_assert_ushort(co, ==, 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcs_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned short x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned short) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_subcs(x, y, ci, &co1);
  r2 = __builtin_subcs(x, y, ci, &co2);

  munit_assert_ushort(r1, ==, r2);
  munit_assert_ushort(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subc(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int co, r;

  r = psnip_builtin_subc(UINT_MAX - 1, UINT_MAX, 0, &co);
  munit_assert_uint(r,  ==, UINT_MAX);
  munit_assert_uint(co, ==, 1);
  r = psnip_builtin_subc(UINT_MAX, UINT_MAX - 1, 0, &co);
  munit_assert_uint(r,  ==, 1);
  munit_assert_uint(co, ==, 0);
  r = psnip_builtin_subc(UINT_MAX, UINT_MAX, 0, &co);
  munit_assert_uint(r,  ==, 0);
  munit_assert_uint(co, ==, 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subc_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned int x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned int) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_subc(x, y, ci, &co1);
  r2 = __builtin_subc(x, y, ci, &co2);

  munit_assert_uint(r1, ==, r2);
  munit_assert_uint(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcl(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long co, r;

  r = psnip_builtin_subcl(ULONG_MAX - 1, ULONG_MAX, 0, &co);
  munit_assert_ulong(r,  ==, ULONG_MAX);
  munit_assert_ulong(co, ==, 1);
  r = psnip_builtin_subcl(ULONG_MAX, ULONG_MAX - 1, 0, &co);
  munit_assert_ulong(r,  ==, 1);
  munit_assert_ulong(co, ==, 0);
  r = psnip_builtin_subcl(ULONG_MAX, ULONG_MAX, 0, &co);
  munit_assert_ulong(r,  ==, 0);
  munit_assert_ulong(co, ==, 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcl_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned long) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_subcl(x, y, ci, &co1);
  r2 = __builtin_subcl(x, y, ci, &co2);

  munit_assert_ulong(r1, ==, r2);
  munit_assert_ulong(co1, ==, co2);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcll(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long co, r;

  r = psnip_builtin_subcll(ULLONG_MAX - 1, ULLONG_MAX, 0, &co);
  munit_assert_ullong(r,  ==, ULLONG_MAX);
  munit_assert_ullong(co, ==, 1);
  r = psnip_builtin_subcll(ULLONG_MAX, ULLONG_MAX - 1, 0, &co);
  munit_assert_ullong(r,  ==, 1);
  munit_assert_ullong(co, ==, 0);
  r = psnip_builtin_subcll(ULLONG_MAX, ULLONG_MAX, 0, &co);
  munit_assert_ullong(r,  ==, 0);
  munit_assert_ullong(co, ==, 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcll_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long long x, y, ci, co1, co2, r1, r2;

  munit_rand_memory(sizeof(x), (uint8_t*) &x);
  munit_rand_memory(sizeof(y), (uint8_t*) &y);
  ci = (unsigned long long) munit_rand_int_range(0, 1);

  r1 = psnip_builtin_subcll(x, y, ci, &co1);
  r2 = __builtin_subcll(x, y, ci, &co2);

  munit_assert_ullong(r1, ==, r2);
  munit_assert_ullong(co1, ==, co2);

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

  size_t i;
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

  size_t i;
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

  size_t i;
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

  size_t i;
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

  size_t i;
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

  size_t i;
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

  size_t i;
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

  size_t i;
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
test_msvc_BitScanReverse(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask = 12;
  unsigned long index;
  unsigned char isNonzero;

  isNonzero = psnip_intrin_BitScanReverse(&index, mask);
  munit_assert_uint8(isNonzero, ==, 1);
  munit_assert_long(index, ==, 3);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanReverse_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask;
  unsigned long i1, i2;
  unsigned char z1, z2;
  munit_rand_memory(sizeof(mask), (unsigned char*) &mask);

  z1 = _BitScanReverse(&i1, mask);
  z2 = psnip_intrin_BitScanReverse(&i2, mask);
  munit_assert_uint8(z1, ==, z2);
  munit_assert_ulong(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanReverse64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask = 12;
  unsigned long index;
  unsigned char isNonzero;

  isNonzero = psnip_intrin_BitScanReverse(&index, mask);
  munit_assert_uint8(isNonzero, ==, 1);
  munit_assert_long(index, ==, 3);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanReverse64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  unsigned long mask;
  unsigned long i1, i2;
  unsigned char z1, z2;
  munit_rand_memory(sizeof(mask), (unsigned char*) &mask);

  z1 = _BitScanReverse(&i1, mask);
  z2 = psnip_intrin_BitScanReverse(&i2, mask);
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

  for (nBit = 0 ; nBit < (int) (sizeof(num) * CHAR_BIT) ; nBit++)
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

  for (nBit = 0 ; nBit < (int) (sizeof(num) * CHAR_BIT) ; nBit++)
    munit_assert_uint8(_bittest64(&num, nBit), ==,
		       psnip_intrin_bittest64(&num, nBit));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i = 1;
  unsigned char result;

  result = psnip_intrin_bittestandcomplement(&i, 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, 3);

  result = psnip_intrin_bittestandcomplement(&i, 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_long(i, ==, 1);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandcomplement(&i1, p);
  r2 = _bittestandcomplement(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_int64_t i = 1;
  unsigned char result;

  result = psnip_intrin_bittestandcomplement64(&i, 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, 3);

  result = psnip_intrin_bittestandcomplement64(&i, 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_long(i, ==, 1);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_int64_t i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandcomplement64(&i1, p);
  r2 = _bittestandcomplement64(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i = -112;
  unsigned char result;

  result = psnip_intrin_bittestandreset(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_long(i, ==, LONG_MAX - 111);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandreset(&i1, p);
  r2 = _bittestandreset(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_int64_t i = -112;
  unsigned char result;

  result = psnip_intrin_bittestandreset64(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_int64(i, ==, INT64_MAX - 111);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  psnip_int64_t i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandreset64(&i1, p);
  r2 = _bittestandreset64(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i = LONG_MAX - 111;
  unsigned char result;

  result = psnip_intrin_bittestandset(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, -112);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandset(&i1, p);
  r2 = _bittestandset(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i = LONG_MAX - 111;
  unsigned char result;

  result = psnip_intrin_bittestandset64(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, -112);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset64_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  long i1, i2, p;
  unsigned char r1, r2;

  munit_rand_memory(sizeof(i1), (uint8_t*) &i1);
  i2 = i1;
  p = munit_rand_int_range(0, (sizeof(i1) * 8) - 1);

  r1 = psnip_intrin_bittestandset64(&i1, p);
  r2 = _bittestandset64(&i2, p);

  munit_assert_int(r1, ==, r2);
  munit_assert_long(i1, ==, i2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftleft128(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { psnip_uint64_t h; psnip_uint64_t l; unsigned char s; psnip_uint64_t r; } test_vec[] = {
    { UINT64_C(0xc89b937dec4245e6), UINT64_C(0x00614c26767421aa), 0x49, UINT64_C(0x3726fbd8848bcc00) },
    { UINT64_C(0x1b34bc50f41dddc2), UINT64_C(0xe3310529c4350e3d), 0x6b, UINT64_C(0xeeee171988294e21) },
    { UINT64_C(0x0fdf0a325f8500cf), UINT64_C(0xb9c6970e79283a75), 0xf2, UINT64_C(0x033ee71a5c39e4a0) },
    { UINT64_C(0x180365eede6f00f7), UINT64_C(0xa69917a0a8ba4f21), 0x2f, UINT64_C(0x807bd34c8bd0545d) },
    { UINT64_C(0x11c6ac1e7df0e0b8), UINT64_C(0x1050d1807a60a262), 0x1d, UINT64_C(0xcfbe1c17020a1a30) },
    { UINT64_C(0x02e53c137c20d540), UINT64_C(0xf57a2e3f441c0808), 0x5d, UINT64_C(0x6f841aa81eaf45c7) },
    { UINT64_C(0x6dbd6705bcee15bb), UINT64_C(0x6dd26e7f362788a3), 0xcb, UINT64_C(0xeb382de770addb6e) },
    { UINT64_C(0x963ebb176aa89013), UINT64_C(0x7ee63eec875cf69b), 0x25, UINT64_C(0x5512026fdcc7dd90) },
    { UINT64_C(0xaf118b20ff49c1f7), UINT64_C(0xd639782316f417f0), 0xf0, UINT64_C(0xc1f7d639782316f4) },
    { UINT64_C(0x0a147c8de3142629), UINT64_C(0x58f274cd75a189a2), 0x51, UINT64_C(0xf91bc6284c52b1e4) },
    { UINT64_C(0xc9a85fb642a66da3), UINT64_C(0x8faf5e951bdb64ed), 0xab, UINT64_C(0x336d1c7d7af4a8de) },
    { UINT64_C(0xe18841f91791695a), UINT64_C(0x86187880f46f2545), 0x5b, UINT64_C(0xc8bc8b4ad430c3c4) },
    { UINT64_C(0x3d692f7d125d1d14), UINT64_C(0x12fb4c1679ffb90d), 0xe9, UINT64_C(0xba3a2825f6982cf3) },
    { UINT64_C(0x3c866788c16f9eaf), UINT64_C(0x87779f2691513545), 0x12, UINT64_C(0x9e2305be7abe1dde) },
    { UINT64_C(0x558fc3daaaf46a64), UINT64_C(0x346aec5219d668cf), 0x0c, UINT64_C(0xfc3daaaf46a64346) },
    { UINT64_C(0x8074e48dad4dbdcb), UINT64_C(0x1e6c715e5caa1ccd), 0x47, UINT64_C(0x3a7246d6a6dee58f) },
    { UINT64_C(0xd108e608c8531b76), UINT64_C(0xfc32ad6dc4131ec7), 0xd3, UINT64_C(0x30464298dbb7e195) },
    { UINT64_C(0x7353770a1f29016f), UINT64_C(0x434a78711d53091a), 0x35, UINT64_C(0x2de8694f0e23aa61) },
    { UINT64_C(0x3ef3184da9376641), UINT64_C(0x80d5d421cacfbc3b), 0x6f, UINT64_C(0xb320c06aea10e567) },
    { UINT64_C(0x7f7fc4ef5a017d1f), UINT64_C(0x67992d2baec2fb00), 0xbc, UINT64_C(0xf67992d2baec2fb0) },
    { UINT64_C(0x60db2e5faae6e6cc), UINT64_C(0x7d2da926fa02ed04), 0xa4, UINT64_C(0xae6e6cc7d2da926f) },
    { UINT64_C(0x643a594b7c3ccba9), UINT64_C(0x091720a0f8202059), 0x8d, UINT64_C(0x4b296f8799752122) },
    { UINT64_C(0x95aa61ee754a6f91), UINT64_C(0x73fd8645e26dfbef), 0xd2, UINT64_C(0x87b9d529be45cff6) },
    { UINT64_C(0x76d1443d49ea1db1), UINT64_C(0x987253d2c6880e4f), 0x4b, UINT64_C(0x8a21ea4f50ed8cc3) },
    { UINT64_C(0x2f73f2962a95ec24), UINT64_C(0x682d7f7a626846ee), 0xdb, UINT64_C(0xb154af6123416bfb) },
    { UINT64_C(0x01f1d47fd915bdeb), UINT64_C(0x60c7de494dd464aa), 0x89, UINT64_C(0xe3a8ffb22b7bd6c1) },
    { UINT64_C(0xa0bd6086fba929ed), UINT64_C(0xc35d24cf3d3736a5), 0xbb, UINT64_C(0x6e1ae92679e9b9b5) },
    { UINT64_C(0xd1f10ad5807b19cc), UINT64_C(0x8e47f3018fe5e658), 0xb7, UINT64_C(0xe64723f980c7f2f3) },
    { UINT64_C(0xf0eb8f04c11be866), UINT64_C(0x492703ac315f0751), 0x3b, UINT64_C(0x3249381d618af83a) },
    { UINT64_C(0x68f686f762838284), UINT64_C(0x772f11c565a16271), 0x07, UINT64_C(0x7b437bb141c1423b) },
    { UINT64_C(0xffd8c8250b414a83), UINT64_C(0xf24672be0ad58ed7), 0x70, UINT64_C(0x4a83f24672be0ad5) },
    { UINT64_C(0x6bc419dc2c157dd5), UINT64_C(0x871f374f4a7c3fa2), 0x3c, UINT64_C(0x5871f374f4a7c3fa) }
  };

  size_t i;
  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    const uint64_t r = psnip_intrin_shiftleft128(test_vec[i].l, test_vec[i].h, test_vec[i].s);
    munit_assert_uint64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftleft128_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t h, l, r1, r2;
  unsigned char s;

  s = (unsigned char) munit_rand_int_range(0, 255);
  munit_rand_memory(sizeof(h), (uint8_t*) &h);
  munit_rand_memory(sizeof(l), (uint8_t*) &l);

  r1 = psnip_intrin_shiftleft128(l, h, s);
  r2 = __shiftleft128(l, h, s);

  munit_assert_uint64(r1, ==, r2);

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftright128(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct { psnip_uint64_t h; psnip_uint64_t l; unsigned char s; psnip_uint64_t r; } test_vec[] = {
    { UINT64_C(0x5e97a525e2fb1493), UINT64_C(0xcca6cbfc2b13eacd), 0xa1, UINT64_C(0xf17d8a49e65365fe) },
    { UINT64_C(0x4fa11690297e0aa4), UINT64_C(0x56447fa0c01751a4), 0x47, UINT64_C(0x48ac88ff41802ea3) },
    { UINT64_C(0xd18efa3afb54cb8b), UINT64_C(0xa48feee70a3b85a1), 0xb3, UINT64_C(0xdf475f6a99717491) },
    { UINT64_C(0x1899bff112e6e87c), UINT64_C(0x8382b04ab02e0618), 0xe8, UINT64_C(0xf112e6e87c8382b0) },
    { UINT64_C(0xa3d2aebafddc5417), UINT64_C(0xb456d21a8c3dffbf), 0xc8, UINT64_C(0x17b456d21a8c3dff) },
    { UINT64_C(0xb85f327b74bf943f), UINT64_C(0x4bf496b411bd0505), 0x2f, UINT64_C(0x64f6e97f287e97e9) },
    { UINT64_C(0xd0dd1ad909cdb4b7), UINT64_C(0x6abf8f3d88c6d170), 0xdb, UINT64_C(0x39b696ed57f1e7b1) },
    { UINT64_C(0xa23c66b3ee4dd9e9), UINT64_C(0x42cee8358f34017c), 0x33, UINT64_C(0x8cd67dc9bb3d2859) },
    { UINT64_C(0x1fd8d2ccfe327f77), UINT64_C(0x07803c35aede0045), 0xa8, UINT64_C(0xccfe327f7707803c) },
    { UINT64_C(0xcdee0a2c072a2b0d), UINT64_C(0x18588090c97d2137), 0xf7, UINT64_C(0xdc14580e54561a30) },
    { UINT64_C(0xbca44f335b0323dc), UINT64_C(0xa6cf3fa736a4f987), 0xf1, UINT64_C(0x2799ad8191ee5367) },
    { UINT64_C(0xb269ee0cbaff3868), UINT64_C(0x3e7985d9dea482ff), 0xe7, UINT64_C(0x1975fe70d07cf30b) },
    { UINT64_C(0x00c97e62f9858f39), UINT64_C(0x89fafb1aed4e77f0), 0xec, UINT64_C(0xe62f9858f3989faf) },
    { UINT64_C(0x6e5e86a0bf281ba9), UINT64_C(0x72d3156bafc4a61e), 0x8f, UINT64_C(0x3752e5a62ad75f89) },
    { UINT64_C(0x088918ecbfaa5fde), UINT64_C(0x933e4397542316d9), 0x57, UINT64_C(0x54bfbd267c872ea8) },
    { UINT64_C(0x92f464468bea7a8a), UINT64_C(0xd841f337d8289ede), 0xa1, UINT64_C(0x45f53d456c20f99b) },
    { UINT64_C(0x840e9db2b186f098), UINT64_C(0xa71d5bf848d5c84f), 0x4f, UINT64_C(0xe1314e3ab7f091ab) },
    { UINT64_C(0xd8eaf024220ad1fa), UINT64_C(0xabdc983b64189e62), 0x6a, UINT64_C(0x090882b47eaaf726) },
    { UINT64_C(0x1e18ea31f10f7dea), UINT64_C(0xaf1eafd43c471b5b), 0xa1, UINT64_C(0xf887bef5578f57ea) },
    { UINT64_C(0x7ece42b458a81020), UINT64_C(0x637b18b6db767aaa), 0x44, UINT64_C(0x0637b18b6db767aa) },
    { UINT64_C(0x72fe6dd2eac8c9a0), UINT64_C(0x4b86110543ffdcc8), 0xd9, UINT64_C(0x6464d025c30882a1) },
    { UINT64_C(0x4c162008ca115ebb), UINT64_C(0x0f70132acbc6d73a), 0x02, UINT64_C(0xc3dc04cab2f1b5ce) },
    { UINT64_C(0x2ffc5dfb7ba9aec1), UINT64_C(0x2615bbdeaa8d4dc1), 0x5a, UINT64_C(0xea6bb049856ef7aa) },
    { UINT64_C(0x136a34d62ce5a379), UINT64_C(0xb6b32977e1a3b9d2), 0x7d, UINT64_C(0x9b51a6b1672d1bcd) },
    { UINT64_C(0xa1534a6f2d538037), UINT64_C(0x7d9bd75985b07b12), 0x0f, UINT64_C(0x006efb37aeb30b60) },
    { UINT64_C(0xb3b20f9bb2e918ea), UINT64_C(0xb4e69cf86a4cd335), 0x1d, UINT64_C(0x9748c755a734e7c3) },
    { UINT64_C(0xcf16a6ac3e03506b), UINT64_C(0x4c280ab89f5e1a68), 0x8e, UINT64_C(0x41ad30a02ae27d78) },
    { UINT64_C(0x9e75011ca34765e8), UINT64_C(0xb9076daa638deed2), 0x7e, UINT64_C(0x79d404728d1d97a2) },
    { UINT64_C(0xaf8eed336740f5fc), UINT64_C(0xa10db26072dad2ef), 0xbb, UINT64_C(0xf1dda66ce81ebf94) },
    { UINT64_C(0x1ba39630e37f9f60), UINT64_C(0xacd24fea6baf7b22), 0x3a, UINT64_C(0xe8e58c38dfe7d82b) },
    { UINT64_C(0x8c5126657d1708f0), UINT64_C(0x09f40c7a191cdfab), 0xdc, UINT64_C(0xd1708f009f40c7a1) },
    { UINT64_C(0x806d0b4a2a6c19fb), UINT64_C(0xc9bee9857229e7bc), 0x21, UINT64_C(0x15360cfde4df74c2) }
  };

  size_t i;
  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    const uint64_t r = psnip_intrin_shiftright128(test_vec[i].l, test_vec[i].h, test_vec[i].s);
    munit_assert_uint64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftright128_native(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t h, l, r1, r2;
  unsigned char s;

  s = (unsigned char) munit_rand_int_range(0, 255);
  munit_rand_memory(sizeof(h), (uint8_t*) &h);
  munit_rand_memory(sizeof(l), (uint8_t*) &l);

  r1 = psnip_intrin_shiftright128(l, h, s);
  r2 = __shiftright128(l, h, s);

  munit_assert_uint64(r1, ==, r2);

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

  unsigned short v;

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

  unsigned long v;

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

  uint64_t v;

  munit_rand_memory(sizeof(v), (uint8_t*) &v);

  munit_assert_int(psnip_intrin_byteswap_uint64(v), ==, _byteswap_uint64(v));

  return MUNIT_OK;
}

#define PSNIP_TEST_BUILTIN(name) \
  { (char*) "/builtin/"#name, test_gnu_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }, \
  { (char*) "/builtin/"#name"/native", test_gnu_##name##_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
#define PSNIP_TEST_INTRIN(name) \
  { (char*) "/intrin/"#name, test_msvc_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }, \
  { (char*) "/intrin/"#name"/native", test_msvc_##name##_native, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
#define PSNIP_TEST_WRAPPER(name) \
  { (char*) "/wrapper/"#name, test_gnu_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }

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
  PSNIP_TEST_BUILTIN(bitreverse8),
  PSNIP_TEST_BUILTIN(bitreverse16),
  PSNIP_TEST_BUILTIN(bitreverse32),
  PSNIP_TEST_BUILTIN(bitreverse64),
  PSNIP_TEST_BUILTIN(addcb),
  PSNIP_TEST_BUILTIN(addcs),
  PSNIP_TEST_BUILTIN(addc),
  PSNIP_TEST_BUILTIN(addcl),
  PSNIP_TEST_BUILTIN(addcll),
  PSNIP_TEST_BUILTIN(subcb),
  PSNIP_TEST_BUILTIN(subcs),
  PSNIP_TEST_BUILTIN(subc),
  PSNIP_TEST_BUILTIN(subcl),
  PSNIP_TEST_BUILTIN(subcll),

  PSNIP_TEST_INTRIN(rotl8),
  PSNIP_TEST_INTRIN(rotl16),
  PSNIP_TEST_INTRIN(rotl),
  PSNIP_TEST_INTRIN(rotl64),
  PSNIP_TEST_INTRIN(rotr8),
  PSNIP_TEST_INTRIN(rotr16),
  PSNIP_TEST_INTRIN(rotr),
  PSNIP_TEST_INTRIN(rotr64),
  PSNIP_TEST_INTRIN(BitScanForward),
  PSNIP_TEST_INTRIN(BitScanForward64),
  PSNIP_TEST_INTRIN(BitScanReverse),
  PSNIP_TEST_INTRIN(BitScanReverse64),
  PSNIP_TEST_INTRIN(bittest),
  PSNIP_TEST_INTRIN(bittest64),
  PSNIP_TEST_INTRIN(bittestandcomplement),
  PSNIP_TEST_INTRIN(bittestandcomplement64),
  PSNIP_TEST_INTRIN(bittestandreset),
  PSNIP_TEST_INTRIN(bittestandreset64),
  PSNIP_TEST_INTRIN(bittestandset),
  PSNIP_TEST_INTRIN(bittestandset64),
  PSNIP_TEST_INTRIN(shiftleft128),
  PSNIP_TEST_INTRIN(shiftright128),
  PSNIP_TEST_INTRIN(byteswap_ushort),
  PSNIP_TEST_INTRIN(byteswap_ulong),
  PSNIP_TEST_INTRIN(byteswap_uint64),

  PSNIP_TEST_WRAPPER(clz32),
  PSNIP_TEST_WRAPPER(clz64),

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
