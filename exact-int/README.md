# Exact-Width Integer Types

Lots of stuff in psnip (as well as outside of psnip) requires
exact-width integer types.  C99 provides them in <stdint.h>, but
sometimes you can't rely on C99 being available.

This header will define macros for `psnip_(u)int(8,16,32,64)_t`, using
methods a bit more portable than just blindly including `<stdint.h>`.

Headers in portable-snippets which use these types will only try to
include `exact-int.h` if they are missing a type they actually use,
which means you're free to create your own definitions for these
types.  This should help ensure that, if you already have exact-size
types, portable-snippets will be compatible with them.

If are looking for a more complete portable implementation of
`<stdint.h>`, there are several projects which aim to provide a more
complete implementation, including:

 * [pstdint.h](http://www.azillionmonkeys.com/qed/pstdint.h) (BSD-3)
 * [msinttypes](https://code.google.com/archive/p/msinttypes/) (BSD-3)

Feel free to file a PR if I'm missing any.
