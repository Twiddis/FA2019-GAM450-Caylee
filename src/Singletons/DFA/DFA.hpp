#pragma once
#include "Singletons/Singleton.hpp"
#include "DFA.hpp"

#include "Singletons/Parser/Tokens.hpp"

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
  bool Tokenize(const std::string &block);
  
private:

    // Helper functions to create the state machine
  State *AddState(TokenType::Enum accepting_token);
  void AddEdge(State *from, State *to, char c);
  void AddDefaultEdge(State *from, State *to);

  State *mRootState;
};

}