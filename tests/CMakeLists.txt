add_executable(dummy dummy.cpp)
target_link_libraries(dummy gtest_main)
set_target_properties(dummy PROPERTIES FOLDER tests)

include(GoogleTest)
gtest_discover_tests(dummy)
