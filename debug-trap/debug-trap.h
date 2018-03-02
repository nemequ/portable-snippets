/* Debugging assertions and traps
 * Portable Snippets - https://gitub.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 *
 * This is an attempt to provide a fairly portable way to generate
 * traps in code. __builtin_trap is _Noreturn, so the compiler may
 * optimize away code found after it, which means you can't really
 * drop into a debugger and step through the code after the trap has
 * been hit.
 *
 * If PSNIP_NDEBUG is defined, or NDEBUG is defined and PSNIP_DEBUG is
 * not, psnip_dbg_assert(expr) will be preprocessed to nothing (i.e.,
 * expr will not be evaluated). Otherwise it will call psnip_trap if
 * expr evaluates to false.
 *
 * Knowledge about how to do this portably basically comes from
 * <https://github.com/scottt/debugbreak/> and GLib's G_BREAKPOINT
 * macro, plus some compiler documentation.
 *
 * On non-hosted platforms we *may* have to fall back on
 * __builtin_trap. On non-hosted non-GNU-compatible compilers on
 * relatively exotic architectures you may end up with an error about
 * stdlib.h being missing... if you have a good way to resolve that on
 * your platform please contact us.
 */

#if !defined(PSNIP_DEBUG_TRAP_H)
#define PSNIP_DEBUG_TRAP_H

#if !defined(PSNIP_NDEBUG) && defined(NDEBUG) && !defined(PSNIP_DEBUG)
#  define PSNIP_NDEBUG 1
#endif

#if defined(HEDLEY_ALWAYS_INLINE)
#  define PSNIP_DBG__ALWAYS_INLINE HEDLEY_ALWAYS_INLINE
#elif defined(__GNUC__) && (__GNUC__ >= 4)
#  define PSNIP_DBG__ALWAYS_INLINE __attribute__((__always_inline__))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define  PSNIP_DBG__ALWAYS_INLINE __forceinline
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define PSNIP_DBG__ALWAYS_INLINE inline
#else
#  define PSNIP_DBG__ALWAYS_INLINE
#endif

#define PSNIP_DBG__FUNCTION static PSNIP_DBG__ALWAYS_INLINE

#if defined(__has_builtin)
#  if __has_builtin(__builtin_debugbreak)
#    define psnip_trap() __builtin_debugbreak()
#  elif __has_builtin(__debugbreak)
#    define psnip_trap() __debugbreak()
#  endif
#endif
#if !defined(psnip_trap)
#  if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#    define psnip_trap() __debugbreak()
#  elif defined(__ARMCC_VERSION)
#    define psnip_trap() __breakpoint(42)
#  elif defined(__DMC__) && defined(_M_IX86)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm int 3h; }
#  elif defined(__i386__) || defined(__x86_64__)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm__ __volatile__("int $03"); }
#  elif defined(__thumb__)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm__ __volatile__(".inst 0xde01"); }
#  elif defined(__aarch64__)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#  elif defined(__arm__)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }
#  elif defined (__alpha__) && !defined(__osf__)
     PSNIP_DBG__FUNCTION void psnip_trap(void) { __asm__ __volatile__("bpt"); }
#  elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#    define psnip_trap() __builtin_trap()
#  else
#    include <signal.h>
#    if defined(SIGTRAP)
#      define psnip_trap() raise(SIGTRAP)
#    else
#      define psnip_trap() raise(SIGABRT)
#    endif
#  endif
#endif

#if defined(HEDLEY_LIKELY)
#  define PSNIP_DBG_LIKELY(expr) HEDLEY_LIKELY(expr)
#elif defined(__GNUC__) && (__GNUC__ >= 3)
#  define PSNIP_DBG_LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#  define PSNIP_DBG_LIKELY(expr) (!!(expr))
#endif

#if !defined(PSNIP_NDEBUG) || (PSNIP_NDEBUG == 0)
#  define psnip_dbg_assert(expr) do { \
    if (!PSNIP_DBG_LIKELY(expr)) { \
      psnip_trap(); \
    } \
  } while (0)
#else
#  define psnip_dbg_assert(expr)
#endif

#endif /* !defined(PSNIP_DEBUG_TRAP_H) */
