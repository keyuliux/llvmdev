
// Generated from LabeledExpr.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "LabeledExprVisitor.h"


/**
 * This class provides an empty implementation of LabeledExprVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LabeledExprBaseVisitor : public LabeledExprVisitor {
public:

  virtual antlrcpp::Any visitProg(LabeledExprParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintExpr(LabeledExprParser::PrintExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssign(LabeledExprParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlank(LabeledExprParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParens(LabeledExprParser::ParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulDiv(LabeledExprParser::MulDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddSub(LabeledExprParser::AddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitId(LabeledExprParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInt(LabeledExprParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }


};

