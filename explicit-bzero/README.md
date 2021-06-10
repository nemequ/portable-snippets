# Securely erasing a buffer

After using any sensitive data such as passwords, the buffers which store them
must be cleared by the code to prevent it from being misused by a malicious
actor by performing core dumps or using other means to access the memory of
the application. However, most compilers optimize away the `memset` call as
they interpret the call as dead code because the memory being written to is not
being used afterwards.

`psnip_explicit_bzero` function could be used to securely zero out a buffer
containing sensitive data.

```c
void psnip_explicit_bzero(void *str, size_t n);
```

The `psnip_explicit_bzero` function writes `n` zero bytes to the string `str`.
If len is zero, bzero() does nothing.

