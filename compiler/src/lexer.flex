D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
// As in Lab: Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

//for debugging in VSstudio
//#define YY_NO_UNISTD_H

// To get rid of register warning for c++=17
// #if (__cplusplus - 0) >= 201703L
//   #define __REGISTER
// #else
//   #define __REGISTER                             register
// #endif

#include "parser.tab.hpp"
#include <stdio.h>

%}

%%

"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"return"		{ return(RETURN); }
"short"			{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"while"			{ return(WHILE); }

0[xX]{H}+{IS}?		{ return(CONSTANT); }
0{D}+{IS}?			{ return(CONSTANT); }
{D}+{IS}?			{ return(CONSTANT); }
L?'(\\.|[^\\'])+'	{ return(CONSTANT); }

{D}+{E}{FS}?			{ return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	{ return(STRING_LITERAL); }

">>="			|
"<<="			|
"+="			|
"-="			|
"*="			|
"/="			|
"%="			|
"&="			|
"^="			|
"|="			{ return(ASSIGN); }

">>"			{ return(RIGHT_OP); }
"<<"			{ return(LEFT_OP); }
"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }

("{"|"<%")		{ return('{'); }
("}"|"%>")		{ return('}'); }
("["|"<:")		{ return('['); }
("]"|":>")		{ return(']'); }

";"				|
","				|
":"				|
"="				|
"("				|
")"				|
"."				|
"&"				|
"!"				|
"~"				|
"-"				|
"+"				|
"*"				|
"/"				|
"%"				|
"<"				|
">"				|
"^"				|
"|"				|
"?"				{ return yytext[0]; }

[ \t\v\n\f]		{ ; }
.				{ fprintf (stderr, "Invalid token: %s\n", yytext); exit(1); }

%%

// Matching parser.y top
void yyerror (char const *s)
{
  fprintf (stderr, "Flex error : %s\n", s);
  exit(1);
}