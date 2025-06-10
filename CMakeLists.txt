cmake_minimum_required(VERSION 3.31)
project(Ex4)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp
        containers.cpp
        containers.hpp)
add_executable(tests
        containers.cpp
        containers.hpp
        doctest.cpp
        doctest.hpp)
