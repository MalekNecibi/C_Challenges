cmake_minimum_required (VERSION 3.5)

project(C_Challenges)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

add_subdirectory(arrays)
add_subdirectory(strings)
add_subdirectory(system_programming)
add_subdirectory(bitmap)
add_subdirectory(debug)
add_subdirectory(error_handling)
add_subdirectory(structures)
add_subdirectory(allocation)

enable_testing()
