# Assertion Checking

This module provide a variety of assert()-style macros.  Unlike the
standard `assert()` macro from `<assert.h>`, most of these macros are
typed so the input values can be propogated to the string output on
failure.

For documentation, µnit offers very similar macros (this module was
originally based off of the macros from µnit), most of
[the documentation for them](https://nemequ.github.io/munit/#assertions)
applies to this module's macros, just substitute the `munit_` namespace
with `psnip_`.

Additionally, unless you define `PSNIP_CHECK_FAIL_DEFINED`, a failing
assertion should be considered undefined behavior when `NDEBUG` and/or
`PSNIP_NDEBUG` is defined.  This allows the compiler to perform
optimizations which would not otherwise be possible.

## Dependencies

To maximize portability you should #include the exact-int module
before including check.h, but if you don't want to add the extra
file to your project you can omit it and this module will simply rely
on <stdint.h>.  As an alternative you may define the following macros
to appropriate values yourself:

 * `psnip_int8_t`
 * `psnip_uint8_t`
 * `psnip_int16_t`
 * `psnip_uint16_t`
 * `psnip_int32_t`
 * `psnip_uint32_t`
 * `psnip_int64_t`
 * `psnip_uint64_t`

Including [Hedley](https://nemequ.github.io/hedley/) before check.h
will significantly improve compiler support and may improve
performance.
