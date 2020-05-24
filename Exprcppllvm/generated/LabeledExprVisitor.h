
// Generated from LabeledExpr.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "LabeledExprParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LabeledExprParser.
 */
class  LabeledExprVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LabeledExprParser.
   */
    virtual antlrcpp::Any visitProg(LabeledExprParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitPrintExpr(LabeledExprParser::PrintExprContext *context) = 0;

    virtual antlrcpp::Any visitAssign(LabeledExprParser::AssignContext *context) = 0;

    virtual antlrcpp::Any visitBlank(LabeledExprParser::BlankContext *context) = 0;

    virtual antlrcpp::Any visitParens(LabeledExprParser::ParensContext *context) = 0;

    virtual antlrcpp::Any visitMulDiv(LabeledExprParser::MulDivContext *context) = 0;

    virtual antlrcpp::Any visitAddSub(LabeledExprParser::AddSubContext *context) = 0;

    virtual antlrcpp::Any visitId(LabeledExprParser::IdContext *context) = 0;

    virtual antlrcpp::Any visitInt(LabeledExprParser::IntContext *context) = 0;


};

