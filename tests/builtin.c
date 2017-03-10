#include <stdlib.h>
#include <limits.h>

#include "munit/munit.h"

#define PSNIP_BUILTIN_EMULATE_NATIVE
#include "../builtin/builtin.h"

#define PSNIP_SIGNED_TYPE_MAX(T) ((T) (1ULL << ((sizeof(T) * CHAR_BIT) - 1)))
#define PSNIP_UNSIGNED_TYPE_MAX(T) (~((T) 0))

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
test_gnu_ffs(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ffs((int) v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ffsl((long) v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ffsll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ffsll((long long) v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clz(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clzl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clzl(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clzll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clzll(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz32(const MunitParameter params[], void* data) {
  psnip_uint32_t v = PSNIP_UNSIGNED_TYPE_MAX(psnip_uint32_t);
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clz32(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clz64(const MunitParameter params[], void* data) {
  psnip_uint64_t v = PSNIP_UNSIGNED_TYPE_MAX(psnip_uint64_t);
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clz64(v), ==, expected);

    v >>= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctz(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ctz(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctzl(const MunitParameter params[], void* data) {
  unsigned long v = ~0U;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ctzl(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctzll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_ctzll(v), ==, expected);

    v <<= 1;
    expected += 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctz32(const MunitParameter params[], void* data) {
  const struct { psnip_uint32_t v; int expected; } tests[] = {
    { UINT32_C(0xd5a00000), 21 }, { UINT32_C(0x36000000), 25 },
    { UINT32_C(0xbbe2ec00), 10 }, { UINT32_C(0xa0000000), 29 },
    { UINT32_C(0x4cd80000), 19 }, { UINT32_C(0xa05bf300),  8 },
    { UINT32_C(0xeea5ac80),  7 }, { UINT32_C(0x08000000), 27 },
    { UINT32_C(0x6a500000), 20 }, { UINT32_C(0x0a900000), 20 },
    { UINT32_C(0xf0042f34),  2 }, { UINT32_C(0x22700000), 20 },
    { UINT32_C(0xc0000000), 30 }, { UINT32_C(0xb38651c8),  3 },
    { UINT32_C(0x42f3b000), 12 }, { UINT32_C(0xf16211c0),  6 },
    { UINT32_C(0xe6fece00),  9 }, { UINT32_C(0xb0000000), 28 },
    { UINT32_C(0xecbd9b00),  8 }, { UINT32_C(0x40000000), 30 },
    { UINT32_C(0x2ea2c000), 14 }, { UINT32_C(0xd18ef600),  9 },
    { UINT32_C(0xd925824c),  2 }, { UINT32_C(0x74168fe0),  5 },
    { UINT32_C(0xd0968000), 15 }, { UINT32_C(0x49953e00),  9 },
    { UINT32_C(0x20000000), 29 }, { UINT32_C(0xe9e00000), 21 },
    { UINT32_C(0xb0831400), 10 }, { UINT32_C(0x2a000000), 25 },
    { UINT32_C(0x05121000), 12 }, { UINT32_C(0x58f63780),  7 }
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 0 ; i < sizeof(tests) / sizeof(tests[0]) ; i++)
    munit_assert_uint32(psnip_builtin_ctz32(tests[i].v), ==, tests[i].expected);

  return MUNIT_OK;
}

static MunitResult
test_gnu_ctz64(const MunitParameter params[], void* data) {
  const struct { psnip_uint64_t v; int expected; } tests[] = {
    { UINT64_C(0x2d1b3eb168fe0000), 17 }, { UINT64_C(0xb9e26858c0000000), 30 },
    { UINT64_C(0x8273288949c00000), 22 }, { UINT64_C(0x47be52b261510000), 16 },
    { UINT64_C(0x6863296cf2b0b800), 11 }, { UINT64_C(0xcca44c0000000000), 42 },
    { UINT64_C(0x5b24000000000000), 50 }, { UINT64_C(0x0480000000000000), 55 },
    { UINT64_C(0xb7c0000000000000), 54 }, { UINT64_C(0x601e137200000000), 33 },
    { UINT64_C(0x2000000000000000), 61 }, { UINT64_C(0x9f57de358606b000), 12 },
    { UINT64_C(0xac04400000000000), 46 }, { UINT64_C(0x5300000000000000), 56 },
    { UINT64_C(0x7240438000000000), 39 }, { UINT64_C(0xf564680000000000), 43 },
    { UINT64_C(0x106ba4119ad4d8e0),  5 }, { UINT64_C(0xd31a19d800000000), 35 },
    { UINT64_C(0x340f946ae7bb4000), 14 }, { UINT64_C(0xfa47686166c48000), 15 },
    { UINT64_C(0xf5901272aab6d800), 11 }, { UINT64_C(0x11811486d23a0000), 17 },
    { UINT64_C(0x2900000000000000), 56 }, { UINT64_C(0xdf2b208000000000), 39 },
    { UINT64_C(0x461f5c4843fdaf5f),  0 }, { UINT64_C(0xdd80000000000000), 55 },
    { UINT64_C(0xfb45cef800000000), 35 }, { UINT64_C(0x28c0000000000000), 54 },
    { UINT64_C(0xf00dface00000000), 33 }, { UINT64_C(0x0200000000000000), 57 },
    { UINT64_C(0x3ee1eef527547280),  7 }, { UINT64_C(0xbc33c7ea705c0000), 18 },
    { UINT64_C(0x00000000ffffffff),  0 }, { UINT64_C(0xffffffff00000000), 32 }
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 0 ; i < sizeof(tests) / sizeof(tests[0]) ; i++) {
    munit_assert_uint64(psnip_builtin_ctz64(tests[i].v), ==, tests[i].expected);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_parity(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_parity(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityl(const MunitParameter params[], void* data) {
  unsigned long v = ~0UL;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_parityl(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_parityll(const MunitParameter params[], void* data) {
  unsigned long long v = ~0ULL;
  int expected = 0;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_parityll(v), ==, expected);

    v <<= 1;
    expected ^= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcount(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_popcount(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountl(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_popcountl(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_popcountll(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = sizeof(v) * 8;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_popcountll(v), ==, expected);

    v >>= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsb(const MunitParameter params[], void* data) {
  unsigned int v = ~0U;
  int expected = (sizeof(v) * 8) - 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clrsb((int) v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbl(const MunitParameter params[], void* data) {
  unsigned long v = ~(0UL);
  int expected = (sizeof(v) * 8) - 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clrsbl((long) v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_clrsbll(const MunitParameter params[], void* data) {
  unsigned long long v = ~(0ULL);
  int expected = (sizeof(v) * 8) - 1;

  (void) params;
  (void) data;

  do {
    munit_assert_int(psnip_builtin_clrsbll((long long) v), ==, expected);

    v <<= 1;
    expected -= 1;
  } while (v != 0);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap16(const MunitParameter params[], void* data) {
  psnip_uint16_t v = (psnip_uint16_t) 0xAABBULL;

  (void) params;
  (void) data;

  munit_assert_uint16(psnip_builtin_bswap16(v), ==, ((psnip_uint16_t) 0xBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap32(const MunitParameter params[], void* data) {
  psnip_uint32_t v = (psnip_uint32_t) 0xAABBCCDDULL;

  (void) params;
  (void) data;

  munit_assert_uint32(psnip_builtin_bswap32(v), ==, ((psnip_uint32_t) 0xDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bswap64(const MunitParameter params[], void* data) {
  psnip_uint64_t v = (psnip_uint64_t) 0xAABBCCDDEEFF0011ULL;

  (void) params;
  (void) data;

  munit_assert_uint64(psnip_builtin_bswap64(v), ==, ((psnip_uint64_t) 0x1100FFEEDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse8(const MunitParameter params[], void* data) {
  const psnip_uint8_t vals[] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 0 ; i < (sizeof(vals) / sizeof(vals[0])) ; i++) {
    munit_assert_uint8(psnip_builtin_bitreverse8((psnip_int8_t) i), ==, (psnip_int8_t) vals[i]);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse16(const MunitParameter params[], void* data) {
  const struct { psnip_uint16_t v; psnip_uint16_t r; } tests[] = {
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

  (void) params;
  (void) data;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint16(psnip_builtin_bitreverse16(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse32(const MunitParameter params[], void* data) {
  const struct { psnip_uint32_t v; psnip_uint32_t r; } tests[] = {
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

  (void) params;
  (void) data;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint32(psnip_builtin_bitreverse32(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_bitreverse64(const MunitParameter params[], void* data) {
  const struct { psnip_uint64_t v; psnip_uint64_t r; } tests[] = {
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

  (void) params;
  (void) data;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint64(psnip_builtin_bitreverse64(tests[i].v), ==, tests[i].r);

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc8(const MunitParameter params[], void* data) {
  const struct { psnip_uint8_t x; psnip_uint8_t y; unsigned char ci; unsigned char co; psnip_uint8_t r; } test_vec[] = {
    { UINT8_C(0x15), UINT8_C(0x0d), 1, 0, UINT8_C(0x23) },
    { UINT8_C(0x1e), UINT8_C(0x32), 1, 0, UINT8_C(0x51) },
    { UINT8_C(0x85), UINT8_C(0x8a), 0, 1, UINT8_C(0x0f) },
    { UINT8_C(0xe0), UINT8_C(0xb5), 0, 1, UINT8_C(0x95) },
    { UINT8_C(0x33), UINT8_C(0x34), 1, 0, UINT8_C(0x68) },
    { UINT8_C(0x17), UINT8_C(0x30), 0, 0, UINT8_C(0x47) },
    { UINT8_C(0x83), UINT8_C(0x39), 1, 0, UINT8_C(0xbd) },
    { UINT8_C(0xb5), UINT8_C(0xed), 0, 1, UINT8_C(0xa2) },
    { UINT8_C(0xab), UINT8_C(0xa0), 1, 1, UINT8_C(0x4c) },
    { UINT8_C(0x0a), UINT8_C(0x20), 1, 0, UINT8_C(0x2b) },
    { UINT8_C(0xb8), UINT8_C(0xe1), 0, 1, UINT8_C(0x99) },
    { UINT8_C(0x33), UINT8_C(0x5e), 1, 0, UINT8_C(0x92) },
    { UINT8_C(0xa1), UINT8_C(0xf9), 0, 1, UINT8_C(0x9a) },
    { UINT8_C(0xfb), UINT8_C(0xe7), 1, 1, UINT8_C(0xe3) },
    { UINT8_C(0x69), UINT8_C(0xad), 0, 1, UINT8_C(0x16) },
    { UINT8_C(0xa0), UINT8_C(0x87), 1, 1, UINT8_C(0x28) },
    { UINT8_C(0xd9), UINT8_C(0x87), 1, 1, UINT8_C(0x61) },
    { UINT8_C(0x71), UINT8_C(0xeb), 0, 1, UINT8_C(0x5c) },
    { UINT8_C(0x5f), UINT8_C(0x85), 0, 0, UINT8_C(0xe4) },
    { UINT8_C(0x10), UINT8_C(0x00), 1, 0, UINT8_C(0x11) },
    { UINT8_C(0x0c), UINT8_C(0x0c), 1, 0, UINT8_C(0x19) },
    { UINT8_C(0xf7), UINT8_C(0xba), 1, 1, UINT8_C(0xb2) },
    { UINT8_C(0x12), UINT8_C(0xdc), 0, 0, UINT8_C(0xee) },
    { UINT8_C(0xa1), UINT8_C(0x84), 1, 1, UINT8_C(0x26) },
    { UINT8_C(0x6b), UINT8_C(0xe4), 1, 1, UINT8_C(0x50) },
    { UINT8_C(0x9e), UINT8_C(0x2a), 1, 0, UINT8_C(0xc9) },
    { UINT8_C(0x60), UINT8_C(0xa4), 1, 1, UINT8_C(0x05) },
    { UINT8_C(0xbc), UINT8_C(0x79), 1, 1, UINT8_C(0x36) },
    { UINT8_C(0x7c), UINT8_C(0xc2), 1, 1, UINT8_C(0x3f) },
    { UINT8_C(0x74), UINT8_C(0xf2), 1, 1, UINT8_C(0x67) },
    { UINT8_C(0xa8), UINT8_C(0x93), 0, 1, UINT8_C(0x3b) },
    { UINT8_C(0xc1), UINT8_C(0xd9), 1, 1, UINT8_C(0x9b) },
  };
  psnip_uint8_t r, co;
  size_t i;

  (void) params;
  (void) data;

  for(i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_builtin_addc8(test_vec[i].x, test_vec[i].y, test_vec[i].ci, &co);
    munit_assert_uint8(r, ==, test_vec[i].r);
    munit_assert_uint8(co, ==, test_vec[i].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc16(const MunitParameter params[], void* data) {
  const struct { psnip_uint16_t x; psnip_uint16_t y; unsigned char ci; unsigned char co; psnip_uint16_t r; } test_vec[] = {
    { UINT16_C(0x0500), UINT16_C(0x088b), 0, 0, UINT16_C(0x0d8b) },
    { UINT16_C(0xe9e9), UINT16_C(0xc711), 1, 1, UINT16_C(0xb0fb) },
    { UINT16_C(0xcf1b), UINT16_C(0xcf1d), 0, 1, UINT16_C(0x9e38) },
    { UINT16_C(0x0372), UINT16_C(0x0460), 1, 0, UINT16_C(0x07d3) },
    { UINT16_C(0xcd54), UINT16_C(0xfcdc), 0, 1, UINT16_C(0xca30) },
    { UINT16_C(0xf25d), UINT16_C(0xb728), 1, 1, UINT16_C(0xa986) },
    { UINT16_C(0xa671), UINT16_C(0x0295), 1, 0, UINT16_C(0xa907) },
    { UINT16_C(0x2f37), UINT16_C(0x1fed), 1, 0, UINT16_C(0x4f25) },
    { UINT16_C(0x13de), UINT16_C(0x4a7b), 0, 0, UINT16_C(0x5e59) },
    { UINT16_C(0x5fbc), UINT16_C(0x70c5), 0, 0, UINT16_C(0xd081) },
    { UINT16_C(0xd6a1), UINT16_C(0x917a), 0, 1, UINT16_C(0x681b) },
    { UINT16_C(0x8220), UINT16_C(0xef59), 0, 1, UINT16_C(0x7179) },
    { UINT16_C(0x3cde), UINT16_C(0xd462), 0, 1, UINT16_C(0x1140) },
    { UINT16_C(0xd5a4), UINT16_C(0xb4e5), 1, 1, UINT16_C(0x8a8a) },
    { UINT16_C(0x142e), UINT16_C(0x76d1), 0, 0, UINT16_C(0x8aff) },
    { UINT16_C(0xa233), UINT16_C(0xa397), 1, 1, UINT16_C(0x45cb) },
    { UINT16_C(0x0b1f), UINT16_C(0xe8e0), 0, 0, UINT16_C(0xf3ff) },
    { UINT16_C(0x2e4c), UINT16_C(0x27a2), 1, 0, UINT16_C(0x55ef) },
    { UINT16_C(0x29bd), UINT16_C(0x21c0), 0, 0, UINT16_C(0x4b7d) },
    { UINT16_C(0x71fa), UINT16_C(0x3a02), 1, 0, UINT16_C(0xabfd) },
    { UINT16_C(0x3eff), UINT16_C(0x1636), 1, 0, UINT16_C(0x5536) },
    { UINT16_C(0x205f), UINT16_C(0x0fcc), 0, 0, UINT16_C(0x302b) },
    { UINT16_C(0x00c5), UINT16_C(0x2caf), 1, 0, UINT16_C(0x2d75) },
    { UINT16_C(0xc338), UINT16_C(0xc71d), 1, 1, UINT16_C(0x8a56) },
    { UINT16_C(0xbd8b), UINT16_C(0xa8f0), 1, 1, UINT16_C(0x667c) },
    { UINT16_C(0xa3fd), UINT16_C(0xb222), 1, 1, UINT16_C(0x5620) },
    { UINT16_C(0xeb27), UINT16_C(0xe539), 1, 1, UINT16_C(0xd061) },
    { UINT16_C(0x473d), UINT16_C(0x799b), 1, 0, UINT16_C(0xc0d9) },
    { UINT16_C(0xf835), UINT16_C(0x6b22), 1, 1, UINT16_C(0x6358) },
    { UINT16_C(0x1423), UINT16_C(0xa1ee), 1, 0, UINT16_C(0xb612) },
    { UINT16_C(0x29d6), UINT16_C(0xcfa1), 0, 0, UINT16_C(0xf977) },
    { UINT16_C(0xc7be), UINT16_C(0x89f4), 1, 1, UINT16_C(0x51b3) }
  };
  psnip_uint16_t r, co;
  size_t i;

  (void) params;
  (void) data;

  for(i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_builtin_addc16(test_vec[i].x, test_vec[i].y, test_vec[i].ci, &co);
    munit_assert_uint16(r, ==, test_vec[i].r);
    munit_assert_uint16(co, ==, test_vec[i].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc32(const MunitParameter params[], void* data) {
  const struct { psnip_uint32_t x; psnip_uint32_t y; unsigned char ci; unsigned char co; psnip_uint32_t r; } test_vec[] = {
    { UINT32_C(0xd6e28399), UINT32_C(0x07b88c6c), 0, 0, UINT32_C(0xde9b1005) },
    { UINT32_C(0x643e007d), UINT32_C(0x43474188), 0, 0, UINT32_C(0xa7854205) },
    { UINT32_C(0xeaf1d0a1), UINT32_C(0x34e5c499), 1, 1, UINT32_C(0x1fd7953b) },
    { UINT32_C(0xc94ffb33), UINT32_C(0xac13b02d), 1, 1, UINT32_C(0x7563ab61) },
    { UINT32_C(0x283e0221), UINT32_C(0x210b98a3), 0, 0, UINT32_C(0x49499ac4) },
    { UINT32_C(0x39cb9609), UINT32_C(0x6dd59214), 0, 0, UINT32_C(0xa7a1281d) },
    { UINT32_C(0x9690ee1b), UINT32_C(0x80cc70bb), 1, 1, UINT32_C(0x175d5ed7) },
    { UINT32_C(0xa2d053d9), UINT32_C(0x7d3bea72), 1, 1, UINT32_C(0x200c3e4c) },
    { UINT32_C(0x5b09a768), UINT32_C(0x77400f87), 1, 0, UINT32_C(0xd249b6f0) },
    { UINT32_C(0xa8118df8), UINT32_C(0x84c23c91), 0, 1, UINT32_C(0x2cd3ca89) },
    { UINT32_C(0xfcabb614), UINT32_C(0xf9c7e062), 0, 1, UINT32_C(0xf6739676) },
    { UINT32_C(0x56cc2b0a), UINT32_C(0x341f8c12), 1, 0, UINT32_C(0x8aebb71d) },
    { UINT32_C(0x1e14adba), UINT32_C(0xc0744d37), 0, 0, UINT32_C(0xde88faf1) },
    { UINT32_C(0xa20417cc), UINT32_C(0x3e357de9), 0, 0, UINT32_C(0xe03995b5) },
    { UINT32_C(0xc639cb32), UINT32_C(0xacd318b0), 1, 1, UINT32_C(0x730ce3e3) },
    { UINT32_C(0x25b7fbdc), UINT32_C(0x5f3da123), 0, 0, UINT32_C(0x84f59cff) },
    { UINT32_C(0x689ed95a), UINT32_C(0xcd952021), 1, 1, UINT32_C(0x3633f97c) },
    { UINT32_C(0xb83126ca), UINT32_C(0x9030dac4), 0, 1, UINT32_C(0x4862018e) },
    { UINT32_C(0x0e0c8854), UINT32_C(0x7f209293), 0, 0, UINT32_C(0x8d2d1ae7) },
    { UINT32_C(0x7ff47a40), UINT32_C(0xb955c586), 1, 1, UINT32_C(0x394a3fc7) },
    { UINT32_C(0xb30a7021), UINT32_C(0x5a01b676), 1, 1, UINT32_C(0x0d0c2698) },
    { UINT32_C(0x5d312656), UINT32_C(0xb5b6696d), 1, 1, UINT32_C(0x12e78fc4) },
    { UINT32_C(0x206382ae), UINT32_C(0xfecd03af), 1, 1, UINT32_C(0x1f30865e) },
    { UINT32_C(0xe8059049), UINT32_C(0xb17468c8), 0, 1, UINT32_C(0x9979f911) },
    { UINT32_C(0x7145adde), UINT32_C(0x6e8d3468), 1, 0, UINT32_C(0xdfd2e247) },
    { UINT32_C(0x79ccd8f1), UINT32_C(0x439c869d), 1, 0, UINT32_C(0xbd695f8f) },
    { UINT32_C(0x2518026c), UINT32_C(0xbf87c59b), 0, 0, UINT32_C(0xe49fc807) },
    { UINT32_C(0xa1ec05c4), UINT32_C(0xd0351014), 0, 1, UINT32_C(0x722115d8) },
    { UINT32_C(0xad89d7d9), UINT32_C(0xfe7d3513), 0, 1, UINT32_C(0xac070cec) },
    { UINT32_C(0x858bb940), UINT32_C(0xae803776), 1, 1, UINT32_C(0x340bf0b7) },
    { UINT32_C(0x9b9e137a), UINT32_C(0xc7a3ba74), 0, 1, UINT32_C(0x6341cdee) },
    { UINT32_C(0x90dc3555), UINT32_C(0x8482c34c), 0, 1, UINT32_C(0x155ef8a1) }
  };
  psnip_uint32_t r, co;
  size_t i;

  (void) params;
  (void) data;

  for(i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_builtin_addc32(test_vec[i].x, test_vec[i].y, test_vec[i].ci, &co);
    munit_assert_uint32(r, ==, test_vec[i].r);
    munit_assert_uint32(co, ==, test_vec[i].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_addc64(const MunitParameter params[], void* data) {
  const struct { psnip_uint64_t x; psnip_uint64_t y; unsigned char ci; unsigned char co; psnip_uint64_t r; } test_vec[] = {
    { UINT64_C(0x87f34d2d7c62e0d2), UINT64_C(0xd4c4e0156a93356b), 1, 1, UINT64_C(0x5cb82d42e6f6163e) },
    { UINT64_C(0x00efff1769bd8f59), UINT64_C(0xc777482ac2f64491), 1, 0, UINT64_C(0xc86747422cb3d3eb) },
    { UINT64_C(0x993775bf564adc9e), UINT64_C(0xf39a41d4215b71f4), 1, 1, UINT64_C(0x8cd1b79377a64e93) },
    { UINT64_C(0xe2ea05bd4fa343d0), UINT64_C(0xd94eaec8b8a6705f), 0, 1, UINT64_C(0xbc38b4860849b42f) },
    { UINT64_C(0x83f531f4f7775d16), UINT64_C(0x11c1da2c369570f0), 1, 0, UINT64_C(0x95b70c212e0cce07) },
    { UINT64_C(0xe9a06ff3e145fa12), UINT64_C(0x8a15e641e99809d1), 1, 1, UINT64_C(0x73b65635cade03e4) },
    { UINT64_C(0x23a6a4caf35aa045), UINT64_C(0x67fb3424f9e35c29), 0, 0, UINT64_C(0x8ba1d8efed3dfc6e) },
    { UINT64_C(0x543a677f003fe9de), UINT64_C(0x98ef222553a62c0a), 1, 0, UINT64_C(0xed2989a453e615e9) },
    { UINT64_C(0x31abdb425f41e936), UINT64_C(0xe5347243906067ed), 0, 1, UINT64_C(0x16e04d85efa25123) },
    { UINT64_C(0xe7bc4f347af75d31), UINT64_C(0x086301897e918285), 0, 0, UINT64_C(0xf01f50bdf988dfb6) },
    { UINT64_C(0xbd242b87dd79ad87), UINT64_C(0x75e7e8220c017586), 0, 1, UINT64_C(0x330c13a9e97b230d) },
    { UINT64_C(0x8bc2b96c29f22baa), UINT64_C(0x43d23d476e43ded1), 0, 0, UINT64_C(0xcf94f6b398360a7b) },
    { UINT64_C(0xc9ef618f647672a4), UINT64_C(0xa237503de7b99143), 0, 1, UINT64_C(0x6c26b1cd4c3003e7) },
    { UINT64_C(0x6f49c49aad18e783), UINT64_C(0xf10bd265ccc5fc53), 1, 1, UINT64_C(0x6055970079dee3d7) },
    { UINT64_C(0x96edea38864740e8), UINT64_C(0xc4472c59d3142c88), 0, 1, UINT64_C(0x5b351692595b6d70) },
    { UINT64_C(0xc28945c921220907), UINT64_C(0x5d5b13bf1e0a75db), 0, 1, UINT64_C(0x1fe459883f2c7ee2) },
    { UINT64_C(0x0c51752efe44cdfd), UINT64_C(0xccb8624452f97aca), 0, 0, UINT64_C(0xd909d773513e48c7) },
    { UINT64_C(0x857dbe02ad4dd1fe), UINT64_C(0x77e6ffb32dc670e5), 0, 0, UINT64_C(0xfd64bdb5db1442e3) },
    { UINT64_C(0xda165ac60b628275), UINT64_C(0x2d199cd8336f6a3d), 1, 1, UINT64_C(0x072ff79e3ed1ecb3) },
    { UINT64_C(0x3b4196f7dcec2617), UINT64_C(0xe37bc8e0eef114ba), 1, 1, UINT64_C(0x1ebd5fd8cbdd3ad2) },
    { UINT64_C(0xf26da63ff8979eee), UINT64_C(0xb583bc60b66f32d7), 1, 1, UINT64_C(0xa7f162a0af06d1c6) },
    { UINT64_C(0xb943a896bed9adeb), UINT64_C(0x8e82416eb329b0ec), 0, 1, UINT64_C(0x47c5ea0572035ed7) },
    { UINT64_C(0xd13b561ef4c2d6b4), UINT64_C(0x04417152716190e9), 0, 0, UINT64_C(0xd57cc7716624679d) },
    { UINT64_C(0x47b6a3af5ea1bed1), UINT64_C(0xee804be33ebbcab1), 1, 1, UINT64_C(0x3636ef929d5d8983) },
    { UINT64_C(0xc787c8d692984d2f), UINT64_C(0x63c4fa3653a9329b), 0, 1, UINT64_C(0x2b4cc30ce6417fca) },
    { UINT64_C(0x299f2bf181ca874c), UINT64_C(0x36a42c37dfa2da55), 0, 0, UINT64_C(0x60435829616d61a1) },
    { UINT64_C(0x853d2f98532f31d1), UINT64_C(0x91c6f369b7e0f644), 1, 1, UINT64_C(0x170423020b102816) },
    { UINT64_C(0xbc06c8ecdfeed660), UINT64_C(0x56050235e8b9d548), 0, 1, UINT64_C(0x120bcb22c8a8aba8) },
    { UINT64_C(0x6e995efd5c0e4161), UINT64_C(0xe6f28bd7b620215c), 0, 1, UINT64_C(0x558bead5122e62bd) },
    { UINT64_C(0x3da1e5684ae63e6f), UINT64_C(0xb74ac37e297276c3), 0, 0, UINT64_C(0xf4eca8e67458b532) },
    { UINT64_C(0x81ced8eddc8c79f2), UINT64_C(0xabc69e6c5b44c02d), 0, 1, UINT64_C(0x2d95775a37d13a1f) },
    { UINT64_C(0x8fe6ae84b79bd7f0), UINT64_C(0x2fb0254a05534cc5), 0, 0, UINT64_C(0xbf96d3cebcef24b5) }
  };
  psnip_uint64_t r, co;
  size_t i;

  (void) params;
  (void) data;

  for(i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_builtin_addc64(test_vec[i].x, test_vec[i].y, test_vec[i].ci, &co);
    munit_assert_uint64(r, ==, test_vec[i].r);
    munit_assert_uint64(co, ==, test_vec[i].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcb(const MunitParameter params[], void* data) {
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

  (void) params;
  (void) data;

  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    unsigned char r, co;
    r = psnip_builtin_subcb(test_vec[0].x, test_vec[0].y, test_vec[0].ci, &co);
    munit_assert_uint8(r,  ==, test_vec[0].r);
    munit_assert_uint8(co, ==, test_vec[0].co);
  }

  return MUNIT_OK;
}

static MunitResult
test_gnu_subcs(const MunitParameter params[], void* data) {
  unsigned short co, r;

  (void) params;
  (void) data;

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
test_gnu_subc(const MunitParameter params[], void* data) {
  unsigned int co, r;

  (void) params;
  (void) data;

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
test_gnu_subcl(const MunitParameter params[], void* data) {
  unsigned long co, r;

  (void) params;
  (void) data;

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
test_gnu_subcll(const MunitParameter params[], void* data) {
  unsigned long long co, r;

  (void) params;
  (void) data;

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
test_msvc_rotl8(const MunitParameter params[], void* data) {
  const psnip_uint8_t v = 'A';
  const psnip_uint8_t expected[] = {
          0x82, 0x05, 0x0a,
    0x14, 0x28, 0x50
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint8(psnip_intrin_rotl8(v, (psnip_uint8_t) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl16(const MunitParameter params[], void* data) {
  const psnip_uint16_t v = 0x12;
  const unsigned short expected[] = {
            0x0024, 0x0048, 0x0090,
    0x0120, 0x0240, 0x0480, 0x0900,
    0x1200, 0x2400, 0x4800, 0x9000,
    0x2001, 0x4002, 0x8004
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint16(psnip_intrin_rotl16(v, (unsigned char) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl(const MunitParameter params[], void* data) {
  const psnip_uint32_t v = 0xfd93U;
  const psnip_uint32_t expected[] = {
                 0x0001fb26U, 0x0003f64cU, 0x0007ec98U,
    0x000fd930U, 0x001fb260U, 0x003f64c0U, 0x007ec980U,
    0x00fd9300U, 0x01fb2600U, 0x03f64c00U, 0x07ec9800U,
    0x0fd93000U, 0x1fb26000U, 0x3f64c000U, 0x7ec98000U,
    0xfd930000U, 0xfb260001U, 0xf64c0003U, 0xec980007U,
    0xd930000fU, 0xb260001fU, 0x64c0003fU, 0xc980007eU,
    0x930000fdU, 0x260001fbU, 0x4c0003f6U, 0x980007ecU,
    0x30000fd9U, 0x60001fb2U, 0xc0003f64U
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint32(psnip_intrin_rotl(v, (int) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotl64(const MunitParameter params[], void* data) {
  const psnip_uint64_t v = UINT64_C(0x3db5195091e98f9d);
  const psnip_uint64_t expected[] = {
                                  UINT64_C(0x7b6a32a123d31f3a), UINT64_C(0xf6d4654247a63e74), UINT64_C(0xeda8ca848f4c7ce9),
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
    UINT64_C(0xd3db5195091e98f9), UINT64_C(0xa7b6a32a123d31f3), UINT64_C(0x4f6d4654247a63e7)
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint64(psnip_intrin_rotl64(v, (int) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr8(const MunitParameter params[], void* data) {
  const psnip_uint8_t v = 'A';
  const psnip_uint8_t expected[] = {
          0xa0, 0x50, 0x28,
    0x14, 0x0a, 0x05
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint8(psnip_intrin_rotr8(v, (psnip_uint8_t) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr16(const MunitParameter params[], void* data) {
  const psnip_uint16_t v = 0x12;
  const psnip_uint16_t expected[] = {
            0x0009, 0x8004, 0x4002,
    0x2001, 0x9000, 0x4800, 0x2400,
    0x1200, 0x0900, 0x0480, 0x0240,
    0x0120, 0x0090, 0x0048
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint16(psnip_intrin_rotr16(v, (psnip_uint8_t) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr(const MunitParameter params[], void* data) {
  const psnip_uint32_t v = 0x0fd93;
  const psnip_uint32_t expected[] = {
                          UINT32_C(0x80007ec9), UINT32_C(0xc0003f64), UINT32_C(0x60001fb2),
    UINT32_C(0x30000fd9), UINT32_C(0x980007ec), UINT32_C(0x4c0003f6), UINT32_C(0x260001fb),
    UINT32_C(0x930000fd), UINT32_C(0xc980007e), UINT32_C(0x64c0003f), UINT32_C(0xb260001f),
    UINT32_C(0xd930000f), UINT32_C(0xec980007), UINT32_C(0xf64c0003), UINT32_C(0xfb260001),
    UINT32_C(0xfd930000), UINT32_C(0x7ec98000), UINT32_C(0x3f64c000), UINT32_C(0x1fb26000),
    UINT32_C(0x0fd93000), UINT32_C(0x07ec9800), UINT32_C(0x03f64c00), UINT32_C(0x01fb2600),
    UINT32_C(0x00fd9300), UINT32_C(0x007ec980), UINT32_C(0x003f64c0), UINT32_C(0x001fb260),
    UINT32_C(0x000fd930), UINT32_C(0x0007ec98), UINT32_C(0x0003f64c)
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint32(psnip_intrin_rotr(v, (int) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_rotr64(const MunitParameter params[], void* data) {
  const psnip_uint64_t v = UINT64_C(0x3db5195091e98f9d);
  const psnip_uint64_t expected[] = {
                                  UINT64_C(0x9eda8ca848f4c7ce), UINT64_C(0x4f6d4654247a63e7), UINT64_C(0xa7b6a32a123d31f3),
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
    UINT64_C(0xdb5195091e98f9d3), UINT64_C(0xeda8ca848f4c7ce9), UINT64_C(0xf6d4654247a63e74)
  };
  size_t i;

  (void) params;
  (void) data;

  for (i = 1; i < (sizeof(expected) / sizeof(expected[0])) ; i++)
    munit_assert_uint64(psnip_intrin_rotr64(v, (int) i), ==, expected[i - 1]);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward(const MunitParameter params[], void* data) {
  unsigned long idx;
  unsigned char isNonzero;
  psnip_uint32_t mask = ~((psnip_uint32_t) 0);
  int i;

  (void) params;
  (void) data;

  munit_assert_uint8(psnip_intrin_BitScanForward(&idx, 0), ==, 0);

  for (i = 0 ; i < 32 ; i++) {
    isNonzero = psnip_intrin_BitScanForward(&idx, mask);
    munit_assert_uint8(isNonzero, ==, 1);
    munit_assert_ulong(idx, ==, i);
    mask <<= 1;
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanForward64(const MunitParameter params[], void* data) {
  unsigned long idx;
  unsigned char isNonzero;
  int i;

  (void) params;
  (void) data;

  munit_assert_uint8(psnip_intrin_BitScanForward64(&idx, 0), ==, 0);

  for (i = 0 ; i < 64 ; i++) {
    isNonzero = psnip_intrin_BitScanForward64(&idx, ULLONG_MAX << i);
    munit_assert_uint8(isNonzero, ==, 1);
    munit_assert_ulong(idx, ==, i);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanReverse(const MunitParameter params[], void* data) {
  psnip_uint32_t mask = 12;
  unsigned long idx;
  unsigned char isNonzero;

  (void) params;
  (void) data;

  isNonzero = psnip_intrin_BitScanReverse(&idx, mask);
  munit_assert_uint8(isNonzero, ==, 1);
  munit_assert_uint32(idx, ==, 3);

  return MUNIT_OK;
}

static MunitResult
test_msvc_BitScanReverse64(const MunitParameter params[], void* data) {
  psnip_uint64_t mask = 12;
  unsigned long idx;
  unsigned char isNonzero;

  (void) params;
  (void) data;

  isNonzero = psnip_intrin_BitScanReverse64(&idx, mask);
  munit_assert_uint8(isNonzero, ==, 1);
  munit_assert_long(idx, ==, 3);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest(const MunitParameter params[], void* data) {
  psnip_int32_t num = 78002;
  const char bits[] = "0100110100001100100000000000000";
  long nBit;

  (void) params;
  (void) data;

  /* Yes, I know this only looks at 31 bits.  I'm trying to match
   * Microsoft's example on
   * https://msdn.microsoft.com/en-us/library/h65k4tze.aspx */

  for (nBit = 0 ; nBit < 31 ; nBit++)
    munit_assert_uint8((psnip_uint8_t) (bits[nBit] == '1'), ==, psnip_intrin_bittest(&num, nBit));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittest64(const MunitParameter params[], void* data) {
  psnip_int64_t num = UINT64_C(0x7273c4752334168f);
  const psnip_uint8_t bits[] = {
    1, 1, 1, 1, 0, 0, 0, 1,   0, 1, 1, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 1, 1, 0, 0,   1, 1, 0, 0, 0, 1, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0,   0, 0, 1, 0, 0, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 0,   0, 1, 0, 0, 1, 1, 1, 0
  };
  int i;

  (void) params;
  (void) data;

  for (i = 0 ; i < 64 ; i++)
    munit_assert_uint8(bits[i], ==, psnip_intrin_bittest64(&num, i));

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement(const MunitParameter params[], void* data) {
  psnip_int32_t i = 1;
  unsigned char result;

  (void) params;
  (void) data;

  result = psnip_intrin_bittestandcomplement(&i, 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, 3);

  result = psnip_intrin_bittestandcomplement(&i, 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_long(i, ==, 1);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandcomplement64(const MunitParameter params[], void* data) {
  psnip_int64_t i = 1;
  unsigned char result;

  (void) params;
  (void) data;

  result = psnip_intrin_bittestandcomplement64(&i, 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_uint64(i, ==, 3);

  result = psnip_intrin_bittestandcomplement64(&i, 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_int64(i, ==, 1);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset(const MunitParameter params[], void* data) {
  psnip_int32_t i = -112;
  unsigned char result;

  (void) params;
  (void) data;

  result = psnip_intrin_bittestandreset(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_int32(i, ==, 0x7fffffff - 111);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandreset64(const MunitParameter params[], void* data) {
  psnip_int64_t i = -112;
  unsigned char result;

  (void) params;
  (void) data;

  result = psnip_intrin_bittestandreset64(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 1);
  munit_assert_int64(i, ==, 0x7fffffffffffffffLL - 111);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset(const MunitParameter params[], void* data) {
  psnip_int32_t i = 0x7fffffff - 111;
  unsigned char result;

  (void) params;
  (void) data;

  result = psnip_intrin_bittestandset(&i, (sizeof(i) * 8) - 1);
  munit_assert_uint8(result, ==, 0);
  munit_assert_long(i, ==, -112);

  return MUNIT_OK;
}

static MunitResult
test_msvc_bittestandset64(const MunitParameter params[], void* data) {
  psnip_int64_t s, d, t;
  int i;
  size_t p;
  unsigned char r;

  (void) params;
  (void) data;

  for (i = 0 ; i < 128 ; i++) {
    munit_rand_memory(sizeof(s), (psnip_uint8_t*) &s);
    d = 0;
    t = s;

    for (p = 0; p < (sizeof(s) * CHAR_BIT) ; p++) {
      if ((t & 1) == 1) {
	r = psnip_intrin_bittestandset64(&d, p);
	munit_assert_uint8(r, ==, 0);
      }
      t >>= 1;
    }

    munit_assert_int64(d, ==, s);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftleft128(const MunitParameter params[], void* data) {
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
  psnip_uint64_t r;

  (void) params;
  (void) data;

  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_intrin_shiftleft128(test_vec[i].l, test_vec[i].h, test_vec[i].s);
    munit_assert_uint64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_shiftright128(const MunitParameter params[], void* data) {
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
  psnip_uint64_t r;

  (void) params;
  (void) data;

  for (i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    r = psnip_intrin_shiftright128(test_vec[i].l, test_vec[i].h, test_vec[i].s);
    munit_assert_uint64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_ushort(const MunitParameter params[], void* data) {
  psnip_uint16_t v = (psnip_uint16_t) 0xAABBULL;

  (void) params;
  (void) data;

  munit_assert_uint16(psnip_intrin_byteswap_ushort(v), ==, ((psnip_uint16_t) 0xBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_ulong(const MunitParameter params[], void* data) {
  psnip_uint32_t v = (psnip_uint32_t) 0xAABBCCDDULL;

  (void) params;
  (void) data;

  munit_assert_uint32(psnip_intrin_byteswap_ulong(v), ==, ((psnip_uint32_t) 0xDDCCBBAAULL));

  return MUNIT_OK;
}

static MunitResult
test_msvc_byteswap_uint64(const MunitParameter params[], void* data) {
  psnip_uint64_t v = (psnip_uint64_t) 0xAABBCCDDEEFF0011ULL;

  (void) params;
  (void) data;

  munit_assert_uint64(psnip_intrin_byteswap_uint64(v), ==, ((psnip_uint64_t) 0x1100FFEEDDCCBBAAULL));

  return MUNIT_OK;
}

#define PSNIP_TEST_BUILTIN(name)					\
  { (char*) "/builtin/"#name, test_gnu_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }
#define PSNIP_TEST_INTRIN(name) \
  { (char*) "/intrin/"#name, test_msvc_##name, NULL, NULL, MUNIT_TEST_OPTION_SINGLE_ITERATION, NULL }

static MunitTest test_suite_tests[] = {
  PSNIP_TEST_BUILTIN(ffs),
  PSNIP_TEST_BUILTIN(ffsl),
  PSNIP_TEST_BUILTIN(ffsll),
  PSNIP_TEST_BUILTIN(clz),
  PSNIP_TEST_BUILTIN(clzl),
  PSNIP_TEST_BUILTIN(clzll),
  PSNIP_TEST_BUILTIN(clz32),
  PSNIP_TEST_BUILTIN(clz64),
  PSNIP_TEST_BUILTIN(ctz),
  PSNIP_TEST_BUILTIN(ctzl),
  PSNIP_TEST_BUILTIN(ctzll),
  PSNIP_TEST_BUILTIN(ctz32),
  PSNIP_TEST_BUILTIN(ctz64),
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
  PSNIP_TEST_BUILTIN(addc8),
  PSNIP_TEST_BUILTIN(addc16),
  PSNIP_TEST_BUILTIN(addc32),
  PSNIP_TEST_BUILTIN(addc64),
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

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1 << 20, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
