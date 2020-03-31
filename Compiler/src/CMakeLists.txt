# Set the files to be included
file(GLOB_RECURSE COMPILER_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE COMPILER_INC "${CMAKE_SOURCE_DIR}/include/*.h")
set(SRC_PARSER
	parser.tab.cpp
	parser.tab.hpp
	lexer.yy.cpp
)


# Add both source and headers to the executable
add_executable(compiler ${COMPILER_SRC} ${COMPILER_INC} main.cpp ${SRC_PARSER}) 

target_include_directories(compiler PUBLIC "${CMAKE_SOURCE_DIR}/include")


# This requires c++ 14
#target_compile_features(compiler PUBLIC cxx_std_14)
