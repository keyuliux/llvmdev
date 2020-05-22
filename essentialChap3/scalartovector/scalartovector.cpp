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
    Type *u32Ty = Type::getInt32Ty(Context);
    Type *vecTy = VectorType::get(u32Ty, 4);
    FunctionType *funcType = 
    FunctionType::get(Builder.getInt32Ty(), vecTy, false);

    Function *fooFunc = 
    Function::Create(funcType, Function::ExternalLinkage, Name, 
    ModuleOb);
    /*
    std::vector<Type *> Integers(FunArgs.size(), Type::getInt32Ty(Context));    
    FunctionType *funcType = FunctionType::get(Builder.getInt32Ty(), Integers, false);

    Function *fooFunc = Function::Create(
        funcType, Function::ExternalLinkage, Name, ModuleOb);
     */
    return (fooFunc);
}

// Create function arguments
void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs) {
    unsigned Idx = 0;
    Function::arg_iterator AI, AE;
    for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end();
    AI !=AE; ++AI, ++Idx)
        AI->setName(FunArgs[Idx]);
}

// Create a block
BasicBlock *createBB(Function *fooFunc, std::string Name) {
    return BasicBlock::Create(Context, Name, fooFunc);
}

// Get address
Value *getGEP(IRBuilder<> &Builder, Value *Base, Value *Offset) {
    return Builder.CreateGEP(Base, Offset, "a1");
    //return Builder.CreateGEP(Builder.getInt32Ty(), Base, Offset, "a1");
}

// write into memory
void getStore(IRBuilder<> &Builder, Value *Address, Value *V) {
    Builder.CreateStore(V, Address);
}

// Read memory
Value *getLoad(IRBuilder<> &Builder, Value *Address) {
    return Builder.CreateLoad(Address, "load");
}

Value *getInsertElement(IRBuilder<> &Builder, Value *Vec, Value *Val,
                        Value *Index) {
    return Builder.CreateInsertElement(Vec, Val, Index);
}

Value *getExtractElement(IRBuilder<> &Builder, Value *Vec, Value *Index) {
    return Builder.CreateExtractElement(Vec, Index);
}
int main(int argc, char *argv[] ) {
    static IRBuilder<> Builder(Context);

    // Create function args
    FunArgs.push_back("a");
    // Create function
    Function *fooFunc = createFunc(Builder, "foo");
    setFuncArgs(fooFunc, FunArgs);

    // Create basic block
    BasicBlock *entry = createBB(fooFunc, "entry");
    Builder.SetInsertPoint(entry);
    Value *Vec = fooFunc->arg_begin();
    SmallVector<Value *, 4> V;
    for (unsigned int i = 0; i < 4; i++) {
        //Value *V = getInsertElement(Builder, Vec, Builder.getInt32((i + 1) * 10),
        //Builder.getInt32(i));
        V[i] = getExtractElement(Builder, Vec, Builder.getInt32(i));
    }
    //Value *gep = getGEP(Builder, Base, Builder.getInt32(1));
    //Value *load = getLoad(Builder, gep);
    //Value *constant = Builder.getInt32(16);
    //getStore(Builder, gep, constant);
    Builder.CreateRet(Builder.getInt32(1));
    verifyFunction(*fooFunc);

    ModuleOb->dump();

    return (0);
}