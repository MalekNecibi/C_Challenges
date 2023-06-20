cmake_minimum_required (VERSION 3.5)

# Set Project Name to Source Directory
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_CXX_FLAGS "-std=c++0x -g -Wall -Werror")
set(CMAKE_C_FLAGS "-std=c11 -g -Wall -Werror")
set(CMAKE_C_FLAGS "-std=c11 -g -Wall -Wextra")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}_tester
               test/tests.cpp
               src/${PROJECT_NAME}.c)

target_link_libraries(${PROJECT_NAME}_tester
                      gtest
                      pthread)

enable_testing()
add_test(NAME    ${PROJECT_NAME}_test
         COMMAND ${PROJECT_NAME}_test)
