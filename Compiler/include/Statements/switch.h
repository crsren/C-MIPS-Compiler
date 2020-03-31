#if !defined(SWITCH_H)
#define SWITCH_H

#include "../helpers.h"
#include "../list.h"

class LabeledStatementList;

class SwitchStatement : public Node
{
    nodePtr condition;
    const List *sList;

public:
    SwitchStatement(nodePtr c, const List *s) : condition(c), sList(s){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    ~SwitchStatement()
    {
        delete condition;
        delete sList;
    }
};

// Only needed for switch statement
class LabeledStatement
{
    std::string label; //assigned in switch statement
public:
    nodePtr statement;
    nodePtr constExpression; // needs to be accessed by switch statement
    // case x : ...
    LabeledStatement(nodePtr cE, nodePtr s) : constExpression(cE), statement(s), label(""){};
    // default : ...
    LabeledStatement(nodePtr s) : constExpression(nullptr), statement(s), label(""){};

    std::string getLabel()
    {
        return label;
    }

    void setLabel(std::string l)
    {
        label = l;
    }
};

class LabeledStatementList
{
public:
    std::list<LabeledStatement *> items; // needs to be accessed by switch statement

    // std::list<int> labelList;
    LabeledStatementList(LabeledStatement *ls)
    {
        items.push_back(ls);
    }

    void add(LabeledStatement *ls)
    {
        items.push_back(ls);
    }

    // void evaluateLabels(std::ostream &out, LocalVariableBindings &bindings)
    // {
    //     for (const auto &ls : items)
    //     {
    //         ls->constExpression->print(out, bindings);
    //         // stored in $2
    //         // push positions in stack in labelList
    //     }
    // }
};

#endif // SWITCH_H
