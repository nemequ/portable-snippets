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
 *     psnip_nonatomic_int64 expected;
 *     do {
 *       expected = psnip_atomic_int64_load(&value);
 *     } while (!psnip_atomic_int64_compare_exchange(&value, &expected, expected * expected));
 *   }
 *
 * Most things are implemented with the preprocessor, but if they were
 * functions the prototypes (the 64-bit versions, just s/64/32/ for
 * the 32-bit versions) would loo like:
 *
 *   psnip_nonatomic_int64 psnip_atomic_int64_load(
 *       psnip_atomic_int64* object);
 *   void psnip_atomic_int64_store(
 *       psnip_atomic_int64* object,
 *       psnip_nonatomic_int64 desired);
 *   _Bool psnip_atomic_int64_compare_exchange(
 *       psnip_atomic_int64* object,
 *       psnip_nonatomic_int64* expected,
 *       psnip_nonatomic_int64 desired);
 *   psnip_nonatomic_int64 psnip_atomic_int64_add(
 *       psnip_atomic_int64* object,
 *       psnip_nonatomic_int64 operand);
 *   psnip_nonatomic_int64 psnip_atomic_int64_sub(
 *       psnip_atomic_int64* object,
 *       psnip_nonatomic_int64 operand);
 */

#if !defined(PSNIP_ATOMIC_H)
#define PSNIP_ATOMIC_H

#if !defined(__has_feature)
#  define __has_feature(feature) 0
#endif

#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 9))
/* For GCC >= 4.9 we can use C11 atomics even when we're not in C11 mode. */
#  define PSNIP_USE_C11_ATOMICS
#elif !defined(__INTEL_COMPILER) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_ATOMICS__)
/* GCC 4.7 and 4.8 sets __STDC_VERSION__ to C11 (if compiling in C11
 * mode) and didn't have stdatomic.h, but failed to set
 * __STDC_NO_ATOMICS__.  Verions prior to 4.7 didn't set
 * __STDC_VERSION__ to C11. */
#  if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 9)
#    define PSNIP_USE_GCC_ATOMICS
#  else
#    define PSNIP_USE_C11_ATOMICS
#  endif
#elif defined(_MSC_VER)
#  define PSNIP_USE_MS_ATOMICS
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#  define PSNIP_USE_GCC_ATOMICS
#elif defined(__clang__) && __has_feature(c_atomic)
#  define PSNIP_USE_CLANG_ATOMICS
#elif defined(__GNUC__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
#  define PSNIP_USE_GCC_SYNC_ATOMICS
#else
#  error No atomic implementation found
#endif

#if defined(_MSC_VER)
#include <windows.h>
typedef LONGLONG psnip_nonatomic_int64;
typedef LONG psnip_nonatomic_int32;
#else
#include <stdint.h>
typedef int_fast64_t psnip_nonatomic_int64;
typedef int_fast32_t psnip_nonatomic_int32;
#endif

#if defined(PSNIP_USE_C11_ATOMICS)

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

#elif defined(PSNIP_USE_CLANG_ATOMICS)

#include <stdint.h>
typedef _Atomic psnip_nonatomic_int64 psnip_atomic_int64;
typedef _Atomic psnip_nonatomic_int32 psnip_atomic_int32;

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

#elif defined(PSNIP_USE_GCC_ATOMICS)

#include <stdint.h>
#if !defined(__INTEL_COMPILER) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
typedef _Atomic int_fast64_t psnip_atomic_int64;
typedef _Atomic int_fast32_t psnip_atomic_int32;
#else
typedef int_fast64_t psnip_atomic_int64;
typedef int_fast32_t psnip_atomic_int32;
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

#elif defined(PSNIP_USE_GCC_SYNC_ATOMICS)

#include <stdint.h>
typedef int_fast64_t psnip_atomic_int64;
typedef int_fast32_t psnip_atomic_int32;

static inline
psnip_nonatomic_int64
psnip_atomic_int64_load(psnip_atomic_int64* object) {
  __sync_synchronize();
  return (psnip_nonatomic_int64) *object;
}

static inline
void
psnip_atomic_int64_store(psnip_atomic_int64* object, psnip_nonatomic_int64 desired) {
  *object = desired;
  __sync_synchronize();
}

static inline
psnip_nonatomic_int32
psnip_atomic_int32_load_(psnip_atomic_int32* object) {
  __sync_synchronize();
  return (psnip_nonatomic_int32) *object;
}

static inline
void
psnip_atomic_int32_store_(psnip_atomic_int32* object, psnip_nonatomic_int32 desired) {
  *object = desired;
  __sync_synchronize();
}

#define psnip_atomic_int64_compare_exchange(object, expected, desired)  \
  __sync_bool_compare_and_swap(object, *(expected), desired)
#define psnip_atomic_int64_add(object, operand) \
  __sync_fetch_and_add(object, operand)
#define psnip_atomic_int64_sub(object, operand) \
  __sync_fetch_and_sub(object, operand)

#define psnip_atomic_int32_load(object) \
  psnip_atomic_int32_load_(object)
#define psnip_atomic_int32_store(object, desired) \
  psnip_atomic_int32_store_(object, desired)

#define psnip_atomic_fence() \
  __sync_synchronize()

#elif defined(PSNIP_USE_MS_ATOMICS)

typedef LONGLONG volatile psnip_atomic_int64;
typedef LONG volatile psnip_atomic_int32;

static __inline
psnip_nonatomic_int64
psnip_atomic_int64_load(psnip_atomic_int64* object) {
  MemoryBarrier();
  return (psnip_nonatomic_int64) *object;
}

static __inline
void
psnip_atomic_int64_store(psnip_atomic_int64* object, psnip_nonatomic_int64 desired) {
  *object = desired;
  MemoryBarrier();
}

static __inline
psnip_nonatomic_int32
psnip_atomic_int32_load_(psnip_atomic_int32* object) {
  MemoryBarrier();
  return (psnip_nonatomic_int32) *object;
}

static __inline
void
psnip_atomic_int32_store_(psnip_atomic_int32* object, psnip_nonatomic_int32 desired) {
  *object = desired;
  MemoryBarrier();
}

#define psnip_atomic_int32_compare_exchange(object, expected, desired)  \
  InterlockedCompareExchange(object, desired, *(expected))
#define psnip_atomic_int32_add(object, operand) \
  InterlockedExchangeAdd(object, operand)
#define psnip_atomic_int32_sub(object, operand) \
  InterlockedExchangeAdd(object, -(operand))

#define psnip_atomic_int64_compare_exchange(object, expected, desired)  \
  InterlockedCompareExchange64(object, desired, *(expected))
#define psnip_atomic_int64_add(object, operand) \
  InterlockedExchangeAdd64(object, operand)
#define psnip_atomic_int64_sub(object, operand) \
  InterlockedExchangeAdd64(object, -(operand))

#define psnip_atomic_int32_load(object) \
  psnip_atomic_int32_load_(object)
#define psnip_atomic_int32_store(object, desired) \
  psnip_atomic_int32_store_(object, desired)

#define psnip_atomic_fence() \
  MemoryBarrier()

#endif

#if !defined(PSNIP_ATOMIC_VAR_INIT)
#  define PSNIP_ATOMIC_VAR_INIT(value) (value)
#endif

/* Most compilers have type-generic atomic implementations. */
#if !defined(psnip_atomic_int32_load)
#define psnip_atomic_int32_load(object) \
  psnip_atomic_int64_load(object)
#endif
#if !defined(psnip_atomic_int32_store)
#define psnip_atomic_int32_store(object, desired)  \
  psnip_atomic_int64_store(object, desired)
#endif
#if !defined(psnip_atomic_int32_compare_exchange)
#define psnip_atomic_int32_compare_exchange(object, expected, desired)  \
  psnip_atomic_int64_compare_exchange(object, expected, desired)
#endif
#if !defined(psnip_atomic_int32_add)
#define psnip_atomic_int32_add(object, operand) \
  psnip_atomic_int64_add(object, operand)
#endif
#if !defined(psnip_atomic_int32_sub)
#define psnip_atomic_int32_sub(object, operand) \
  psnip_atomic_int64_sub(object, operand)
#endif

#endif /* defined(PSNIP_ATOMIC_H) */
