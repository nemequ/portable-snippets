#define PSNIP_UNALIGNED_ALLOW_UNDEFINED
/* #define PSNIP_UNALIGNED_ALLOW_UBSAN */
/* #define PSNIP_UNALIGNED_IMPL 2 */
/* #define PSNIP_UNALIGNED_IMPL 3 */

#include "../exact-int/exact-int.h"
#include "../unaligned/unaligned.h"
#include "munit/munit.h"

#include <stdio.h>

static psnip_uint8_t buffer[1024 * 1024];

static MunitResult
test_unaligned_uint64(const MunitParameter params[], void* data) {
  psnip_uint64_t v;
  psnip_uint8_t* c = buffer;
  psnip_uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);

  (void) params;
  (void) data;

  while (c <= e) {
    munit_rand_memory(sizeof(v), (psnip_uint8_t*) &v);
    v ^= psnip_unaligned_load_uint64(c);
    psnip_unaligned_store_uint64(c, v);

    c++;
  }

  return MUNIT_OK;
}

static MunitResult
test_unaligned_uint32(const MunitParameter params[], void* data) {
  psnip_uint32_t v;
  psnip_uint8_t* c = buffer;
  psnip_uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);

  (void) params;
  (void) data;

  while (c <= e) {
    munit_rand_memory(sizeof(v), (psnip_uint8_t*) &v);
    v ^= psnip_unaligned_load_uint32(c);
    psnip_unaligned_store_uint32(c, v);

    c++;
  }

  return MUNIT_OK;
}

static MunitResult
test_unaligned_uint16(const MunitParameter params[], void* data) {
  psnip_uint16_t v;
  psnip_uint8_t* c = buffer;
  psnip_uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);

  (void) params;
  (void) data;

  while (c <= e) {
    munit_rand_memory(sizeof(v), (psnip_uint8_t*) &v);
    v ^= psnip_unaligned_load_uint16(c);
    psnip_unaligned_store_uint16(c, v);

    c++;
  }

  return MUNIT_OK;
}

/* Try to get the compiler to vectorize this; SIMD instructions are
   more likely to have problems with unaligned accesses. */
#if defined(__GNUC__)
#  if !defined(__clang__)
__attribute__((__optimize__(3),__noinline__))
#  else
__attribute__((__noinline__))
#  endif
#endif
static void
dangerous_copy(size_t count, psnip_uint64_t* dest, const psnip_uint64_t* src) {
  size_t i;
  for (i = 0 ; i < count ; i++) {
    psnip_unaligned_store_uint64(&(dest[i]), psnip_unaligned_load_uint64(&(src[i])));
  }
}

#if defined(__GNUC__)
#  if !defined(__clang__)
__attribute__((__optimize__(0),__noinline__))
#  else
__attribute__((__optnone__,__noinline__))
#  endif
#endif
static MunitResult
test_unaligned_uint64_tempt(const MunitParameter params[], void* data) {
  static psnip_uint8_t buffer2[sizeof(buffer)];
  psnip_uint8_t buffer_x = 0;
  psnip_uint8_t buffer_y = 0;
  size_t i;

  (void) params;
  (void) data;

  munit_rand_memory(sizeof(buffer), buffer);


  dangerous_copy((sizeof(buffer) / sizeof(psnip_uint64_t)) - 1,
		 (void*) (buffer2 + 1), (void*) (buffer + 1));

  /* XOR all the data together, just to try to convince the compiler
   * not to optimize anything away. */

  for (i = 1 ; i < (sizeof(buffer) - (sizeof(psnip_uint64_t) - 1)) ; i++) {
    buffer_x ^= buffer[i];
    buffer_y ^= buffer[i];
  }

  munit_assert_uint8(buffer_x, ==, buffer_y);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/unaligned/uint64",       test_unaligned_uint64,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/unaligned/uint32",       test_unaligned_uint32,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/unaligned/uint16",       test_unaligned_uint16,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/unaligned/uint64/tempt", test_unaligned_uint64_tempt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  munit_rand_memory(sizeof(buffer), buffer);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
