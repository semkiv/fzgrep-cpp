cmake_minimum_required(VERSION 3.15.0)

# enable selection of MSVC runtime
cmake_policy(SET CMP0091 NEW)

# enable organization of CMake targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(fzgrep)

# add a variable to hold the name of the executable
set(MAIN_EXE "${PROJECT_NAME}")

add_executable("${MAIN_EXE}")

add_subdirectory(src)

# enable tests
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
