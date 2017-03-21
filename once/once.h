/* Once (v1)
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 */

#if !defined(PSNIP_ONCE__H)
#define PSNIP_ONCE__H

#define PSNIP_ONCE__BACKEND_ATOMIC  1
#define PSNIP_ONCE__BACKEND_PTHREAD 2
#define PSNIP_ONCE__BACKEND_C11     11
#define PSNIP_ONCE__BACKEND_WIN32   32

#if !defined(PSNIP_ONCE_BACKEND) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201102L) && !defined(__STDC_NO_THREADS__)
#  include <limits.h>
#  if defined(__STDC_NO_THREADS__) || (defined(__GNUC__) && (__GLIBC__ < 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ < 16)))
/* stdc-predef.h didn't include __STDC_NO_THREADS__ until 2.16.  icc
   doesn't include stdc-predef.h until we pull in limits.h, so the
   first check doesn't work. */
#  else
#    include <threads.h>
#    define PSNIP_ONCE_BACKEND PSNIP_ONCE_BACKEND_C11
#  endif
#endif

#if !defined(PSNIP_ONCE_BACKEND) && defined(_WIN32) && (!defined(WINVER) || (defined(WINVER) && (WINVER >= 0x0600)))
#  include <Windows.h>
#  define PSNIP_ONCE_BACKEND PSNIP_ONCE__BACKEND_WIN32
#endif

#if !defined(PSNIP_ONCE_BACKEND) && defined(PTHREAD_ONCE_INIT)
#  define PSNIP_ONCE_BACKEND PSNIP_ONCE__BACKEND_PTHREAD
#endif

#if !defined(PSNIP_ONCE_BACKEND)
#  include "../atomic/atomic.h"
#  if !defined(PSNIP_ATOMIC_NOT_FOUND)
#    define PSNIP_ONCE_BACKEND PSNIP_ONCE__BACKEND_ATOMIC
#  endif
#endif

#if !defined(PSNIP_ONCE_BACKEND)
#  error No once backend found.
#endif

#if defined(__GNUC__) && (__GNUC__ >= 3)
#  define PSNIP_ONCE__UNLIKELY(expr) __builtin_expect(!!(expr), !!0)
#else
#  define PSNIP_ONCE__UNLIKELY(expr) (!!(expr))
#endif

#if PSNIP_ONCE_BACKEND == PSNIP_ONCE__BACKEND_C11
#  define PSNIP_ONCE_INIT ONCE_FLAG_INIT
typedef once_flag psnip_once;
#  define psnip_once_call(flag, func) call_once(flag, func)
#elif PSNIP_ONCE_BACKEND == PSNIP_ONCE__BACKEND_PTHREAD
#  define PSNIP_ONCE_INIT PTHREAD_ONCE_INIT
typedef pthread_once_t psnip_once;
#  define psnip_once_call(flag, func) pthread_once(flag, func)
#elif PSNIP_ONCE_BACKEND == PSNIP_ONCE__BACKEND_WIN32
#  define PSNIP_ONCE_INIT INIT_ONCE_STATIC_INIT
typedef INIT_ONCE psnip_once;
static BOOL CALLBACK psnip_once__callback_wrap(INIT_ONCE* InitOnce, void* Parameter, void** Context) {
  (void) Context;
  (void) InitOnce;
#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable:4055)
#endif
  ((void (*)(void)) Parameter)();
#if defined(_MSC_VER)
#  pragma warning(pop)
#endif
  return !0;
}
#  if defined(_MSC_VER) && (_MSC_VER >= 1500)
#    define psnip_once_call(flag, func) \
  __pragma(warning(push)) \
  __pragma(warning(disable:4152)) \
  InitOnceExecuteOnce(flag, &psnip_once__callback_wrap, func, NULL) \
  __pragma(warning(pop))
#  else
#    define psnip_once_call(flag, func) InitOnceExecuteOnce(flag, &psnip_once__callback_wrap, func, NULL)
#  endif
#elif PSNIP_ONCE_BACKEND == PSNIP_ONCE__BACKEND_ATOMIC
#  define PSNIP_ONCE_INIT PSNIP_ATOMIC_VAR_INIT(0)
typedef psnip_atomic_int32 psnip_once;
static void psnip_once_call(psnip_once* flag, void (*func)(void)) {
  psnip_int32_t state = psnip_atomic_int32_load(flag);
  if (PSNIP_ONCE__UNLIKELY(state == 0)) {
    if (psnip_atomic_int32_compare_exchange(flag, &state, 1)) {
      func();
      psnip_atomic_int32_store(flag, 2);
    } else {
      do {
	/* Spin; another thread is calling the initialization
	   function. */
      } while (psnip_atomic_int32_load(flag) == 1);
    }
  }
}
#endif

#endif /* !defined(PSNIP_ONCE__H) */
