#include "AST.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
    const Node *root = parseAST(argv[2]);
    //parseAST(argv[1]); for debuggin in VS

    cout << '\n';

    //root->print(cout);

    ofstream output(argv[4]);

    if (output.is_open())
    {
        // current date/time based on current system
        time_t now = time(0);
        string dt = ctime(&now);
        output << "# Created on " << dt << '\n';

        root->print(output);

        // introduce main function in python
        output << "\nif __name__ == \"__main__\":\n\timport sys\n\tret=main()\n\tsys.exit(ret)\n";
    }
    else
    {
        std::cerr << "Could not open output file.\n";
    }

    return 0;
}