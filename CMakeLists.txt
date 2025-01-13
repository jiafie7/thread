cmake_minimum_required(VERSION 3.19)

project(thread)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O2 -Wall -Werror -Wno-unused)

include_directories(./)

file(GLOB_RECURSE SOURCES "utility/*.cpp" "thread/*.cpp" "task/*.cpp")

add_executable(thread_main ${SOURCES} thread_main.cpp)

add_executable(cond_main ${SOURCES} cond_main.cpp)

add_executable(main ${SOURCES} main.cpp)
