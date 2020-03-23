#include "AST.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{

    const Node *root = parseAST(); //fn from yacc

    cout << endl
         << "Writing to output.py\n";

    string filename = "output.py";
    ofstream output(filename);

    if (output.is_open())
    {
        // current date/time based on current system
        time_t now = time(0);
        string dt = ctime(&now);
        output << "# Created on " << dt << '\n';

        root->print(output);

        // introduce main function in python
        output << "\n\nif __name__ == \"__main__\":\n\timport sys\n\tret=main()\n\tsys.exit(ret)\n";
    }
    else
    {
        std::cerr << "Could not open output.py.\n";
    }

    return 0;
}