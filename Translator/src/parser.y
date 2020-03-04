%code requires{
	#include "AST.h"
	#include <list>

	extern const ASTNode* root;
}

%union {
	const Node * nodePtr;
	std::string* str; //for direct inputs like CONSTANT, IDENTIFIER or VOID?
}

%type <nodePtr> //list all nodes

%token IDENTIFIER CONSTANT
%token EQ_OP
%token AND_OP OR_OP

%token INT VOID

%token IF ELSE WHILE RETURN

%start translation_unit
%%

primary_expression
	: IDENTIFIER												{ $$ = new Primitive($1); }
	| CONSTANT													{ $$ = new Primitive($1); }
	| '(' assignment_expression ')'								{ $$ = $2; }
	;

postfix_expression
	: primary_expression										{ $$ = $1;} //pass as variable
	| postfix_expression '(' ')'										//new function with no input arguments
	| postfix_expression '(' argument_expression_list ')' 				//new function with input arguments
	;

argument_expression_list
	: assignment_expression										{ $$ = new std::list<nodePtr>; $$.push_back($1);}
	| argument_expression_list ',' assignment_expression		{ $1.push_back($3); $$ = $1; }
	;

unary_expression
	: postfix_expression										{ $$ = $1; }
	| '-' unary_expression										{ $$ = new Unary($1, $2); }
	;

multiplicative_expression
	: unary_expression											{ $$ = $1; }
	| multiplicative_expression '*' unary_expression			{ $$ = new Operator($1, $2, $3); }
	;

additive_expression
	: multiplicative_expression									{ $$ = $1; }
	| additive_expression '+' multiplicative_expression			{ $$ = new Operator($1, $2, $3); }
	| additive_expression '-' multiplicative_expression			{ $$ = new Operator($1, $2, $3); }
	;

relational_expression
	: additive_expression										{ $$ = $1; }
	| relational_expression '<' additive_expression				{ $$ = new Operator($1, $2, $3); }
	;

equality_expression
	: relational_expression										{ $$ = $1; }
	| equality_expression EQ_OP relational_expression			{ $$ = new Operator($1, $2, $3); }
	;

logical_and_expression
	: equality_expression										{ $$ = $1; }
	| logical_and_expression AND_OP equality_expression			{ $$ = new Operator($1, "and", $3); }
	;

logical_or_expression
	: logical_and_expression									{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression		{ $$ = new Operator($1, "or", $3); }
	;

assignment_expression
	: logical_or_expression										{ $$ = $1; }
	| unary_expression '=' assignment_expression				// new assignment expression
	;

declaration
	//: VOID and INT seperately instead of using type_specifier
	//to allow direct assignment of variable / function decleration
	// put direct_declerator in here instead
	: type_specifier direct_declarator ';'						{ $$ = new varDecleration($2); } // implement
	| type_specifier direct_declarator '=' assignment_expression{ $$ = new varDecleration($2, $4); }
	;

type_specifier
	: VOID														// pass on "void"
	| INT 														// pass on "int" both for feature selections stmt
	;

direct_declarator
	: IDENTIFIER 												{ $$ = new Primitive($1); }
	| direct_declarator '(' parameter_list ')'					{ $$ = new fnDeclerator($1, $2); } //implement
	| direct_declarator '(' ')'									{ $$ = new fnDeclerator($1, $2); }
	;

parameter_list	//list
	: parameter_declaration										{ $$ = new std::list<nodePtr>; $$.push_back($1);}
	| parameter_list ',' parameter_declaration					{ $1.push_back($3); $$ = $1; }
	;

parameter_declaration
	: type_specifier direct_declarator							// not really needed, decelration above
	| type_specifier											// invalid
	;

statement
	: compound_statement										{ $$ = $1; }
	| expression_statement										{ $$ = $1; }
	| selection_statement										{ $$ = $1; }
	| iteration_statement										{ $$ = $1; }
	| jump_statement											{ $$ = $1; }
	;

compound_statement
	: '{' statement_list '}'									{ $$ = new compound($2); } //implement for indent;
	;

statement_list //list
	: statement 												{ $$ = new std::list<nodePtr>; $$.push_back($1);}
	| statement_list statement 									{ $1.push_back($2); $$ = $1; }
	;

expression_statement
	: ';'														{ $$ = NULL; } //?
	| assignment_expression ';'									{ $$ = $1; }
	;

selection_statement
	: IF '(' assignment_expression ')' statement 				{ $$ = new Selection($3, $5); }
	| IF '(' assignment_expression ')' statement ELSE statement { $$ = new Selection($3, $5, $7); }
	;

iteration_statement
	: WHILE '(' assignment_expression ')' statement 			{ $$ = new Iteration($3, $5); }		
	;

jump_statement
	: RETURN ';'												{ $$ = new Jump(NULL); }
	| RETURN assignment_expression ';'							{ $$ = new Jump($2); }
	;

translation_unit //list
	: external_declaration										{ $$ = $1; }
	| translation_unit external_declaration						{ $$ = $1; }
	;

external_declaration
	: function_definition										{ $$ = $1; }
	| declaration												{ $$ = $1; }
	;

function_definition
	: type_specifier direct_declarator compound_statement       { $$ = new fnDefinition($1, $2, $3); } //implement
	;

%%

//see 2-parser

//LINKS
// + Linked lists: https://stackoverflow.com/questions/31513730/building-a-linked-list-in-yacc-with-left-recursive-grammar