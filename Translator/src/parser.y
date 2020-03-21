%code requires{
	#include "AST.h"

	extern const Node *g_root;

	 //declaring lex generated functions to fix possible issues as provided in 2-parser CW
	int yylex(void);
  	void yyerror(const char *);
}

%union {
	const Node * nodePtr;
	std::string * string; //for direct inputs like CONSTANT, IDENTIFIER or VOID?
	unsigned char symbol;
}

%nterm <nodePtr> primary_expression postfix_expression argument_expression_list unary_expression
%nterm <nodePtr> multiplicative_expression additive_expression relational_expression equality_expression
%nterm <nodePtr> logical_and_expression logical_or_expression assignment_expression declaration
%nterm <nodePtr> direct_declarator parameter_list parameter_declaration statement statement_list
%nterm <nodePtr> compound_statement selection_statement iteration_statement jump_statement
%nterm <nodePtr> translation_unit external_declaration function_definition
%nterm <nodePtr> open_statement closed_statement
%type <string> IDENTIFIER CONSTANT VOID INT type_specifier
%type <symbol> '-' '*' '+' '<' '='

%token IDENTIFIER CONSTANT
%token EQ_OP
%token AND_OP OR_OP

%token INT VOID

%token IF ELSE WHILE RETURN

%start root
%%

primary_expression
	: IDENTIFIER												{ $$ = new Primitive(*$1); }
	| CONSTANT													{ $$ = new Primitive(*$1); }
	| '(' assignment_expression ')'								{ $$ = $2; }
	;

postfix_expression
	: primary_expression										{ $$ = $1;} //pass as variable
	| postfix_expression '(' ')'										 //WHAT
	| postfix_expression '(' argument_expression_list ')' 				 // WHAT
	;

argument_expression_list
	: assignment_expression										{ $$ = new paramList($1); }
	| argument_expression_list ',' assignment_expression		{ $$->add($3); }
	;

unary_expression
	: postfix_expression										{ $$ = $1; }
	| '-' unary_expression										{ $$ = new Unary("-", $2); }
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
	| equality_expression EQ_OP relational_expression			{ $$ = new Operator($1, "==", $3); }
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
	| unary_expression '=' assignment_expression				{ $$ = new Assignment($1, $3); }
	;

declaration // always int so no need to pass type_specifier, python doesnt care anyways
	: type_specifier direct_declarator ';'						{ $$ = new VarDeclarator($2); }
	| type_specifier direct_declarator '=' assignment_expression{ $$ = new VarDeclarator($2, $4); }
	;

type_specifier
	: VOID														{ $$ = $1; } // pass on "void"
	| INT 														{ $$ = $1; }// pass on "int" both for feature selections stmt
	;

direct_declarator
	: IDENTIFIER 												{ $$ = new Primitive(*$1); }
	| direct_declarator '(' parameter_list ')'					{ $$ = new FnDeclarator($1, $3); }
	| direct_declarator '(' ')'									{ $$ = new FnDeclarator($1); }
	;

parameter_list	//list
	: parameter_declaration										{ $$ = new paramList($1);}
	| parameter_list ',' parameter_declaration					{ $$->add($3); }
	;

parameter_declaration //always int so no need to pass type_specifier
	: type_specifier direct_declarator							{ $$ = new FnParameter($2); }
	;

statement
	//: compound_statement										{ $$ = $1; }
	: selection_statement										{ $$ = $1; }
	| iteration_statement										{ $$ = $1; }
	| jump_statement											{ $$ = $1; }
	;

compound_statement //now also expression_statement
	: '{' statement_list '}'									{ $$ = new Compound($2); }
	| assignment_expression ';'									{ nodePtr tmp = new paramList($1); $$ = new Compound(tmp); delete tmp; }
	;

statement_list //list
	: statement 												{ $$ = new statementList($1); }
	| statement_list statement 									{ $$->add($2); }
	;

selection_statement
	: open_statement { $$ = $1; }
	| closed_statement { $$ = $1; }
	;

open_statement
	: IF '(' assignment_expression ')' selection_statement 		{ $$ = new Selection($3, $5); }
	| IF '(' assignment_expression ')' closed_statement ELSE open_statement { $$ = new Selection($3, $5, $7); }
	
closed_statement
	: compound_statement										{ $$ = $1; }
	| IF '(' assignment_expression ')' closed_statement ELSE closed_statement { $$ = new Selection($3, $5, $7); }

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

function_definition // type specifier does not matter since always "def " decleration in python
	: type_specifier direct_declarator compound_statement       { $$ = new FnDefinition($2, $3); }
	;

root : translation_unit											{ g_root = $1; }

%%
const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=NULL;
  yyparse();
  return g_root;
}