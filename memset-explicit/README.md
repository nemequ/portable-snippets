# Securely erasing a buffer

After using any sensitive data such as passwords, the buffers which store them
must be cleared by the code to prevent it from being misused by a malicious
actor by performing core dumps or using other means to access the memory of
the application. However, most compilers optimize away the `memset` call as
they interpret the call as dead code because the memory being written to is not
being used afterwards.

`psnip_memset_explicit` function is used to securely write a value to the buffer to be erased.

```c
void *psnip_memset_explicit(void *s, int c, size_t n);
```

The memset_explicit function copies the value of `c` (converted to an
`unsigned char`) into each of the first `n` characters of the object pointed
to by `s`. It returns the value of `s`.

