#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "EvalListener.h"

#include "defs.h"


using namespace std;
using namespace llvm;

static std::unique_ptr<Module> TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value *> NamedValues;

void EvalListener::enterProg(LabeledExprParser::ProgContext *ctx) {
    // Make the module, which holds all the code.
    TheModule = llvm::make_unique<Module>("my cool jit", getGlobalContext());
}

void EvalListener::exitProg(LabeledExprParser::ProgContext *ctx) {
    // Print out all of the generated code.
    TheModule->dump();

}

/* 
//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//
namespace {
/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual Value *codegen() = 0;
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
  Value *codegen() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
  Value *codegen() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  Value *codegen() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
  Value *codegen() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &Name, std::vector<std::string> Args)
      : Name(Name), Args(std::move(Args)) {}
  Function *codegen();
  const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
  Function *codegen();
};
} // end anonymous namespace
//===----------------------------------------------------------------------===//
// Code Generation
//===----------------------------------------------------------------------===//

static std::unique_ptr<Module> TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value *> NamedValues;

Value *ErrorV(const char *Str) {
  Error(Str);
  return nullptr;
}

Value *NumberExprAST::codegen() {
  return ConstantFP::get(getGlobalContext(), APFloat(Val));
}

Value *VariableExprAST::codegen() {
  // Look this variable up in the function.
  Value *V = NamedValues[Name];
  if (!V)
    return ErrorV("Unknown variable name");
  return V;
}

Value *BinaryExprAST::codegen() {
  Value *L = LHS->codegen();
  Value *R = RHS->codegen();
  if (!L || !R)
    return nullptr;

  switch (Op) {
  case '+':
    return Builder.CreateFAdd(L, R, "addtmp");
  case '-':
    return Builder.CreateFSub(L, R, "subtmp");
  case '*':
    return Builder.CreateFMul(L, R, "multmp");
  case '<':
    L = Builder.CreateFCmpULT(L, R, "cmptmp");
    // Convert bool 0/1 to double 0.0 or 1.0
    return Builder.CreateUIToFP(L, Type::getDoubleTy(getGlobalContext()),
                                "booltmp");
  default:
    return ErrorV("invalid binary operator");
  }
}

Value *CallExprAST::codegen() {
  // Look up the name in the global module table.
  Function *CalleeF = TheModule->getFunction(Callee);
  if (!CalleeF)
    return ErrorV("Unknown function referenced");

  // If argument mismatch error.
  if (CalleeF->arg_size() != Args.size())
    return ErrorV("Incorrect # arguments passed");

  std::vector<Value *> ArgsV;
  for (unsigned i = 0, e = Args.size(); i != e; ++i) {
    ArgsV.push_back(Args[i]->codegen());
    if (!ArgsV.back())
      return nullptr;
  }

  return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Function *PrototypeAST::codegen() {
  // Make the function type:  double(double,double) etc.
  std::vector<Type *> Doubles(Args.size(),
                              Type::getDoubleTy(getGlobalContext()));
  FunctionType *FT =
      FunctionType::get(Type::getDoubleTy(getGlobalContext()), Doubles, false);

  Function *F =
      Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());

  // Set names for all arguments.
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++]);

  return F;
}

Function *FunctionAST::codegen() {
  // First, check for an existing function from a previous 'extern' declaration.
  Function *TheFunction = TheModule->getFunction(Proto->getName());

  if (!TheFunction)
    TheFunction = Proto->codegen();

  if (!TheFunction)
    return nullptr;

  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  NamedValues.clear();
  for (auto &Arg : TheFunction->args())
    NamedValues[Arg.getName()] = &Arg;

  if (Value *RetVal = Body->codegen()) {
    // Finish off the function.
    Builder.CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);

    return TheFunction;
  }

  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  return nullptr;
}
*/
/*
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

*/