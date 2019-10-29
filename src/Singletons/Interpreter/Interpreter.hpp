#pragma once
#include "Singletons/Singleton.hpp"
#include "Objects/Register/Register.hpp"
#include "Utility/Visitors/Visitor.hpp"

namespace CayleeEngine
{
typedef std::vector<std::unique_ptr<SyntaxNode>>::const_iterator instruction_ptr;

class Interpreter : public Singleton<Interpreter>
{
public:
  Interpreter();
  ~Interpreter();

  void SetInstructions(const std::vector<std::unique_ptr<SyntaxNode>>& instructions);
  void ExecuteNext();



  void AddRegister(std::string name, obj::Register *reg) { mRegisters.emplace(name, reg); }

private:

  const std::vector<std::unique_ptr<SyntaxNode>> *mInstructions;

  instruction_ptr mCurrentInstruction;
  std::unordered_map<std::string, instruction_ptr> mValidLabels;
  std::unordered_map<std::string, obj::Register*> mRegisters;
};

class LabelFinder : public Visitor
{
public:
  VisitResult Visit(LabelNode*             node) override;

  instruction_ptr mCurrentInstruction;
  std::unordered_map<std::string, instruction_ptr> mLabels;
};

class Executor : public Visitor
{
public:
  VisitResult Visit(InstructionNode*             node) override;
  VisitResult Visit(LabelNode*             node) override;

  instruction_ptr mCurrentInstruction;
  instruction_ptr mNextInstruction;

  std::unordered_map<std::string, instruction_ptr> *mValidLabels;
  std::unordered_map<std::string, obj::Register*> *mRegisters;
};

}