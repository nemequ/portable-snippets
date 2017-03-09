#define PSNIP_UNALIGNED_ALLOW_UNDEFINED
/* #define PSNIP_UNALIGNED_ALLOW_UBSAN */
/* #define PSNIP_UNALIGNED_IMPL 2 */
/* #define PSNIP_UNALIGNED_IMPL 3 */

#include "../exact-int/exact-int.h"
#include "../unaligned/unaligned.h"
#include "munit/munit.h"

#include <stdio.h>

static uint8_t buffer[1024 * 1024];

static MunitResult
test_unaligned_uint64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint64_t v;

  uint8_t* c = buffer;
  uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);
  while (c <= e) {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);
    v ^= psnip_unaligned_load_uint64(c);
    psnip_unaligned_store_uint64(c, v);

    c++;
  }

  return MUNIT_OK;
}

static MunitResult
test_unaligned_uint32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint32_t v;

  uint8_t* c = buffer;
  uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);
  while (c <= e) {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);
    v ^= psnip_unaligned_load_uint32(c);
    psnip_unaligned_store_uint32(c, v);

    c++;
  }

  return MUNIT_OK;
}

static MunitResult
test_unaligned_uint16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  uint16_t v;

  uint8_t* c = buffer;
  uint8_t* e = &(buffer[sizeof(buffer)]) - sizeof(v);
  while (c <= e) {
    munit_rand_memory(sizeof(v), (uint8_t*) &v);
    v ^= psnip_unaligned_load_uint16(c);
    psnip_unaligned_store_uint16(c, v);

    c++;
  }

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/unaligned/uint64", test_unaligned_uint64, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/unaligned/uint32", test_unaligned_uint32, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/unaligned/uint16", test_unaligned_uint16, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  munit_rand_memory(sizeof(buffer), buffer);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
