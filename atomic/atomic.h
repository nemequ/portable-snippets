/* Atomic operations (v1)
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * This is a small abstraction layer for some common atomic operations
 * (load, store, add, subtract, and compare & swap) implemented using
 * various compiler-specific builtins.
 *
 * There are four types, 32-bit and 64-bit integers which are both
 * atomic and non-atomic.  The atomic versions should be used for the
 * atomic variable, the non-atomic variables should be used to store
 * values read from or written to an atomic variable.  For example, a
 * basic CAS loop:
 *
 *   void square_dest(psnip_atomic_int64* value) {
 *     psnip_int64_t expected;
 *     do {
 *       expected = psnip_atomic_int64_load(&value);
 *     } while (!psnip_atomic_int64_compare_exchange(&value, &expected, expected * expected));
 *   }
 *
 * Most things are implemented with the preprocessor, but if they were
 * functions the prototypes (the 64-bit versions, just s/64/32/ for
 * the 32-bit versions) would loo like:
 *
 *   psnip_int64_t psnip_atomic_int64_load(
 *       psnip_atomic_int64* object);
 *   void psnip_atomic_int64_store(
 *       psnip_atomic_int64* object,
 *       psnip_int64_t desired);
 *   _Bool psnip_atomic_int64_compare_exchange(
 *       psnip_atomic_int64* object,
 *       psnip_int64_t* expected,
 *       psnip_int64_t desired);
 *   psnip_int64_t psnip_atomic_int64_add(
 *       psnip_atomic_int64* object,
 *       psnip_int64_t operand);
 *   psnip_int64_t psnip_atomic_int64_sub(
 *       psnip_atomic_int64* object,
 *       psnip_int64_t operand);
 */

#if !defined(PSNIP_ATOMIC_H)
#define PSNIP_ATOMIC_H

/* For maximum portability include the exact-int module from
   portable snippets. */
#if \
  !defined(psnip_int64_t) || \
  !defined(psnip_int32_t)
#  include <stdint.h>
#  if !defined(psnip_int64_t)
#    define psnip_int64_t int64_t
#  endif
#  if !defined(psnip_int32_t)
#    define psnip_int32_t int32_t
#  endif
#endif

#if !defined(PSNIP_ATOMIC_STATIC_INLINE)
#  if defined(__GNUC__)
#    define PSNIP_ATOMIC__COMPILER_ATTRIBUTES __attribute__((__unused__))
#  else
#    define PSNIP_ATOMIC__COMPILER_ATTRIBUTES
#  endif

#  if defined(HEDLEY_INLINE)
#    define PSNIP_ATOMIC__INLINE HEDLEY_INLINE
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define PSNIP_ATOMIC__INLINE inline
#  elif defined(__GNUC_STDC_INLINE__)
#    define PSNIP_ATOMIC__INLINE __inline__
#  elif defined(_MSC_VER) && _MSC_VER >= 1200
#    define PSNIP_ATOMIC__INLINE __inline
#  else
#    define PSNIP_ATOMIC__INLINE
#  endif

#  define PSNIP_ATOMIC__FUNCTION PSNIP_ATOMIC__COMPILER_ATTRIBUTES static PSNIP_ATOMIC__INLINE
#endif

#if defined(__has_feature)
#  define PSNIP_ATOMIC_HAS_FEATURE(feature) __has_feature(feature)
#else
#  define PSNIP_ATOMIC_HAS_FEATURE(feature) 0
#endif

#define PSNIP_ATOMIC_IMPL_NONE 0
#define PSNIP_ATOMIC_IMPL_GCC 1
#define PSNIP_ATOMIC_IMPL_GCC_SYNC 2
#define PSNIP_ATOMIC_IMPL_CLANG 3
#define PSNIP_ATOMIC_IMPL_MS 4
#define PSNIP_ATOMIC_IMPL_OPENMP 5
#define PSNIP_ATOMIC_IMPL_C11 11

#if defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_GCC
#elif !defined(__INTEL_COMPILER) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_ATOMICS__)
/* GCC 4.7 and 4.8 sets __STDC_VERSION__ to C11 (if compiling in C11
 * mode) and didn't have stdatomic.h, but failed to set
 * __STDC_NO_ATOMICS__.  Verions prior to 4.7 didn't set
 * __STDC_VERSION__ to C11. */
#  if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 9)
#    define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_GCC
#  else
#    define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_C11
#  endif
#elif defined(_MSC_VER)
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_MS
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_GCC
#elif PSNIP_ATOMIC_HAS_FEATURE(c_atomic)
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_CLANG
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_GCC_SYNC
#elif (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x5140)) || (defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5140))
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_GCC
#elif defined(_OPENMP)
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_OPENMP
#else
#  define PSNIP_ATOMIC_NOT_FOUND
#  define PSNIP_ATOMIC_IMPL PSNIP_ATOMIC_IMPL_NONE
#  warning No atomic implementation found
#endif

#if !defined(PSNIP_ATOMIC_NOT_FOUND)

#if PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_C11

#include <stdatomic.h>
typedef atomic_int_fast64_t psnip_atomic_int64;
typedef atomic_int_fast32_t psnip_atomic_int32;

#define PSNIP_ATOMIC_VAR_INIT(value) ATOMIC_VAR_INIT(value)

#define psnip_atomic_int64_load(object) \
  atomic_load(object)
#define psnip_atomic_int64_store(object, desired) \
  atomic_store(object, desired)
#define psnip_atomic_int64_compare_exchange(object, expected, desired) \
  atomic_compare_exchange_strong(object, expected, desired)
#define psnip_atomic_int64_add(object, operand) \
  atomic_fetch_add(object, operand)
#define psnip_atomic_int64_sub(object, operand) \
  atomic_fetch_sub(object, operand)
#define psnip_atomic_fence() \
  atomic_thread_fence(memory_order_seq_cst)

#define PSNIP_ATOMIC_IS_TG

#elif PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_CLANG

#include <stdint.h>
typedef _Atomic psnip_int64_t psnip_atomic_int64;
typedef _Atomic psnip_int32_t psnip_atomic_int32;

#define psnip_atomic_int64_load(object) \
  __c11_atomic_load(object, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_store(object, desired) \
  __c11_atomic_store(object, desired, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_compare_exchange(object, expected, desired) \
  __c11_atomic_compare_exchange_strong(object, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_add(object, operand) \
  __c11_atomic_fetch_add(object, operand, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_sub(object, operand) \
  __c11_atomic_fetch_sub(object, operand, __ATOMIC_SEQ_CST)
#define psnip_atomic_fence() \
  __c11_atomic_thread_fence(__ATOMIC_SEQ_CST)

#define PSNIP_ATOMIC_IS_TG

#elif PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_GCC

#include <stdint.h>
#if !defined(__INTEL_COMPILER) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)) && !defined(_OPENMP)
typedef _Atomic psnip_int64_t psnip_atomic_int64;
typedef _Atomic psnip_int32_t psnip_atomic_int32;
#else
typedef psnip_int64_t psnip_atomic_int64;
typedef psnip_int32_t psnip_atomic_int32;
#endif

#define psnip_atomic_int64_load(object) \
  __atomic_load_n(object, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_store(object, desired) \
  __atomic_store_n(object, desired, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_compare_exchange(object, expected, desired) \
  __atomic_compare_exchange_n(object, expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_add(object, operand) \
  __atomic_add_fetch(object, operand, __ATOMIC_SEQ_CST)
#define psnip_atomic_int64_sub(object, operand) \
  __atomic_sub_fetch(object, operand, __ATOMIC_SEQ_CST)
#define psnip_atomic_fence() \
  __atomic_thread_fence(__ATOMIC_SEQ_CST)

#define PSNIP_ATOMIC_IS_TG

#elif PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_GCC_SYNC

#include <stdint.h>
typedef psnip_int64_t psnip_atomic_int64;
typedef psnip_int32_t psnip_atomic_int32;

PSNIP_ATOMIC__FUNCTION
psnip_int64_t
psnip_atomic_int64_load(psnip_atomic_int64* object) {
  __sync_synchronize();
  return (psnip_int64_t) *object;
}

PSNIP_ATOMIC__FUNCTION
void
psnip_atomic_int64_store(psnip_atomic_int64* object, psnip_int64_t desired) {
  *object = desired;
  __sync_synchronize();
}

#define psnip_atomic_int64_compare_exchange(object, expected, desired)  \
  __sync_bool_compare_and_swap(object, *(expected), desired)
#define psnip_atomic_int64_add(object, operand) \
  __sync_fetch_and_add(object, operand)
#define psnip_atomic_int64_sub(object, operand) \
  __sync_fetch_and_sub(object, operand)

PSNIP_ATOMIC__FUNCTION
psnip_int32_t
psnip_atomic_int32_load(psnip_atomic_int32* object) {
  __sync_synchronize();
  return (psnip_int32_t) *object;
}

PSNIP_ATOMIC__FUNCTION
void
psnip_atomic_int32_store(psnip_atomic_int32* object, psnip_int32_t desired) {
  *object = desired;
  __sync_synchronize();
}

#define psnip_atomic_int32_compare_exchange(object, expected, desired)  \
  __sync_bool_compare_and_swap(object, *(expected), desired)
#define psnip_atomic_int32_add(object, operand) \
  __sync_fetch_and_add(object, operand)
#define psnip_atomic_int32_sub(object, operand) \
  __sync_fetch_and_sub(object, operand)

#define psnip_atomic_fence() \
  __sync_synchronize()

#elif PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_MS

#include <Windows.h>

typedef long long volatile psnip_atomic_int64;
typedef long volatile psnip_atomic_int32;

#define psnip_atomic_int32_load(object) \
  __pragma(warning(push)) \
  __pragma(warning(disable:28112)) \
  (*(object)) \
  __pragma(warning(pop))
#define psnip_atomic_int32_store(object, desired) \
  InterlockedExchange(object, desired)
#define psnip_atomic_int32_compare_exchange(object, expected, desired) \
  InterlockedCompareExchange(object, desired, *(expected))
#define psnip_atomic_int32_add(object, operand) \
  InterlockedExchangeAdd(object, operand)
#define psnip_atomic_int32_sub(object, operand) \
  InterlockedExchangeAdd(object, -(operand))

#define psnip_atomic_int64_load(object) \
  __pragma(warning(push)) \
  __pragma(warning(disable:28112)) \
  (*(object)) \
  __pragma(warning(pop))
#define psnip_atomic_int64_store(object, desired) \
  InterlockedExchange64(object, desired)
#define psnip_atomic_int64_compare_exchange(object, expected, desired)  \
  InterlockedCompareExchange64(object, desired, *(expected))
#define psnip_atomic_int64_add(object, operand) \
  InterlockedExchangeAdd64(object, operand)
#define psnip_atomic_int64_sub(object, operand) \
  InterlockedExchangeAdd64(object, -(operand))

#define psnip_atomic_fence() \
  MemoryBarrier()

#elif PSNIP_ATOMIC_IMPL == PSNIP_ATOMIC_IMPL_OPENMP

#include <stdint.h>
typedef psnip_int64_t psnip_atomic_int64;
typedef psnip_int32_t psnip_atomic_int32;

PSNIP_ATOMIC__FUNCTION
psnip_int64_t
psnip_atomic_int64_load(psnip_atomic_int64* object) {
  psnip_int64_t ret;
#pragma omp critical(psnip_atomic)
  ret = *object;
  return ret;
}

PSNIP_ATOMIC__FUNCTION
void
psnip_atomic_int64_store(psnip_atomic_int64* object, psnip_int64_t desired) {
#pragma omp critical(psnip_atomic)
  *object = desired;
}

PSNIP_ATOMIC__FUNCTION
int
psnip_atomic_int64_compare_exchange_(psnip_atomic_int64* object, psnip_int64_t* expected, psnip_int64_t desired) {
  int ret;
#pragma omp critical(psnip_atomic)
  ret = (*object == *expected) ? ((*object = desired), 1) : 0;
  return ret;
}

#define psnip_atomic_int64_compare_exchange(object, expected, desired) \
  psnip_atomic_int64_compare_exchange_(object, expected, desired)

PSNIP_ATOMIC__FUNCTION
psnip_int64_t
psnip_atomic_int64_add(psnip_atomic_int64* object, psnip_int64_t operand) {
  int ret;
#pragma omp critical(psnip_atomic)
  *object = (ret = *object) + operand;
  return ret;
}

PSNIP_ATOMIC__FUNCTION
psnip_int64_t
psnip_atomic_int64_sub(psnip_atomic_int64* object, psnip_int64_t operand) {
  int ret;
#pragma omp critical(psnip_atomic)
  *object = (ret = *object) - operand;
  return ret;
}
PSNIP_ATOMIC__FUNCTION
psnip_int32_t
psnip_atomic_int32_load(psnip_atomic_int32* object) {
  psnip_int32_t ret;
#pragma omp critical(psnip_atomic)
  ret = *object;
  return ret;
}

PSNIP_ATOMIC__FUNCTION
void
psnip_atomic_int32_store(psnip_atomic_int32* object, psnip_int32_t desired) {
#pragma omp critical(psnip_atomic)
  *object = desired;
}

PSNIP_ATOMIC__FUNCTION
int
psnip_atomic_int32_compare_exchange_(psnip_atomic_int32* object, psnip_int32_t* expected, psnip_int32_t desired) {
  int ret = 1;
#pragma omp critical(psnip_atomic)
  ret = (*object == *expected) ? ((*object = desired), 1) : 0;
  return ret;
}

#define psnip_atomic_int32_compare_exchange(object, expected, desired) \
  psnip_atomic_int32_compare_exchange_(object, expected, desired)

PSNIP_ATOMIC__FUNCTION
psnip_int32_t
psnip_atomic_int32_add(psnip_atomic_int32* object, psnip_int32_t operand) {
  int ret;
#pragma omp critical(psnip_atomic)
  *object = (ret = *object) + operand;
  return ret;
}

PSNIP_ATOMIC__FUNCTION
psnip_int32_t
psnip_atomic_int32_sub(psnip_atomic_int32* object, psnip_int32_t operand) {
  int ret;
#pragma omp critical(psnip_atomic)
  *object = (ret = *object) - operand;
  return ret;
}

PSNIP_ATOMIC__FUNCTION
void
psnip_atomic_fence() {
#pragma omp critical(psnip_atomic)
  { }
}


#endif

#if !defined(PSNIP_ATOMIC_VAR_INIT)
#  define PSNIP_ATOMIC_VAR_INIT(value) (value)
#endif

/* Most compilers have type-generic atomic implementations. */
#if defined(PSNIP_ATOMIC_IS_TG)
#define psnip_atomic_int32_load(object) \
  psnip_atomic_int64_load(object)
#define psnip_atomic_int32_store(object, desired)  \
  psnip_atomic_int64_store(object, desired)
#define psnip_atomic_int32_compare_exchange(object, expected, desired)  \
  psnip_atomic_int64_compare_exchange(object, expected, desired)
#define psnip_atomic_int32_add(object, operand) \
  psnip_atomic_int64_add(object, operand)
#define psnip_atomic_int32_sub(object, operand) \
  psnip_atomic_int64_sub(object, operand)
#endif /* defined(PSNIP_ATOMIC_IS_TG) */

#endif /* !defined(PSNIP_ATOMIC_NOT_FOUND) */

#endif /* defined(PSNIP_ATOMIC_H) */
