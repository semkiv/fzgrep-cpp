cmake_minimum_required(VERSION 3.13.0)

project(fzgrep)

enable_testing()

find_package(Threads REQUIRED)

message("-- Detecting IWYU")
find_program(IWYU_PATH NAMES include-what-you-use iwyu)
if(IWYU_PATH)
    message("-- Detecting IWYU - found ${IWYU_PATH}")
else()
    message(WARNING "-- Detecting IWYU - not found")
endif()

message("-- Detecting clang-tidy")
find_program(CLANG_TIDY_PATH NAMES clang-tidy)
if(CLANG_TIDY_PATH)
    message("-- Detecting clang-tidy - found ${CLANG_TIDY_PATH}")
else()
    message(WARNING "-- Detecting clang-tidy - not found")
endif()

# Debug optimization options
set(
    MSVC_DEBUG_FLAGS
    "/Od"
    "/Zi"
)
set(
    CLANG_GCC_DEBUG_FLAGS
    "-O0"
    "-g"
)

# Release optimization options
set(
    MSVC_RELEASE_FLAGS
    "/O2"
    "/GL"
    "/Gw"
    "/Gy"
    "/D"
    "NDEBUG"
)
set(
    CLANG_GCC_RELEASE_FLAGS
    "-O3"
    "-flto"
    "-DNDEBUG"
)

# Microsoft Visual C++ compilation options
set(
    MSVC_FLAGS
    "/utf-8"
    "/EHsc"
    "/MP"
    "/WX"
    "/W4"
    "/analyze"
    # "/fsanitize=address" # breaks incremental builds
)

# Clang compilation options
set(
    CLANG_FLAGS
    "-pedantic-errors"
    "-Werror"
    "-Wpedantic"
    "-Wall"
    "-Wextra"
    "-Wctor-dtor-privacy"
    "-Wnon-virtual-dtor"
    "-Wold-style-cast"
    "-Woverloaded-virtual"
    "-Wsign-promo"
    "-Wfloat-equal"
    "-Wshadow"
    "-Wcast-qual"
    "-Wconversion"
    "-Wzero-as-null-pointer-constant"
    "-Wextra-semi"
    "-Wsign-conversion"
    "-Wredundant-decls"
)

# GCC compilation options
set(
    GCC_FLAGS
    "${CLANG_FLAGS}"
    "-Wduplicated-branches"
    "-Wduplicated-cond"
    "-Wlogical-op"
    "-Wcast-align=strict"
    # "-fanalyzer" # Clnag doesn't like this (and makes clang-tidy complain about it)
)

add_executable("${PROJECT_NAME}" "src/main.cpp")

set_target_properties(
    "${PROJECT_NAME}"
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
    EXPORT_COMPILE_COMMANDS ON
    CXX_INCLUDE_WHAT_YOU_USE "${IWYU_PATH}"
    CXX_CLANG_TIDY "${CLANG_TIDY_PATH};--extra-arg=-Wno-unknown-warning-option"
)

target_compile_options(
    "${PROJECT_NAME}"
    PRIVATE
    "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:${MSVC_DEBUG_FLAGS}>"
    "$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELEASE>>:${MSVC_RELEASE_FLAGS}>"
    "$<$<AND:$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>,$<CONFIG:DEBUG>>:${CLANG_GCC_DEBUG_FLAGS}>"
    "$<$<AND:$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>,$<CONFIG:RELEASE>>:${CLANG_GCC_RELEASE_FLAGS}>"
    "$<$<CXX_COMPILER_ID:MSVC>:${MSVC_FLAGS}>"
    "$<$<CXX_COMPILER_ID:Clang>:${CLANG_FLAGS}>"
    "$<$<CXX_COMPILER_ID:GNU>:${GCC_FLAGS}>"
)

target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE
    Threads::Threads
)

add_subdirectory(src)
add_subdirectory(tests)
