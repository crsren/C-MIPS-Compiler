
all : parser lexer

parser : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

lexer : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex


clean :
	rm -f src/*.tab.cpp src/*.yy.cpp src/*.output
