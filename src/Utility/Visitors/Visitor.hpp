#pragma once

#include "Singletons/Parser/SyntaxNodes.hpp"

namespace CayleeEngine
{
enum VisitResult
{
  Continue,
  Stop
};

class Visitor
{
public:
  virtual VisitResult Visit(SyntaxNode*            )     { return Continue; }
  virtual VisitResult Visit(LabelNode*             node) { return this->Visit(static_cast<SyntaxNode*>(node)); }
  virtual VisitResult Visit(StatementNode*         node) { return this->Visit(static_cast<SyntaxNode*>(node)); }
  virtual VisitResult Visit(InstructionNode*       node) { return this->Visit(static_cast<StatementNode*>(node)); }
  virtual VisitResult Visit(LiteralNode*           node) { return this->Visit(static_cast<StatementNode*>(node)); }
  virtual VisitResult Visit(RegisterReferenceNode* node) { return this->Visit(static_cast<StatementNode*>(node)); }
  virtual VisitResult Visit(LabelReferenceNode*    node) { return this->Visit(static_cast<StatementNode*>(node)); }
};

class PrintVisitor : public Visitor
{
public:
  VisitResult Visit(SyntaxNode*            node) override;
  VisitResult Visit(LabelNode*             node) override;
  VisitResult Visit(StatementNode*         node) override;
  VisitResult Visit(InstructionNode*       node) override;
  VisitResult Visit(LiteralNode*           node) override;
  VisitResult Visit(RegisterReferenceNode* node) override;
  VisitResult Visit(LabelReferenceNode*    node) override;
};

}