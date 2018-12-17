//===--- StmtC.h - Classes for extending C statements --*- C++ -*===//
// Author: Yiyong.Li
//
//    This file is rewritten simply for getting my hands wet in Clang development.
//
//===------------------------------------------------------------===//

/// Implementation of "StmtC.h"

#include "clang/AST/StmtC.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ASTContext.h"

using namespace clang;

CForEachStmt::CForEachStmt(Stmt *Elem, Expr *Arr,
                           Stmt *Body, SourceLocation FEL,
                           SourceLocation RPL)
    : Stmt(CForEachStmtClass) {
      SubExprs[ELEM] = Elem;
      SubExprs[ARRAY] = Arr;
      SubExprs[BODY] = Body;
      ForLoc = FEL;
      RParenLoc = RPL;
}