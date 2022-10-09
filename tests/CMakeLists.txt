include(GoogleTest)

function(add_unit_test _NAME _SOURCE _FOLDER)
    add_executable("${_NAME}" "${_SOURCE}")
    set_target_properties(
        "${_NAME}"
        PROPERTIES
        FOLDER "${_FOLDER}"
    )
    target_link_libraries("${_NAME}" gtest_main)
    gtest_discover_tests("${_NAME}")
endfunction()

add_unit_test("dummy" "dummy.cpp" "tests")
