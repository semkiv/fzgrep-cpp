cmake_minimum_required(VERSION 3.15.0)

cmake_policy(SET CMP0091 NEW)

project(fzgrep)

set(MAIN_EXE "${PROJECT_NAME}")

add_executable("${MAIN_EXE}")

enable_testing()

# Debug optimization options
set(MSVC_DEBUG_FLAGS "/Od" "/Zi")
set(CLANG_GCC_DEBUG_FLAGS "-O0" "-g")

# Release optimization options
set(MSVC_RELEASE_FLAGS "/O2" "/GL" "/Gw" "/Gy" "/D" "NDEBUG")
set(CLANG_GCC_RELEASE_FLAGS "-O3" "-flto" "-DNDEBUG")

# Microsoft Visual C++ compilation options
set(
    MSVC_FLAGS "/utf-8" "/EHsc" "/MP" "/WX" "/W4" "/analyze"
    # "/fsanitize=address" # breaks incremental builds
)

# Clang compilation options
set(CLANG_FLAGS "-pedantic-errors" "-Werror" "-Wpedantic" "-Wall" "-Wextra" "-Wctor-dtor-privacy"
    "-Wnon-virtual-dtor" "-Wold-style-cast" "-Woverloaded-virtual" "-Wsign-promo" "-Wfloat-equal"
    "-Wshadow" "-Wcast-qual" "-Wconversion" "-Wzero-as-null-pointer-constant" "-Wextra-semi"
    "-Wsign-conversion" "-Wredundant-decls")

# GCC compilation options
set(
    GCC_FLAGS "${CLANG_FLAGS}" "-Wduplicated-branches" "-Wduplicated-cond" "-Wlogical-op" "-Wcast-align=strict"
    # "-fanalyzer" # Clnag doesn't like this (and makes clang-tidy complain about it)
)

set_target_properties(
    "${MAIN_EXE}"
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE CXX_EXTENSIONS OFF
        EXPORT_COMPILE_COMMANDS ON
)

target_compile_options(
    "${MAIN_EXE}"
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
    "${MAIN_EXE}"
    PRIVATE
    Threads::Threads
)

find_package(Threads REQUIRED)

message("-- Detecting IWYU")
find_program(IWYU_PATH NAMES include-what-you-use iwyu)
if(IWYU_PATH)
    message("-- IWYU - found ${IWYU_PATH}")
    set_property(
        TARGET "${MAIN_EXE}"
        PROPERTY CXX_INCLUDE_WHAT_YOU_USE "${IWYU_PATH}"
    )
else()
    message(WARNING "IWYU - not found")
endif()

message("-- Detecting clang-tidy")
find_program(CLANG_TIDY_PATH NAMES clang-tidy)
if(CLANG_TIDY_PATH)
    message("-- clang-tidy - found ${CLANG_TIDY_PATH}")
    set_property(
        TARGET "${MAIN_EXE}"
        PROPERTY CXX_CLANG_TIDY "${CLANG_TIDY_PATH};--extra-arg=-Wno-unknown-warning-option"
    )
else()
    message(WARNING "clang-tidy - not found")
endif()

add_subdirectory(src)
add_subdirectory(tests)
