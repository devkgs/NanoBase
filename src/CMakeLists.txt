
set(BINARY ${CMAKE_PROJECT_NAME})

## src
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set (SOURCES ${SOURCES})

#add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(${BINARY}_run ${SOURCES})
target_link_libraries(${BINARY}_run PRIVATE ${CMAKE_PROJECT_NAME}_lib) # Link your library here
target_include_directories(${BINARY}_run PRIVATE ${CMAKE_SOURCE_DIR}/lib/json/include)

## Google test
add_library(${BINARY}_lib STATIC ${SOURCES})
