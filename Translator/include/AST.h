#if !defined(AST_H)
#define AST_H

#include "helpers.h"
#include "node.h"
#include "operator.h"
#include "unary.h"
#include "statements.h"
#include "primitive.h"

#include <iostream>

extern const Node *root; //

typedef const Node *nodePtr;

#endif // AST_H
