CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : lexer parser

parser : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

lexer : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex


clean :
	rm -rf bin
	rm src/*.tab.cpp
	rm src/*.yy.cpp
