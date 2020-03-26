%code requires{
	#include "AST.h"

	//matched below context-free grammar
	 const Node *g_root;
	 FILE *yyin; // Lexer input file

	 //declaring lex generated functions to fix possible issues as provided in 2-parser CW
	int yylex(void);
  	void yyerror(const char *);
}
// Possible type that symbols can take on
%union{

}

%define parse.error verbose //For debugging

//// Symbol definitions ---------------------------------------------------------
/// Lexer tokens ----------------------------------------------------------------------
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
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
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
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
	: unary_expression
	//| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

//https://en.cppreference.com/w/c/language/operator_other#Conditional_operator
conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	//f (a, "(t=3, t+2)", c)
	//| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

//// Declaration ------------------------------------------------------------

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

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

// storage_class_specifier
// 	: TYPEDEF
// 	| STATIC
// 	;

type_specifier //no signed needed, short?
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| struct_specifier
	| enum_specifier
	| TYPE_NAME
	;

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

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

//https://en.cppreference.com/w/c/language/initialization
initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

/// Statement -----------------------------------------------------------------

//https://docs.microsoft.com/en-us/cpp/c-language/goto-and-labeled-statements-c?view=vs-2019
labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;


statement_list
	: statement
	| statement_list statement
	;

//https://docs.microsoft.com/en-us/cpp/c-language/expression-statement-c?view=vs-2019
expression_statement
	: ';'
	| expression ';'
	;

//https://docs.microsoft.com/en-us/cpp/c-language/switch-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/if-statement-c?view=vs-2019
selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

//https://docs.microsoft.com/en-us/cpp/c-language/while-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/do-while-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/for-statement-c?view=vs-2019
iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

//https://docs.microsoft.com/en-us/cpp/c-language/continue-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/goto-and-labeled-statements-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/break-statement-c?view=vs-2019
//https://docs.microsoft.com/en-us/cpp/c-language/return-statement-c?view=vs-2019
jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;



//// Declarator -----------------------------------------------------------------

pointer
	: '*'
	//| '*' type_qualifier_list
	| '*' pointer
	//| '*' type_qualifier_list pointer
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

//https://docs.microsoft.com/en-us/cpp/c-language/c-abstract-declarators?view=vs-2019
direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

//https://en.cppreference.com/w/c/language/declarations
//http://c-faq.com/decl/spiral.anderson.html
direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;


//primitive data type variable declaration
//or any user-defined type structure declaration
declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;


//// Top level & Global Scope -----------------------------------------------------------------

//https://docs.microsoft.com/en-us/cpp/c-language/obsolete-forms-of-function-declarations-and-definitions?view=vs-2019
//https://stackoverflow.com/questions/18820751/identifier-list-vs-parameter-type-list-in-c/18820829#18820829
function_definition
	// : declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	//| declarator compound_statement
	;

 //decarations in global scope
external_declaration
	: function_definition															{ $$ = $1; }
	| declaration																	{ $$ = $1; }
	;

translation_unit //top level list
	: external_declaration
	| translation_unit external_declaration
	; //implement

root: translation_unit																{ g_root = $1; }

%%
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


// redundant grammar:
// parameter_type_list
// ELLIPSE, VOLATILE; EXTERN; AUTO; REGISTER; UNION