#include "topLevel.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    const Node *root = parseAST(argv[1]);

    cout << '\n';

    //root->print(cout, NULL);
    ofstream output("chingchong.txt");
    if (output.is_open())
    {
        output << ".data\n";
        root->print(output, nullptr);
    }
    else
    {
        cerr << "Could not open output file.";
        return -1;
    }

    return 0;
}