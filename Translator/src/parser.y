%code requires{
	//#include "ast.hpp"
}

%token IDENTIFIER CONSTANT
%token EQ_OP
%token AND_OP OR_OP

%token INT VOID

%token IF ELSE WHILE RETURN

%start translation_unit
%%

primary_expression
	: IDENTIFIER									//{ $$ = new Identifier($1); }
	| CONSTANT										//{ $$ = new Constant($1); }
	| '(' assignment_expression ')'							//{ $$ = $2 }
	;

postfix_expression
	: primary_expression
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	;

argument_expression_list	//list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| unary_operator unary_expression
	;

unary_operator
	: '+' //dont need (deleted "*")
	| '-'
	;

multiplicative_expression
	: unary_expression											{ $$ = $1; }
	| multiplicative_expression '*' unary_expression
	;

additive_expression
	: multiplicative_expression									{ $$ = $1; }
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

relational_expression
	: additive_expression										{ $$ = $1; }
	| relational_expression '<' additive_expression
	;

equality_expression
	: relational_expression										{ $$ = $1; }
	| equality_expression EQ_OP relational_expression
	;

logical_and_expression
	: equality_expression										{ $$ = $1; }
	| logical_and_expression AND_OP equality_expression
	;

logical_or_expression
	: logical_and_expression									{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression
	;

assignment_expression
	: logical_or_expression										{ $$ = $1; }
	| unary_expression '=' assignment_expression
	;

declaration
	: type_specifier init_declarator ';'
	;

init_declarator
	: direct_declarator											{ $$ = $1; }
	| direct_declarator '=' assignment_expression
	;

type_specifier
	: VOID
	| INT
	;

direct_declarator
	: IDENTIFIER
	| '(' direct_declarator ')'									{ $$ = $2; }
	| direct_declarator '(' IDENTIFIER ')'					// new function
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' ')'
	;

parameter_list	//list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: type_specifier direct_declarator							// declare fn / var
	| type_specifier											// how valid w/o any identifier?
	;

statement
	: compound_statement										{ $$ = $1; }
	| expression_statement										{ $$ = $1; }
	| selection_statement										{ $$ = $1; }
	| iteration_statement										{ $$ = $1; }
	| jump_statement											{ $$ = $1; }
	;

compound_statement
	: '{' statement_list '}'									{ $$ = $2; }
	;

statement_list //list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'														{ $$ = NULL; } //?
	| assignment_expression ';'									{ $$ = $1; }
	;

selection_statement
	: IF '(' assignment_expression ')' statement 								// new selection statement
	| IF '(' assignment_expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' assignment_expression ')' statement
	;

jump_statement
	: RETURN ';'
	| RETURN assignment_expression ';'
	;

translation_unit //list
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition										{ $$ = $1; }
	| declaration												{ $$ = $1; }
	;

function_definition
	: type_specifier direct_declarator compound_statement       // new function
	| direct_declarator compound_statement						// how is this valid? redefinition of function?
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
