# Portable Snippets

This is a collection of public domain (CC0) code snippets written in C
for performing various common tasks which are typically OS,
architecture, and/or compiler-dependent.  Basically, our goal is to
move those annoying preprocessor conditionals from your code to ours.

Modules have no fixed target (such as C89) since that would preclude
some functionality; instead, we simply try to provide the widest
support we can for each module.  If you have a platform which isn't
supported for a particular feature but could be, please let us know;
we'd be happy to try to work out a way to support it.

Everything is tested continuously with various versions of GCC, Clang,
and PGI ([on Travis
CI](https://travis-ci.org/nemequ/portable-snippets)), MSVC ([on
AppVeyor](https://ci.appveyor.com/project/quixdb/portable-snippets)),
and Emscripten (on
[Codefresh](https://g.codefresh.io/repositories/nemequ/portable-snippets/builds?filter=trigger:build;branch:master;service:591f783d728f4b0001051d3e~portable-snippets)):

[![Travis CI status](https://travis-ci.org/nemequ/portable-snippets.svg?branch=master)](https://travis-ci.org/nemequ/portable-snippets) [![AppVeyor status](https://ci.appveyor.com/api/projects/status/quoq2hwes530p29w/branch/master?svg=true)](https://ci.appveyor.com/project/quixdb/portable-snippets/branch/master) [![Codefresh status](https://g.codefresh.io/api/badges/build?repoOwner=nemequ&repoName=portable-snippets&branch=master&pipelineName=portable-snippets&accountName=nemequ&type=cf-1)](https://g.codefresh.io/repositories/nemequ/portable-snippets/builds?filter=trigger:build;branch:master;service:591f783d728f4b0001051d3e~portable-snippets)

Currently ready-to-use modules include:

 * [builtin](https://github.com/nemequ/portable-snippets/tree/master/builtin) —
   use compiler built-ins/intrinsics, or fall back on standard C
 * [endian](https://github.com/nemequ/portable-snippets/tree/master/endian) —
   endianness detection and swapping
 * [atomic](https://github.com/nemequ/portable-snippets/tree/master/atomic) —
   common atomic synchronization operations
 * [safe-math](https://github.com/nemequ/portable-snippets/tree/master/safe-math) —
   overflow-safe integer functions
 * [exact-int](https://github.com/nemequ/portable-snippets/tree/master/exact-int) —
   exact-width integer types (think `<stdint.h>`)
 * [clock](https://github.com/nemequ/portable-snippets/tree/master/clock) —
   cross-platform wall clock, CPU time, and monotonic time

There are also modules which may not yet be ready for widespread use, but
would benefit greatly from testing:

 * [unaligned](https://github.com/nemequ/portable-snippets/tree/master/unaligned) —
   fast unaligned loads & stores
 * [once](https://github.com/nemequ/portable-snippets/tree/master/once) —
   one-time initialization
 * [random](https://github.com/nemequ/portable-snippets/tree/master/random) —
   random number generation (3 flavors: cryptographic, reproducible, and fast)
 * [debug-trap](https://github.com/nemequ/portable-snippets/tree/master/debug-trap) —
   debugging traps and assertions
 * [check](https://github.com/nemequ/portable-snippets/tree/master/check) —
   assertion checking
 * [explicit-bzero](https://github.com/nemequ/portable-snippets/tree/master/explicit-bzero) —
   secure clearing of sensitive data in a buffer

Modules can be used in isolation, though some do work better together,
so if you can keep the whole repository together instead of just
copying a single file we recommend you do so.

Please don't be shy about filing issues about any of these; if you
have problems it's likely others will, as well, so we would like to
fix them.

If you have something you would like to contribute, please file an
issue or pull request.  If you'd like to help out by writing something
new, take a look at the ["enhancement"
issues](https://github.com/nemequ/portable-snippets/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement)
in our issue tracker for ideas.

Some things don't really fit this repository, so here are a few
small-ish projects for doing things portably which you may be
interested in:

 * [Hedley](https://nemequ.github.io/hedley/) — macros to enable
   compiler-specific features which make your code easier to use,
   harder to misuse, safer, faster, and more portable.
 * [parg](https://github.com/jibsen/parg) —
   Argument parsing similar to getopt/getopt_long.  Public domain.
 * [TinyCThread](https://tinycthread.github.io/) — Implements the C11
   threads API on top of pthreads and the Windows API.  zlib license.
 * [win-iconv](https://github.com/win-iconv/win-iconv) — Windows
   implementation of the iconv API (character set conversion).
 * [mman-win32](https://github.com/witwall/mman-win32) — `mman.h`
   (`mmap()`, *etc.*) implementation for Windows.

If there is a project you'd like to see added to the list, please file
an issue or pull request.
