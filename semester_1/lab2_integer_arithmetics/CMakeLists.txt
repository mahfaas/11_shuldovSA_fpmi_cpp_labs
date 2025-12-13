cmake_minimum_required(VERSION 3.14)
project(lab2_integer_arithmetics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mersenne_lib
    mersenne.cpp
    mersenne.h
)

add_executable(lab2_v10
    v10.cpp
)

target_link_libraries(lab2_v10 PRIVATE mersenne_lib)

enable_testing()
add_subdirectory(tests)
