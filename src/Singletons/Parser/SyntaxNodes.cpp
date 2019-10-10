#include "precompiled.hpp"
#include "SyntaxNodes.hpp"

#include "Utility/Visitors/Visitor.hpp"

namespace CayleeEngine
{

void LabelNode::Walk(Visitor *  visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  SyntaxNode::Walk(visitor, false);

}
void StatementNode::Walk(Visitor * visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  SyntaxNode::Walk(visitor, false);

  if (mNextNode.get())
    mNextNode->Walk(visitor);
}

void InstructionNode::Walk(Visitor * visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  StatementNode::Walk(visitor, false);
}

void LiteralNode::Walk(Visitor * visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  StatementNode::Walk(visitor, false);
}
void RegisterReferenceNode::Walk(Visitor * visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  StatementNode::Walk(visitor, false);
}

void LabelReferenceNode::Walk(Visitor * visitor, bool visit)
{
  if (visit && visitor->Visit(this) == Stop)
    return;

  StatementNode::Walk(visitor, false);
}
}