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
typedef SmallVector<BasicBlock *, 16> BBList;
typedef SmallVector<Value *, 16> ValList;

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

// Create ifelse
Value *createIfElse(IRBuilder<> &Builder, BBList List, ValList VL) {
    Value *Condtn = VL[0];
    Value *Arg1 = VL[1];
    BasicBlock *ThenBB = List[0];
    BasicBlock *ElseBB = List[1];
    BasicBlock *MergeBB = List[2];
    Builder.CreateCondBr(Condtn, ThenBB, ElseBB);

    Builder.SetInsertPoint(ThenBB);
    Value *ThenVal = Builder.CreateAdd(Arg1, Builder.getInt32(1),
    "thenaddtmp");
    Builder.CreateBr(MergeBB);

    Builder.SetInsertPoint(ElseBB);
    Value *ElseVal = Builder.CreateAdd(Arg1, Builder.getInt32(2),
    "elseaddtmp");
    Builder.CreateBr(MergeBB);

    unsigned PhiBBSize = List.size() - 1;
    Builder.SetInsertPoint(MergeBB);
    PHINode *Phi = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()),
    PhiBBSize, "iftmp");
    Phi->addIncoming(ThenVal, ThenBB);
    Phi->addIncoming(ElseVal, ElseBB);

    return Phi;
}

// Create loop
// for(i=1; i < b; i ++)
Value *createLoop(IRBuilder<> &Builder, BBList List, ValList VL,
Value *StartVal, Value *EndVal) {
    BasicBlock *PreheaderBB = Builder.GetInsertBlock();
    Value *val = VL[0];//Arg1
    BasicBlock *LoopBB = List[0];
    Builder.CreateBr(LoopBB);

    Builder.SetInsertPoint(LoopBB);
    PHINode *IndVar = Builder.CreatePHI(Type::getInt32Ty(Context), 2, "i");
    IndVar->addIncoming(StartVal, PreheaderBB); // i = 1, PreheaderBB %endry
    Value *Add = Builder.CreateAdd(val, Builder.getInt32(5), "addtmp"); //Arg1 + 5
    Value *StepVal = Builder.getInt32(1);
    Value *NextVal = Builder.CreateAdd(IndVar, StepVal, "nextval");// i + 1
    Value *EndCond = Builder.CreateICmpULT(IndVar, EndVal, "endcond");// i < Arg2
    EndCond = Builder.CreateICmpNE(EndCond, Builder.getInt1(0), "loopcond");
    BasicBlock *LoopEndBB = Builder.GetInsertBlock();
    BasicBlock *AfterBB = List[1];
    Builder.CreateCondBr(EndCond, LoopBB, AfterBB);

    Builder.SetInsertPoint(AfterBB);
    IndVar->addIncoming(NextVal, LoopEndBB); // i = nextval, LoopEndBB %loop
    return Add;
}

int main(int argc, char *argv[] ) {
    static IRBuilder<> Builder(Context);

    // Create function args
    FunArgs.push_back("a");
    FunArgs.push_back("b");
    // Create global variable
    GlobalVariable *gVar = createGlob(Builder, "x");
    // Create function
    Function *fooFunc = createFunc(Builder, "foo");
    setFuncArgs(fooFunc, FunArgs);
    // Create basic block
    BasicBlock *entry = createBB(fooFunc, "entry");
    Builder.SetInsertPoint(entry);
    // Create loop
    Function::arg_iterator AI = fooFunc->arg_begin();
    Value *Arg1 = AI++;
    Value *Arg2 = AI;
    Value *constant = Builder.getInt32(16);
    Value *val = createArith(Builder, Arg1, constant);
    ValList VL;
    VL.push_back(Arg1);

    BBList List;
    BasicBlock *LoopBB = createBB(fooFunc, "loop");
    BasicBlock *AfterBB = createBB(fooFunc, "afterloop");
    List.push_back(LoopBB);
    List.push_back(AfterBB);

    Value *StartVal = Builder.getInt32(1);
    Value *Res = createLoop(Builder, List, VL, StartVal, Arg2);

    Builder.CreateRet(Res);
    verifyFunction(*fooFunc);

    ModuleOb->dump();

    return (0);
}