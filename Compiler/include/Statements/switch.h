#if !defined(SWITCH_H)
#define SWITCH_H

#include "helpers.h"
#include "standard_list.h"

class LabeledStatementList;

class SwitchStatement : public Node
{
    nodePtr condition;
    List *sList;

public:
    SwitchStatement(nodePtr c, List *s) : condition(c), sList(s){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const override;

    ~SwitchStatement()
    {
        delete condition;
        delete sList;
    }
};

// Only needed for switch statement
class LabeledStatement : public Node
{
    nodePtr statement;
    nodePtr constExpression; // needs to be accessed by switch statement

public:
    // case x : ...
    LabeledStatement(nodePtr cE, nodePtr s) : constExpression(cE), statement(s){};
    // default : ...
    LabeledStatement(nodePtr s) : constExpression(nullptr), statement(s){};

    void print(std::ostream &out, LocalVariableBindings *bindings) const {};

    nodePtr getStatement() const
    {
        return statement;
    }

    nodePtr getConstExpression() const
    {
        return constExpression;
    }
};

// class LabeledStatementList : public List
// {
//     std::vector<LabeledStatement *> items; // needs to be accessed by switch statement

// public:
//     // std::list<int> labelList;
//     LabeledStatementList(LabeledStatement *ls)
//     {
//         items.push_back(ls);
//     }

//     void add(LabeledStatement *ls)
//     {
//         items.push_back(ls);
//     }

//     std::vector<LabeledStatement *> &getItems()
//     {
//         return items;
//     }

//     // void evaluateLabels(std::ostream &out, LocalVariableBindings &bindings)
//     // {
//     //     for (const auto &ls : items)
//     //     {
//     //         ls->constExpression->print(out, bindings);
//     //         // stored in $2
//     //         // push positions in stack in labelList
//     //     }
//     // }
// };

#endif // SWITCH_H
