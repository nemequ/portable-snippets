# Built-Ins

These snippets are intended to provide portable versions of many of
GCC's built-ins and MSVC's intrinsics.  In general, the plan is to
provide `psnip_builtin_*` functions which correspond to `__builtin_*`
in GCC.  `psnip_intrin_*` which correspond to the `_*` intrinsics
in MSVC will be provided in the intrin/ directory of psnip.

If the compiler already has the builtin, the psnip function will
simply be defined to that builtin, meaning there should be no
performance penalty.  If the compiler does not have an implementation
it will be implemented using either a built-in/intrinsic the compiler
*does* support (i.e., using an MSVC intrinsic to implement a GCC
built-in), or a fully-portable pure C implementation.

This is very much a work in progress.  Eventually I plan to include
implementations of all built-ins/intrinsics which make sense.
Built-ins/intrinsics which are really there to implement standard
functionality (e.g., `__builtin_huge_val`) will not be implemented;
use the standard versions.

I haven't really focused on optimizing the portable versions;
they're really just there as fallbacks.  However, patches are
certainly welcome.

## Implementation Status

Note that this table doesn't include variants (i.e., there is ffs but
no ffsl or ffsll), but where the main function is implemented so are
the variants.

| GCC built-in | MSVC fallback | Portable fallback |
| ------------ | ------------- | ----------------- |
| ffs          | ✓             | ✓                 |
| clz          | ✓             | ✓                 |
| ctz          |               |                   |
| clrsb        |               |                   |
| popcount     |               |                   |
| parity       |               |                   |
| bswap*       |               |                   |
