#if !defined(JUMP_H)
#define JUMP_H

#include "helpers.h"

class ReturnStatement : public Node
{
private:
    nodePtr expression;

public:
    ReturnStatement(nodePtr e = nullptr) : expression(e){};

    void print(std::ostream &out, !!!) const override;

    ~ReturnStatement { delete expression; };
};

#endif // JUMP_H
