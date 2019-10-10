#include "precompiled.hpp"
#include "Visitor.hpp"


namespace CayleeEngine
{
  VisitResult PrintVisitor::Visit(SyntaxNode * node)
  {
    return Continue;
  }
  VisitResult PrintVisitor::Visit(LabelNode * node)
  {
    std::cout << "LabelNode (" << node->mName.str() << ") ";

    return Continue;
  }
  VisitResult PrintVisitor::Visit(StatementNode * node)
  {
    return Continue;
  }
  VisitResult PrintVisitor::Visit(InstructionNode * node)
  {
    std::cout << "InstructionNode (" << Token::gTokenNames[node->mKeyword] << ") ";

    return Continue;
  }
  VisitResult PrintVisitor::Visit(LiteralNode * node)
  {

    return Continue;
  }
  VisitResult PrintVisitor::Visit(RegisterReferenceNode * node)
  {
    return Continue;
  }
  VisitResult PrintVisitor::Visit(LabelReferenceNode * node)
  {
    return Continue;
  }
}