cmake_minimum_required(VERSION 3.17)
project(HW2)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pthread --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread --coverage")

add_compile_options("--coverage")

add_subdirectory(lib/utils)
add_subdirectory(lib/word_search)
add_subdirectory(lib/word_search_procs)

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests tests/test.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(tests ${GTEST_LIBRARIES} utils word_search gcov)

add_executable(tests_procs tests/test.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(tests_procs ${GTEST_LIBRARIES} utils word_search_procs gcov)


add_executable(stress_test tests/stress_test.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(stress_test ${GTEST_LIBRARIES} utils word_search gcov)

add_executable(stress_test_procs tests/stress_test.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(stress_test_procs ${GTEST_LIBRARIES} utils word_search_procs gcov)
