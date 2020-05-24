#ifndef EVALVISITOR_H_TXT_
#define EVALVISITOR_H_TXT_

#include <iostream>
#include <string>
#include <map>
#include "antlr4-runtime.h"
#include "LabeledExprBaseVisitor.h"

#include "defs.h"

using namespace std;

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

#endif /* EVALVISITOR_H_TXT_ */