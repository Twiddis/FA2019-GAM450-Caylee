#include "precompiled.hpp"
#include "Parser.hpp"

namespace CayleeEngine
{
Parser::Parser()
{
}

bool Parser::Parse(const std::vector<Token> &token_stream)
{
    // NOTES:
    // An "instruction" is an entire line
    // Instructions must end in a newline
  mCurrentToken = token_stream.begin();
  mInstructions.clear();
  mParsingErrors.clear();

  mCurrentLine = 0;

    // Keep parsing until the very end
  while (mCurrentToken->mTokenType != TokenType::EndOfFile) 
  {

    try {
      Expect(Instruction() || Label() || Comment() || mCurrentToken->mTokenType == TokenType::Newline);
      ++mCurrentLine;
      while (Accept(TokenType::Newline));

    }
      // If parsing error occured, make note and move to next instruction
      // TODO: Have line info, error info in exception for
      //       in-game debugging purposes
    catch (std::runtime_error err) {
      std::cout << "Parsing error at line: " << mCurrentLine << std::endl;
      mParsingErrors.push_back(err);

      while (mCurrentToken->mTokenType != TokenType::Newline && mCurrentToken->mTokenType != TokenType::EndOfFile)
        ++mCurrentToken;
    }
  }

  return !mParsingErrors.empty();
}

// Helpers
//////////////////////////////////////////////////////////////////////

void Parser::Walk(Visitor * visitor)
{
  for (auto &instruction : mInstructions) {
    instruction->Walk(visitor, true);
    std::cout << std::endl;
  }
}

bool Parser::Accept(TokenType::Enum token_type)
{
  if (mCurrentToken->mTokenType == token_type) {
    ++mCurrentToken;
    return true;
  }

  return false;
}

bool Parser::Expect(TokenType::Enum token_type)
{
  if (mCurrentToken->mTokenType != token_type)
    throw std::runtime_error("Parsing Error");

  ++mCurrentToken;
  return true;
}

bool Parser::Accept(bool accepted)
{
  return accepted;
}

bool Parser::Expect(bool expected)
{
  if (!expected)
    throw std::runtime_error("Parsing Error");
    
  return expected;
}

// Grammar Rules
//////////////////////////////////////////////////////////////////////

bool Parser::Label()
{
  if (Accept(TokenType::LabelName)) {
    std::unique_ptr<LabelNode> new_label = std::make_unique<LabelNode>();

    new_label->mName = *(mCurrentToken - 1);
    mInstructions.push_back(std::move(new_label));
    return true;
  }

  return false;
}
//////////////////////////////////////////////////////////////////////

bool Parser::Comment()
{
  return Accept(TokenType::Comment);
}
//////////////////////////////////////////////////////////////////////

bool Parser::Instruction()
{
  bool result = Accept(NoOperation() || 
                       Move() || 
                       Jump() || 
                       Add() || 
                       Subtract() || 
                       Negate() || 
                       JumpIfNegative() || 
                       JumpIfPositive() || 
                       JumpIfZero());
  return result;
}
//////////////////////////////////////////////////////////////////////

bool Parser::NoOperation()
{
  return Accept(TokenType::NoOperation);
}
//////////////////////////////////////////////////////////////////////

bool Parser::Move()
{
  if (!Accept(TokenType::Move))
    return false;

  Expect(TokenType::Literal);
  Expect(TokenType::RegisterName);

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LiteralNode> new_literal = std::make_unique<LiteralNode>();
  std::unique_ptr<RegisterReferenceNode> new_register = std::make_unique<RegisterReferenceNode>();

  new_instruction->mKeyword = *(mCurrentToken - 3);
  new_literal->mValue = std::stoi(std::string((mCurrentToken - 2)->mText, (mCurrentToken - 2)->mTextLength));
  new_register->mName = *(mCurrentToken - 1);

  new_literal->mNextNode = std::move(new_register);
  new_instruction->mNextNode = std::move(new_literal);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::Jump()
{
  if (!Accept(TokenType::Jump))
    return false;

    // Label references are tokenized as register name
    // TODO: Still works out, but may have to change later
  Expect(TokenType::RegisterName);
 
  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LabelReferenceNode> new_register = std::make_unique<LabelReferenceNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_register->mName = *(mCurrentToken - 1);

  new_instruction->mNextNode = std::move(new_register);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::Add()
{
  if (!Accept(TokenType::Add))
    return false;

  Expect(TokenType::Literal);
  
  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LiteralNode> new_literal = std::make_unique<LiteralNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_literal->mValue = std::stoi(std::string((mCurrentToken - 1)->mText, (mCurrentToken - 1)->mTextLength));

  new_instruction->mNextNode = std::move(new_literal);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::Subtract()
{
  if (!Accept(TokenType::Subtract))
    return false;

  Expect(TokenType::Literal);

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LiteralNode> new_literal = std::make_unique<LiteralNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_literal->mValue = std::stoi(std::string((mCurrentToken - 1)->mText, (mCurrentToken - 1)->mTextLength));

  new_instruction->mNextNode = std::move(new_literal);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::Negate()
{
  if (!Accept(TokenType::Negate))
    return false;

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();

  new_instruction->mKeyword = *(mCurrentToken - 1);

  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::JumpIfNegative()
{
  if (!Accept(TokenType::JumpIfNegative))
    return false;

    // Label references are tokenized as register name
    // TODO: Still works out, but may have to change later
  Expect(TokenType::RegisterName);

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LabelReferenceNode> new_label = std::make_unique<LabelReferenceNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_label->mName = *(mCurrentToken - 1);

  new_instruction->mNextNode = std::move(new_label);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::JumpIfPositive()
{
  if (!Accept(TokenType::JumppIfPositive))
    return false;

  // Label references are tokenized as register name
  // TODO: Still works out, but may have to change later
  Expect(TokenType::RegisterName);

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LabelReferenceNode> new_label = std::make_unique<LabelReferenceNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_label->mName = *(mCurrentToken - 1);

  new_instruction->mNextNode = std::move(new_label);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////

bool Parser::JumpIfZero()
{
  if (!Accept(TokenType::JumpIfZero))
    return false;

    // Label references are tokenized as register name
    // TODO: Still works out, but may have to change later
  Expect(TokenType::RegisterName);

  std::unique_ptr<InstructionNode> new_instruction = std::make_unique<InstructionNode>();
  std::unique_ptr<LabelReferenceNode> new_label = std::make_unique<LabelReferenceNode>();

  new_instruction->mKeyword = *(mCurrentToken - 2);
  new_label->mName = *(mCurrentToken - 1);

  new_instruction->mNextNode = std::move(new_label);
  mInstructions.push_back(std::move(new_instruction));

  return true;
}
//////////////////////////////////////////////////////////////////////


}