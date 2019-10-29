#include "precompiled.hpp"
#include "Interpreter.hpp"

#include "Singletons/Parser/SyntaxNodes.hpp"


namespace CayleeEngine
{
Interpreter::Interpreter() { }
Interpreter::~Interpreter() { }

void Interpreter::SetInstructions(const std::vector<std::unique_ptr<SyntaxNode>>& instructions)
{
  mInstructions = &instructions;
  mCurrentInstruction = mInstructions->begin();
  mValidLabels.clear();
  mRegisters.clear();

  LabelFinder label_finder;
  label_finder.mCurrentInstruction = instructions.begin();

  while (label_finder.mCurrentInstruction != instructions.end())
  {
    label_finder.mCurrentInstruction->get()->Walk(&label_finder, true);
    ++label_finder.mCurrentInstruction;
  }

  mValidLabels = label_finder.mLabels;
}

void Interpreter::ExecuteNext()
{
  if (mInstructions->empty())
    return;

  Executor executor;

  executor.mCurrentInstruction = mCurrentInstruction;
  executor.mValidLabels = &mValidLabels;
  executor.mRegisters = &mRegisters;

  mCurrentInstruction->get()->Walk(&executor, true);
  mCurrentInstruction = executor.mNextInstruction;
}

////////////////////////////////////////////////////////////////////////////////
VisitResult LabelFinder::Visit(LabelNode * node)
{
  mLabels.emplace(node->mName.str(), std::next(mCurrentInstruction));
  return Stop;
}
////////////////////////////////////////////////////////////////////////////////

VisitResult Executor::Visit(InstructionNode * node)
{
  switch (node->mKeyword.mTokenType)
  {
  case TokenType::Move: {
    int val = static_cast<LiteralNode*>(node->mNextNode.get())->mValue;
    std::string reg = static_cast<RegisterReferenceNode*>(node->mNextNode->mNextNode.get())->mName.str();
    mRegisters->find(reg)->second->SetValue(val);
    break;
  }

  case TokenType::Add: {
    int val = static_cast<LiteralNode*>(node->mNextNode.get())->mValue;
    int acc = mRegisters->find("ACC")->second->GetValue();
    mRegisters->find("ACC")->second->SetValue(val + acc);
    break;
  }

  case TokenType::Subtract: {
    int val = static_cast<LiteralNode*>(node->mNextNode.get())->mValue;
    int acc = mRegisters->find("ACC")->second->GetValue();
    mRegisters->find("ACC")->second->SetValue(acc - val);
    break;
  }

  case TokenType::Jump: {
    std::string label = static_cast<LabelReferenceNode*>(node->mNextNode.get())->mName.str();
    mNextInstruction = mValidLabels->find(label + ":")->second;
    return Stop;
  }

  case TokenType::JumpIfZero: {
    std::string label = static_cast<LabelReferenceNode*>(node->mNextNode.get())->mName.str();
    int acc = mRegisters->find("ACC")->second->GetValue();
    
    if (acc == 0) {
      mNextInstruction = mValidLabels->find(label + ":")->second;
      return Stop;
    }
    break;
  }
  default:
    break;
  }
  mNextInstruction = std::next(mCurrentInstruction);
  return Stop;
}
VisitResult Executor::Visit(LabelNode *)
{
    // Skip if label
  mNextInstruction = std::next(mCurrentInstruction);

  return Stop;
}
////////////////////////////////////////////////////////////////////////////////
}