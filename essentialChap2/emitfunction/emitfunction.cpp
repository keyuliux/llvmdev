#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Analysis/Verifier.h"



using namespace llvm;

static LLVMContext &Context = getGlobalContext();
static Module *ModuleOb = new Module("my compiler", Context);

Function *createFunc(IRBuilder<> &Builder, std::string Name) {
    FunctionType *funcType = FunctionType::get(Builder.getInt32Ty(), false);

    Function *fooFunc = Function::Create(
        funcType, Function::ExternalLinkage, Name, ModuleOb);
    return (fooFunc);
}

int main(int argc, char *argv[] ) {
    static IRBuilder<> Builder(Context);
    Function *fooFunc = createFunc(Builder, "foo");
    verifyFunction(*fooFunc);

    ModuleOb->dump();

    return (0);
}
