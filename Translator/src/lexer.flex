%option noyywrap
%option never-interactive

%{
  #include "parser.tab.hpp"
  #define YY_NO_UNISTD_H
%}

%%

int		  	              { fprintf(stderr, "int\n"); return INT; }
void 	  	              { return VOID; }
if			                { return IF; }
else		                { return ELSE; }
while		                { return WHILE; }
return		              { return RETURN; }

"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }

"&&"			              { return AND_OP; }
"||"			              { return OR_OP; }
"<"				              { return '<'; }
"=="			              { return EQ_OP; }
"="				              { return '='; }

"("                     { return '('; }
")"                     { return ')'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
";"				              { fprintf(stderr, "semiclon\n"); return ';'; }

[0]|[1-9][0-9]+ 				{ fprintf(stderr, "constant\n"); return CONSTANT; }
[a-zA-Z_][a-zA-Z0-9_]*  { return IDENTIFIER; }

[ \t\r\n]+		{;}

.             { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

