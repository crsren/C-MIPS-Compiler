#if !defined(TOP_LEVEL_H)
#define TOP_LEVEL_H

// - Include all files here for easier access in parser
// - Define parseAST() to be found in parser.y (builds the AST and outputs its root node)

// Declaration
//#include "Declaration/declaration.h"
#include "Declaration/declarators.h"
//#include "Declaration/type_specifiers.h"

// Expressions
#include "Expressions/arithmetic_operation.h"
#include "Expressions/assignment_expression.h"
#include "Expressions/binary_operation.h"
#include "Expressions/bitwise_operation.h"
#include "Expressions/boolean_operation.h"
#include "Expressions/primitives.h"
#include "Expressions/unary_operation.h"

// Function
#include "Function/fn_call.h"
#include "Function/fn_declarator.h"
#include "Function/fn_definition.h"

// Statement
#include "Statements/compound.h"
#include "Statements/for.h"
#include "Statements/if_else.h"
#include "Statements/jump.h"
#include "Statements/switch.h"
#include "Statements/while.h"

// Context
#include "Context/bindings.h"

extern const Node *parseAST(const char *input);

#endif // TOP_LEVEL_H
