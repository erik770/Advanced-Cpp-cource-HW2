cmake_minimum_required(VERSION 3.17)
project(HW2)
set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")

#add_compile_options("--coverage")

add_subdirectory(lib/utils)
add_subdirectory(lib/word_search)
add_subdirectory(lib/word_search_procs)

add_executable(IW_2 main.c)
target_link_libraries(IW_2 utils word_search)

#enable_testing()
#find_package(GTest REQUIRED)
#add_executable(gtests tests/test.cpp)
#include_directories(${GTEST_INCLUDE_DIRS})
#target_link_libraries(gtests ${GTEST_LIBRARIES} utils gcov)