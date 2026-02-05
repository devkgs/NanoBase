cmake_minimum_required(VERSION 3.22)
project(NanoBase)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(lib/json/include)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)

#add_executable(NanoBase main.cpp)
