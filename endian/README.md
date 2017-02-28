# Endianness Detection and Swapping

This header provides a convenient way to detect endianness, and
perform swapping.  It provides 6 important functions:

```c
psnip_uint16_t psnip_endian_le16(psnip_uint16_t v);
psnip_uint32_t psnip_endian_le32(psnip_uint32_t v);
psnip_uint64_t psnip_endian_le64(psnip_uint64_t v);
psnip_uint16_t psnip_endian_be16(psnip_uint16_t v);
psnip_uint32_t psnip_endian_be32(psnip_uint32_t v);
psnip_uint64_t psnip_endian_be64(psnip_uint64_t v);
```

These are usually implemented as macros, the prototypes above are
purely for documentation.

These functions will swap byte ordering to or from the provided type
**if necessary**.  For example, `psnip_endian_le32` is used to convert
a 32-bit unsigned integer to/from little-endian.  If the machine is
little-endian nothing will be done, but if it is big-endian then a
swap will be performed.  It's a bit like `hton`/`ntoh`, except instead
of host to/from network order, it's host to/from whatever order you
want.

If you wish to ignore the result of compile-time detection attempts,
you may define `PSNIP_ENDIAN_FORCE_RT` prior to including this header
to force run-time detection.
