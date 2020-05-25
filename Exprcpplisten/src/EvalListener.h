#ifndef EVALLISTENER_H_TXT_
#define EVALLISTENER_H_TXT_

#include <iostream>
#include <string>
#include <map>
#include "antlr4-runtime.h"
#include "LabeledExprBaseListener.h"

using namespace std;
using namespace antlrcpp;
using namespace antlr4;
/**
 * This interface defines an abstract listener for a parse tree produced by LabeledExprParser.
 */
class  EvalListener : public LabeledExprBaseListener {
public:

   virtual void enterProg(LabeledExprParser::ProgContext *ctx) override;
   virtual void exitProg(LabeledExprParser::ProgContext *ctx) override;
   /*

   virtual void enterPrintExpr(LabeledExprParser::PrintExprContext *ctx) override;
   virtual void exitPrintExpr(LabeledExprParser::PrintExprContext *ctx) override;

   virtual void enterAssign(LabeledExprParser::AssignContext *ctx) override;
   virtual void exitAssign(LabeledExprParser::AssignContext *ctx) override;

   virtual void enterBlank(LabeledExprParser::BlankContext *ctx) override;
   virtual void exitBlank(LabeledExprParser::BlankContext *ctx) override;

   virtual void enterParens(LabeledExprParser::ParensContext *ctx) override;
   virtual void exitParens(LabeledExprParser::ParensContext *ctx) override;

   virtual void enterMulDiv(LabeledExprParser::MulDivContext *ctx) override;
   virtual void exitMulDiv(LabeledExprParser::MulDivContext *ctx) override;

   virtual void enterAddSub(LabeledExprParser::AddSubContext *ctx) override;
   virtual void exitAddSub(LabeledExprParser::AddSubContext *ctx) override;

   virtual void enterId(LabeledExprParser::IdContext *ctx) override;
   virtual void exitId(LabeledExprParser::IdContext *ctx) override;

   virtual void enterInt(LabeledExprParser::IntContext *ctx) override;
   virtual void exitInt(LabeledExprParser::IntContext *ctx) override;

 */
};
/*

class EvalVisitor : public LabeledExprBaseVisitor
{
public:
    void init(void);
    void moduledump(void);
    virtual antlrcpp::Any visitPrintExpr(LabeledExprParser::PrintExprContext *ctx) override;
    virtual antlrcpp::Any visitAssign(LabeledExprParser::AssignContext *ctx) override;
    virtual antlrcpp::Any visitMulDiv(LabeledExprParser::MulDivContext *ctx) override;
    virtual antlrcpp::Any visitAddSub(LabeledExprParser::AddSubContext *ctx) override;
    virtual antlrcpp::Any visitInt(LabeledExprParser::IntContext *ctx) override;
    virtual antlrcpp::Any visitId(LabeledExprParser::IdContext *ctx) override;
    virtual antlrcpp::Any visitParens(LabeledExprParser::ParensContext *ctx) override;

private:
    map<string, int> memory;
};
*/
#endif /* EVALLISTENER_H_TXT_ */