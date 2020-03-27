#if !defined(SELECTION)
#define SELECTION

#include "helpers.h"

class SelectionStatement : public Node
{
private:
    nodePtr condition;
    nodePtr statement1;
    nodePtr statement2;
    bool has_else;

public:
    //if statement
    SelectionStatement(nodeptr c, nodePtr s) : condition(c), statement1(s), statement2(nullptr), has_else(false){};
    // if else statement
    SelectionStatement(nodePtr c, nodePtr s1, nodePtr s2) : condition(c), statement1(s1), statement2(s2), has_else(true){};

    void print(std::ostream &out, !!!) const override; // implement

    ~SelectionStatement()
    {
        delete condition;
        delete statement1;
        delete statement2;
    }
};

#endif // SELECTION
