CC := g++ # this is the main compiler
# CC := clang --analyze # and comment out the linker last line

CFLAGS := -g -Wall -Wextra -Wpedantic -std=c++11 -Wno-c++11-extensions

COMPINC := -Icompiler/include
COMPBUILDDIR := compiler/build
COMPSRCDIR := compiler/src

all : bin/compiler

# Make the parser
bin/compiler:	$(COMPBUILDDIR)/main.o $(COMPBUILDDIR)/helpers.o $(COMPBUILDDIR)/mips.o $(COMPBUILDDIR)/node.o $(COMPBUILDDIR)/standard_list.o $(COMPBUILDDIR)/topLevel.o \

		$(COMPBUILDDIR)/Context/bindings.o \

		$(COMPBUILDDIR)/Declarations/declarators.o \

		$(COMPBUILDDIR)/Expressions/arithmetic_operation.o $(COMPBUILDDIR)/Expressions/bool_operation.o $(COMPBUILDDIR)/Expressions/assignment.o \

		$(COMPBUILDDIR)/Function/fn_call.o $(COMPBUILDDIR)/Function/fn_declarator.o $(COMPBUILDDIR)/Function/fn_definition.o \

		$(COMPBUILDDIR)/Statements/compound.o $(COMPBUILDDIR)/Statements/for.o $(COMPBUILDDIR)/Statements/if_else.o \
		$(COMPBUILDDIR)/Statements/jump.o $(COMPBUILDDIR)/Statements/switch.o $(COMPBUILDDIR)/Statements/while.o \

	@echo "Linking..."
	@echo " mkdir -p bin"; mkdir -p bin
	@echo " $(CC) $^ -o $@"; $(CC) $^ -o $@

$(COMPBUILDDIR)/%.o : $(COMPSRCDIR)/%.cpp
	@echo "Building sources..."
	@echo " mkdir -p $(COMPBUILDDIR)"; mkdir -p $(COMPBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<"; $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<

$(COMPBUILDDIR)/%.yy.o : $(COMPSRCDIR)/%.yy.cpp
	@echo "Building lex..."
	@echo " mkdir -p $(COMPBUILDDIR)"; mkdir -p $(COMPBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<"; $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<

$(COMPBUILDDIR)/parser.tab.o : $(COMPSRCDIR)/parser.tab.cpp
	@echo "Building yacc..."
	@echo " mkdir -p $(COMPBUILDDIR)"; mkdir -p $(COMPBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<"; $(CC) $(CFLAGS) $(COMPINC) -c -o $@ $<

$(COMPSRCDIR)/lexer.yy.cpp : $(COMPSRCDIR)/lexer.flex
	@echo "Creating lex..."
	@echo " flex -o $@  $<"; flex -o $@  $<

$(COMPSRCDIR)/parser.tab.cpp $(COMPSRCDIR)/parser.tab.hpp : $(COMPSRCDIR)/parser.y
	@echo "Creating yacc..."
	@echo " bison -v -d $< -o $(COMPSRCDIR)/parser.tab.cpp"; bison -v -d $< -o $(COMPSRCDIR)/parser.tab.cpp

clean :
	@echo "Cleaning..."
	rm -rf bin
	rm -rf $(LEXBUILDDIR)
	rm -f $(LEXSRCDIR)/lexer.yy.cpp
	rm -rf $(PARBUILDDIR)
	rm -f $(PARSRCDIR)/lexer.yy.cpp
	rm -f $(PARSRCDIR)/parser.tab.cpp
	rm -f $(PARSRCDIR)/parser.tab.hpp
	rm -f $(PARSRCDIR)/parser.output
	rm -rf $(COMPBUILDDIR)
	rm -f $(COMPSRCDIR)/lexer.yy.cpp
	rm -f $(COMPSRCDIR)/parser.tab.cpp
	rm -f $(COMPSRCDIR)/parser.tab.hpp
	rm -f $(COMPSRCDIR)/parser.output

.PHONY : clean
