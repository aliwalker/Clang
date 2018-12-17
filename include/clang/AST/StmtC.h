//===--- StmtC.h - Classes for extending C statements --*- C++ -*===//
// Author: Yiyong.Li
//
//    This file is rewritten simply for getting my hands wet in Clang development.
//
//===------------------------------------------------------------===//

/// \file
/// Defines the C statement AST node classes.

#ifndef LLVM_CLANG_AST_STMTC_H
#define LLVM_CLANG_AST_STMTC_H

#include "clang/AST/Stmt.h"
#include "llvm/Support/Compiler.h"


namespace clang {


/// Represents C's foreach statement.
class CForEachStmt : public Stmt {
  enum { ELEM, ARRAY, BODY, END_EXPR };
  Stmt* SubExprs[END_EXPR];
  SourceLocation ForLoc;
  SourceLocation RParenLoc;
public:
  CForEachStmt(Stmt *Elem, Expr *Arr, Stmt *Body,
               SourceLocation FEL, SourceLocation RPL);
  explicit CForEachStmt(EmptyShell Empty) :
    Stmt(CForEachStmtClass, Empty) {  }

  Stmt *getElement() const { return SubExprs[ELEM]; }
  Expr *getArray() const {
    return reinterpret_cast<Expr*>(SubExprs[ARRAY]);
  }
  Stmt *getBody() const { return SubExprs[BODY]; }

  void setElement(Stmt *S) { SubExprs[ELEM] = S; }
  void setArray(Expr *E) {
    SubExprs[ARRAY] = reinterpret_cast<Stmt*>(E);
  }
  void setBody(Stmt *S) { SubExprs[BODY] = S; }

  SourceLocation getForLoc() const { return ForLoc; }
  void setForLoc(SourceLocation Loc) { ForLoc = Loc; }
  SourceLocation getRParenLoc() const { return RParenLoc; }
  void setRParenLoc(SourceLocation Loc) { RParenLoc = Loc; }

  SourceLocation getBeginLoc() const LLVM_READONLY { return ForLoc; }
  SourceLocation getEndLoc() const LLVM_READONLY {
    return SubExprs[BODY]->getEndLoc();
  }

  static bool classof(const Stmt *T) {
    return T->getStmtClass() == CForEachStmtClass;
  }

  child_range children() {
    return child_range(&SubExprs[ELEM], &SubExprs[END_EXPR]);
  }
};

} // clang


#endif