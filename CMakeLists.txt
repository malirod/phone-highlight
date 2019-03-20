cmake_minimum_required(VERSION 3.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/cmake-common-utils")
include(PreferClang)
include(PreferCcache)
include(DefaultDebug)
include(PreferGoldLinker)

project(PhoneHighlight VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Manage dependencies with Conan
include(SetupConan)

find_package(boost_range REQUIRED)
find_package(boost_algorithm REQUIRED)
find_package(boost_locale REQUIRED)
find_package(icu REQUIRED)

include(CTest)

# Add possibility to sanitize code
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools/cmake/sanitizers-cmake/cmake/")
find_package(Sanitizers REQUIRED)

# Add possibility to get code coverage
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/CMake-codecov/cmake")
find_package(codecov REQUIRED)

# Set global warnings configuration for all sub-projects
add_compile_options(-Wall -Wextra -pedantic -Werror)

set(LIB_NAME PhoneHighlight)
set(SRC_LIST
    "src/PhoneHighlight.h"
    "src/PhoneHighlight.cpp"
    "src/PhoneHighlightUtil.h"
    "src/PhoneHighlightUtil.cpp"
    "src/PhoneHighlightAlt.h"
    "src/PhoneHighlightAlt.cpp"
    "src/PhoneHighlightYS.h"
    "src/PhoneHighlightYS.cpp"
    "src/UtfUtils.h"
    "src/UtfUtils.cpp"
    "src/UtfUtilsIcu.h"
    "src/UtfUtilsIcu.cpp")

add_library(${LIB_NAME} ${SRC_LIST})
add_library(rms::${LIB_NAME} ALIAS ${LIB_NAME})

add_sanitizers(${LIB_NAME})
add_coverage(${LIB_NAME} src)
target_include_directories(${LIB_NAME} PUBLIC src)
target_compile_features(${LIB_NAME} PRIVATE cxx_std_14)
target_link_libraries(${LIB_NAME} PRIVATE boost_range::boost_range boost_algorithm::boost_algorithm boost_locale::boost_locale icu::icu)

if (BUILD_TESTING)
    find_package(Catch2 REQUIRED)

    set(TEST_LIB_NAME "${LIB_NAME}_test")

    set(TEST_SRC_LIST
        "test/PhoneHighlightTest.cpp"
        "test/PhoneHighlightAltTest.cpp"
        "test/PhoneHighlightYSTest.cpp"
        "test/UtfUtilsTest.cpp"
        "test/UtfUtilsIcuTest.cpp")

    add_library(${TEST_LIB_NAME} OBJECT ${TEST_SRC_LIST})
    add_library(rms::${TEST_LIB_NAME} ALIAS ${TEST_LIB_NAME})

    add_sanitizers(${TEST_LIB_NAME})
    list(APPEND LCOV_REMOVE_PATTERNS "'*/test/*'")
    add_coverage(${TEST_LIB_NAME})

    target_include_directories(${TEST_LIB_NAME} PRIVATE test)
    target_compile_features(${TEST_LIB_NAME} PRIVATE cxx_std_14)
    target_link_libraries(${TEST_LIB_NAME} PUBLIC rms::${LIB_NAME} Catch2::Catch2)

    # define test runner
    set(TEST_RUNNER_NAME testrunner)

    add_executable(${TEST_RUNNER_NAME} "test/TestRunner.cpp")

    target_compile_features(${TEST_RUNNER_NAME} PRIVATE cxx_std_14)
    target_link_libraries(${TEST_RUNNER_NAME} PRIVATE ${TEST_LIB_NAME})

    add_sanitizers(${TEST_RUNNER_NAME})

    add_test(NAME all COMMAND ${TEST_RUNNER_NAME})

    # define benchmark target
    find_package(google-benchmark REQUIRED)
    find_package(Threads REQUIRED)
    set(BENCHMARK_NAME benchmark)

    add_executable(${BENCHMARK_NAME} "benchmark/Benchmark.cpp")

    target_compile_features(${BENCHMARK_NAME} PRIVATE cxx_std_14)
    target_link_libraries(${BENCHMARK_NAME} PRIVATE rms::${LIB_NAME} google-benchmark::google-benchmark Threads::Threads)
endif()

include(ClangTidy)
include(PrepareDoxygen)
include(ClangStaticAnalyzer)