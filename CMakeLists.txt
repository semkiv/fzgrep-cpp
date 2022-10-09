cmake_minimum_required(VERSION 3.15.0)

cmake_policy(SET CMP0091 NEW)

project(fzgrep)

enable_testing()

set(MAIN_EXE "${PROJECT_NAME}")

add_executable("${MAIN_EXE}")

add_subdirectory(src)
add_subdirectory(tests)
