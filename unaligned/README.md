# Unaligned Loads and Stores

**WARNING**: This module is work-in-progress, and not yet ready for
widespread adoption.  Testing, however, would be greatly appreciated.

This header provides fast load/store operations.

## Rationale

Yann Collet wrote a [great blog
post](https://fastcompression.blogspot.fr/2015/08/accessing-unaligned-memory.html)
about accessing unaligned memory a while back which is well worth a
read.  Basically, there are a few different methods to access
unaligned memory, with different performance implications.  `memcpy`
is safe, but slow on some compilers.  Other methods rely on undefined
behavior which may or may not be safe depending on the compiler and
platform, and/or compiler-specific constructs.

It's important to note that, if you rely on undefined behavior,
compilers which currently work may stop working in the future when
optimizations are added.  For example, unaligned accesses are usually
allowed on x86, but not for some SIMD instructions.  GCC 4.9 added an
optimization which automatically vectorized some code in LZ4, and
since LZ4 (at the time) relied on unaligned accesses that change broke
LZ4.

The biggest value of this module is the logic to determine which
method to use on different combinations of compilers, compiler
versions, and architectures.

## Usage

`unaligned.h` defines macros which can be used to generate inline
functions for whatever types you want.  For example, to generate
functions for `int`:

```c
PSNIP_UNALIGNED_LOAD_DEFINE(foo_load, int)
PSNIP_UNALIGNED_STORE_DEFINE(foo_store, int)
```

Would yield functions which look something like:

```c
int foo_load(const void* src);
void foo_store(void* dest, int src);
```

By default, we will use `memcpy` as it's the only completely safe
option.  However, if you define `PSNIP_UNALIGNED_ALLOW_UNDEFINED`
prior to including `unaligned.h` it will check for platforms where
unaligned accesses are safe and faster than `memcpy()`.  On such
platforms, access may be done through either a cast & dereference or
through a packed union.

If you include `exact-int.h` before including `unaligned.h` (or define
the exact-width types yourself), we will also define functions to
load/store to/from those types:

```c
psnip_int16_t  psnip_unaligned_load_int16  (const void* src);
psnip_int32_t  psnip_unaligned_load_int32  (const void* src);
psnip_int64_t  psnip_unaligned_load_int64  (const void* src);
psnip_uint16_t psnip_unaligned_load_uint16 (const void* src);
psnip_uint32_t psnip_unaligned_load_uint32 (const void* src);
psnip_uint64_t psnip_unaligned_load_uint64 (const void* src);
void           psnip_unaligned_store_int16 (void* dest, int16_t src);
void           psnip_unaligned_store_int32 (void* dest, int32_t src);
void           psnip_unaligned_store_int64 (void* dest, int64_t src);
void           psnip_unaligned_store_uint16(void* dest, uint16_t src);
void           psnip_unaligned_store_uint32(void* dest, uint32_t src);
void           psnip_unaligned_store_uint64(void* dest, uint64_t src);
```

If you also include `endian.h` before including `unaligned.h`, we will
also define macros to load/store different-endian values to/from
the exact-width types:

```c
psnip_int16_t  psnip_unaligned_load_int16le  (const void* src);
psnip_int32_t  psnip_unaligned_load_int32le  (const void* src);
psnip_int64_t  psnip_unaligned_load_int64le  (const void* src);
psnip_int16_t  psnip_unaligned_load_int16be  (const void* src);
psnip_int32_t  psnip_unaligned_load_int32be  (const void* src);
psnip_int64_t  psnip_unaligned_load_int64be  (const void* src);
psnip_uint16_t psnip_unaligned_load_uint16le (const void* src);
psnip_uint32_t psnip_unaligned_load_uint32le (const void* src);
psnip_uint64_t psnip_unaligned_load_uint64le (const void* src);
psnip_uint16_t psnip_unaligned_load_uint16be (const void* src);
psnip_uint32_t psnip_unaligned_load_uint32be (const void* src);
psnip_uint64_t psnip_unaligned_load_uint64be (const void* src);
void           psnip_unaligned_store_int16le (void* dest, psnip_int16_t src);
void           psnip_unaligned_store_int32le (void* dest, psnip_int32_t src);
void           psnip_unaligned_store_int64le (void* dest, psnip_int64_t src);
void           psnip_unaligned_store_int16be (void* dest, psnip_int16_t src);
void           psnip_unaligned_store_int32be (void* dest, psnip_int32_t src);
void           psnip_unaligned_store_int64be (void* dest, psnip_int64_t src);
void           psnip_unaligned_store_uint16le(void* dest, psnip_int16_t src);
void           psnip_unaligned_store_uint32le(void* dest, psnip_int32_t src);
void           psnip_unaligned_store_uint64le(void* dest, psnip_int64_t src);
void           psnip_unaligned_store_uint16be(void* dest, psnip_int16_t src);
void           psnip_unaligned_store_uint32be(void* dest, psnip_int32_t src);
void           psnip_unaligned_store_uint64be(void* dest, psnip_int64_t src);
```

These are implemented as macros, the prototypes above are purely for
documentation.
