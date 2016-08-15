include (CheckFunctionExists)

set(ClockGettime_LIBRARIES "")
set(ClockGettime_FOUND 0)
mark_as_advanced(ClockGettime_LIBRARIES CLOCK_GETTIME_FOUND)

set(CMAKE_REQUIRED_LIBRARIES_orig "${CMAKE_REQUIRED_LIBRARIES}")
set(CMAKE_REQUIRED_LIBRARIES "")

check_function_exists(clock_gettime ClockGettime_LIBC)
if(ClockGettime_LIBC)
  set(ClockGettime_LIBRARIES "")
  set(ClockGettime_FOUND 1)
else()
  set(CMAKE_REQUIRED_LIBRARIES rt)
  check_function_exists(clock_gettime ClockGettime_LIBRT)

  if(ClockGettime_LIBRT)
    set(ClockGettime_LIBRARIES rt)
    set(ClockGettime_FOUND 1)
  else()
    # mingw puts clock_gettime in pthreads
    set(CMAKE_REQUIRED_LIBRARIES pthread)
    check_function_exists(clock_gettime ClockGettime_LIBPTHREAD)

    if(ClockGettime_LIBPTHREAD)
      set(ClockGettime_LIBRARIES pthread)
      set(ClockGettime_FOUND 1)
    endif()

    unset(ClockGettime_LIBPTHREAD)
  endif()

  unset(ClockGettime_LIBRT)
endif()

unset(ClockGettime_LIBC)

set(CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES_orig}")
unset(CMAKE_REQUIRED_LIBRARIES_orig)
