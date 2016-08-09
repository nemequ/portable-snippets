# Portable Snippets

This is a collection of snippets written in C for doing various tasks
in a relatively portable manner.  Some of them may be a bit overkill
for your application; feel free to just take what you need.
Everything is CC0 licensed (public domain).

This repository currently contains:

* endian.h — endianness detection and swapping

Please don't be shy about filing issues about these; if you have
problems it's likely others will, as well, so we would like to fix
them.

If you have a snippet you would like to contribute, please file an
issue or pull request.  These are coming soon (I have the code, just
need to clean it up and/or remove some proprietary bits):

 * Runtime CPU feature detection (SSE, AVX, NEON, etc.).
 * High-precision time.  There is
   [some code in µnit for this](https://github.com/nemequ/munit/blob/ca64cf27eda984855323917736ed595030f150db/munit.c#L274)
   but it's geared towards timing.
 * A portable stdatomic.h

Some things don't really fit in a "snippet", or aren't public domain
and so cannot be included in this repository, so here are a few
projects for doing things portably which you may be interested in:

 * [parg](https://github.com/jibsen/parg) —
   Argument parsing similar to getopt/getopt_long.  Public domain.
 * [TinyCThread](https://tinycthread.github.io/) — Implements the C11
   threads API on top of pthreads and the Windows API.  zlib license.
 * [pstdint.h](http://www.azillionmonkeys.com/qed/pstdint.h) —
   stdint.h/cstdint for platforms which don't have it.  3-clause BSD
   license.
 * [safe-math](https://github.com/nemequ/safe-math) — portable
   overflow-safe path functions.  MIT license.

If there is a project you'd like to see added to the list, please file
an issue.
