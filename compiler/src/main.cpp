#include "topLevel.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    // const Node *root = parseAST();
    const Node *root = parseAST(argv[1]); //for debuggin in VS

    cout << '\n';

    //root->print(cout, NULL);

    if (output.is_open())
    {
        root->print(output, NULL);

    }
    else
    {
        std::cerr << "Could not open output file.";
    }

    return 0;
}