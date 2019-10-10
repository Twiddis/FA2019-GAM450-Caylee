#include "precompiled.hpp"
#include "Visitor.hpp"


namespace CayleeEngine
{
  VisitResult PrintVisitor::Visit(SyntaxNode * )
  {
    return Continue;
  }
  VisitResult PrintVisitor::Visit(LabelNode * node)
  {
    std::cout << "LabelNode (" << node->mName.str() << ") ";

    return Continue;
  }
  VisitResult PrintVisitor::Visit(StatementNode * )
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
    std::cout << "LiteralNode (" << node->mValue << ") ";
    return Continue;
  }
  VisitResult PrintVisitor::Visit(RegisterReferenceNode * node)
  {
    std::cout << "RegisterReferenceNode (" << node->mName.str() << ") ";

    return Continue;
  }
  VisitResult PrintVisitor::Visit(LabelReferenceNode * node)
  {
    std::cout << "LabelReferenceNode (" << node->mName.str() << ") ";
    return Continue;
  }
}