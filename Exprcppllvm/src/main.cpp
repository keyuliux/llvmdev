#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "LabeledExprLexer.h"
#include "LabeledExprParser.h"

#include "EvalVisitor.h"
#include "defs.h"

using namespace llvm;
 
using namespace std;
using namespace antlrcpp;
using namespace antlr4;

//static Module *TheModule;
//static IRBuilder<> Builder(getGlobalContext());

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

    //cout << "Evaluation:" << endl;
    EvalVisitor eval;
    eval.init();
    eval.visit(tree);
    eval.moduledump();
    // Make the module, which holds all the code.
    //TheModule = new Module("my cool jit", Context);

    // Print out all of the generated code.
    //TheModule->dump();
    return 0;
}