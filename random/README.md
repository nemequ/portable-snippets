# Random Numbers

This provides methods for obtaining random, or pseudo-random, numbers.

There is generally only on function to worry about:

```c
int
psnip_random_bytes(enum PSnipRandomSource source,
                   size_t length,
		   psnip_uint8_t data[length]);
```

This will fill `data` with `length` bytes of randomness from `source`.
It returns 0 on success or, -1 if the source is not available (only
possible with the secure source), -2 if you supplied an invalid source
argument, or another negative number for other unexpected errors.

## Secure

`PSNIP_RANDOM_SOURCE_SECURE` tries to obtain cryptographically secure
random numbers.  This may or may not be available, depending on the
platform; if no source can be found `psnip_random_get_bytes` will
return -1 (you can pass 0 for the length if you just want to query for
support without actually generating anything).

This will try various methods.  Currently, this means:

 * [`RtlGenRandom()`](http://msdn.microsoft.com/en-us/library/windows/desktop/aa387694%28v=vs.85%29.aspx) on Windows
 * `getrandom()` on Solaris >= 11.3 (**TODO**), Linux >= 3.17
 * `arc4random()` on some BSDs (**TODO**)
 * [AES-NI](https://software.intel.com/en-us/articles/intel-advanced-encryption-standard-aes-instructions-set/) on CPUs which support it
 * Reading from `/dev/urandom` or `/dev/random` (if they exist)

If your platform isn't supported, please get in touch to discuss
adding a back-end.

## Reproducible

`PSNIP_RANDOM_SOURCE_REPRODUCIBLE` generates a *reproducible* stream
of pseudo-random numbers.  Currently we use a 32-bit variant of PCG;
this was chosen because it provides pretty good quality random
numbers, and the state is small enough that we can use atomic
operations instead of a mutex.

To deal with seeding, there are two additional functions:

```c
psnip_uint32_t psnip_random_get_seed (void);
void           psnip_random_set_seed (const psnip_uint32_t seed);
```

You can use the `psnip_random_set_seed` function to seed this
generator.  If you do not provide a seed we'll try to generate a
decent seed for you, but we make no promises about the quality.
Potential sources for the seed include libc's `rand()`, system time,
`lrand48()`, etc.

Even with a high quality seed, **this is not cryptographically secure**.

## Fast

`PSNIP_RANDOM_SOURCE_FAST` just tries to provide a random number
quickly.  It probably isn't cryptographically secure, but may be; for
example, if you have a hardware-based RNG which we believe would be
faster than the reproducible PRNG, we'll use it.

Note that, even if the fast source is implemented using the same
algorithm as the reproducible source (i.e., PGC with a 32-bit state),
the fast source will *not* alter the state of the reproducible PRNG.
