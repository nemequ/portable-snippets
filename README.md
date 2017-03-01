# Portable Snippets

This is a curated collection of snippets written in C for performing
various common tasks in a relatively portable manner.

All modules can be used in isolation, though some do work better
together.  Everything is CC0 licensed (public domain), and tested with
various versions of GCC, Clang, and PGI ([on Travis
CI](https://travis-ci.org/nemequ/portable-snippets)), and MSVC ([on
AppVeyor](https://ci.appveyor.com/project/quixdb/portable-snippets)).

Currently read-to-use modules include:

 * [builtin](https://github.com/nemequ/portable-snippets/tree/master/builtin) —
   use compiler builtins/intrinsics, or fall back on standard C
 * [endian](https://github.com/nemequ/portable-snippets/tree/master/endian) —
   endianness detection and swapping
 * [atomic](https://github.com/nemequ/portable-snippets/tree/master/atomic) —
   common atomic synchronization operations
 * [safe-math](https://github.com/nemequ/portable-snippets/tree/master/safe-math) —
   overflow-safe integer functions
 * [exact-width](https://github.com/nemequ/portable-snippets/tree/master/exact-width) —
   exact width types (think `<stdint.h>`) which are used by some other headers

There are also a few modules under heavy development which are not yet
ready for deployment, but would benefit greatly from testing:

 * [clock](https://github.com/nemequ/portable-snippets/tree/master/clock) —
   cross-platform wall clock, CPU time, and monotonic time
 * [unaligned](https://github.com/nemequ/portable-snippets/tree/master/unaligned) —
   fast unaligned loads & stores

Please don't be shy about filing issues about any of these; if you
have problems it's likely others will, as well, so we would like to
fix them.

If you have something you would like to contribute, please file an
issue or pull request.  If you'd like to help out by writing something
new, take a look at the ["enhancement"
issues](https://github.com/nemequ/portable-snippets/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement)
in our issue tracker for ideas.

Some things don't really fit in a "snippet", or aren't public domain
and so cannot be included in this repository, so here are a few small
projects for doing things portably which you may be interested in:

 * [Hedley](https://nemequ.github.io/hedley/) — macros to enable
   compiler-specific features which make your code easier to use,
   harder to misues, safer, faster, and more portable.
 * [parg](https://github.com/jibsen/parg) —
   Argument parsing similar to getopt/getopt_long.  Public domain.
 * [TinyCThread](https://tinycthread.github.io/) — Implements the C11
   threads API on top of pthreads and the Windows API.  zlib license.
 * [win-iconv](https://github.com/win-iconv/win-iconv) — Windows
   implementation of the iconv API (character set conversion).

If there is a project you'd like to see added to the list, please file
an issue.
