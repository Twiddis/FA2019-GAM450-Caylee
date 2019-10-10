#include "precompiled.hpp"
#include "Tokens.hpp"

namespace CayleeEngine
{
const char* Token::gTokenNames[] =
{
  #define TOKEN(Type, Value) #Value,

  #include "Tokens.inl"
  #undef TOKEN
};

std::ostream& operator<<(std::ostream& out, const Token& token)
{
  if (token.mTokenType == TokenType::Newline)
    out << "Token(Newline)";
  else if (token.mTokenType == TokenType::ReturnCarriage)
    out << "Token(Return Carriage)";
  else
    out << "Token(" << Token::gTokenNames[token.mTokenType] << ")";

  if (token.mTokenType == TokenType::RegisterName || token.mTokenType == TokenType::LabelName)
    out << " [" << token.str() << "]";
  
  return out;
}

Token::Token() 
  : mText(""), 
    mTextLength(0), 
    mTokenType(TokenType::Invalid)
{}

Token::Token(const char *text, size_t length, TokenType::Enum type)
  : mText(text),
    mTextLength(length),
    mTokenType(type)
{}

std::string Token::str() const
{
  return std::string(mText, mTextLength);
}

Token::operator bool() const
{
  return mTokenType != TokenType::Invalid;
}


}