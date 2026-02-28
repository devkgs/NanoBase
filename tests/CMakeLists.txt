# Define a function to create test binaries
function(create_test_binary TEST_BINARY TEST_SOURCES)
    add_executable(${TEST_BINARY} ${TEST_SOURCES})
    add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
    target_link_libraries(${TEST_BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
endfunction()

### Database Test ###
set(DATABASE_TEST_SOURCES
        database_test.cpp
        main.cpp
)
create_test_binary(Database_Tests "${DATABASE_TEST_SOURCES}")

### JsonEngine Test ###
set(JSONENGINE_TEST_SOURCES
        jsonengine_test.cpp
        main.cpp
)
create_test_binary(JsonEngine_Tests "${JSONENGINE_TEST_SOURCES}")


### All tests ###
set(TEST_SOURCES
        ${DATABASE_TEST_SOURCES}
        ${JSONENGINE_TEST_SOURCES}
)

add_executable(runAllTests ${TEST_SOURCES})
add_test(NAME runAllTests COMMAND runAllTests)
target_link_libraries(runAllTests ${CMAKE_PROJECT_NAME}_lib gtest gmock)
