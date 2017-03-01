cmake_minimum_required(VERSION 2.8.6)

project(portable-snippet-tests)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include (CheckCCompilerFlag)
if(ENABLE_AGGRESSIVE_WARNINGS)
  if(MSVC)
    set(EXTRA_WARNING_FLAGS
      /W4)

    if(FATAL_WARNINGS)
      list(APPEND EXTRA_WARNING_FLAGS /WX)
    endif()
  else()
    set (EXTRA_WARNING_FLAGS
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
      -Minform=inform)

    if(FATAL_WARNINGS)
      list(APPEND EXTRA_WARNING_FLAGS -Werror)
    endif()
  endif()

  foreach (flag ${EXTRA_WARNING_FLAGS})
    string (REGEX REPLACE "[^a-zA-Z0-9]+" "_" test_name "CFLAG_${flag}")
    CHECK_C_COMPILER_FLAG ("${flag}" ${test_name})

    if (${test_name})
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
    endif ()
  endforeach (flag)
endif()

add_library(munit munit/munit.c)
find_package(ClockGettime)
if(ClockGettime_FOUND)
	set_property(TARGET munit
		APPEND PROPERTY COMPILE_DEFINITIONS MUNIT_ALLOW_CLOCK_GETTIME)
  target_link_libraries(munit ${ClockGettime_LIBRARIES})
endif()
set_property (TARGET munit PROPERTY C_STANDARD "99")

function(psnip_add_tests)
  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES TESTS)
  cmake_parse_arguments(PSNIP_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_executable("${PSNIP_TEST_TARGET}" ${PSNIP_TEST_SOURCES})
  target_link_libraries("${PSNIP_TEST_TARGET}" munit)

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
  find_package(OpenMP REQUIRED)
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
