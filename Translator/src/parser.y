%code requires{
	#include "ast.hpp"
}

%token IDENTIFIER CONSTANT
%token EQ_OP
%token AND_OP OR_OP

%token INT VOID

%token IF ELSE WHILE RETURN

%start translation_unit
%%

primary_expression
	: IDENTIFIER									{ $$ = new Identifier($1); }
	| CONSTANT										{ $$ = new Constant($1); }
	| '(' assignment_expression ')'							{ $$ = $2 }
	;

postfix_expression
	: primary_expression
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| unary_operator unary_expression
	;

unary_operator
	| '+' //dont need (deleted "*")
	| '-'
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression
	;

additive_expression
	: multiplicative_expression									{ $$ = $1; }
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

relational_expression
	: additive_expression
	| relational_expression '<' additive_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	;

logical_and_expression
	: equality_expression
	| logical_and_expression AND_OP equality_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

assignment_expression
	: logical_or_expression
	| unary_expression '=' assignment_expression
	;

declaration
	| declaration_specifiers init_declarator ';'
	;

declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| CONSTANT
	| CONSTANT declaration_specifiers
	;

init_declarator
	: direct_declarator
	| direct_declarator '=' assignment_expression
	;

type_specifier
	: VOID
	| INT
	;

IDENTIFIER
	: IDENTIFIER
	| IDENTIFIER ',' IDENTIFIER
	;

direct_declarator
	: IDENTIFIER
	| '(' direct_declarator ')'
	| direct_declarator '(' IDENTIFIER ')'
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' ')'
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers direct_declarator
	| declaration_specifiers direct_abstract_declarator
	| declaration_specifiers
	;

statement
	: compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

compound_statement
	| '{' statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| assignment_expression ';'
	;

selection_statement
	: IF '(' assignment_expression ')' statement
	| IF '(' assignment_expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' assignment_expression ')' statement
	;

jump_statement
	| RETURN ';'
	| RETURN assignment_expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers direct_declarator declaration_list compound_statement
	| declaration_specifiers direct_declarator compound_statement
	| direct_declarator declaration_list compound_statement
	| direct_declarator compound_statement
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
