# Find Check library
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

# Helper function to add a test
function(add_gb_test TEST_NAME)
    add_executable(${TEST_NAME} ${TEST_NAME}.c)

    target_link_libraries(${TEST_NAME}
        gbcore
        ${CHECK_LIBRARIES}
    )

    target_include_directories(${TEST_NAME} PRIVATE
        ${CHECK_INCLUDE_DIRS}
    )

    # Register with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# NOTE: Add test executables
# We'll add more as they are written
add_gb_test(test_utils)
add_gb_test(test_cartridge)
# add_gb_test(test_cpu)
# add_gb_test(test_mmu)
