%option noyywrap

%{
#include "lexer.hpp"
%}

%%

int			{ return INT; }
void 		{ return VOID; }
/* main !!*/
if			{ return IF; }
else		{ return ELSE; }
while		{ return WHILE; }
return		{ return RETURN; }

[*]             { return '*'; }
[+]             { return '+'; }
[-]             { return '-'; }

[&&]			{ return AND_OP; }
[||]			{ return OR_OP; }
[<]				{ return '<'; }
[==]			{ return EQ_OP; }
[=]				{ return '='; }

[(]             { return '('; }
[)]             { return ')'; }
[{]             { return '{'; }
[}]             { return '}'; }

[;]				{ return ';'; }

[0]|[1-9][0-9]+ 				{ return CONSTANT; }
[a-zA-Z_][a-zA-Z0-9_]*          { return IDENTIFIER; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

