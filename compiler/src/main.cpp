#include "topLevel.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) //RUN: compiler -S <input.c> -o <output.s>
{
    std::cerr << "main::print\tSTART\n";

    std::cerr << "Parse AST\n";
    const Node *root = parseAST(argv[2]);

    if (root == nullptr) //REMOVE LATER
    {
        std::cerr << "if (the AST root is NULL)\n";
        std::cerr << "\tThe root node was nullptr" << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "DONE PARSING" << "\n";

    std::cerr << "Open the output file stream: " << argv[4] << "\n";
    //root->print(cout, NULL);
    std::ofstream output(argv[4]);

    if (output.is_open())
    {
        std::cerr << "if (the output file stream" << argv[4] << " was opened)\n";
        output << ".data\n";
        std::cerr << "\tPrint AST\n";
        root->print(output, nullptr);
    }
    else
    {
        std::cerr << "if (the output file stream" << argv[4] << " was NOT opened)\n";
        std::cerr << "\tCould not open output file.\n";
        return -1;
    }

    std::cerr << "main::print\tEND\n";

    return 0;
}