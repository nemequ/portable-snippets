/* Clocks (v1)
 * Portable Snippets - https://github.com/nemequ/portable-snippets
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 *   To the extent possible under law, the authors have waived all
 *   copyright and related or neighboring rights to this code.  For
 *   details, see the Creative Commons Zero 1.0 Universal license at
 *   https://creativecommons.org/publicdomain/zero/1.0/
 */

#if !defined(PSNIP_CLOCK_H)
#define PSNIP_CLOCK_H

/* For maximum portability include the exact-int module from
   portable snippets. */
#if !defined(psnip_uint64_t) || !defined(psnip_int32_t) || \
  !defined(psnip_uint32_t) || !defined(psnip_int32_t)
#  include <stdint.h>
#  if !defined(psnip_int64_t)
#    define psnip_int64_t int64_t
#  endif
#  if !defined(psnip_uint64_t)
#    define psnip_uint64_t uint64_t
#  endif
#  if !defined(psnip_int32_t)
#    define psnip_int32_t int32_t
#  endif
#  if !defined(psnip_uint32_t)
#    define psnip_uint32_t uint32_t
#  endif
#endif

#if !defined(PSNIP_CLOCK_STATIC_INLINE)
#  if defined(__GNUC__)
#    define PSNIP_CLOCK__COMPILER_ATTRIBUTES __attribute__((__unused__))
#  else
#    define PSNIP_CLOCK__COMPILER_ATTRIBUTES
#  endif

#  define PSNIP_CLOCK__FUNCTION PSNIP_CLOCK__COMPILER_ATTRIBUTES static
#endif

enum PsnipClockType {
  /* This clock provides the current time, in units since 1970-01-01
   * 00:00:00 UTC not including leap seconds.  In other words, UNIX
   * time.  Keep in mind that this clock doesn't account for leap
   * seconds, and can go backwards (think NTP adjustments). */
  PSNIP_CLOCK_TYPE_WALL = 1,
  /* The CPU time is a clock which increases only when the current
   * process is active (i.e., it doesn't increment while blocking on
   * I/O). */
  PSNIP_CLOCK_TYPE_CPU = 2,
  /* Monotonic time is always running (unlike CPU time), but it only
     ever moves forward unless you reboot the system.  Things like NTP
     adjustments have no effect on this clock. */
  PSNIP_CLOCK_TYPE_MONOTONIC = 3
};

struct PsnipClockTimespec {
  psnip_uint64_t seconds;
  psnip_uint64_t nanoseconds;
};

/* Methods we support: */

#define PSNIP_CLOCK_METHOD_CLOCK_GETTIME                   1
#define PSNIP_CLOCK_METHOD_TIME                            2
#define PSNIP_CLOCK_METHOD_GETTIMEOFDAY                    3
#define PSNIP_CLOCK_METHOD_QUERYPERFORMANCECOUNTER         4
#define PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME              5
#define PSNIP_CLOCK_METHOD_CLOCK                           6
#define PSNIP_CLOCK_METHOD_GETPROCESSTIMES                 7
#define PSNIP_CLOCK_METHOD_GETRUSAGE                       8
#define PSNIP_CLOCK_METHOD_GETSYSTEMTIMEPRECISEASFILETIME  9
#define PSNIP_CLOCK_METHOD_GETTICKCOUNT64                 10

#include <assert.h>

#if defined(HEDLEY_UNREACHABLE)
#  define PSNIP_CLOCK_UNREACHABLE() HEDLEY_UNREACHABLE()
#else
#  define PSNIP_CLOCK_UNREACHABLE() assert(0)
#endif

/* Choose an implementation */

/* #undef PSNIP_CLOCK_WALL_METHOD */
/* #undef PSNIP_CLOCK_CPU_METHOD */
/* #undef PSNIP_CLOCK_MONOTONIC_METHOD */

/* We want to be able to detect the libc implementation, so we include
   <limits.h> (<features.h> isn't available everywhere). */
#if defined(__unix__) || defined(__unix) || defined(__linux__)
#  include <limits.h>
#  include <unistd.h>
#endif

#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
/* glibc 2.17+ and FreeBSD are known to work without librt.  If you
 * know of others please let us know so we can add them. */
#  if \
  (defined(__GLIBC__) && (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 17))) || \
  (defined(__FreeBSD__)) || \
  !defined(PSNIP_CLOCK_NO_LIBRT)
/* Even though glibc unconditionally sets _POSIX_TIMERS, it doesn't
   actually declare the relevant APIs unless _POSIX_C_SOURCE >=
   199309L, and if you compile in standard C mode (e.g., c11 instead
   of gnu11) _POSIX_C_SOURCE will be unset by default. */
#    if _POSIX_C_SOURCE >= 199309L
#      define PSNIP_CLOCK_HAVE_CLOCK_GETTIME
#    endif
#  endif
#endif

#if defined(_WIN32)
#  if !defined(PSNIP_CLOCK_CPU_METHOD)
#    define PSNIP_CLOCK_CPU_METHOD PSNIP_CLOCK_METHOD_GETPROCESSTIMES
#  endif
#  if !defined(PSNIP_CLOCK_MONOTONIC_METHOD)
#    define PSNIP_CLOCK_MONOTONIC_METHOD PSNIP_CLOCK_METHOD_QUERYPERFORMANCECOUNTER
#  endif
#endif

#if defined(__MACH__) && !defined(__gnu_hurd__)
#  if !defined(PSNIP_CLOCK_MONOTONIC_METHOD)
#    define PSNIP_CLOCK_MONOTONIC_METHOD PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME
#  endif
#endif

#if defined(PSNIP_CLOCK_HAVE_CLOCK_GETTIME)
#  include <time.h>
#  if !defined(PSNIP_CLOCK_WALL_METHOD)
#    if defined(CLOCK_REALTIME_PRECISE)
#      define PSNIP_CLOCK_WALL_METHOD PSNIP_CLOCK_METHOD_CLOCK_GETTIME
#      define PSNIP_CLOCK_CLOCK_GETTIME_WALL CLOCK_REALTIME_PRECISE
#    elif !defined(__sun)
#      define PSNIP_CLOCK_WALL_METHOD PSNIP_CLOCK_METHOD_CLOCK_GETTIME
#      define PSNIP_CLOCK_CLOCK_GETTIME_WALL CLOCK_REALTIME
#    endif
#  endif
#  if !defined(PSNIP_CLOCK_CPU_METHOD)
#    if defined(_POSIX_CPUTIME) || defined(CLOCK_PROCESS_CPUTIME_ID)
#      define PSNIP_CLOCK_CPU_METHOD PSNIP_CLOCK_METHOD_CLOCK_GETTIME
#      define PSNIP_CLOCK_CLOCK_GETTIME_CPU CLOCK_PROCESS_CPUTIME_ID
#    elif defined(CLOCK_VIRTUAL)
#      define PSNIP_CLOCK_CPU_METHOD PSNIP_CLOCK_METHOD_CLOCK_GETTIME
#      define PSNIP_CLOCK_CLOCK_GETTIME_CPU CLOCK_VIRTUAL
#    endif
#  endif
#  if !defined(PSNIP_CLOCK_MONOTONIC_METHOD)
#    if defined(_POSIX_MONOTONIC_CLOCK) || defined(CLOCK_MONOTONIC)
#      define PSNIP_CLOCK_MONOTONIC_METHOD PSNIP_CLOCK_METHOD_CLOCK_GETTIME
#      define PSNIP_CLOCK_CLOCK_GETTIME_MONOTONIC CLOCK_MONOTONIC
#    endif
#  endif
#endif

#if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)
#  if !defined(PSNIP_CLOCK_WALL_METHOD)
#    define PSNIP_CLOCK_WALL_METHOD PSNIP_CLOCK_METHOD_GETTIMEOFDAY
#  endif
#endif

#if !defined(PSNIP_CLOCK_WALL_METHOD)
#  define PSNIP_CLOCK_WALL_METHOD PSNIP_CLOCK_METHOD_TIME
#endif

#if !defined(PSNIP_CLOCK_CPU_METHOD)
#  define PSNIP_CLOCK_CPU_METHOD PSNIP_CLOCK_METHOD_CLOCK
#endif

/* Primarily here for testing. */
#if !defined(PSNIP_CLOCK_MONOTONIC_METHOD) && defined(PSNIP_CLOCK_REQUIRE_MONOTONIC)
#  error No monotonic clock found.
#endif

/* Implementations */

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_CLOCK_GETTIME)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_CLOCK_GETTIME)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME)) || \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_CLOCK)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_CLOCK)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_CLOCK)) || \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_TIME)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_TIME)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_TIME))
#  include <time.h>
#endif

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_GETTIMEOFDAY)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_GETTIMEOFDAY)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETTIMEOFDAY))
#  include <sys/time.h>
#endif

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_GETPROCESSTIMES)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_GETPROCESSTIMES)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETPROCESSTIMES)) || \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_GETTICKCOUNT64)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_GETTICKCOUNT64)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETTICKCOUNT64))
#  include <windows.h>
#endif

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_GETRUSAGE)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_GETRUSAGE)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETRUSAGE))
#  include <sys/time.h>
#  include <sys/resource.h>
#endif

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME))
#  include <CoreServices/CoreServices.h>
#  include <mach/mach.h>
#  include <mach/mach_time.h>
#endif

/*** Implementations ***/

#define PSNIP_CLOCK_NSEC_PER_SEC ((psnip_uint32_t) (1000000000ULL))

#if \
  (defined(PSNIP_CLOCK_CPU_METHOD)       && (PSNIP_CLOCK_CPU_METHOD       == PSNIP_CLOCK_METHOD_CLOCK_GETTIME)) || \
  (defined(PSNIP_CLOCK_WALL_METHOD)      && (PSNIP_CLOCK_WALL_METHOD      == PSNIP_CLOCK_METHOD_CLOCK_GETTIME)) || \
  (defined(PSNIP_CLOCK_MONOTONIC_METHOD) && (PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME))
PSNIP_CLOCK__FUNCTION psnip_uint32_t
psnip_clock__clock_getres (clockid_t clk_id) {
  struct timespec res;
  int r;

  r = clock_getres(clk_id, &res);
  if (r != 0)
    return 0;

  return (psnip_uint32_t) (PSNIP_CLOCK_NSEC_PER_SEC / res.tv_nsec);
}

PSNIP_CLOCK__FUNCTION int
psnip_clock__clock_gettime (clockid_t clk_id, struct PsnipClockTimespec* res) {
  struct timespec ts;

  if (clock_gettime(clk_id, &ts) != 0)
    return -10;

  res->seconds = (psnip_uint64_t) (ts.tv_sec);
  res->nanoseconds = (psnip_uint64_t) (ts.tv_nsec);

  return 0;
}
#endif

PSNIP_CLOCK__FUNCTION psnip_uint32_t
psnip_clock_wall_get_precision (void) {
#if !defined(PSNIP_CLOCK_WALL_METHOD)
  return 0;
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_getres(PSNIP_CLOCK_CLOCK_GETTIME_WALL);
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_GETTIMEOFDAY
  return 1000000;
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_TIME
  return 1;
#else
  return 0;
#endif
}

PSNIP_CLOCK__FUNCTION int
psnip_clock_wall_get_time (struct PsnipClockTimespec* res) {
  (void) res;

#if !defined(PSNIP_CLOCK_WALL_METHOD)
  return -2;
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_gettime(PSNIP_CLOCK_CLOCK_GETTIME_WALL, res);
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_TIME
  res->seconds = time(NULL);
  res->nanoseconds = 0;
#elif defined(PSNIP_CLOCK_WALL_METHOD) && PSNIP_CLOCK_WALL_METHOD == PSNIP_CLOCK_METHOD_GETTIMEOFDAY
  struct timeval tv;

  if (gettimeofday(&tv, NULL) != 0)
    return -6;

  res->seconds = tv.tv_sec;
  res->nanoseconds = tv.tv_usec * 1000;
#else
  return -2;
#endif

  return 0;
}

PSNIP_CLOCK__FUNCTION psnip_uint32_t
psnip_clock_cpu_get_precision (void) {
#if !defined(PSNIP_CLOCK_CPU_METHOD)
  return 0;
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_getres(PSNIP_CLOCK_CLOCK_GETTIME_CPU);
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_CLOCK
  return CLOCKS_PER_SEC;
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_GETPROCESSTIMES
  return PSNIP_CLOCK_NSEC_PER_SEC / 100;
#else
  return 0;
#endif
}

PSNIP_CLOCK__FUNCTION int
psnip_clock_cpu_get_time (struct PsnipClockTimespec* res) {
#if !defined(PSNIP_CLOCK_CPU_METHOD)
  (void) res;
  return -2;
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_gettime(PSNIP_CLOCK_CLOCK_GETTIME_CPU, res);
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_CLOCK
  clock_t t = clock();
  if (t == ((clock_t) -1))
    return -5;
  res->seconds = t / CLOCKS_PER_SEC;
  res->nanoseconds = (t % CLOCKS_PER_SEC) * (PSNIP_CLOCK_NSEC_PER_SEC / CLOCKS_PER_SEC);
#elif defined(PSNIP_CLOCK_CPU_METHOD) && PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_GETPROCESSTIMES
  FILETIME CreationTime, ExitTime, KernelTime, UserTime;
  LARGE_INTEGER date, adjust;

  if (!GetProcessTimes(GetCurrentProcess(), &CreationTime, &ExitTime, &KernelTime, &UserTime))
    return -7;

  /* http://www.frenk.com/2009/12/convert-filetime-to-unix-timestamp/ */
  date.HighPart = UserTime.dwHighDateTime;
  date.LowPart = UserTime.dwLowDateTime;
  adjust.QuadPart = 11644473600000 * 10000;
  date.QuadPart -= adjust.QuadPart;

  res->seconds = date.QuadPart / 10000000;
  res->nanoseconds = (date.QuadPart % 10000000) * (PSNIP_CLOCK_NSEC_PER_SEC / 100);
#elif PSNIP_CLOCK_CPU_METHOD == PSNIP_CLOCK_METHOD_GETRUSAGE
  struct rusage usage;
  if (getrusage(RUSAGE_SELF, &usage) != 0)
    return -8;

  res->seconds = usage.ru_utime.tv_sec;
  res->nanoseconds = tv.tv_usec * 1000;
#else
  (void) res;
  return -2;
#endif

  return 0;
}

PSNIP_CLOCK__FUNCTION psnip_uint32_t
psnip_clock_monotonic_get_precision (void) {
#if !defined(PSNIP_CLOCK_MONOTONIC_METHOD)
  return 0;
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_getres(PSNIP_CLOCK_CLOCK_GETTIME_MONOTONIC);
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME
  static mach_timebase_info_data_t tbi = { 0, };
  if (tbi.denom == 0)
    mach_timebase_info(&tbi);
  return (psnip_uint32_t) (tbi.numer / tbi.denom);
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETTICKCOUNT64
  return 1000;
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_QUERYPERFORMANCECOUNTER
  LARGE_INTEGER Frequency;
  QueryPerformanceFrequency(&Frequency);
  return (psnip_uint32_t) ((Frequency.QuadPart > PSNIP_CLOCK_NSEC_PER_SEC) ? PSNIP_CLOCK_NSEC_PER_SEC : Frequency.QuadPart);
#else
  return 0;
#endif
}

PSNIP_CLOCK__FUNCTION int
psnip_clock_monotonic_get_time (struct PsnipClockTimespec* res) {
#if !defined(PSNIP_CLOCK_MONOTONIC_METHOD)
  (void) res;
  return -2;
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_CLOCK_GETTIME
  return psnip_clock__clock_gettime(PSNIP_CLOCK_CLOCK_GETTIME_MONOTONIC, res);
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_MACH_ABSOLUTE_TIME
  psnip_uint64_t nsec = mach_absolute_time();
  static mach_timebase_info_data_t tbi = { 0, };
  if (tbi.denom == 0)
    mach_timebase_info(&tbi);
  nsec *= ((psnip_uint64_t) tbi.numer) / ((psnip_uint64_t) tbi.denom);
  res->seconds = nsec / PSNIP_CLOCK_NSEC_PER_SEC;
  res->nanoseconds = nsec % PSNIP_CLOCK_NSEC_PER_SEC;
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_QUERYPERFORMANCECOUNTER
  LARGE_INTEGER t, f;
  if (QueryPerformanceCounter(&t) == 0)
    return -12;

  QueryPerformanceFrequency(&f);
  res->seconds = t.QuadPart / f.QuadPart;
  res->nanoseconds = t.QuadPart % f.QuadPart;
  if (f.QuadPart > PSNIP_CLOCK_NSEC_PER_SEC)
    res->nanoseconds /= f.QuadPart / PSNIP_CLOCK_NSEC_PER_SEC;
  else
    res->nanoseconds *= PSNIP_CLOCK_NSEC_PER_SEC / f.QuadPart;
#elif defined(PSNIP_CLOCK_MONOTONIC_METHOD) && PSNIP_CLOCK_MONOTONIC_METHOD == PSNIP_CLOCK_METHOD_GETTICKCOUNT64
  const ULONGLONG msec = GetTickCount64();
  res->seconds = msec / 1000;
  res->nanoseconds = sec % 1000;
#else
  return -2;
#endif

  return 0;
}

/* Returns the number of ticks per second for the specified clock.
 * For example, a clock with millisecond precision would return 1000,
 * and a clock with 1 second (such as the time() function) would
 * return 1.
 *
 * If the requested clock isn't available, it will return 0.
 * Hopefully this will be rare, but if it happens to you please let us
 * know so we can work on finding a way to support your system.
 *
 * Note that different clocks on the same system often have a
 * different precisions.
 */
PSNIP_CLOCK__FUNCTION psnip_uint32_t
psnip_clock_get_precision (enum PsnipClockType clock_type) {
  switch (clock_type) {
    case PSNIP_CLOCK_TYPE_MONOTONIC:
      return psnip_clock_monotonic_get_precision ();
    case PSNIP_CLOCK_TYPE_CPU:
      return psnip_clock_cpu_get_precision ();
    case PSNIP_CLOCK_TYPE_WALL:
      return psnip_clock_wall_get_precision ();
  }

  PSNIP_CLOCK_UNREACHABLE();
  return 0;
}

/* Set the provided timespec to the requested time.  Returns 0 on
 * success, or a negative value on failure. */
PSNIP_CLOCK__FUNCTION int
psnip_clock_get_time (enum PsnipClockType clock_type, struct PsnipClockTimespec* res) {
  assert(res != NULL);

  switch (clock_type) {
    case PSNIP_CLOCK_TYPE_MONOTONIC:
      return psnip_clock_monotonic_get_time (res);
    case PSNIP_CLOCK_TYPE_CPU:
      return psnip_clock_cpu_get_time (res);
    case PSNIP_CLOCK_TYPE_WALL:
      return psnip_clock_wall_get_time (res);
  }

  return -1;
}

#endif /* !defined(PSNIP_CLOCK_H) */
