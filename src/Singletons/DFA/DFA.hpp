#pragma once
#include "Singletons/Singleton.hpp"
#include "DFA.hpp"
#include "Tokens.hpp"

namespace CayleeEngine
{

class DFA : public Singleton<DFA>
{
  struct State
  {
    std::unordered_map<char, State*> mEdges;
    State *mDefaultEdge;

      // Invalid token if this isn't an accepting state
    TokenType::Enum mAcceptingToken;
  };

public:
  DFA();
  ~DFA();

  bool Tokenize(const char *block, std::vector<Token> &token_stream);
  
private:

    // Helper functions to create the state machine
  State *AddState(TokenType::Enum accepting_token = TokenType::Invalid);
  void AddEdge(State *from, State *to, char c);
  void AddDefaultEdge(State *from, State *to);

  void DestroyNodes(State *root);

  Token TokenizeKeyword(const char *start, size_t length);

  State *mRootState;
  std::unordered_map<std::string, Token> mKeywordMap;
};

}