cmake_minimum_required(VERSION 3.17)
project(word_count)

set(CMAKE_CXX_STANDARD 17)

add_executable(word_count main.cpp WordCounter.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")