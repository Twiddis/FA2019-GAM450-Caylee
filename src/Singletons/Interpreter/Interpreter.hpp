#pragma once
#include "Singletons/Singleton.hpp"


namespace CayleeEngine
{
struct SyntaxNode;

class Interpreter : public Singleton<Interpreter>
{
public:
  Interpreter();
  ~Interpreter();

  void SetInstructions(const std::vector<std::unique_ptr<SyntaxNode>>& instructions);
  void ExecuteNext();

  typedef std::vector<std::unique_ptr<SyntaxNode>>::const_iterator instruction_ptr;

private:

  const std::vector<std::unique_ptr<SyntaxNode>> *mInstructions;

  instruction_ptr mCurrentInstruction;
  std::unordered_map<std::string, instruction_ptr> mValidLabels;
  std::unordered_map<std::string, int> mRegisters;


};

}