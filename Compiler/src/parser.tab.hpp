/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y" /* yacc.c:1909  */

	#include "topLevel.h"
	#include <string>

	//matched below context-free grammar
	 extern const Node *g_root;
	 extern FILE *yyin; // Lexer input file

	int yylex(void);
  	void yyerror(const char *);

#line 56 "src/parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    CONSTANT = 259,
    STRING_LITERAL = 260,
    SIZEOF = 261,
    PTR_OP = 262,
    INC_OP = 263,
    DEC_OP = 264,
    LEFT_OP = 265,
    RIGHT_OP = 266,
    LE_OP = 267,
    GE_OP = 268,
    EQ_OP = 269,
    NE_OP = 270,
    AND_OP = 271,
    OR_OP = 272,
    ASSIGN = 273,
    TYPE_NAME = 274,
    TYPEDEF = 275,
    STATIC = 276,
    CHAR = 277,
    SHORT = 278,
    INT = 279,
    LONG = 280,
    SIGNED = 281,
    UNSIGNED = 282,
    FLOAT = 283,
    DOUBLE = 284,
    CONST = 285,
    VOID = 286,
    CASE = 287,
    DEFAULT = 288,
    IF = 289,
    ELSE = 290,
    SWITCH = 291,
    WHILE = 292,
    DO = 293,
    FOR = 294,
    GOTO = 295,
    CONTINUE = 296,
    BREAK = 297,
    RETURN = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "src/parser.y" /* yacc.c:1909  */

	std::string * str;
	double num;

	List * listPtr; // not const to allow adding items
	ParameterList * paramListPtr;
	InitDeclaratorList * initDeclaratorListPtr;

	const Node * nodePtr;
	const Declarator* declaratorPtr;
	InitDeclarator * initDeclaratorPtr; // not const since type is set later
	const ParameterDeclaration * paramDeclPtr;
	//const Identifier * identifierPtr;

#line 127 "src/parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
