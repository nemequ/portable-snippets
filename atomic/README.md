# Atomic Operations

This header provides atomic operations in a way which is portable to
most platforms.  Current back-ends include:

 * C11
 * GCC-style __atomic_* builtins
 * Old-style GCC sync_* builtins
 * clang-style __c11_atomic_* builtins
 * MSVC-style Interlocked* intrinsics

This is sufficient to support most modern, actively developed
compilers.  The only real exception I'm aware of is [PGI C/C++
Compiler](http://www.pgroup.com/), which [doesn't currently support
atomics](http://www.pgroup.com/userforum/viewtopic.php?t=5504) but
hopefully will soon.

Most things are implemented with the preprocessor, but if they were
functions the prototypes (the 64-bit versions, just s/64/32/ for the
32-bit versions) would loo like:

```c
psnip_nonatomic_int64 psnip_atomic_int64_load(
  psnip_atomic_int64* object);

void psnip_atomic_int64_store(
  psnip_atomic_int64* object,
  psnip_nonatomic_int64 desired);

_Bool psnip_atomic_int64_compare_exchange(
  psnip_atomic_int64* object,
  psnip_nonatomic_int64* expected,
  psnip_nonatomic_int64 desired);

psnip_nonatomic_int64 psnip_atomic_int64_add(
  psnip_atomic_int64* object,
  psnip_nonatomic_int64 operand);

psnip_nonatomic_int64 psnip_atomic_int64_sub(
  psnip_atomic_int64* object,
  psnip_nonatomic_int64 operand);
```

If no atomics are supported, `PSNIP_ATOMIC_NOT_FOUND` will be
defined; you'll probably have to use locks (if you want a portable API
for that you may be interested in
[TinyCThread](https://github.com/tinycthread/tinycthread/)).
