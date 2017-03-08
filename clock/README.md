# Clock

This header provides a way to access time information.  It's basically
a more portable version of `clock_gettime` with fewer supported
clocks.  Currently supported clocks are:

 * Wall clock
   * `clock_gettime`
   * `gettimeofday`
   * `time`
 * CPU clock
   * `clock_gettime`
   * `GetProcessTimes`
   * `getrusage`
 * Monotonic clock
   * `clock_gettime`
   * `mach_absolute_time`
   * `QueryPerformanceCounter`

If you are using a platform where a clock isn't provided, please let
us know about it so we can try to figure out how to add support!

Note that, on some platforms, `clock_gettime` requires linking to
librt.  If you prefer, you can define `PSNIP_CLOCK_NO_LIBRT` prior to
including `clock.h` and `clock_gettime` will only be used on platforms
known to support using `clock_gettime` *without* linking against
librt.  The price will likely be lower-resolution CPU and wall clocks,
and no monotonic clock.
