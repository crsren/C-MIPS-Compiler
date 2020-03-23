CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/translator

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/translator : src/main.cpp src/parser.tab.cpp src/parser.tab.hpp src/lexer.yy.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o $@ $^


clean :
	rm -rf bin
	rm src/*.tab.cpp
	rm src/*.yy.cpp
