# Once

This is a simple abstraction for a once which will choose from a few
different back-ends:

 * If C11 threads are available, use `call_once()`.
 * On Windows, use
   [InitOnceExecuteOnce()](https://msdn.microsoft.com/en-us/library/windows/desktop/ms683493(v=vs.85).aspx)
 * If `PTHREAD_ONCE_INIT` is defined (*i.e.*, if `<pthread.h>` has
   been included prior to including `once.h`), use `pthread_once()`.
 * Use `[atomic.h](../atomic)`.
