#include "topLevel.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) //RUN: compiler -S <input.c> -o <output.s>
{
    std::cerr << GlobalIndent::instance().globalIndent << "main::print\tSTART\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Parse AST\n";
    const Node *root = parseAST(argv[2]);

    if (root == nullptr) //REMOVE LATER
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the AST root is NULL)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tThe root node was nullptr" << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << GlobalIndent::instance().globalIndent << "DONE PARSING"
              << "\n";

    std::cerr << GlobalIndent::instance().globalIndent << "Open the output file stream: " << argv[4] << "\n";
    //root->print(cout, NULL);
    std::ofstream output(argv[4]);

    if (output.is_open())
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the output file stream" << argv[4] << " was opened)\n";
        output << ".data\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tPrint AST\n";
        root->print(output, nullptr); //std::cerr
    }
    else
    {
        std::cerr << GlobalIndent::instance().globalIndent << "if (the output file stream" << argv[4] << " was NOT opened)\n";
        std::cerr << GlobalIndent::instance().globalIndent << "\tCould not open output file.\n";
        return -1;
    }

    std::cerr << GlobalIndent::instance().globalIndent << "main::print\tEND\n";

    return 0;
}