cmake_minimum_required(VERSION 3.1...3.15)

# set the project name
project(BabaYaga-Compiler VERSION 1.0 LANGUAGES CXX)


# Add the subdirectory containing the source code
add_subdirectory(src)


# Appending flags to CMake variables to remove flex register warning
#add_definitions("-Wno-deprecated-register")
#list(APPEND flags "-Wno-deprecated-register")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")

