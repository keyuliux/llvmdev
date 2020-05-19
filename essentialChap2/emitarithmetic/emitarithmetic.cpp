#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Analysis/Verifier.h"
#include <vector>


using namespace llvm;

static LLVMContext &Context = getGlobalContext();
static Module *ModuleOb = new Module("my compiler", Context);
static std::vector<std::string> FunArgs;
// Create a function in a module
Function *createFunc(IRBuilder<> &Builder, std::string Name) {
    
    std::vector<Type *> Integers(FunArgs.size(), Type::getInt32Ty(Context));    
    FunctionType *funcType = FunctionType::get(Builder.getInt32Ty(), Integers, false);

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

// Create function arguments
void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs) {
    unsigned Idx = 0;
    Function::arg_iterator AI, AE;
    for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end();
    AI !=AE; ++AI, ++Idx)
        AI->setName(FunArgs[Idx]);
}

// Create arithmetic
Value *createArith(IRBuilder<> &Builder, Value *L, Value *R) {
    return Builder.CreateMul(L,R, "multmp");
}

int main(int argc, char *argv[] ) {
    static IRBuilder<> Builder(Context);

    // create function args
    FunArgs.push_back("a");
    FunArgs.push_back("b");
    // create global variable
    GlobalVariable *gVar = createGlob(Builder, "x");
    // create function
    Function *fooFunc = createFunc(Builder, "foo");
    setFuncArgs(fooFunc, FunArgs);
    // create basic block
    BasicBlock *entry = createBB(fooFunc, "entry");
    Builder.SetInsertPoint(entry);
    Value *Arg1 = fooFunc->arg_begin();
    Value *constant = Builder.getInt32(16);
    Value *val = createArith(Builder, Arg1, constant);
    Builder.CreateRet(val);
    verifyFunction(*fooFunc);

    ModuleOb->dump();

    return (0);
}