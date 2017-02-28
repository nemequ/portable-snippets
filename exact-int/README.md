# Exact-Width Integer Types

Lots of stuff in psnip (as well as outside of psnip) requires
exact-width integer types.  C99 provides them in <stdint.h>, but
sometimes you can't rely on C99 being available.

This header will define macros for `psnip_(u)int(8,16,32,64)_t`, using
methods a bit more portable than just blindly including `<stdint.h>`:

 * On platforms where we know `<stdint.h>` is available (such as if
   we're compiling in C99 mode), we include `<stdint.h>`.
 * Otherwise, if we're using Visual Studio, use types we know exist.
 * If not, use `<limits.h>` to try to find some correctly-size types.

Headers in portable-snippets which use these types will only try to
include `exact-int.h` if they are missing a type they actually use,
which means you're free to create your own definitions for these
types.  This should help ensure that, if you already have exact-size
types, portable-snippets will be compatible with them.

If are looking for a more complete portable implementation of
`<stdint.h>` (for example, if you need the `UINT*_C` macros), there
are several projects which aim to provide a more complete
implementation, including:

 * [pstdint.h](http://www.azillionmonkeys.com/qed/pstdint.h) (BSD-3)
 * [msinttypes](https://code.google.com/archive/p/msinttypes/) (BSD-3)

Feel free to file a PR if I'm missing any.
