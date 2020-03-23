%option noyywrap
%option never-interactive

%{
  //#define YY_NO_UNISTD_H

// To get rid of register warning for c++=17
#if (__cplusplus - 0) >= 201703L
  #define __REGISTER
#else
  #define __REGISTER                             register
#endif
  #include "parser.tab.hpp"
%}

%%

"void"	  	            { return VOID; }
"int"		  	            { return INT; }
"if"			              { return IF; }
"else"		              { return ELSE; }
"while"		              { return WHILE; }
"return"		            { return RETURN; }

[0]|[1-9][0-9]* 				{ yylval.str = new std::string(yytext); return CONSTANT; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = new std::string(yytext); return IDENTIFIER; }


"&&"			              { return AND_OP; }
"||"			              { return OR_OP; }
"=="			              { return EQ_OP; }


"+"                     |              
"-"                     |              
"*"                     |              
"="	                    |              
"<"				              |              
"("                     |              
")"                     |              
"{"                     |              
"}"                     |              
";"				              |              
","                     { return yytext[0]; }


[ \t\r\n]+		{;}

.                       { fprintf (stderr, "Invalid token: %s\n", yytext); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex error : %s\n", s);
  exit(1);
}

