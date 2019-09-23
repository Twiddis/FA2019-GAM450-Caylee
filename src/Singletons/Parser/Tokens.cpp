#include "precompiled.hpp"
#include "Tokens.hpp"

namespace CayleeEngine
{
namespace Tokens
{
  const char *gTokenNames[] =
  {
    #define TOKEN(Type, Value) #Value,
    #include "Tokens.inl"
    #undef TOKEN
  };
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
  out << token.mText;
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
  return std::string(mText);
}

Token::operator bool() const
{
  return mTokenType != TokenType::Invalid;
}


}