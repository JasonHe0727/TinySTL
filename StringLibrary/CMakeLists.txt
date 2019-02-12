cmake_minimum_required(VERSION 3.12)
project(StringLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(StringLibrary main.cpp String.cpp String.hpp Exception.cpp Exception.hpp Ptr.cpp Ptr.hpp)