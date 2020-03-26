# Set the files to be included
file(GLOB_RECURSE SRC_TRANS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE INCLUDE_TRANS "${CMAKE_SOURCE_DIR}/include/*.h")
set(SRC_PARSER
	parser.tab.cpp
	parser.tab.hpp
	lexer.yy.cpp
)


# Add both source and headers to the executable
add_executable(translator ${SRC_TRANS} ${INCLUDE_TRANS} main.cpp ${SRC_PARSER}) 

target_include_directories(translator PUBLIC "${CMAKE_SOURCE_DIR}/include")


# This requires c++ 14
target_compile_features(translator PUBLIC cxx_std_14)
