cmake_minimum_required(VERSION 3.14)
project(TinySTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(TinySTL main.cpp List.hpp String.hpp String.cpp yl/String.cpp yl/String.hpp yl/Console.cpp yl/Console.hpp yl/StringBuilder.cpp yl/StringBuilder.hpp yl/Array.cpp yl/Array.hpp)