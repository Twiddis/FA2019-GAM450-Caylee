#pragma once
#include "Singletons/DFA/Tokens.hpp"

namespace CayleeEngine
{
  class Visitor;

  struct SyntaxNode
  {
    virtual void Walk(Visitor*, bool) {}
  };

  struct LabelNode : public SyntaxNode
  {
    Token mName;

    void Walk(Visitor* visitor, bool visit = true) override;
  };

  struct StatementNode : public SyntaxNode
  {
    std::unique_ptr<StatementNode> mNextNode;

    void Walk(Visitor* visitor, bool visit = true) override;
  };

  struct InstructionNode : public StatementNode
  {
    Token mKeyword;

    void Walk(Visitor* visitor, bool visit = true) override;
  };

  struct LiteralNode : public StatementNode
  {
    int mValue;

    void Walk(Visitor* visitor, bool visit = true) override;
  };

    // Named References include labels and registers
  struct RegisterReferenceNode : public StatementNode
  {
    Token mName;
    //Symbol?

    void Walk(Visitor* visitor, bool visit = true) override;
  };
  struct LabelReferenceNode : public StatementNode
  {
    Token mName;
    //Symbol?

    void Walk(Visitor* visitor, bool visit = true) override;
  };
}