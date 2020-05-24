#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "EvalVisitor.h"


using namespace std;
using namespace llvm;
static LLVMContext &Context = getGlobalContext();
static Module *ModuleOb;
static IRBuilder<> Builder(getGlobalContext());
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

void EvalVisitor::init(void) {

    ModuleOb = new Module("my cool jit", Context);

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
    auto args = fooFunc->arg_begin();
    Value *Arg1 = &(*args);
    Value *constant = Builder.getInt32(10);
    Value *val = createArith(Builder, Arg1, constant);
    Builder.CreateRet(val);
}
void EvalVisitor::moduledump(void) {
    ModuleOb->dump();
}
antlrcpp::Any EvalVisitor::visitPrintExpr(LabeledExprParser::PrintExprContext *ctx)
{
    int value = visit(ctx->expr());
    //cout << value << endl;
    return 0;
}

antlrcpp::Any EvalVisitor::visitAssign(LabeledExprParser::AssignContext *ctx)
{
    string id = ctx->ID()->getText();
    int value = visit(ctx->expr());
    memory[id] = value;
    return value;
}

antlrcpp::Any EvalVisitor::visitMulDiv(LabeledExprParser::MulDivContext *ctx)
{
    int left  = visit(ctx->expr(0));
    int right = visit(ctx->expr(1));

    Value *L = Builder.getInt32(left);
    Value *R = Builder.getInt32(right);
    if (L == 0 || R == 0) return 0;
    if (ctx->op->getType() == LabeledExprParser::MUL) {
        Builder.CreateFMul(L, R, "multmp");
    } else {
        Builder.CreateFDiv(L, R, "divtmp");
    }
    return (ctx->op->getType() == LabeledExprParser::MUL)
            ? left*right : left/right;
}

antlrcpp::Any EvalVisitor::visitAddSub(LabeledExprParser::AddSubContext *ctx)
{
    int left  = visit(ctx->expr(0));
    int right = visit(ctx->expr(1));

    Value *L = Builder.getInt32(left);
    Value *R = Builder.getInt32(right);
    if (L == 0 || R == 0) return 0;
    if (ctx->op->getType() == LabeledExprParser::ADD) {
        Builder.CreateFAdd(L, R, "addtmp");
    } else {
        Builder.CreateFSub(L, R, "subtmp");
    }
    return (ctx->op->getType() == LabeledExprParser::ADD)
            ? left + right : left - right;
}

antlrcpp::Any EvalVisitor::visitInt(LabeledExprParser::IntContext *ctx)
{
    return stoi(ctx->INT()->getText());
}

antlrcpp::Any EvalVisitor::visitId(LabeledExprParser::IdContext *ctx)
{
    string id = ctx->ID()->getText();
    return (memory.find(id) != memory.end())
            ? memory[id] : 0;
}

antlrcpp::Any EvalVisitor::visitParens(LabeledExprParser::ParensContext *ctx)
{
    return visit(ctx->expr());
}