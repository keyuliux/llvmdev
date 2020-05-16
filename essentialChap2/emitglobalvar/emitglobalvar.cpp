#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Analysis/Verifier.h"
#include <vector>


using namespace llvm;

static LLVMContext &Context = getGlobalContext();
static Module *ModuleOb = new Module("my compiler", Context);

// Create a function in a module
Function *createFunc(IRBuilder<> &Builder, std::string Name) {
    FunctionType *funcType = FunctionType::get(Builder.getInt32Ty(), false);

    Function *fooFunc = Function::Create(
        funcType, Function::ExternalLinkage, Name, ModuleOb);
    return (fooFunc);
}

// Create a block
BasicBlock *createBB(Function *fooFunc, std::string Name) {
    return BasicBlock::Create(Context, Name, fooFunc);
}

// Create global variable
GlobalVariable *createGlob(IRBuilder<> &Builder, std::string Name) {
    ModuleOb->getOrInsertGlobal(Name, Builder.getInt32Ty());
    GlobalVariable *gVar = ModuleOb->getNamedGlobal(Name);
    gVar->setLinkage(GlobalValue::CommonLinkage);
    gVar->setAlignment(4);
    return gVar;
}
int main(int argc, char *argv[] ) {
    static IRBuilder<> Builder(Context);
    // create global variable
    GlobalVariable *gVar = createGlob(Builder, "x");
    // create function
    Function *fooFunc = createFunc(Builder, "foo");
    // create basic block
    BasicBlock *entry = createBB(fooFunc, "entry");
    Builder.SetInsertPoint(entry);
    Builder.CreateRet(Builder.getInt32(0));
    verifyFunction(*fooFunc);

    ModuleOb->dump();

    return (0);
}