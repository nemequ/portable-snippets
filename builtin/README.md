# Built-Ins

These snippets are intended to provide portable versions of many of
GCC's built-ins and MSVC's intrinsics.  In general, the plan is to
provide `psnip_builtin_*` functions which correspond to `__builtin_*`
in GCC, and `psnip_intrin_*` which correspond to the `_*` intrinsics
in MSVC.

If PSNIP_BUILTIN_EMULATE_NATIVE is defined *before* `builtin.h` is
included, this header will also define any missing native-style
built-ins, allowing you to use the native names without regard for
which compiler is actually in use (i.e., you can use `__builtin_ffs`
directly in MSVC, or any other compiler).

If the compiler already has the builtin, the psnip function will
simply be defined to that builtin, meaning there should be no
performance penalty.  If the compiler does not have an implementation
it will be implemented using either a built-in/intrinsic the compiler
*does* support (i.e., using an MSVC intrinsic to implement a GCC
built-in), or a fully-portable pure C implementation.

For GCC-style builtins, the header will also define exact-width 32-
and 64-bit variants in the form of `psnip_builtin_foo32` and
`psnip_builtin_foo64`.  These are typically just aliases for the
appropriate function, but if we can't find an appropriate type a fully
portable implementation will be used.

## Implementation Status

This is very much a work in progress.  Eventually I plan to include
implementations of all built-ins/intrinsics which make sense.  That
specifically does **not** include built-ins which are really there to
implement standard functionality (e.g., `__builtin_huge_val`) will not
be implemented; use the standard versions.

Architecture-specific builtins which do not have a generic version in
either GCC or MSVC may receive an implementation, but probably not
until people specifically request (or, better yet, provide) one.

Functions without a portable version have not been implemented at all
(i.e., there is no psnip_* function yet).

| GCC built-in     | Portable | MSVC |
| ---------------- | -------- | ---- |
| ffs              | ✓        | ✓    |
| ffsl             | ✓        | ✓    |
| ffsll            | ✓        | ✓    |
| clz              | ✓        | ✓    |
| clzl             | ✓        | ✓    |
| clzll            | ✓        | ✓    |
| ctz              | ✓        |      |
| ctzl             | ✓        |      |
| ctzll            | ✓        |      |
| clrsb            |          |      |
| clrsbl           |          |      |
| clrsbll          |          |      |
| popcount         | ✓        |      |
| popcountl        | ✓        |      |
| popcountll       | ✓        |      |
| parity           | ✓        |      |
| parityl          | ✓        |      |
| parityll         | ✓        |      |
| bswap16          |          |      |
| bswap32          |          |      |
| bswap64          |          |      |

| MSVC intrinsic         | Portable | GCC  |
| ---------------------- | -------- | ---- |
| rotl8                  | ✓        |      |
| rotl16                 | ✓        |      |
| rotl                   | ✓        |      |
| rotl64                 | ✓        |      |
| rotr8                  | ✓        |      |
| rotr16                 | ✓        |      |
| rotr                   | ✓        |      |
| rotr64                 | ✓        |      |
| BitScanForward         | ✓        |      |
| BitScanForward64       | ✓        |      |
| BitScanReverse         |          |      |
| BitScanReverse64       |          |      |
| mul128                 |          |      |
| umul128                |          |      |
| shiftleft128           |          |      |
| shiftright128          |          |      |
| mulh                   |          |      |
| umulh                  |          |      |
| byteswap_uint64        |          |      |
| byteswap_ulong         |          |      |
| byteswap_ushort        |          |      |
| bittest                | ✓        |      |
| bittest64              | ✓        |      |
| bittestandcomplement   |          |      |
| bittestandcomplement64 |          |      |
| bittestandreset        |          |      |
| bittestandreset64      |          |      |
| bittestandset          |          |      |
| bittestandset64        |          |      |

Note that it may not be possible to implement built-ins from one
compiler using the built-ins from another.

If we are missing a function you feel should be included, please [file
an issue](https://github.com/nemequ/portable-snippets/issues).

## Alternatives & Supplements

For bswap/byteswap functions, you should really use endian.h which
also handles endianness detection as well as providing easier to use
APIs.

For overflow-safe integer operations (i.e., `__builtin_*_overflow`),
use safe-math.h.
