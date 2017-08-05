cmake_minimum_required(VERSION 3.7)
project(uGame)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
set(SOURCE_FILES src/main.cpp)
add_executable(uGame ${SOURCE_FILES})