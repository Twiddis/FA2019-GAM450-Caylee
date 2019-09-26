#pragma once

namespace CayleeEngine
{
    // Token token enumeration, tokens defined in "Tokens.inl"
  namespace TokenType
  {
    enum Enum
    {
      #define TOKEN(Type, Value) Type,
      #include "Tokens.inl"
      #undef TOKEN
      _End
    };
  }

  class Token
  {
  public:
    Token();
    Token(const char *text, size_t length, TokenType::Enum type);

      // Print function
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

      // Returns the text string
    std::string str() const;

      // Simply returns true if not invalid.
      // Used for parsing
    operator bool() const;

    const char *mText;
    size_t mTextLength;
    TokenType::Enum mTokenType;

      // Array of token names
    static const char *gTokenNames[];
  };

}