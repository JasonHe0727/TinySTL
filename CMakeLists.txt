cmake_minimum_required(VERSION 3.10)
project(TinySTL)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/headers test/headers)

file(GLOB SOURCES "src/sources/*.cpp")
file(GLOB TESTS "test/sources/*.cpp")

add_executable(TinySTL main.cpp ${SOURCES} ${TESTS})
