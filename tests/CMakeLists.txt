# Define a function to create test binaries
function(create_test_binary TEST_BINARY TEST_SOURCES)
    add_executable(${TEST_BINARY} ${TEST_SOURCES})
    add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
    target_link_libraries(${TEST_BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
endfunction()

### Example Test ###
set(EXAMPLE_TEST_SOURCES
        database_test.cpp
        main.cpp
)
create_test_binary(Example_Tests "${EXAMPLE_TEST_SOURCES}")

### All tests ###
set(TEST_SOURCES
        ${EXAMPLE_TEST_SOURCES}
)

add_executable(runAllTests ${TEST_SOURCES})
add_test(NAME runAllTests COMMAND runAllTests)
target_link_libraries(runAllTests ${CMAKE_PROJECT_NAME}_lib gtest)
