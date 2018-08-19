# Debugging assertions and traps

This is an attempt to provide a fairly portable way to generate traps
in code. `__builtin_trap` is `_Noreturn`, so the compiler may optimize
away code found after it, which means you can't really drop into a
debugger and step through the code after the trap has been hit.

If `PSNIP_NDEBUG` is defined, or `NDEBUG` is defined and `PSNIP_DEBUG`
is not, `psnip_dbg_assert(expr)` will be preprocessed to nothing
(i.e., `expr` will not be evaluated). Otherwise it will call
`psnip_trap` if `expr` evaluates to false.

Knowledge about how to do this portably basically comes from:

 * [scottt/debugbreak](https://github.com/scottt/debugbreak/).
 * GLib's [G_BREAKPOINT](https://developer.gnome.org/glib/stable/glib-Warnings-and-Assertions.html#G-BREAKPOINT:CAPS) macro.
 * [TI's Wiki](http://processors.wiki.ti.com/index.php/Software_Breakpoints_in_the_IDE)
 * Assorted compiler documentation.

On non-hosted platforms we *may* have to fall back on
`__builtin_trap`. On non-hosted non-GNU-compatible compilers on
relatively exotic architectures you may end up with an error about
stdlib.h being missing... if you have a good way to resolve that on
your platform please contact us.
