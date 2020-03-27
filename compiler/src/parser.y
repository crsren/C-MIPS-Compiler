%code requires{
	#include "topLevel.h"

	//matched below context-free grammar
	 const Node *g_root;
	 FILE *yyin; // Lexer input file

	 //declaring lex generated functions to fix possible issues as provided in 2-parser CW
	int yylex(void);
  	void yyerror(const char *);
}
// Possible type that symbols can take on
%union{
	Node* nodePtr;
	std::string* str;
	
}

%define parse.error verbose //For debugging

//// Symbol definitions ---------------------------------------------------------------
/// Lexer tokens ----------------------------------------------------------------------
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP ASSIGN     
%token TYPE_NAME
%token TYPEDEF  STATIC 
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST  VOID
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

// To avoid dangling else problem
%nonassoc ')'
%nonassoc ELSE

/// Symbol types -----------------------------------------------------------------------
// Define type of terminal & non-terminal symbols
//%type <> ...
//$nterm <> for exclusively non-terminal symbols

// Terminals (from lexer) IDENTIFIER, CONSTANT STRING_LITERAL
// Expressions
// Statements
// Declarations
// (List)

%start g_root
%%

// Grammar based on Jeff Lee's ANSI C Yacc grammar 
// https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

//// Expressions -----------------------------------------------------------------

primary_expression
	: IDENTIFIER 												{ $$ = new Identifier(*$1); }
	| CONSTANT 													{ $$ = new Constant($1); }
	| STRING_LITERAL			 								{ fprintf(stderr, "\n STRING_LITERAL not implemented\n"); }
	| '(' expression ')' 										{ $$ = $2; }
	;

postfix_expression
	: primary_expression 										{ $$ = $1; }
	| postfix_expression '[' expression ']'			 			{ fprintf(stderr, "\n ARRAY ACCESS not implemented\n"); }
	| postfix_expression '(' ')'								{ $$ = new fnCall($1); }
	| postfix_expression '(' argument_expression_list ')'		{ $$ = new fnCall($1, $3); }
	//| postfix_expression '.' IDENTIFIER
	//| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP 								{ $$ = new postOperation("+", $2); }	
	| postfix_expression DEC_OP 								{ $$ = new postOperation("-", $2); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression 		 								{ $$ = $1; }								
	| INC_OP unary_expression 									{ $$ = new preOperation("+", $2); }
	| DEC_OP unary_expression 									{ $$ = new preOperation("-",$2); }
	| unary_operator cast_expression			 				{ fprintf(stderr, "\n UNARY_OPERATOR not implemented\n"); }
	| SIZEOF unary_expression			 						{ fprintf(stderr, "\n SIZEOF not implemented\n"); }
	| SIZEOF '(' type_name ')'			 						{ fprintf(stderr, "\n SIZEOF not implemented\n"); }
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression  										{ $$ = $1; }
	//| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression 											{ $$ = $1; }					
	| multiplicative_expression '*' cast_expression 			{ $$ = new ArithmeticOperation($1,"*", $3); }
	| multiplicative_expression '/' cast_expression 			{ $$ = new ArithmeticOperation($1, "/", $3); }
	| multiplicative_expression '%' cast_expression 			{ $$ = new ArithmeticOperation($1, "%", $3); }
	;

additive_expression
	: multiplicative_expression 								{ $$ = $1; }
	| additive_expression '+' multiplicative_expression 		{ $$ = new ArithmeticOperation($1, "+", $3); }
	| additive_expression '-' multiplicative_expression 		{ $$ = new ArithmeticOperation($1, "-", $3); }
	;

shift_expression
	: additive_expression 										{ $$ = $1; }
	| shift_expression LEFT_OP additive_expression 				{ $$ = new BitwiseOperation($1, "<<", $3); }
	| shift_expression RIGHT_OP additive_expression 			{ $$ = new BitwiseOperation($1, ">>", $3); }
	;

relational_expression
	: shift_expression 											{ $$ = $1; }
	| relational_expression '<' shift_expression 				{ $$ = new BooleanOperation($1, "<", $3); }
	| relational_expression '>' shift_expression 				{ $$ = new BooleanOperation($1, ">", $3); }
	| relational_expression LE_OP shift_expression				{ $$ = new BooleanOperation($1, "<=", $3); } 				
	| relational_expression GE_OP shift_expression				{ $$ = new BooleanOperation($1, ">=", $3); }
	;

equality_expression
	: relational_expression 									{ $$ = $1; }
	| equality_expression EQ_OP relational_expression			{ $$ = new BooleanOperation($1, "==", $3); }
	| equality_expression NE_OP relational_expression			{ $$ = new BooleanOperation($1, "!=", $3); }
	;

and_expression
	: equality_expression 										{ $$ = $1; }
	| and_expression '&' equality_expression 					{ $$ = new BitwiseOperation($1, "&", $3); }
	;

exclusive_or_expression
	: and_expression 		 									{ $$ = $1; }
	| exclusive_or_expression '^' and_expression 				{ $$ = new BitwiseOperation($1, "^", $3); }
	;

inclusive_or_expression
	: exclusive_or_expression 									{ $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression 		{ $$ = new BitwiseOperation($1, "|", $3); }
	;

logical_and_expression
	: inclusive_or_expression 									{ $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression		{ fprintf(stderr, "\n LOGICAL_AND_EXPRESSION not implemented\n"); }
	;

logical_or_expression
	: logical_and_expression									{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression		{ fprintf(stderr, "\n LOGICAL_OR_EXPRESSION not implemented\n"); }
	;

//https://en.cppreference.com/w/c/language/operator_other#Conditional_operator
conditional_expression
	: logical_or_expression										{ $$ = $1; }
	//| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression									{ $$ = $1; }
	| unary_expression '=' assignment_expression 				{ $$ = new AssignmentExpression($1, $3); }

	// middle will be assignment string ("*=")
	// → remove last char ("=") and use BinaryOperation
	| unary_expression ASSIGN assignment_expression 			{ $2[strlen(p)-1]='\0';
																$$ = new AssignmentExpression($1, new ArithmeticOperation($1, *$2, $3)); }
	;

expression
	: assignment_expression										{ $$ = $1; }

//f (a, "(t=3, t+2)", c)
	//| expression ',' assignment_expression
	;

constant_expression //dont really need this
	: conditional_expression									{ $$ = $1; }
	;

//// Initialization ---------------------------------------------------------

//https://en.cppreference.com/w/c/language/initialization
initializer
	: assignment_expression										{ $$ = $1; }

////initializer list "vector<in> v{1,2,3}"
	//| '{' initializer_list '}'
	//| '{' initializer_list ',' '}'
	;

// initializer_list
// 	: initializer
// 	| initializer_list ',' initializer
// 	;


// storage_class_specifier
// 	: TYPEDEF
// 	| STATIC
// 	;

//!
type_specifier
	: VOID
	| CHAR			 		            						{ fprintf(stderr, "\n CHAR not implemented\n"); }
	| SHORT		            	 								{ fprintf(stderr, "\n SHORT not implemented\n"); }
	| INT
	| LONG			 	            							{ fprintf(stderr, "\n LONG not implemented\n"); }
	| FLOAT		            	 								{ fprintf(stderr, "\n FLOAT not implemented\n"); }
	| DOUBLE		        	 								{ fprintf(stderr, "\n DOUBLE not implemented\n"); }
	//| struct_specifier			 							{ fprintf(stderr, "\nSTRUCT_SPECIFIER not implemented\n"); }
	//| enum_specifier			 								{ fprintf(stderr, "\n ENUM_SPECIFIER not implemented\n"); }
	//| TYPE_NAME			 					        		{ fprintf(stderr, "\n TYPE_NAME not implemented\n"); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| CONST specifier_qualifier_list
	| CONST
	;

// type_qualifier_list //needed in pointer?
// 	: CONST
// 	| type_qualifier_list CONST
// 	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;


identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

//// Declarator -----------------------------------------------------------------

pointer
	: '*'
	//| '*' type_qualifier_list
	| '*' pointer
	//| '*' type_qualifier_list pointer
	;

// abstract_declarator
// 	: pointer
// 	| direct_abstract_declarator
// 	| pointer direct_abstract_declarator
// 	;

// //https://docs.microsoft.com/en-us/cpp/c-language/c-abstract-declarators?view=vs-2019
// direct_abstract_declarator
// 	: '(' abstract_declarator ')'
// 	| '[' ']'
// 	| '[' constant_expression ']'
// 	| direct_abstract_declarator '[' ']'
// 	| direct_abstract_declarator '[' constant_expression ']'
// 	| '(' ')'
// 	| '(' parameter_list ')'
// 	| direct_abstract_declarator '(' ')'
// 	| direct_abstract_declarator '(' parameter_list ')'
// 	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

//https://en.cppreference.com/w/c/language/declarations
//http://c-faq.com/decl/spiral.anderson.html
direct_declarator
	: IDENTIFIER 													// new simple declarator
	| '(' declarator ')' 											{ $$ = $2; }
	| direct_declarator '[' constant_expression ']' 				// new array declarator
	| direct_declarator '[' ']' 									// new array declarator
	| direct_declarator '(' parameter_list ')'						{ $$ = new FnDeclarator($1, $3); }
	// | direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'										{ $$ = new FnDeclarator($1); }
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

//storage-class specifiers
//type specifiers (ie primitive, user-defined)
//type qualifiers (ie are they "modifiable")
declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| CONST
	| CONST declaration_specifiers
	;

//primitive data type variable declaration
//or any user-defined type structure declaration
declaration
	//: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'				{ $$ = new VarDeclaration($1, $2); } //! implement
	;

declaration_list
	: declaration 													{ $$ = new List($1); }
	| declaration_list declaration 									{ $1->add($2); $$ = $1; }
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

/// Statement -----------------------------------------------------------------

//https://docs.microsoft.com/en-us/cpp/c-language/goto-and-labeled-statements-c?view=vs-2019
labeled_statement
    // "stop: <some body>" ; goto stop; 
	: IDENTIFIER ':' statement			 							{ fprintf(stderr, "\n IDENTIFIER not implemented\n"); }
	| CASE constant_expression ':' statement			 			{ fprintf(stderr, "\n CASE not implemented\n"); }
	| DEFAULT ':' statement			 								{ fprintf(stderr, "\n DEFAULT not implemented\n"); }
	;

// C89 does not allow declarations after statements 
// https://stackoverflow.com/questions/6488503/c89-mixing-variable-declarations-and-code
compound_statement
	: '{' '}'
	| '{' statement_list '}'										{ $$ = new CompoundStatement(nullptr, $2); }
	| '{' declaration_list '}'										{ $$ = new CompoundStatement($2, nullptr); }
	| '{' declaration_list statement_list '}'						{ $$ = new CompoundStatement($2, $3); }
	;


statement_list //! not sure if this has to have additional features to list
	: statement 													{ $$ = new List($1); }
	| statement_list statement 										{ $1->add($2); $$ = $1; }
	;

//https://docs.microsoft.com/en-us/cpp/c-language/expression-statement-c?view=vs-2019
expression_statement
	: ';'															{ $$ = NULL; }
	| expression ';'												{ $$ = $1; }
	;

//https://docs.microsoft.com/en-us/cpp/c-language/switch-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/if-statement-c?view=vs-2019
selection_statement
	: IF '(' expression ')' statement 								{ $$ = new SelectionStatement($3, $5); }
	| IF '(' expression ')' statement ELSE statement 				{ $$ = new SelectionStatement($3, $5, $7); }
	| SWITCH '(' expression ')' statement			 			    { fprintf(stderr, "\n SWITCH not implemented\n"); }
	;

//https://docs.microsoft.com/en-us/cpp/c-language/while-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/do-while-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/for-statement-c?view=vs-2019
iteration_statement
	: WHILE '(' expression ')' statement			 								{ fprintf(stderr, "\n WHILE not implemented\n"); }
	| DO statement WHILE '(' expression ')' ';'			 							{ fprintf(stderr, "\n WHILE not implemented\n"); }
	| FOR '(' expression_statement expression_statement ')' statement				{ fprintf(stderr, "\n WHILE not implemented\n"); }
	| FOR '(' expression_statement expression_statement expression ')' statement	{ fprintf(stderr, "\n WHILE not implemented\n"); }
	;

//https://docs.microsoft.com/en-us/cpp/c-language/continue-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/goto-and-labeled-statements-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/break-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/return-statement-c?view=vs-2019
jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'															{ $$ = new ReturnStatement();	}
	| RETURN expression ';'													{ $$ = new ReturnStatement($2); }
	;

statement
	: labeled_statement														{ $$ = $1; }
	| compound_statement													{ $$ = $1; }
	| expression_statement													{ $$ = $1; }
	| selection_statement													{ $$ = $1; }
	| iteration_statement													{ $$ = $1; }
	| jump_statement														{ $$ = $1; }
	;

//// Global & Top Level -----------------------------------------------------------------

//https://docs.microsoft.com/en-us/cpp/c-language/obsolete-forms-of-function-declarations-and-definitions?view=vs-2019
//https://stackoverflow.com/questions/18820751/identifier-list-vs-parameter-type-list-in-c/18820829#18820829
function_definition
	// : declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	// Functions with return type int/int* aren't required to have a declaration
	//| declarator declaration_list compound_statement
	//| declarator compound_statement
	;

 //decarations in global scope
external_declaration
	: function_definition													{ $$ = $1; }
	| declaration															{ $$ = $1; }
	;

translation_unit //top level list
	: external_declaration													{ $$ = new List($1); }
	| translation_unit external_declaration									{ $1->add($3); $$ = $1; }
	;

root: translation_unit														{ g_root = $1; }

%%

// REDUNDANT GRAMMAR:
// parameter_type_list
// ELLIPSE, VOLATILE; EXTERN; AUTO; REGISTER; UNION



//// Later -------------------------------------------------------------
/// Struct -------------------------------------------------------------
// struct_specifier //no union needed
// 	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
// 	| STRUCT '{' struct_declaration_list '}'
// 	| STRUCT IDENTIFIER
// 	;

// struct_declaration_list
// 	: struct_declaration
// 	| struct_declaration_list struct_declaration
// 	;

// struct_declaration
// 	: specifier_qualifier_list struct_declarator_list ';'
// 	;

// struct_declarator_list
// 	: struct_declarator
// 	| struct_declarator_list ',' struct_declarator
// 	;

// struct_declarator
// 	: declarator
// 	| ':' constant_expression
// 	| declarator ':' constant_expression
// 	;


/// Enum -------------------------------------------------------------

// enum_specifier
// 	: ENUM '{' enumerator_list '}'
// 	| ENUM IDENTIFIER '{' enumerator_list '}'
// 	| ENUM IDENTIFIER
// 	;

// enumerator_list
// 	: enumerator
// 	| enumerator_list ',' enumerator
// 	;

// enumerator
// 	: IDENTIFIER
// 	| IDENTIFIER '=' constant_expression
// 	;

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

//#include <stdio.h>

//  char yytext[];
//  int column;

// yyerror(s)
// char *s;
// {
// 	fflush(stdout);
// 	printf("\n%*s\n%*s\n", column, "^", column, s);
// }

// Definition of root ptr (to match declaration earlier)
const Node *g_root;

// Function to parse AST to main (to match declaration in main.cpp)
const Node *parseAST(const char *inputFile)
{
	yyin = fopen(input, "r");
	if (!yyin)
	// {
	// 	fprintf(stderr, "(%s) could not be opened", input);
	// 	return nullptr;
	// }
    
	g_root=NULL;
    yyparse();
    return g_root;
}