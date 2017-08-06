cmake_minimum_required(VERSION 3.7)
project(uGame)
add_definitions(-D_OS_UNIX)
add_definitions(-D_DEBUG)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)
set(SOURCE_FILES src/main.cpp src/utils/Utils.cpp include/utils/Utils.h include/Constants.h src/utils/Logger.cpp include/utils/Logger.h src/core/Application.cpp include/core/Application.h src/core/AssetsManager.cpp include/core/AssetsManager.h src/core/PackageStream.cpp include/core/PackageStream.h src/utils/MD5.cpp include/utils/MD5.h)
add_executable(uGame ${SOURCE_FILES})