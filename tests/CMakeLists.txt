add_executable(dummy dummy.cpp)
target_link_libraries(dummy gtest_main)

include(GoogleTest)
gtest_discover_tests(dummy)
