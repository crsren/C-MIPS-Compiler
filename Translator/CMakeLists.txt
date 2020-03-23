cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
	message("You are running a version of cmake older than 3.12, please update!")
endif()

# set the project name
project(ChrisCompiler VERSION 1.0 LANGUAGES CXX)


# Add the subdirectory containing the source code
add_subdirectory(src)
