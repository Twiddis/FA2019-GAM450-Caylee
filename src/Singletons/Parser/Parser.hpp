#pragma once
#include "Singletons/Singleton.hpp"

#include "Singletons/DFA/Tokens.hpp"
#include "Utility/UniqueVector/UniqueVector.hpp"

#include "SyntaxNodes.hpp"

namespace CayleeEngine
{
class Visitor;

class Parser : public Singleton<Parser>
{
public:
  Parser();
  bool Parse(const std::vector<Token> &token_stream);
  
  const std::vector<std::unique_ptr<SyntaxNode>>& GetInstructions() { return mInstructions; }

  void Walk(Visitor* visitor);

private:
  bool Accept(TokenType::Enum token_type);
  bool Expect(TokenType::Enum token_type);
  bool Accept(bool accepted);
  bool Expect(bool expected);

  bool Label();
  bool Comment();
  bool Instruction();

  bool NoOperation();
  bool Move();
  bool Jump();
  bool Add();
  bool Subtract();
  bool Negate();
  bool JumpIfNegative();
  bool JumpIfPositive();
  bool JumpIfZero();

  std::vector<Token>::const_iterator mCurrentToken;
  std::vector<std::unique_ptr<SyntaxNode>> mInstructions;
  std::vector<std::runtime_error> mParsingErrors;
};


}