# Built-Ins

This module provides portable implementations of many compiler
builtins and intrinsics, allowing you to use builtins and intrinsics
on compilers which don't support them.  This includes other compilers
(*e.g.*, GCC builtins on MSVC) and older versions of the same
compiler.

We also provide exact-width variants of many builtins; no more calling
different functions depending on the size of `int`, `long`, `long
long`, etc.  These are typically just aliases for the appropriate
function, but if we can't find an appropriate type a fully portable
implementation will be used.

If you define `PSNIP_BUILTIN_EMULATE_NATIVE` *before* `builtin.h` is
included, this header will also define any missing native-style
built-ins, allowing you to use the native names without regard for
which compiler is actually in use (*i.e.*, you can use `__builtin_ffs`
directly in MSVC, or any other compiler, including GCC < 3.3).

If the compiler already has the builtin, the psnip function will
simply be defined to that builtin.  If the compiler does not have an
implementation it will be implemented using either a
built-in/intrinsic the compiler *does* support (i.e., using an MSVC
intrinsic to implement a GCC built-in), or a fully-portable pure C
implementation.

For example, for GCC's `__builtin_ffs` builtin, we provide
implementations which work everywhere (including versions of GCC prior
to 3.3, when `__builtin_ffs` was introduced) of the following
functions:

```c
int psnip_builtin_ffs(int);
int psnip_builtin_ffsl(long);
int psnip_builtin_ffsll(long long);
int psnip_builtin_ffs32(psnip_int32_t);
int psnip_builtin_ffs64(psnip_int64_t);
```

Additionally, when when PSNIP_BUILTIN_EMULATE_NATIVE is defined (and
the compiler doesn't already provide them), we also provide

```c
int __builtin_ffs(int);
int __builtin_ffsl(long);
int __builtin_ffsll(long long);
```

Note that these are often provided as macros, the prototypes are for
documentation only.

## Implementation Status

Almost every generic builtin we can implement has been implemented.
This should work with almost anywhere (our biggest restriction is
probably that we currently assume `CHAR_BIT == 8`), but every commit
is tested before landing in the master branch on various versions of
GCC, clang, MSVC, and PGI (thanks to [Travis
CI](https://travis-ci.org/nemequ/portable-snippets) and
[AppVeyor](https://ci.appveyor.com/project/quixdb/portable-snippets)).
Sporadic testing is also done on ICC and Oracle Developer Studio.

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

Clang builtins:

 - [x] bitreverse8
 - [x] bitreverse16
 - [x] bitreverse32
 - [x] bitreverse64
 - [x] addcb
 - [x] addcs
 - [x] addc
 - [x] addcl
 - [x] addcll
 - [x] subcb
 - [x] subcs
 - [x] subc
 - [x] subcl
 - [x] subcll

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
 - [x] BitScanReverse
 - [x] BitScanReverse64
 - [ ] mul128
 - [ ] umul128
 - [x] shiftleft128
 - [x] shiftright128
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

For overflow-safe integer operations (*i.e.*, `__builtin_*_overflow`),
use [safe-math.h](../safe-math).

If we are missing a function you feel should be included, please [file
an issue](https://github.com/nemequ/portable-snippets/issues).  Please
keep in mind that some things are simply impossible to implement
without compiler support.

## Alternatives & Supplements

For overflow-safe integer operations (i.e., `__builtin_*_overflow`),
use [safe-math.h](../safe-math).

For bswap/byteswap functions, you should really use
[endian.h](../endian) which also handles endianness detection as well
as providing easier to use APIs.

For things which are effectively progressive enhancements (such as
`__builtin_expect`) as opposed to hard requirements, see
[Hedley](https://nemequ.github.io/hedley/).

## Areas for future work

### Optimization

Performance should be pretty good but we're always open to shaving off
a few operations, even if it means creating different variants for
different compilers or architectures.

Creating implementations of one compiler's builtins using builtins
from another is probably your best bet to improve performance.
Another useful possibility is using architecure-specific builtins, or
even embedded assembly, to accelerate portable versions when they are
available.

### Architecture-specific builtins

GCC and MSVC both have lots of architecture-specific builtins.
Especially GCC, which supports many architectures.  If you come across
one which is useful and could be implemented with a portable fallback,
let us know.

### Builtins from other compilers

We've looked at GCC, MSVC, and Clang, but we're happy to support
builtins from other compilers, too.
