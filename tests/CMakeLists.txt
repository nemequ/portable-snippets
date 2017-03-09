cmake_minimum_required(VERSION 3.0)

project(portable-snippet-tests)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)
endif()

include(CheckFunctionExists)
check_function_exists(clock_gettime CLOCK_GETTIME_RES)
if(CLOCK_GETTIME_RES)
  set(CLOCK_GETTIME_EXISTS yes)
else()
  set(orig_req_libs "${CMAKE_REQUIRED_LIBRARIES}")
  set(CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES};rt")

  check_function_exists(clock_gettime CLOCK_GETTIME_LIBRT_RES)
  if(CLOCK_GETTIME_LIBRT_RES)
    set(CLOCK_GETTIME_EXISTS yes)
    set(CLOCK_GETTIME_LIBRARY "rt")
  endif()

  set(CMAKE_REQUIRED_LIBRARIES "${orig_req_libs}")
  unset(orig_req_libs)
endif()

include (AddCompilerFlags)

set(PSNIP_C_FLAGS)

if(FATAL_WARNINGS)
  set_compiler_specific_flags(VARIABLE FATAL_WARNING_FLAGS
    GCCISH -Werror
    MSVC /WX)
  list(APPEND PSNIP_C_FLAGS ${FATAL_WARNING_FLAGS})
endif()

if(ENABLE_AGGRESSIVE_WARNINGS)
  set_compiler_specific_flags(VARIABLE EXTRA_WARNING_FLAGS
    GCCISH
      -Wall
      -Waggregate-return
      -Wcast-align
      -Wclobbered
      -Wempty-body
      -Werror=format=2
      -Werror=format-security
      -Werror=implicit-function-declaration
      -Werror=init-self
      -Werror=missing-include-dirs
      -Werror=missing-prototypes
      -Werror=pointer-arith
      -Wextra
      -Wformat-nonliteral
      -Wformat-security
      -Wignored-qualifiers
      -Winit-self
      -Winvalid-pch
      -Wlogical-op
      -Wmissing-declarations
      -Wmissing-format-attribute
      -Wmissing-include-dirs
      -Wmissing-noreturn
      -Wmissing-parameter-type
      -Wmissing-prototypes
      -Wnested-externs
      -Wno-missing-field-initializers
      -Wno-strict-aliasing
      -Wno-uninitialized
      -Wno-unused-parameter
      -Wold-style-definition
      -Woverride-init
      -Wpacked
      -Wpointer-arith
      -Wredundant-decls
      -Wreturn-type
      -Wshadow
      -Wsign-compare
      -Wstrict-prototypes
      -Wswitch-enum
      -Wsync-nand
      -Wtype-limits
      -Wundef
      -Wuninitialized
      -WUnsafe-loop-optimizations
      -Wwrite-strings
      -Wsuggest-attribute=format
    PGI
      -Minform=inform
    MSVC
      /W4)

  list(APPEND PSNIP_C_FLAGS ${EXTRA_WARNING_FLAGS})
endif()

if(NOT ENABLE_SANITIZER STREQUAL "")
  if(ENABLE_SANITIZER STREQUAL "undefined")
    set_compiler_specific_flags(VARIABLE UBSAN_FLAGS
      GCCISH -fsanitize=undefined
      GCC -fno-sanitize-recover=undefined,float-cast-overflow,float-divide-by-zero
      CLANG -fno-sanitize-recover=undefined,integer)
    list(APPEND PSNIP_C_FLAGS ${UBSAN_FLAGS})
  endif()
endif()

add_library(munit munit/munit.c)
set_property(TARGET munit PROPERTY C_STANDARD "99")
if("${CLOCK_GETTIME_EXISTS}")
  target_compile_definitions(munit PRIVATE "MUNIT_ALLOW_CLOCK_GETTIME")
  target_link_libraries(munit "${CLOCK_GETTIME_LIBRARY}")
endif()

function(psnip_add_tests)
  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES TESTS)
  cmake_parse_arguments(PSNIP_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_executable("${PSNIP_TEST_TARGET}" ${PSNIP_TEST_SOURCES})
  target_link_libraries("${PSNIP_TEST_TARGET}" munit)
  target_add_compiler_flags("${PSNIP_TEST_TARGET}" ${PSNIP_C_FLAGS})

  if(PSNIP_TEST_TESTS)
    foreach(TEST ${PSNIP_TEST_TESTS})
      add_test(NAME "${TEST}"
	COMMAND $<TARGET_FILE:${PSNIP_TEST_TARGET}> "${TEST}")
    endforeach(TEST)
  else()
    add_test(NAME "/${PSNIP_TEST_TARGET}"
      COMMAND $<TARGET_FILE:${PSNIP_TEST_TARGET}>)
  endif()
endfunction(psnip_add_tests)

psnip_add_tests(TARGET endian
  SOURCES
    endian.c)

psnip_add_tests(TARGET atomic
  SOURCES
    atomic.c)

if(ENABLE_OPENMP)
  target_compile_options(atomic PRIVATE ${OpenMP_C_FLAGS})
endif()

psnip_add_tests(TARGET builtin
  SOURCES
    builtin.c
  TESTS
    "/builtin"
    "/intrin"
    "/wrapper")

psnip_add_tests(TARGET safe-math
  SOURCES
    safe-math.c)

psnip_add_tests(TARGET unaligned
  SOURCES
    unaligned.c)

psnip_add_tests(TARGET clock
  SOURCES
    clock.c)

if("${CLOCK_GETTIME_EXISTS}")
  target_link_libraries(clock "${CLOCK_GETTIME_LIBRARY}")
else()
  target_compile_definitions(clock PRIVATE "PSNIP_CLOCK_NO_LIBRT")
endif()
