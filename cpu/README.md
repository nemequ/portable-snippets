# CPU Information

This module provides an API for querying some CPU features, such as
ISA extension support, that works across multiple architectures and
platforms.

## Dependencies

This module requires the once portable-snippet module.  If you do not
include once.h before cpu.h, cpu.h will automatically include
"../once/once.h".  If you include once.h manually you are free to use
whatever directory structure you like.

## Limitations

This code currently only supports x86/x86-64 and ARM.
