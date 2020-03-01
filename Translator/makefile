CPPFLAGS = -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include


lexer: src/lexer.flex
	flex -o src/lexer.yy.cpp src/lexer.flex

parser:
	bison -v -d src/parser.y -o src/parser.tab.cpp

all: lexer parser
	mkdir -p bin
	rm bin/*

clean:
	rm src/*.o
	rm bin/*
