# Clock

**WARNING**: This header is nowhere near ready for widespread
adoption.  Testing, however, would be greatly appreciated (especially
on non-Linux platforms).

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
