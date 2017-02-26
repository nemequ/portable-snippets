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

GCC builtins:

 - [x] ffs
 - [x] ffsl
 - [x] ffsll
 - [x] clz
 - [x] clzl
 - [x] clzll
 - [x] ctz
 - [x] ctzl
 - [x] ctzll
 - [x] clrsb
 - [x] clrsbl
 - [x] clrsbll
 - [x] popcount
 - [x] popcountl
 - [x] popcountll
 - [x] parity
 - [x] parityl
 - [x] parityll
 - [x] bswap16
 - [x] bswap32
 - [x] bswap64

MSVC intrinsics:

 - [x] rotl8
 - [x] rotl16
 - [x] rotl
 - [x] rotl64
 - [x] rotr8
 - [x] rotr16
 - [x] rotr
 - [x] rotr64
 - [x] BitScanForward
 - [x] BitScanForward64
 - [ ] BitScanReverse
 - [ ] BitScanReverse64
 - [ ] mul128
 - [ ] umul128
 - [ ] shiftleft128
 - [ ] shiftright128
 - [ ] mulh
 - [ ] umulh
 - [x] byteswap_uint64
 - [x] byteswap_ulong
 - [x] byteswap_ushort
 - [x] bittest
 - [x] bittest64
 - [x] bittestandcomplement
 - [x] bittestandcomplement64
 - [x] bittestandreset
 - [x] bittestandreset64
 - [x] bittestandset
 - [x] bittestandset64

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
