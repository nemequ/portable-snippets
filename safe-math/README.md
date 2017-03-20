# Overflow-safe math functions

The safe-math.h header defines numerous functions for verifying that
integer operations do not overflow.  Available implementations, in
order of priority:

 * Compiler builtins (i.e., `__builtin_*_overflow`).
 * On Windows, use `<intsafe.h>` for the types it supports.
 * If a larger type is available, promote the inputs and verify the
   result falls within the range of the result type before casting to
   it.
 * Check that the operation would not result in an overflow before
   performing it.  See [INT32-C in CERT's C Coding
   Standard](https://www.securecoding.cert.org/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow)
   for details.

# APIs

## Preferred API

Regardless of which implementation is chosen, the preferred API is the
same.  For each type and operation, we define:

```c
psnip_safe_bool psnip_safe_{type_identifier}_{operation} ({T}* result, {T} a, {T} b);
```

For example, for addition on signed integers, there is

```c
psnip_safe_bool psnip_safe_int_add (int* res, int a, int b);
```

Values for type_identifier and T are:

| Identifier | Type                 |
| ---------- | -------------------- |
| `char`     | `char`               |
| `uchar`    | `unsigned char`      |
| `short`    | `short`              |
| `ushort`   | `unsigned short`     |
| `int`      | `int`                |
| `uint`     | `unsigned int`       |
| `long`     | `long`               |
| `ulong`    | `unsigned long`      |
| `llong`    | `long long`          |
| `ullong`   | `unsigned long long` |
| `size`     | `size_t`             |
| `int8`     | `int8_t`             |
| `uint8`    | `uint8_t`            |
| `int16`    | `int16_t`            |
| `uint16`   | `uint16_t`           |
| `int32`    | `int32_t`            |
| `uint32`   | `uint32_t`           |
| `int64`    | `int64_t`            |
| `uint64`   | `uint64_t`           |

Operations are:

 * add (addition)
 * sub (subtraction)
 * mul (multiplication)
 * div (division)
 * mod (modulus)
 * neg (negation, for signed types only)

Negation only has one input argument, all the others have two.

`psnip_safe_bool` is defined to _Bool (for C99) or int.

## Emulation of native APIs

If you prefer, you can `#define` either `PSNIP_SAFE_EMULATE_NATIVE` or
`PSNIP_BUILTIN_EMULATE_NATIVE` and we will also provide an API
compatible with [GCC's overflow
builtins](https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html)
unless the compiler we're using already provides it.  There are two
things to watch out for if you choose this:

 * The type-generic functions (`__builtin_add_overflow`,
   `__builtin_sub_overflow`, and `__builtin_mul_overflow`) will only
   be available in C11 mode.
 * The argument order is slightly different, with the result coming
   last instead of first.  We prefer the result to come first so the
   call looks a bit more like an assignment operation, but GCC made a
   different choice.

## The `safe_larger_*` API

In order to implement the versions of functions which promote the
arguments then check the result before casting back to original type,
we had to create an API.  It's really intended as an internal API, and
is a bit of a pain, but if you'd rather just have a larger result
instead of having to check for the overflow case it can be useful.

For types where we know of a larger type we define the macro
`PSNIP_SAFE_HAVE_TYPE_LARGER`, as well as a typedef to the larger type
called `psnip_safe_type_larger`.  For example, we know that there is a type
larger than `int16_t` (`int32_t`), so there is:

```C
#define PSNIP_SAFE_HAVE_INT16_LARGER
typedef int32_t psnip_safe_int16_larger;
```

This gets slightly more complicated (but more useful) when dealing
with the non-fixed-length types.  For example, short may or may not be
larger than char (it's not shorter, but they may be equal).  So,
assuming char is less than 64-bits (or the compiler supports 128-bit
numbers), we will define `PSNIP_SAFE_HAVE_CHAR_LARGER` and
`psnip_safe_char_larger` will be a typedef to the first type which is larger
than char (the order we try is `char`, `short`, `int`, `long`, `long
long`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, then the 128-bit
integer type if available).  So, `psnip_safe_char_larger` is a typedef to
`short` if `short` is larger than `char`, otherwise `int` if `int` is
larger than `char`, otherwise `long`, etc.

In addition to the typedefs, if there is a larger known type we
also generate a set of functions in the form of

```C
psnip_safe_type_larger psnip_safe_larger_type_operation(type, type)
```

This is done for every type and every operation; for example, if
`PSNIP_SAFE_HAVE_CHAR_LARGER` is defined, then so too will be

 * `psnip_safe_char_larger psnip_safe_larger_char_add(char, char)`
 * `psnip_safe_char_larger psnip_safe_larger_char_sub(char, char)`
 * `psnip_safe_char_larger psnip_safe_larger_char_mul(char, char)`
 * `psnip_safe_char_larger psnip_safe_larger_char_div(char, char)`
 * `psnip_safe_char_larger psnip_safe_larger_char_mod(char, char)`
 * `psnip_safe_char_larger psnip_safe_larger_char_neg(char)`

# Caveats

The type-generic functions are only guaranteed to be available in C11
mode since there was no standard way to implement them until C11.

Even if you request emulation of the GCC builtins, we cannot provide
the `__builtin_*_overflow_p` functions.
