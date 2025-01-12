cmake_minimum_required(VERSION 3.19)

project(thread)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O2 -Wall -Werror -Wno-unused)

include_directories(./)

file(GLOB_RECURSE SOURCES "utility/*.cpp")

add_executable(thread_main ${SOURCES} thread_main.cpp)
