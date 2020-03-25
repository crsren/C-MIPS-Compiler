#ifndef AST_H
#define AST_H

#include "helpers.h"
#include "node.h"
#include "operator.h"
#include "unary.h"
#include "statements.h"
#include "primitive.h"
#include "list.h"
#include "variable.h"
#include "function.h"

//extern const Node *parseAST(const char *);
extern const Node *parseAST();

#endif // AST_H
