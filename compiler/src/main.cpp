#include "topLevel.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) //RUN: compiler -S <input.c> -o <output.s>
{
    const Node *root = parseAST(argv[2]);
    if (root == nullptr) //REMOVE LATER
    {
        cerr << "\nThe root node was nullptr" << endl;
        return EXIT_FAILURE;
    }
    cout << '\n';

    //root->print(cout, NULL);
    ofstream output(argv[4]);
    if (output.is_open())
    {
        output << ".data\n";
        root->print(output, nullptr);
    }
    else
    {
        cerr << "Could not open output file.\n";
        return -1;
    }

    return 0;
}