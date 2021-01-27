cmake_minimum_required(VERSION 3.17)
project(word_count)

set(CMAKE_CXX_STANDARD 14)

add_executable(word_count main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")