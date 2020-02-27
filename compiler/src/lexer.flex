%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}


DIGIT [0-9]

LETTER [A-Za-z]

DECIMAL {DIGIT}+"."?{DIGIT}*


DATA_TYPE_INT "int"

//DATA_TYPE_DOUBLE "double"

//DATA_TYPE_FLOAT "float"

//DATA_TYPE_CHARACTER "char"

//DATA_TYPE_UNSIGNED "unsigned"

DATA_TYPE {DATA_TYPE_INT} //| {DATA_TYPE_DOUBLE} | {DATA_TYPE_FLOAT} | {DATA_TYPE_CHARACTER} | {DATA_TYPE_UNSIGNED}


IDENTIFIER_NAME ({LETTER} | "_")({LETTER} | "_" | {DIGIT})*

FUNCTION_DECLARATION {DATA_TYPE}" "{IDENTIFIER_NAME}"("({DATA_TYPE}" "{IDENTIFIER_NAME}",")*({DATA_TYPE}" "{IDENTIFIER_NAME})")"

CODE_SPACES [ \t\r\n]+

%%

"{"                 { return OPERATOR_OPEN_SCOPE; }
"}"                 { return OPERATOR_CLOSE_SCOPE; }

"*"                 { return ARITHMETIC_OPERATOR_TIMES; }
"+"                 { return ARITHMETIC_OPERATOR_PLUS; }
"-"                 { return ARITHMETIC_OPERATOR_MINUS; }
"="                 { return ARITHMETIC_OPERATOR_EQUALS; }
//"/"                 { return ARITHMETIC_OPERATOR_DIVIDE; }
//"\^"                { return ARITHMETIC_OPERATOR_EXPONENT; }

"<"                 { return LOGICAL_OPERATOR_LOWER_THAN; }
"=="                { return LOGICAL_OPERATOR_EQUALS; }

"("                 { return OPERATOR_LBRACKET; }
")"                 { return OPERATOR_RBRACKET; }



{DECIMAL}           {
                        yylval.number = strtod(yytext, 0);
                        return T_NUMBER;
                    }

{IDENTIFIER_NAME}   {
                        yylval.string = new std::string(yytext);
                        return T_VARIABLE;
                    }

{CODE_SPACES}       {;}

.                   {
                        fprintf(stderr, "Invalid token\n");
                        exit(1);
                    }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
