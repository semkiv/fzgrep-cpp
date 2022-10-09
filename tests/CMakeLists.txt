add_executable(dummy dummy.cpp)
set_target_properties(
    dummy
    PROPERTIES
    FOLDER "tests"
)

target_link_libraries(dummy gtest_main)

include(GoogleTest)
gtest_discover_tests(dummy)
