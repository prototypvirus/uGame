cmake_minimum_required(VERSION 3.7)
project(uGame)
add_definitions(-D_OS_UNIX)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
set(SOURCE_FILES src/main.cpp src/utils/Utils.cpp include/utils/Utils.h include/Constants.h)
add_executable(uGame ${SOURCE_FILES})