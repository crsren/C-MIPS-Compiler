#include "../include/AST.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
    string filename = "output.py";
    const Node *root = parseAST(); //fn from yacc

    // current date/time based on current system
    time_t now = time(0);
    string dt = ctime(&now);

    ofstream output(filename);
    output << "# Produced @ " << dt << '\n';
    // introduce main function in python

    if (output.is_open())
    {
        root->print(output);
    }

    return 0;
}