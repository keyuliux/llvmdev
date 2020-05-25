#include <iostream>
#include <fstream>

#include "tree/ParseTreeWalker.h"
#include "antlr4-runtime.h"
#include "LabeledExprLexer.h"
#include "LabeledExprParser.h"

#include "EvalListener.h"
 
using namespace std;
using namespace antlrcpp;
using namespace antlr4;

int main(int argc, const char *args[])
{
    // llvm context
    //LLVMContext &Context = getGlobalContext();

    ifstream ins;

    // Create the input stream.
    ins.open(args[1]);
    ANTLRInputStream input(ins);

    // Create a lexer which scans the character stream
    // to create a token stream.
    LabeledExprLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    // Create a parser which parses the token stream.
    LabeledExprParser parser(&tokens);
    tree::ParseTree *tree = parser.prog();

    EvalListener listener;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    return 0;
}